#include "femas/market/femas_book_manager.h"
#include "core/assist/logger.h"
namespace fh
{
namespace femas
{
namespace market
{



CFemasBookManager::CFemasBookManager(fh::core::market::MarketListenerI *sender)
{
        // noop
        m_book_sender = sender;
	 m_trademap.clear();
}      


CFemasBookManager::~CFemasBookManager()
{
        // noop
}   



std::string CFemasBookManager::GetUpdateTimeStr(CUstpFtdcDepthMarketDataField *pMarketData)
{
    std::string timestr="";
    char ctmp[20]={0};	
    strncpy(ctmp,pMarketData->ActionDay,4);
    ctmp[4] = '-';
    strncpy(ctmp+5,pMarketData->ActionDay+4,2);	
    ctmp[7] = '-';
    strncpy(ctmp+8,pMarketData->ActionDay+6,2);	
    ctmp[10] = ' ';
    timestr = ctmp;	
    timestr+=pMarketData->UpdateTime;
    timestr+=".";	 
    std::string tmp = std::to_string(pMarketData->UpdateMillisec);
    if(pMarketData->UpdateMillisec != 500)
    {
        tmp = "000";
    }		
    tmp += "000";
    timestr += tmp;	
    	
    return timestr;
}

ullong CFemasBookManager::GetUpdateTimeInt(CUstpFtdcDepthMarketDataField *pMarketData)
{
    std::string timestr="";
    char ctmp[20]={0};	
    strncpy(ctmp,pMarketData->ActionDay,4);
    ctmp[4] = '-';
    strncpy(ctmp+5,pMarketData->ActionDay+4,2);	
    ctmp[7] = '-';
    strncpy(ctmp+8,pMarketData->ActionDay+6,2);
    ctmp[10] = ' ';
    timestr = ctmp;	
    timestr+=pMarketData->UpdateTime;
    ullong tmp_time = 0;
    tmp_time = str2stmp(timestr.c_str());	
    tmp_time *= 1000;
    tmp_time += pMarketData->UpdateMillisec;
    tmp_time *= 1000;
    tmp_time *= 1000;	
    return tmp_time;	
}

ullong CFemasBookManager::str2stmp(const char *strTime)
{
     if (strTime != NULL)
     {
         struct tm sTime;
 #ifdef __GNUC__
         strptime(strTime, "%Y-%m-%d %H:%M:%S", &sTime);
 #else
         sscanf(strTime, "%d-%d-%d %d:%d:%d", &sTime.tm_year, &sTime.tm_mon, &sTime.tm_mday, &sTime.tm_hour, &sTime.tm_min, &sTime.tm_sec);
         sTime.tm_year -= 1900;
         sTime.tm_mon -= 1;
 #endif
         ullong ft = mktime(&sTime);
         return ft;
     }
     else {
         return time(0);
     }
}

void CFemasBookManager::SendFemasmarketData(CUstpFtdcDepthMarketDataField *pMarketData)
{
	LOG_INFO("CFemasBookManager::SendFemasmarketData ");     
	if(NULL == pMarketData)
	{
       	        LOG_INFO("Error pMarketData is NULL ");
		return;
	}
	pb::dms::L2 l2_info;

       l2_info.set_contract(pMarketData->InstrumentID);

	   
	pb::dms::DataPoint *bid;// = l2_info.add_bid();
	pb::dms::DataPoint *ask;// = l2_info.add_offer();
	
	if (pMarketData->BidPrice1==DBL_MAX || pMarketData->BidVolume1 <= 0)
	{
           //bid->set_price(0.0);
	}
	else
	{
	    bid = l2_info.add_bid();
           bid->set_price(pMarketData->BidPrice1);
	    bid->set_size(pMarketData->BidVolume1);	   
	}	
		
	if (pMarketData->AskPrice1==DBL_MAX || pMarketData->AskVolume1 <= 0)
	{
           //ask->set_price(0.0);
	}
	else
	{
	    ask = l2_info.add_offer();
           ask->set_price(pMarketData->AskPrice1);
	    ask->set_size(pMarketData->AskVolume1);	   
	}
	

	if (pMarketData->BidPrice2==DBL_MAX || pMarketData->BidVolume2 <= 0)
	{
           //bid->set_price(0.0);
	}
	else
	{
	    bid = l2_info.add_bid();
           bid->set_price(pMarketData->BidPrice2);
	    bid->set_size(pMarketData->BidVolume2);	   
	}	
	

	if (pMarketData->AskPrice2==DBL_MAX || pMarketData->AskVolume2 <= 0)
	{
           //ask->set_price(0.0);
	}
	else
	{
	    ask = l2_info.add_offer();
           ask->set_price(pMarketData->AskPrice2);
	    ask->set_size(pMarketData->AskVolume2);	   
	}
	
	if (pMarketData->BidPrice3==DBL_MAX || pMarketData->BidVolume3 <= 0)
	{
           //bid->set_price(0.0);
	}
	else
	{
	    bid = l2_info.add_bid();
           bid->set_price(pMarketData->BidPrice3);
	    bid->set_size(pMarketData->BidVolume3);	   
	}	
	

	if (pMarketData->AskPrice3==DBL_MAX || pMarketData->AskVolume3 <= 0)
	{
           //ask->set_price(0.0);
	}
	else
	{
	    ask = l2_info.add_offer();
           ask->set_price(pMarketData->AskPrice3);
	    ask->set_size(pMarketData->AskVolume3);	   
	}
	
	if (pMarketData->BidPrice4==DBL_MAX || pMarketData->BidVolume4 <= 0)
	{
           //bid->set_price(0.0);
	}
	else
	{
	    bid = l2_info.add_bid();
           bid->set_price(pMarketData->BidPrice4);
	    bid->set_size(pMarketData->BidVolume4);	   
	}	
	

	if (pMarketData->AskPrice4==DBL_MAX || pMarketData->AskVolume4 <= 0)
	{
           //ask->set_price(0.0);
	}
	else
	{
	    ask = l2_info.add_offer();
           ask->set_price(pMarketData->AskPrice4);
	    ask->set_size(pMarketData->AskVolume4);	   
	}
	
	if (pMarketData->BidPrice5==DBL_MAX || pMarketData->BidVolume5 <= 0)
	{
           //bid->set_price(0.0);
	}
	else
	{
	    bid = l2_info.add_bid();
           bid->set_price(pMarketData->BidPrice5);
	    bid->set_size(pMarketData->BidVolume5);	   
	}	
	

	if (pMarketData->AskPrice5==DBL_MAX || pMarketData->AskVolume5 <= 0)
	{
           //ask->set_price(0.0);
	}
	else
	{
	    ask = l2_info.add_offer();
           ask->set_price(pMarketData->AskPrice5);
	    ask->set_size(pMarketData->AskVolume5);	   
	}
	
	//m_book_sender->OnL2(l2_info);

	//以上发送L2 行情

	//发送最优价
	if((pMarketData->BidPrice1 == DBL_MAX || pMarketData->BidVolume1 <= 0) && (pMarketData->AskVolume1 <= 0 || pMarketData->AskPrice1 == DBL_MAX))
	{
           LOG_INFO("Bid and Offer NULL ");
	}
	else
	if(pMarketData->BidPrice1 == DBL_MAX || pMarketData->BidVolume1 <= 0)	
	{
           pb::dms::Offer offer_info;
	    offer_info.set_contract(pMarketData->InstrumentID);	   
	    pb::dms::DataPoint *offer = offer_info.mutable_offer();
	    offer->set_price(pMarketData->AskPrice1);
	    offer->set_size(pMarketData->AskVolume1);	
	    m_book_sender->OnOffer(offer_info);
	}
	else
	if(pMarketData->AskPrice1 == DBL_MAX || pMarketData->AskVolume1 <= 0)	
	{
           pb::dms::Bid bid_info;
	    bid_info.set_contract(pMarketData->InstrumentID);	   
	    pb::dms::DataPoint *bid = bid_info.mutable_bid();
	    bid->set_price(pMarketData->BidPrice1);
	    bid->set_size(pMarketData->BidVolume1);	
	    m_book_sender->OnBid(bid_info);
	}	
	else
	{
           pb::dms::BBO bbo_info;
	    bbo_info.set_contract(pMarketData->InstrumentID);		
           pb::dms::DataPoint *bid = bbo_info.mutable_bid();
	    bid->set_price(pMarketData->BidPrice1);
	    bid->set_size(pMarketData->BidVolume1);	
           pb::dms::DataPoint *ask = bbo_info.mutable_offer();
           ask->set_price(pMarketData->AskPrice1);
           ask->set_size(pMarketData->AskVolume1);	   
           m_book_sender->OnBBO(bbo_info);
		
	}

	//发送teade行情
	int tmpvolume = MakePriceVolume(pMarketData);
	LOG_INFO("CFemasBookManager::MakePriceVolume = ",tmpvolume); 
	if(tmpvolume > 0)
	{
            pb::dms::Trade trade_info;
	     trade_info.set_contract(pMarketData->InstrumentID);	
	     pb::dms::DataPoint *trade_id = trade_info.mutable_last();	
	     trade_id->set_price(pMarketData->LastPrice);
	     trade_id->set_size(tmpvolume);	
            trade_info.set_time(std::to_string(GetUpdateTimeInt(pMarketData)));   
	     m_book_sender->OnTrade(trade_info);	 
	}

       pb::dms::Turnover Turnoverinfo;
       Turnoverinfo.set_contract(pMarketData->InstrumentID);
	Turnoverinfo.set_total_volume(pMarketData->Volume);
	Turnoverinfo.set_turnover(pMarketData->Turnover);
	m_book_sender->OnTurnover(Turnoverinfo);
    
	l2_info.set_time(std::to_string(GetUpdateTimeInt(pMarketData)));     

	m_book_sender->OnL2(l2_info);
	
}

void CFemasBookManager::CheckTime(CUstpFtdcDepthMarketDataField *pMarketData)
{
    LOG_INFO("CFemasBookManager::CheckTime "); 
    char ctmpf[3]={0};
    char ctmps[3]={0};	
    strncpy(ctmpf,pMarketData->UpdateTime,2);	
    strncpy(ctmps,(m_trademap[pMarketData->InstrumentID]->mtime).c_str(),2);		
    if(std::atoi(ctmpf) > 18 && std::atoi(ctmps) < 18)
    {
        LOG_INFO("CFemasBookManager::clear  Instrument map");
        m_trademap[pMarketData->InstrumentID]->mvolume=pMarketData->Volume;
	 m_trademap[pMarketData->InstrumentID]->mtime=pMarketData->UpdateTime;	
    }
}

//void CFemasBookManager::ClearMap()
//{
//    m_trademap.clear();
//}

int CFemasBookManager::MakePriceVolume(CUstpFtdcDepthMarketDataField *pMarketData)
{
    LOG_INFO("CFemasBookManager::MakePriceVolume "); 
    if(m_trademap.count(pMarketData->InstrumentID) == 0)
    {
        LOG_INFO("CFemasBookManager::insert map InstrumentID = ",pMarketData->InstrumentID); 
        m_trademap[pMarketData->InstrumentID] = new mstrade();
	 m_trademap[pMarketData->InstrumentID]->mvolume=pMarketData->Volume;
	 m_trademap[pMarketData->InstrumentID]->mtime=pMarketData->UpdateTime;
        return 0;
    }
    else
    {
        CheckTime(pMarketData);
	 LOG_INFO("CFemasBookManager::pMarketData->Volume =  ",pMarketData->Volume); 	
	 LOG_INFO("CFemasBookManager::m_trademap->Volume =  ",m_trademap[pMarketData->InstrumentID]->mvolume); 
        int tmpVolume =  pMarketData->Volume - m_trademap[pMarketData->InstrumentID]->mvolume;
	 m_trademap[pMarketData->InstrumentID]->mvolume=pMarketData->Volume;
	 m_trademap[pMarketData->InstrumentID]->mtime=pMarketData->UpdateTime;	
        return (tmpVolume > 0 ? tmpVolume : 0);     
    }		
}

void CFemasBookManager::SendFemasToDB(const std::string &message)
{
    m_book_sender->OnOrginalMessage(message);
    return;	
}

	
} // namespace market
} // namespace femas
} // namespace fh
