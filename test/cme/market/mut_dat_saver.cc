
#include "gmock/gmock.h"

#include <boost/iterator/counting_iterator.hpp>
#include "cme/market/dat_saver.h"
#include "core/assist/time_measurer.h"
#include "cme/market/message/message_utility.h"
#include "core/assist/time_measurer.h"
#include "core/assist/logger.h"
#include "core/assist/utility.h"

#include "../../core/assist/mut_common.h"
#include "../../core/market/mock_marketi.h"
#include "../../core/market/mock_marketlisteneri.h"
#include "../../core/book/autotest_book_sender.h"

#include "mut_dat_saver.h"

namespace fh
{
namespace cme
{
namespace market
{
    MutDatSaver::MutDatSaver():
    m_vecRevPacket()
    {
        // noop
    }

    MutDatSaver::~MutDatSaver()
    {
        // noop
    }
    
    void MutDatSaver::SetUp()
    {
        m_vecRevPacket.clear();
    }
    
    void MutDatSaver::TearDown()
    {
    }
    // case desc: 
    // Security Definition Messages For Options and Spreads.
    // Instrument: 0EMDH8 C1330 SecurityID: 998870
    // check: {market_segment_id=99 security_group=8$ activation_date_ime=1489782300000000000 expiration_date_ime=1521207000000000000}
    //
    TEST_F(MutDatSaver, DatSaver_Test001)
    {
        fh::core::market::MarketListenerI *autotest_book_sender = nullptr; 
        fh::cme::market::DatSaver *dat_saver = nullptr;        

        autotest_book_sender = new fh::core::book::AutoTestBookSender(); 
        
        if(autotest_book_sender!=nullptr)
        {
            dat_saver = new DatSaver(autotest_book_sender);
            if(nullptr == dat_saver)
            {
                LOG_ERROR("----- dat_saver is nullptr, malloc failed! ------");       
                delete autotest_book_sender;
                autotest_book_sender = nullptr;
                return;
            }

            fh::core::book::AutoTestBookSender *autotest_book_sender_check = dynamic_cast<fh::core::book::AutoTestBookSender *>(autotest_book_sender);
            int caseId = fh::core::assist::common::CaseIdValue::Sd_1;
            autotest_book_sender_check->SetCaseId(caseId);
            //   [609]UDP Incremental:224.0.28.122, 11609
            //   [609]UDP Incremental:224.0.25.101, 11709
            //   [609]UDP Definition:224.0.28.122, 16609
            //   [609]UDP Recovery:224.0.28.122, 19609
            
            std::string recvBufFileName;
            fh::core::assist::common::getAbsolutePath(recvBufFileName);        
            recvBufFileName += "market_609_426_sd_1.log";            
            
            std::vector<fh::cme::market::message::MdpMessage> definition_datas; // define message
            // received define message
            // udp received from [224.0.28.122:16609](1176)=01
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.122:16609](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] define message **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] define message **************\n");
                    }
            ); 

