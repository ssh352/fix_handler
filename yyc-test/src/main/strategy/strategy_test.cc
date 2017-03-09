
#include <boost/lexical_cast.hpp>
#include "core/global.h"
#include "core/assist/utility.h"
#include "core/assist/logger.h"
#include "core/zmq/zmq_receiver.h"
#include "core/zmq/zmq_sender.h"
#include "pb/ems/ems.pb.h"

class BookReceiver : public fh::core::zmq::ZmqReceiver
{
    public:
        explicit BookReceiver(const std::string &url) : fh::core::zmq::ZmqReceiver(url) {}
        virtual ~BookReceiver() {}

    public:
        virtual void Save(char *data, size_t size)
        {
            LOG_INFO("received book: ", std::string(data, size));
        }

    private:
        DISALLOW_COPY_AND_ASSIGN(BookReceiver);
};

class OrderResultReceiver : public fh::core::zmq::ZmqReceiver
{
    public:
        explicit OrderResultReceiver(const std::string &url) : fh::core::zmq::ZmqReceiver(url) {}
        virtual ~OrderResultReceiver() {}

    public:
        virtual void Save(char *data, size_t size)
        {
            char type = data[0];
            if(type == 'F')
            {
                pb::ems::Fill fill;
                if(fill.ParseFromArray(data + 1, size - 1))
                {
                    LOG_INFO("received order result: ", fh::core::assist::utility::Format_pb_message(fill));
                }
                else
                {
                    LOG_ERROR("received order result: parse error: ", type);
                }
            }
            else if(type == 'O')
            {
                pb::ems::Order order;
                if(order.ParseFromArray(data + 1, size - 1))
                {
                    LOG_INFO("received order result: ", fh::core::assist::utility::Format_pb_message(order));
                }
                else
                {
                    LOG_ERROR("received order result: parse error: ", type);
                }
            }
            else
            {
                LOG_ERROR("received order result: invalid type: ", type);
            }
        }

    private:
        DISALLOW_COPY_AND_ASSIGN(OrderResultReceiver);
};

std::string make_order()
{
    std::uint32_t r = fh::core::assist::utility::Random_number(1, 10);

    pb::ems::Order order;
    order.set_client_order_id("TEST-1");
    order.set_account("YYC");
    order.set_contract("ES987");
    order.set_buy_sell(pb::ems::BuySell::BS_Buy);
    order.set_price(std::to_string(100 + r));
    order.set_quantity(r);
    order.set_tif(pb::ems::TimeInForce::TIF_None);
    order.set_order_type(pb::ems::OrderType::OT_Limit);
    order.set_exchange_order_id("CME-1");
    order.set_status(pb::ems::OrderStatus::OS_Pending);
    order.set_working_price(std::to_string(100 - r));
    order.set_working_quantity(r / 2);
    order.set_filled_quantity(r - r / 2);
    order.set_message("test information in order");
    //order.set_submit_time();

    std::string str = order.SerializeAsString();
    static const char *msg_type = "DFGH";
    return str.insert(0, 1, msg_type[r % 4]);
}


int main(int argc, char* argv[])
{
    try
    {
        if (argc != 5)
        {
            LOG_ERROR("Usage: strategy_test <send_port> <result_receive_port> <book_receive_port> <send_interval_ms>");
            LOG_ERROR("Ex:       strategy_test 6001 6002 5558 1000");

            return 1;
        }

        std::thread book_receiver([argv]{
            LOG_INFO("start receiver book on port ", argv[3]);
            std::string host = std::string("tcp://localhost:") + argv[3];
            BookReceiver r(host);
            r.Start_receive();
        });
        book_receiver.detach();

        std::thread result_receiver([argv]{
               LOG_INFO("start result receiver on port ", argv[2]);
               std::string host = std::string("tcp://localhost:") + argv[2];
            OrderResultReceiver r(host);
            r.Start_receive();
        });
        result_receiver.detach();

        LOG_INFO("start sender on port ", argv[1]);
        auto send_interval_ms = boost::lexical_cast<std::uint16_t>(argv[4]);
        std::string host = std::string("tcp://*:") + argv[1];
        fh::core::zmq::ZmqSender sender(host);
        while(true)
        {
            std::string order = make_order();
            sender.Send(order);
            LOG_INFO("sent:  ", order);
            std::this_thread::sleep_for(std::chrono::milliseconds(send_interval_ms));
        }
    }
    catch (std::exception& e)
    {
        LOG_ERROR("Exception: ", e.what());
    }

    return 0;
}

// ./strategy_test 6001 6002 5558 1000
