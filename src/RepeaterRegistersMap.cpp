#include "RepeaterRegistersMap.h"
#include "LMS_Commands.h"

void RepeaterRegistersMap::InitializeControlParameters()
{
    map<eRepeaterParameter, ControlParameter> params;
    params[ENABLE_TX] = ControlParameter(0x0000, 0, 0, 1, "ENABLE_TX");
    params[GCORRQ_TX] = ControlParameter(0x0003, 10, 0, 0x7FF, "GCORRQ_TX");
    params[GCORRI_TX] = ControlParameter(0x0004, 10, 0, 0x7FF, "GCORRI_TX");
    params[INSEL] = ControlParameter(0x0005, 15, 15, 0, "INSEL");
    params[IQCORR_TX] = ControlParameter(0x0005, 11, 0, 0, "IQCORR_TX");
    params[DCCORRI_TX] = ControlParameter(0x0006, 15, 8, 0, "DCCORRI_TX");
    params[DCCORRQ_TX] = ControlParameter(0x0006, 7, 0, 0, "DCCORRQ_TX");
    params[DC_BYP_TX] = ControlParameter(0x0009, 5, 5, 0, "DC_BYP_TX");
    params[INVSINC_BYP] = ControlParameter(0x0009, 4, 4, 0, "INVSINC_BYP");
    params[FIR_BYP_TX] = ControlParameter(0x0009, 2, 2, 0, "FIR_BYP_TX");
    params[GC_BYP_TX] = ControlParameter(0x0009, 1, 1, 0, "GC_BYP_TX");
    params[PHC_BYP_TX] = ControlParameter(0x0009, 0, 0, 0, "PHC_BYP_TX");
    params[TNCO] = ControlParameter(0x000F, 1, 0, 1, "TNCO");

    params[ENABLE_RX] = ControlParameter(0x0200, 0, 0, 1, "ENABLE_RX");
    params[GCORRQ_RX] = ControlParameter(0x0203, 10, 0, 0x7FF, "GCORRQ_RX");
    params[GCORRI_RX] = ControlParameter(0x0204, 10, 0, 0x7FF, "GCORRI_RX");
    params[IQCORR_RX] = ControlParameter(0x0205, 11, 0, 0, "IQCORR_RX");
    params[DCCORR] = ControlParameter(0x0206, 10, 8, 0, "DCCORR");
    params[FIR_BYP_RX] = ControlParameter(0x020D, 4, 4, 0, "FIR_BYP_RX");
    params[DC_BYP_RX] = ControlParameter(0x020D, 2, 2, 0, "DC_BYP_RX");
    params[PHC_BYP_RX] = ControlParameter(0x020D, 1, 1, 0, "PHC_BYP_RX");
    params[GC_BYP_RX] = ControlParameter(0x020D, 0, 0, 0, "GC_BYP_RX");
    SetControlParameters(params);
}

RepeaterRegistersMap::RepeaterRegistersMap()
{
    mCmdRead = CMD_BRDSPI16_RD;
    mCmdWrite = CMD_BRDSPI16_WR;
    InitializeControlParameters();
    InitializeDefaultValuesAndMasks();
}

RepeaterRegistersMap::~RepeaterRegistersMap()
{

}
