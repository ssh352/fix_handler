#ifndef __FH_CME_MARKET_MESSAGE_INSTRUMENT_H__
#define __FH_CME_MARKET_MESSAGE_INSTRUMENT_H__

#include "core/global.h"

namespace fh
{
namespace cme
{
namespace market
{
namespace message
{
    struct Instrument
    {
        std::uint32_t packet_seq_num;
        std::uint16_t template_id;
        std::uint16_t appId;
        std::uint32_t securityID;
        std::uint8_t depthGBX;    // GBX- Real Book depth
        std::uint8_t depthGBI;        // GBI-Implied Book depth

        // TODO serialize to send
        std::string Serialize() const
        {
            std::ostringstream os;
            os << "instrument: ";
            os << "packet_seq_num=" << packet_seq_num << " ";
            os << "template_id=" << template_id << " ";
            os << "securityID=" << securityID << " ";
            os << "depthGBX=" << (int)depthGBX << " ";
            os << "depthGBI=" << (int)depthGBI << " ";

            return os.str();
        }
    };
} // namespace message
} // namespace market
} // namespace cme
} // namespace fh

#endif // __FH_CME_MARKET_MESSAGE_INSTRUMENT_H__
