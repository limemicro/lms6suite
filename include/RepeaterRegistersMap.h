#ifndef LMS_REPEATER_H
#define LMS_REPEATER_H

#include "GenericRegistersMap.h"

enum eRepeaterParameter
{
    ENABLE_TX,
    ENABLE_RX,
    GCORRQ_TX,
    GCORRI_TX,
    INSEL,
    IQCORR_TX,
    DCCORRI_TX,
    DCCORRQ_TX,
    DC_BYP_TX,
    INVSINC_BYP,
    FIR_BYP_TX,
    GC_BYP_TX,
    PHC_BYP_TX,
    TNCO,
    GCORRQ_RX,
    GCORRI_RX,
    IQCORR_RX,
    DCCORR,
    FIR_BYP_RX,
    DC_BYP_RX,
    PHC_BYP_RX,
    GC_BYP_RX
};

class RepeaterRegistersMap : public GenericRegistersMap<eRepeaterParameter, unsigned short>
{
public:
    RepeaterRegistersMap();
    ~RepeaterRegistersMap();
    void InitializeControlParameters();
};

#endif // LMS_REPEATER_H

