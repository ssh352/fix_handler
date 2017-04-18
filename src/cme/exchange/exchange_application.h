
#ifndef __FH_CME_EXCHANGE_EXCHANGE_APPLICATION_H__
#define __FH_CME_EXCHANGE_EXCHANGE_APPLICATION_H__

#include <string>
#include "core/global.h"
#include "cme/exchange/strategy_communicator.h"
#include "cme/exchange/globex_communicator.h"


namespace fh
{
namespace cme
{
namespace exchange
{
    class ExchangeApplication
    {
        public:
            explicit ExchangeApplication(
                const std::string &fix_setting_file = "exchange_client.cfg",
                const std::string &app_setting_file = "exchange_settings.ini");
            virtual ~ExchangeApplication();

        public:
            bool Start();
            void Stop();

        private:
            void Initial_application(const std::string &fix_setting_file, const std::string &app_setting_file);
            std::vector<::pb::ems::Order> Get_init_orders();

        private:
            StrategyCommunicator *m_strategy;
            GlobexCommunicator *m_globex;

        private:
            DISALLOW_COPY_AND_ASSIGN(ExchangeApplication);
    };
} // namespace exchange
} // namespace cme
} // namespace fh

#endif     // __FH_CME_EXCHANGE_EXCHANGE_APPLICATION_H__