
#ifndef __FH_CORE_ASSIST_COMMON_H__
#define __FH_CORE_ASSIST_COMMON_H__

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <quickfix/Message.h>
#include "core/global.h"
#include "pb/ems/ems.pb.h"
#include "pb/dms/dms.pb.h"

namespace fh
{
namespace core
{
namespace assist
{
namespace common
{
    enum CaseIdValue 
    {
        MakePrice_1 = 1,
        MakePrice_2 = 2,
        Sd_1 = 3,
        Sd_2 = 4,
        Fs_1 = 5,
        Fs_2 = 6,
        Order_Qty = 7,
        Sm_1 = 8,
        Sm_2 = 9,
        Sm_3 = 10,
        Sm_4 = 11,
        Sm_5 = 12,
        Sm_6 = 13,
        UNKNOW_VALUE = 255
    };
    
    struct DefineMsg_Compare
    {
        std::string market_segment_id;
        std::string security_group;
        std::string activation_date_ime;
        std::string expiration_date_ime;
        
        std::string order_qty;
        
        std::string mdentry_px_mantissa;  // mdentry_px
        std::string mdentry_px_exponent;
        std::string mdentry_size;

        
        std::string To_string() const
        {
            std::ostringstream os;
            os << "DefineMsg_Compare={";
            os << "market_segment_id=" << market_segment_id << " ";
            os << "security_group=" << security_group << " ";
            os << "activation_date_ime=" << activation_date_ime << " ";            
            os << "expiration_date_ime=" << expiration_date_ime << "}";

            return os.str();
        }
        
        std::string To_order_qty_string() const
        {
            std::ostringstream os;
            os << "DefineMsg_Compare={";            
            os << "orderQty=" << order_qty << "}";

            return os.str();
        }
        
        std::string To_mdentry_price_size_string() const
        {
            std::ostringstream os;
            os << "mDEntry_Price_Size_Compare={";    
            os << "mdentry_px_mantissa=" << mdentry_px_mantissa << " ";  
            os << "mdentry_px_exponent=" << mdentry_px_exponent << " ";             
            os << "mdentry_size=" << mdentry_size << "}";

            return os.str();
        }
    };
    
    void getAbsolutePath(std::string &path);
    
    void show_message(const std::string &hex_message);
    
    // read mdp packets from file(one packet per line) for test 
    // std::vector<std::string>
    void Read_packets(std::vector<std::string> &packets, const std::string &filename, const std::string &packet_from, const std::string &packet_start_indicate = "=");

} // namespace utility
} // namespace assist
} // namespace core
} // namespace fh

#endif //  __FH_CORE_ASSIST_COMMON_H__
