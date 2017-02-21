
#include "dat_replayer.h"
#include "utility.h"
#include "logger.h"

namespace rczg
{
    
    DatReplayer::DatReplayer(
    		const boost::asio::ip::address &server_address,
			const unsigned short server_port,
			const std::string &username,
			const std::string &password,
			const std::string &channel_id
	) : m_endpoint(server_address, server_port), m_username(username), m_password(password), m_channel_id(channel_id)
    {
    	// noop
    }

    // request data([begin, end)) from tcp receiver, and process it with processor
    void DatReplayer::Start_receive(std::function<void(char *, const size_t)> processor, std::uint32_t begin, std::uint32_t end)
    {
    	rczg::TCPReceiver tcp_receiver(m_endpoint);
    	this->Send_Logon(tcp_receiver, processor, begin, end - 1); // convert [begin, end) to [begin, end - 1]
    	tcp_receiver.Start_receive();
    }

    void DatReplayer::Send_Logon(
    		rczg::TCPReceiver &tcp_receiver,
			std::function<void(char *, const size_t)> processor,
			std::uint32_t begin, std::uint32_t end)
    {
    	std::string logon_message = rczg::utility::Make_fix_logon_message(m_username, m_password);
    	tcp_receiver.Send(
    			[this, &tcp_receiver, processor, begin, end](char *buffer, const size_t length){
    				this->On_Logon(tcp_receiver, processor, begin, end, buffer, length);
    			},
    			logon_message);
    	LOG_INFO("tcp replayer sent logon: ", logon_message);
    }

    void DatReplayer::On_Logon(
    		rczg::TCPReceiver &tcp_receiver,
			std::function<void(char *, const size_t)> processor,
			std::uint32_t begin, std::uint32_t end,
			char *buffer, const size_t length)
    {
        LOG_INFO("tcp replayer received logon: length=", length, ", data=", rczg::utility::Hex_str(buffer, length));
        this->Send_recovery_request(tcp_receiver, processor, begin, end);
    }

    void DatReplayer::Send_recovery_request(
    		rczg::TCPReceiver &tcp_receiver,
			std::function<void(char *, const size_t)> processor,
			std::uint32_t begin, std::uint32_t end)
    {
    	std::string recovery_request_message = rczg::utility::Make_fix_recovery_request_message(
    			m_channel_id, std::to_string(rczg::utility::Current_time_ns()), begin, end);
    	tcp_receiver.Send(
    			[this, &tcp_receiver, processor](char *buffer, const size_t length){
    				this->On_recovery_data(tcp_receiver, processor, buffer, length);
    			},
				recovery_request_message);
    	LOG_INFO("tcp replayer send data: ", recovery_request_message);
    }

    void DatReplayer::On_recovery_data(
    		rczg::TCPReceiver &tcp_receiver,
			std::function<void(char *, const size_t)> processor,
			char *buffer, const size_t length)
    {
    	LOG_INFO("tcp replayer received data: length=", length, ", data=", rczg::utility::Hex_str(buffer, length));

		// pick packet one by one from received data
    	char *start = buffer;
    	char *end = buffer + length;
    	while(start < end)
    	{
    		// first 2 bytes is packet length
    		std::uint16_t packet_length = *(std::uint16_t *)start;
    		std::uint16_t template_id = rczg::utility::Get_sbe_template_id(start + 2);

    		if(template_id == 16)	 // 16: logout message
    		{
        		LOG_INFO("tcp replayer received logout message");
        		tcp_receiver.Stop();
        		return;
    		}

    		if(template_id != 12)	// 12: heartbeat message
    		{
    			// recovery data message
        		processor(start + 2, packet_length);
    		}

			tcp_receiver.Receive(
					[this, &tcp_receiver, processor](char *buffer, const size_t length){
						this->On_recovery_data(tcp_receiver, processor, buffer, length);
					});

    		// jump to next packet
    		start += packet_length + 2;
    	}
    }

    DatReplayer::~DatReplayer()
    {
        // noop
    }
    
} // namespace rczg
