
#include "femas_market.h"



namespace fh
{
namespace femas
{
namespace market
{


CFemasMarket::CFemasMarket(fh::core::market::MarketListenerI *listener)
: fh::core::market::MarketI(listener)
{
    m_pUstpFtdcMduserApi = CUstpFtdcMduserApi::CreateFtdcMduserApi();
    m_FemasMarkrtManager = new fh::femas::market::CFemasMarkrtManager(m_pUstpFtdcMduserApi);
    if(NULL == m_pUstpFtdcMduserApi || NULL == m_FemasMarkrtManager)
    {
          printf("Error m_pUstpFtdcMduserApi or m_FemasMarkrtManager is NULL \n");
	   return;	  
    }	
    m_FemasMarkrtManager->CreateFemasBookManager(listener);	
}

// implement of MarketI
bool CFemasMarket::Start()
{
    printf("CFemasMarket::Start() \n");
    if(NULL == m_pUstpFtdcMduserApi)
    {
          printf("Error m_pUstpFtdcMduserApi is NULL \n");
	   return false;	  
    }
      

    m_pUstpFtdcMduserApi->RegisterSpi(m_FemasMarkrtManager);
    //m_pUstpFtdcMduserApi->SubscribeMarketDataTopic (21001, USTP_TERT_RESUME);
    //m_pUstpFtdcMduserApi->SubscribeMarketDataTopic (3101, USTP_TERT_RESTART);

    m_pUstpFtdcMduserApi->SubscribeMarketDataTopic (21001, USTP_TERT_RESUME);
//    m_pUstpFtdcMduserApi->SubscribeMarketDataTopic (3101, USTP_TERT_RESTART);	
    //m_pUstpFtdcMduserApi->SubscribeMarketDataTopic (100, USTP_TERT_RESUME);
	 
    std::string tmpurl = m_pFileConfig->Get("femas-market.url");
    printf("femas url = %s \n",tmpurl.c_str());
	 
    m_pUstpFtdcMduserApi->RegisterFront((char*)(tmpurl.c_str()));



     m_pUstpFtdcMduserApi->Init();

     return true;	 
}
 // implement of MarketI
void CFemasMarket::Initialize(std::vector<std::string> insts)
{

}
// implement of MarketI
void CFemasMarket::Stop()
{
     printf("CFemasMarket::Release \n");

     if(NULL == m_pUstpFtdcMduserApi)
     {
          printf("Error m_pUstpFtdcMduserApi is NULL \n");
	   return;	  
     }
	 
     m_pUstpFtdcMduserApi->Release();
}
// implement of MarketI
void CFemasMarket::Subscribe(std::vector<std::string> instruments)
{

}
// implement of MarketI
void CFemasMarket::UnSubscribe(std::vector<std::string> instruments)
{

}
 // implement of MarketI
void CFemasMarket::ReqDefinitions(std::vector<std::string> instruments)
{

}


 void CFemasMarket::SetFileConfigData(std::string &FileConfig)
 {
     printf("CFemasMarket::SetFileConfigData file = %s \n",FileConfig.c_str());
     m_pFileConfig = new fh::core::assist::Settings(FileConfig); 
     

     if(NULL == m_FemasMarkrtManager)
     {
          printf("Error m_FemasMarkrtManager is NULL \n");
	   return;	  
     }

     m_FemasMarkrtManager->SetFileData(FileConfig);	 
      	 
 }



}
}
}