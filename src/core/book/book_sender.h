#ifndef __FH_CORE_BOOK_BOOK_SENDER_H__
#define __FH_CORE_BOOK_BOOK_SENDER_H__

#include <string>
#include "core/global.h"
#include "core/market/marketlisteneri.h"
#include "core/zmq/zmq_sender.h"

namespace fh
{
namespace core
{
namespace book
{
    class BookSender : public fh::core::market::MarketListenerI
    {
        public:
            BookSender(const std::string &org_url, const std::string &book_url);
            virtual ~BookSender();

        public:
            // implement of MarketListenerI
            void OnMarketDisconnect(core::market::MarketI* market) override;
            // implement of MarketListenerI
            void OnMarketReconnect(core::market::MarketI* market) override;
            // implement of MarketListenerI
            void OnContractDefinition(const pb::dms::Contract &contract) override;
            // implement of MarketListenerI
            void OnBBO(const pb::dms::BBO &bbo) override;
            // implement of MarketListenerI
            void OnBid(const pb::dms::Bid &bid) override;
            // implement of MarketListenerI
            void OnOffer(const pb::dms::Offer &offer) override;
            // implement of MarketListenerI
            void OnL2(const pb::dms::L2 &l2) override;
            // implement of MarketListenerI
            void OnL3() override;
            // implement of MarketListenerI
            void OnTrade(const pb::dms::Trade &trade) override;
            // implement of MarketListenerI
            void OnContractAuctioning(const std::string &contract) override;
            // implement of MarketListenerI
            void OnContractNoTrading(const std::string &contract)  override;
            // implement of MarketListenerI
            void OnContractTrading(const std::string &contract)    override;
            // implement of MarketListenerI
            void OnOrginalMessage(const std::string &message) override;
            // implement of MarketListenerI
            void OnTurnover(const pb::dms::Turnover &turnover) override;

        private:
            fh::core::zmq::ZmqSender m_org_sender;
            fh::core::zmq::ZmqSender m_book_sender;

        private:
            DISALLOW_COPY_AND_ASSIGN(BookSender);
    };
} // namespace book
} // namespace core
} // namespace fh

#endif // __FH_CORE_BOOK_BOOK_SENDER_H__
