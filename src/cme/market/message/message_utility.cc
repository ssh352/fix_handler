
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "cme/market/message/sbe_encoder.h"
#include "cme/market/message/message_utility.h"
#include "core/assist/utility.h"
#include "core/assist/logger.h"

namespace fh
{
namespace cme
{
namespace market
{
namespace message
{
namespace utility
{

    // split packet to messages
    std::uint32_t Pick_messages_from_packet(const char *buffer, const size_t data_length, std::vector<fh::cme::market::message::MdpMessage> &mdp_messages)
    {
        const char *data_begin = buffer;
        const char *data_end = data_begin + data_length;
        std::uint32_t packet_seq_num = *((std::uint32_t *)data_begin);
        std::uint64_t packet_sending_time = *((std::uint64_t *)(data_begin + 4));

        const char *current_position = data_begin + 4 + 8;
        while(current_position < data_end)
        {
            std::uint16_t message_length = *((std::uint16_t *)current_position);
            const char *message = current_position + 2;
            fh::cme::market::message::MdpMessage mdp(message, message_length - 2, data_length, packet_seq_num, packet_sending_time);
            mdp_messages.push_back(std::move(mdp));
            current_position = current_position + message_length;
        }

        return packet_seq_num;
    }

    // get message's template id from sbe packet
    std::uint16_t Get_sbe_template_id(const char *packet)
    {
        // 4: MsgSeqNum 8: SendingTime 2: MsgSize 2: BlockLength 2: TemplateId
        return *((std::uint32_t *)(packet + 4 + 8 + 2 + 2));
    }

    // create fix logon message(35=A)
    std::string Make_fix_logon_message(const std::string &username, const std::string &password)
    {
        // 35: MsgType 553: Username 554: Password 10: CheckSum
        std::vector<std::string> tags = {"35=A", "553=" + username, "554=" + password};
        std::transform(tags.cbegin(), tags.cend(), tags.begin(), [](const std::string &s){ return s + "\001";});
        std::string message = boost::algorithm::join(tags, "");
        std::string checksum = fh::core::assist::utility::Calculate_fix_checksum(message);

        return message + checksum;
    }

    // create fix replay request message(35=V)
    std::string Make_fix_recovery_request_message(
            const std::string &channel_id, const std::string &req_id,
            std::uint32_t begin, std::uint32_t end)
    {
        // 35: MsgType 1180: ApplID 262: MDReqID 1182: ApplBeginSeqNo 1183: ApplEndSeqNo 10: CheckSum
        std::vector<std::string> tags = {"35=V", "1180=" + channel_id, "262=" + req_id, "1182=" + std::to_string(begin), "1183=" + std::to_string(end)};
        std::transform(tags.cbegin(), tags.cend(), tags.begin(), [](const std::string &s){ return s + "\001";});
        std::string message = boost::algorithm::join(tags, "");
        std::string checksum = fh::core::assist::utility::Calculate_fix_checksum(message);

        return message + checksum;
    }

    // make a mdp message for test
    std::size_t Make_message(char *position, std::uint32_t *ids, size_t len)
    {
        auto index = fh::core::assist::utility::Random_number(0, len - 1);
        fh::cme::market::message::SBEEncoder encoder;
        encoder.Start_encode(ids[index]);
        std::pair<const char*, std::size_t> encoded = encoder.Encoded_buffer();

        std::size_t message_size = encoded.second + 2;  // 长度要包括本身这 2 个字节
        std::memcpy(position, &message_size, 2);
        std::memcpy(position + 2, encoded.first, encoded.second);

        LOG_DEBUG("make message: size= 2 + ", encoded.second, " msg=", fh::core::assist::utility::Hex_str(encoded.first, encoded.second));

        return message_size;
    }

    // make a mdp packet for test
    std::size_t Make_packet(char *buffer, std::uint32_t packet_seq_num, std::uint32_t *ids, size_t len)
    {
        // data layout:
        //  MsgSeqNum : 4 bytes
        //  SendingTime : 8 bytes
        //  Message :
        //   MsgSize : 2 bytes
        //   SBE data

        auto time = fh::core::assist::utility::Current_time_ns();
        std::memcpy(buffer, &packet_seq_num, 4);
        std::memcpy(buffer + 4, &time, 8);

        char *position = buffer + 4 + 8;
        std::uint32_t message_num = fh::core::assist::utility::Random_number(1, 5);
        for(std::uint32_t i = 0; i < message_num; ++i)
        {
            std::size_t message_total_size = Make_message(position, ids, len);
            position = position + message_total_size;
        }

        LOG_DEBUG("make packet: seq=", packet_seq_num, " time=", time, " num=", message_num, " size=", position - buffer);
        return position - buffer;
    }

    // read mdp packets from file(one packet per line) for test
    std::vector<std::pair<std::string, std::string>> Read_packets(const std::string &filename, const std::string &packet_start_indicate)
    {
        std::vector<std::pair<std::string, std::string>> packets;
        std::ifstream input(filename);
        std::string line;
        while (std::getline(input, line))
        {
            auto pos = line.find(packet_start_indicate);
            if(pos != std::string::npos)
            {
                line.erase(0, pos + packet_start_indicate.size());
            }

            std::istringstream iss(line);
            std::vector<std::string> tokens;
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

            std::vector<char> bytes;
            std::ostringstream byte_line;
            int index = 0;
            std::for_each(tokens.begin(), tokens.end(), [&bytes, &index, &byte_line](std::string &s){
                boost::trim_right(s);
                boost::trim_left(s);
                if(s != "")
                {
                    bytes.push_back((char) strtol(s.c_str(), nullptr, 16));
                    index ++;
                    std::string dec(" ");
                    if(index % 40 == 0) dec = "\n";
                    else if(index % 20 == 0) dec = "    ";
                    else if(index % 10 == 0) dec = "  ";
                    byte_line << s << dec;
                }
            });
            packets.push_back({std::string(bytes.cbegin(), bytes.cend()), byte_line.str()});
        }

        return packets;
    }

    // convert price in sbe message to double
    double Get_price(std::pair<std::int64_t, std::int8_t> price_mantissa)
    {
        // first is mantissa, second is exponent
        return price_mantissa.first * std::pow(10, price_mantissa.second);
    }

} // namespace utility
} // namespace message
} // namespace market
} // namespace cme
} // namespace fh
