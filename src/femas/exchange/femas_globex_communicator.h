#ifndef __FH_FEMA_EXCHANGE_GLOBX_H__
#define __FH_FEMA_EXCHANGE_GLOBX_H__

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "USTPFtdcTraderApi.h"
#include "core/exchange/exchangei.h"
#include "pb/ems/ems.pb.h"
#include "core/assist/settings.h"

namespace fh
{
namespace femas
{
namespace exchange
{

    class CUstpFtdcTraderManger : public CUstpFtdcTraderSpi
    {
        public:
		   CUstpFtdcTraderManger(CUstpFtdcTraderApi *pUserApi) :
                                                                  m_pUserApi (pUserApi) 
		   {

		   }
	          ~CUstpFtdcTraderManger ()
	          {

		   }
	 public:
	 	   virtual void OnFrontConnected();
		   virtual void OnFrontDisconnected(int nReason);
		   virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField  *pRspInfo, int nRequestID, bool bIsLast);
		   virtual void OnRspOrderInsert(CUstpFtdcInputOrderField  *pInputOrder, CUstpFtdcRspInfoField  *pRspInfo, int nRequestID, bool bIsLast);
		   virtual void OnRtnOrder(CUstpFtdcOrderField  *pOrder);
		   virtual void OnRspError(CUstpFtdcRspInfoField  *pRspInfo, int nRequestID, bool bIsLast);
		   void SetFileConfigData(std::string &FileConfig);	
        private:
		   CUstpFtdcTraderApi *m_pUserApi;
		   fh::core::assist::Settings *m_pFileConfig;
    };

    class CFemasGlobexCommunicator : public core::exchange::ExchangeI
    {
          public:
		   CFemasGlobexCommunicator(core::exchange::ExchangeListenerI *strategy,const std::string &config_file);
                 virtual ~CFemasGlobexCommunicator();
          public:
                 // implement of ExchangeI
                bool Start(const std::vector<::pb::ems::Order> &init_orders) override;
                // implement of ExchangeI
                void Stop() override;

         public:
                // implement of ExchangeI
                void Initialize(std::vector<::pb::dms::Contract> contracts) override;
                // implement of ExchangeI
                void Add(const ::pb::ems::Order& order) override;
                 // implement of ExchangeI
                void Change(const ::pb::ems::Order& order) override;
                // implement of ExchangeI
                void Delete(const ::pb::ems::Order& order) override;
                // implement of ExchangeI
                void Query(const ::pb::ems::Order& order) override;
                // implement of ExchangeI
                void Query_mass(const char *data, size_t size) override;
                // implement of ExchangeI
                void Delete_mass(const char *data, size_t size) override;

				 
	  public:			 
                 CUstpFtdcTraderManger* m_pUstpFtdcTraderManger;
                 fh::core::assist::Settings *m_pFileConfig;
		   CUstpFtdcTraderApi *m_pUserApi;
  

	  private:
                 core::exchange::ExchangeListenerI *m_strategy;
				 
		   std::vector<::pb::ems::Order> m_init_orders;		 

	  private:
	  	
                 //DISALLOW_COPY_AND_ASSIGN(CFemasGlobexCommunicator);			 

			
    };



}
}
}









#endif