            std::for_each(definition_datas.begin(), definition_datas.end(), 
                [this, autotest_book_sender, dat_saver](fh::cme::market::message::MdpMessage &m)
                {                              
                    //dat_saver->Send_message(m);
                    static fh::core::assist::TimeMeasurer t;

                    // send to db
                    std::string json = m.Serialize();
                    if(json == "")  // 返回是空说明是不需要保存的消息
                    {
                        LOG_INFO("message not need be saved: ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                    else
                    {
                        autotest_book_sender->OnOrginalMessage(json);
                        //LOG_INFO("{DB}sent to zmq(original data): ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                });
              
                        
            m_vecRevPacket.clear();
                      
            
            // 数据校验            
            if(autotest_book_sender_check!=nullptr)
            {
                std::string securityID = "securityID=998870";
                autotest_book_sender_check->CheckResult(securityID);
                //autotest_book_sender_check->OnOrginalMessage(securityID);
            }

            delete dat_saver;
            dat_saver = nullptr;
            
            delete autotest_book_sender;
            autotest_book_sender = nullptr;
        }
                  
    }
    
    // case desc: 
    // Security Definition Messages For Options and Spreads.
    // Instrument: UD:$8: RR 0424990802 SecurityID: 990802
    // check: 
    //
    TEST_F(MutDatSaver, DatSaver_Test002)
    {
        fh::core::market::MarketListenerI *autotest_book_sender = nullptr; 
        fh::cme::market::DatSaver *dat_saver = nullptr;        

        autotest_book_sender = new fh::core::book::AutoTestBookSender(); 
        
        if(autotest_book_sender!=nullptr)
        {
            dat_saver = new DatSaver(autotest_book_sender);
            if(nullptr == dat_saver)
            {
                LOG_ERROR("----- dat_saver is nullptr, malloc failed! ------");       
                delete autotest_book_sender;
                autotest_book_sender = nullptr;
                return;
            }

            fh::core::book::AutoTestBookSender *autotest_book_sender_check = dynamic_cast<fh::core::book::AutoTestBookSender *>(autotest_book_sender);
            int caseId = fh::core::assist::common::CaseIdValue::Sd_2;
            autotest_book_sender_check->SetCaseId(caseId);
            //   [609]UDP Incremental:224.0.28.122, 11609
            //   [609]UDP Incremental:224.0.25.101, 11709
            //   [609]UDP Definition:224.0.28.122, 16609
            //   [609]UDP Recovery:224.0.28.122, 19609
            
            std::string recvBufFileName;
            fh::core::assist::common::getAbsolutePath(recvBufFileName);        
            recvBufFileName += "market_609_426_sd_2.log";            
            
            m_vecRevPacket.clear();
            std::vector<fh::cme::market::message::MdpMessage> definition_datas; // define message
            // received define message
            // udp received from [224.0.28.122:16609](1176)=01
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.122:16609](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] define message **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] define message **************\n");
                    }
            ); 

            m_vecRevPacket.clear();
            
            // received increment packet , message=d
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.122:11609](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] increment packet **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] increment packet **************\n");
                    }
            ); 
            
            
            std::for_each(definition_datas.begin(), definition_datas.end(), 
                [this, autotest_book_sender, dat_saver](fh::cme::market::message::MdpMessage &m)
                {                              
                    //dat_saver->Send_message(m);
                    static fh::core::assist::TimeMeasurer t;

                    // send to db
                    std::string json = m.Serialize();
                    if(json == "")  // 返回是空说明是不需要保存的消息
                    {
                        LOG_INFO("message not need be saved: ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                    else
                    {
                        autotest_book_sender->OnOrginalMessage(json);
                        //LOG_INFO("{DB}sent to zmq(original data): ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                });
              
                        
            m_vecRevPacket.clear();
                      
            
            // 数据校验            
            if(autotest_book_sender_check!=nullptr)
            {
                std::string securityID = "securityID=990802";
                autotest_book_sender_check->CheckResult(securityID);
                //autotest_book_sender_check->OnOrginalMessage(securityID);
            }

            delete dat_saver;
            dat_saver = nullptr;
            
            delete autotest_book_sender;
            autotest_book_sender = nullptr;
        }
                  
    }
        
    // case desc: 
    // Steps of the test Security Definition Messages For Futures and Spreads.
    // Instrument: 1DVEU7 SecurityID: 996791
    // check: {market_segment_id=99 security_group=91 activation_date_ime=1466460000000000000 expiration_date_ime=1505489400000000000}
    //
    TEST_F(MutDatSaver, DatSaver_Test003)
    {
        fh::core::market::MarketListenerI *autotest_book_sender = nullptr; 
        fh::cme::market::DatSaver *dat_saver = nullptr;        

        autotest_book_sender = new fh::core::book::AutoTestBookSender(); 
        
        if(autotest_book_sender!=nullptr)
        {
            dat_saver = new DatSaver(autotest_book_sender);
            if(nullptr == dat_saver)
            {
                LOG_ERROR("----- dat_saver is nullptr, malloc failed! ------");       
                delete autotest_book_sender;
                autotest_book_sender = nullptr;
                return;
            }

            fh::core::book::AutoTestBookSender *autotest_book_sender_check = dynamic_cast<fh::core::book::AutoTestBookSender *>(autotest_book_sender);
            int caseId = fh::core::assist::common::CaseIdValue::Fs_1;
            autotest_book_sender_check->SetCaseId(caseId);
            //   [627]UDP Incremental:224.0.28.79, 11627
            //   [627]UDP Incremental:224.0.25.101, 11727
            //   [627]UDP Definition:224.0.28.79, 16627
            //   [627]UDP Recovery:224.0.28.124, 19627
            
            std::string recvBufFileName;
            fh::core::assist::common::getAbsolutePath(recvBufFileName);        
            recvBufFileName += "market_627_426_fs_1.log";     
            
            m_vecRevPacket.clear();
            std::vector<fh::cme::market::message::MdpMessage> definition_datas; // define message
            // received define message
            // udp received from [224.0.28.122:16609](1176)=01
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.79:11627](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] define message **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] define message **************\n");
                    }
            ); 

            std::for_each(definition_datas.begin(), definition_datas.end(), 
                [this, autotest_book_sender, dat_saver](fh::cme::market::message::MdpMessage &m)
                {                              
                    //dat_saver->Send_message(m);
                    static fh::core::assist::TimeMeasurer t;

                    // send to db
                    std::string json = m.Serialize();
                    if(json == "")  // 返回是空说明是不需要保存的消息
                    {
                        LOG_INFO("message not need be saved: ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                    else
                    {
                        autotest_book_sender->OnOrginalMessage(json);
                        //LOG_INFO("{DB}sent to zmq(original data): ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                });
              
                        
            m_vecRevPacket.clear();
                      
            
            // 数据校验            
            if(autotest_book_sender_check!=nullptr)
            {
                std::string securityID = "securityID=996791";
                autotest_book_sender_check->CheckResult(securityID);
                //autotest_book_sender_check->OnOrginalMessage(securityID);
            }

            delete dat_saver;
            dat_saver = nullptr;
            
            delete autotest_book_sender;
            autotest_book_sender = nullptr;
        }
                  
    }
    
    // case desc: 
    // Steps of the test Security Definition Messages For Futures and Spreads.
    // Instrument: 1DVEU7-1DVEH8 SecurityID: 996781
    // check: {market_segment_id=99 security_group=91 activation_date_ime=1481929200000000000 expiration_date_ime=1505489400000000000}
    //
    TEST_F(MutDatSaver, DatSaver_Test004)
    {
        fh::core::market::MarketListenerI *autotest_book_sender = nullptr; 
        fh::cme::market::DatSaver *dat_saver = nullptr;        

        autotest_book_sender = new fh::core::book::AutoTestBookSender(); 
        
        if(autotest_book_sender!=nullptr)
        {
            dat_saver = new DatSaver(autotest_book_sender);
            if(nullptr == dat_saver)
            {
                LOG_ERROR("----- dat_saver is nullptr, malloc failed! ------");       
                delete autotest_book_sender;
                autotest_book_sender = nullptr;
                return;
            }

            fh::core::book::AutoTestBookSender *autotest_book_sender_check = dynamic_cast<fh::core::book::AutoTestBookSender *>(autotest_book_sender);
            int caseId = fh::core::assist::common::CaseIdValue::Fs_2;
            autotest_book_sender_check->SetCaseId(caseId);
            //   [627]UDP Incremental:224.0.28.79, 11627
            //   [627]UDP Incremental:224.0.25.101, 11727
            //   [627]UDP Definition:224.0.28.79, 16627
            //   [627]UDP Recovery:224.0.28.124, 19627
            
            std::string recvBufFileName;
            fh::core::assist::common::getAbsolutePath(recvBufFileName);        
            recvBufFileName += "market_627_426_fs_2.log";     
            
            m_vecRevPacket.clear();
            std::vector<fh::cme::market::message::MdpMessage> definition_datas; // define message
            // received define message
            // udp received from [224.0.28.79:16627](1368)=01
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.79:16627](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] define message **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] define message **************\n");
                    }
            ); 

            std::for_each(definition_datas.begin(), definition_datas.end(), 
                [this, autotest_book_sender, dat_saver](fh::cme::market::message::MdpMessage &m)
                {                              
                    //dat_saver->Send_message(m);
                    static fh::core::assist::TimeMeasurer t;

                    // send to db
                    std::string json = m.Serialize();
                    if(json == "")  // 返回是空说明是不需要保存的消息
                    {
                        LOG_INFO("message not need be saved: ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                    else
                    {
                        autotest_book_sender->OnOrginalMessage(json);
                        //LOG_INFO("{DB}sent to zmq(original data): ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                });
              
                        
            m_vecRevPacket.clear();
                      
            
            // 数据校验            
            if(autotest_book_sender_check!=nullptr)
            {
                std::string securityID = "securityID=996781";
                autotest_book_sender_check->CheckResult(securityID);
                //autotest_book_sender_check->OnOrginalMessage(securityID);
            }

            delete dat_saver;
            dat_saver = nullptr;
            
            delete autotest_book_sender;
            autotest_book_sender = nullptr;
        }
                  
    }

    // case desc: 
    // Request For Quote Message.
    // Instrument: 1DVEU7-1DVEH8 SecurityID: 996781
    // check: {"orderQty" : "290"}
    //
    TEST_F(MutDatSaver, DatSaver_Test005)
    {
        fh::core::market::MarketListenerI *autotest_book_sender = nullptr; 
        fh::cme::market::DatSaver *dat_saver = nullptr;        

        autotest_book_sender = new fh::core::book::AutoTestBookSender(); 
        
        if(autotest_book_sender!=nullptr)
        {
            dat_saver = new DatSaver(autotest_book_sender);
            if(nullptr == dat_saver)
            {
                LOG_ERROR("----- dat_saver is nullptr, malloc failed! ------");       
                delete autotest_book_sender;
                autotest_book_sender = nullptr;
                return;
            }

            fh::core::book::AutoTestBookSender *autotest_book_sender_check = dynamic_cast<fh::core::book::AutoTestBookSender *>(autotest_book_sender);
            int caseId = fh::core::assist::common::CaseIdValue::Order_Qty;
            autotest_book_sender_check->SetCaseId(caseId);
            //   [627]UDP Incremental:224.0.28.79, 11627
            //   [627]UDP Incremental:224.0.25.101, 11727
            //   [627]UDP Definition:224.0.28.79, 16627
            //   [627]UDP Recovery:224.0.28.124, 19627
            
            std::string recvBufFileName;
            fh::core::assist::common::getAbsolutePath(recvBufFileName);        
            recvBufFileName += "market_627_426_qm.log";     
            
            m_vecRevPacket.clear();
            std::vector<fh::cme::market::message::MdpMessage> definition_datas; // define message
            // received define message
            // udp received from [224.0.28.79:16627](1368)=01
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.79:16627](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] define message **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] define message **************\n");
                    }
            ); 

            m_vecRevPacket.clear();
            
            // received increment packet
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.25.101:11727](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] increment packet **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] increment packet **************\n");
                    }
            ); 
            
            std::for_each(definition_datas.begin(), definition_datas.end(), 
                [this, autotest_book_sender, dat_saver](fh::cme::market::message::MdpMessage &m)
                {                              
                    //dat_saver->Send_message(m);
                    static fh::core::assist::TimeMeasurer t;

                    // send to db
                    std::string json = m.Serialize();
                    if(json == "")  // 返回是空说明是不需要保存的消息
                    {
                        LOG_INFO("message not need be saved: ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                    else
                    {
                        autotest_book_sender->OnOrginalMessage(json);
                        //LOG_INFO("{DB}sent to zmq(original data): ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                });
              
                        
            m_vecRevPacket.clear();
                      
            
            // 数据校验            
            if(autotest_book_sender_check!=nullptr)
            {
                std::string securityID = "securityID=996781";
                autotest_book_sender_check->CheckResult(securityID);                
            }

            delete dat_saver;
            dat_saver = nullptr;
            
            delete autotest_book_sender;
            autotest_book_sender = nullptr;
        }
                  
    }
    
    //
    // case desc: 
    // Statistic Messages: 
    // 3 Electronic volume statistics were sent. Please validate the following values and A trading session high price was sent. Please validate the following values.
    // Instrument:1DVEU7 SecurityID:996791
    // out:  "mDEntryPx" : { "mantissa" : "241450000000", "exponent" : "-7" }, "mDEntrySize" : "47"
    //
    TEST_F(MutDatSaver, DatSaver_Test006)
    {
        fh::core::market::MarketListenerI *autotest_book_sender = nullptr; 
        fh::cme::market::DatSaver *dat_saver = nullptr;        

        autotest_book_sender = new fh::core::book::AutoTestBookSender(); 
        
        if(autotest_book_sender!=nullptr)
        {
            dat_saver = new DatSaver(autotest_book_sender);
            if(nullptr == dat_saver)
            {
                LOG_ERROR("----- dat_saver is nullptr, malloc failed! ------");       
                delete autotest_book_sender;
                autotest_book_sender = nullptr;
                return;
            }

            fh::core::book::AutoTestBookSender *autotest_book_sender_check = dynamic_cast<fh::core::book::AutoTestBookSender *>(autotest_book_sender);
            int caseId = fh::core::assist::common::CaseIdValue::Sm_3;
            autotest_book_sender_check->SetCaseId(caseId);
            //   [627]UDP Incremental:224.0.28.79, 11627
            //   [627]UDP Incremental:224.0.25.101, 11727
            //   [627]UDP Definition:224.0.28.79, 16627
            //   [627]UDP Recovery:224.0.28.124, 19627
            
            std::string recvBufFileName;
            fh::core::assist::common::getAbsolutePath(recvBufFileName);        
            recvBufFileName += "market_627_427_sm_3.log";
            
            m_vecRevPacket.clear();
            std::vector<fh::cme::market::message::MdpMessage> definition_datas; // define message
            // received define message
            // udp received from [224.0.28.79:16627](1368)=01
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.79:16627](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] define message **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] define message **************\n");
                    }
            ); 

            m_vecRevPacket.clear();
            
            // received increment packet
            fh::core::assist::common::Read_packets(m_vecRevPacket, recvBufFileName, "udp received from [224.0.28.79:11627](", "=");
            std::for_each(m_vecRevPacket.cbegin(), m_vecRevPacket.cend(),
                    [this, &definition_datas](const std::string &revPacket)
                    {
                        // decode                                                
                        std::uint32_t seq = fh::cme::market::message::utility::Pick_messages_from_packet(revPacket.data(), revPacket.size(), definition_datas);

                        printf("*********** [begin] increment packet **************\n");
                                               
                        LOG_INFO("seq=", seq, ", definition_datas count=", definition_datas.size());

                        printf("*********** [end] increment packet **************\n");
                    }
            ); 
            
            std::for_each(definition_datas.begin(), definition_datas.end(), 
                [this, autotest_book_sender, dat_saver](fh::cme::market::message::MdpMessage &m)
                {                              
                    //dat_saver->Send_message(m);
                    static fh::core::assist::TimeMeasurer t;

                    // send to db
                    std::string json = m.Serialize();
                    if(json == "")  // 返回是空说明是不需要保存的消息
                    {
                        LOG_INFO("message not need be saved: ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                    else
                    {
                        autotest_book_sender->OnOrginalMessage(json);
                        //LOG_INFO("{DB}sent to zmq(original data): ", t.Elapsed_nanoseconds(), "ns, seq=", m.packet_seq_num(), " type=", m.message_type());
                    }
                });
              
                        
            m_vecRevPacket.clear();
                      
            
            // 数据校验            
            if(autotest_book_sender_check!=nullptr)
            {
                std::string securityID = "securityID=996791";
                autotest_book_sender_check->CheckResult(securityID);                
            }

            delete dat_saver;
            dat_saver = nullptr;
            
            delete autotest_book_sender;
            autotest_book_sender = nullptr;
        }
                  
    }
} // namespace market
} // namespace cme
} // namespace fh
