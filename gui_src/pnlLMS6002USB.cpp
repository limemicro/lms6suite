#include "pnlLMS6002USB.h"
#include "ConnectionManager.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/spinctrl.h>

const long pnlLMS6002USB::ID_BUTTON_UPDATEALL = wxNewId();
const long pnlLMS6002USB::ID_VCXOCV = wxNewId();

BEGIN_EVENT_TABLE(pnlLMS6002USB,wxPanel)
END_EVENT_TABLE()

pnlLMS6002USB::Register::Register()
: address(0), msb(0), lsb(0), defaultValue(0)
{
}


pnlLMS6002USB::Register::Register(unsigned short address, unsigned char msb, unsigned char lsb, unsigned short defaultValue)
    : address(address), msb(msb), lsb(lsb), defaultValue(defaultValue)
{
}

pnlLMS6002USB::pnlLMS6002USB(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
    : PluginPanel(this)
{
    m_serPort = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlLMS6002USB::Initialize( ConnectionManager *pControl)
{
    m_serPort = pControl;
}

void pnlLMS6002USB::UpdatePanel()
{
    GenericPacket pkt;
    pkt.cmd = CMD_ANALOG_VAL_RD;
    pkt.outLen = 1;
    pkt.outBuffer[0] = 0x00;
    int status = STATUS_UNDEFINED;
    if(m_serPort)
        status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        int index = pkt.inBuffer[2] * 256 + pkt.inBuffer[3];
        if (index > 255)
            index = 255;
        cmbVCXOcontrolVoltage->SetSelection(index);
    }
    else
    {
        int index = 0;
        cmbVCXOcontrolVoltage->SetSelection(index);
    }
}

void pnlLMS6002USB::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{	
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 5, 5);

    wxStaticBoxSizer* namedBox = new wxStaticBoxSizer(wxVERTICAL, this, "VCXO Control Voltage");
    wxArrayString choices;
    for (int i = 0; i < 256; ++i)
        choices.push_back(wxString::Format("%.3f V", i*3.3 / 256));
    cmbVCXOcontrolVoltage = new wxComboBox(this, ID_VCXOCV, "", wxDefaultPosition, wxDefaultSize, choices);

    namedBox->Add(cmbVCXOcontrolVoltage, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    cmbVCXOcontrolVoltage->SetSelection(0);
        
    FlexGridSizer1->Add(namedBox, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
        
    Connect(ID_VCXOCV, wxEVT_COMMAND_COMBOBOX_SELECTED, (wxObjectEventFunction)&pnlLMS6002USB::ParameterChangeHandler);

    wxSize freqTextfieldSize(64, -1);
    mPanelStreamPLL = new wxPanel(this, wxNewId());
    wxFlexGridSizer* sizerPllControls = new wxFlexGridSizer(0, 3, 5, 5);
    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Tx CLK (MHz):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPllFreqTxMHz = new wxTextCtrl(mPanelStreamPLL, wxNewId(), _("61.44"), wxDefaultPosition, freqTextfieldSize);
    sizerPllControls->Add(txtPllFreqTxMHz, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    lblRealFreqTx = new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Real: ? MHz"));
    sizerPllControls->Add(lblRealFreqTx, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Rx CLK (MHz):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPllFreqRxMHz = new wxTextCtrl(mPanelStreamPLL, wxNewId(), _("61.44"), wxDefaultPosition, freqTextfieldSize);
    sizerPllControls->Add(txtPllFreqRxMHz, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    lblRealFreqRx = new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Real: ? MHz"));
    sizerPllControls->Add(lblRealFreqRx, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Tx CLK Phase (Deg):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPhaseOffsetDeg = new wxTextCtrl(mPanelStreamPLL, wxNewId(), _("90"), wxDefaultPosition, freqTextfieldSize);
    sizerPllControls->Add(txtPhaseOffsetDeg, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    btnConfigurePLL = new wxButton(mPanelStreamPLL, wxNewId(), _("Configure"));
    sizerPllControls->Add(btnConfigurePLL, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    Connect(btnConfigurePLL->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(pnlLMS6002USB::OnConfigurePLL), NULL, this);

    wxStaticBoxSizer* streamPllGroup = new wxStaticBoxSizer(wxHORIZONTAL, mPanelStreamPLL, _T("LMS6 Digital Interface Clock"));
    mPanelStreamPLL->SetSizer(streamPllGroup);
    streamPllGroup->Add(sizerPllControls, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    streamPllGroup->Fit(mPanelStreamPLL);
    FlexGridSizer1->Add(mPanelStreamPLL, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);

    wxStaticBoxSizer* bypasses = new wxStaticBoxSizer(wxVERTICAL, this, _T("Bypass"));
    chkRX_DCCORR_BYP = new wxCheckBox(this, wxNewId(), _("Rx DC corrector"));
    bypasses->Add(chkRX_DCCORR_BYP, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(chkRX_DCCORR_BYP->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    chkRX_PHCORR_BYP = new wxCheckBox(this, wxNewId(), _("Rx Phase corrector"));;
    bypasses->Add(chkRX_PHCORR_BYP, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(chkRX_PHCORR_BYP->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    chkRX_GCORR_BYP = new wxCheckBox(this, wxNewId(), _("Rx Gain corrector"));;
    bypasses->Add(chkRX_GCORR_BYP, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(chkRX_GCORR_BYP->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    chkTX_PHCORR_BYP = new wxCheckBox(this, wxNewId(), _("Tx Phase corrector"));;
    bypasses->Add(chkTX_PHCORR_BYP, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(chkTX_PHCORR_BYP->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    chkTX_GCORR_BYP = new wxCheckBox(this, wxNewId(), _("Tx Gain corrector"));;
    bypasses->Add(chkTX_GCORR_BYP, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(chkTX_GCORR_BYP->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    FlexGridSizer1->Add(bypasses, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);

    wxFlexGridSizer* tx_correctorsSizer = new wxFlexGridSizer(0, 2, 0, 5);
    wxSize spinBoxSize(64, -1);
    long spinBoxStyle = wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER;
    tx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Tx GCORRQ")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    spinTX_GCORRQ = new wxSpinCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, spinBoxSize, spinBoxStyle, 0, 255, 255);
    tx_correctorsSizer->Add(spinTX_GCORRQ, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(spinTX_GCORRQ->GetId(), wxEVT_TEXT_ENTER, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinTX_GCORRQ->GetId(), wxEVT_SPINCTRL, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinTX_GCORRQ->GetId(), wxEVT_SPIN, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    tx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Tx GCORRI")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    spinTX_GCORRI = new wxSpinCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, spinBoxSize, spinBoxStyle, 0, 255, 255);
    tx_correctorsSizer->Add(spinTX_GCORRI, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(spinTX_GCORRI->GetId(), wxEVT_TEXT_ENTER, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinTX_GCORRI->GetId(), wxEVT_SPINCTRL, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinTX_GCORRI->GetId(), wxEVT_SPIN, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    tx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Tx PHCORR")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    spinTX_PHCORR = new wxSpinCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, spinBoxSize, spinBoxStyle, -2048, 2047, 0);
    tx_correctorsSizer->Add(spinTX_PHCORR, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(spinTX_PHCORR->GetId(), wxEVT_TEXT_ENTER, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinTX_PHCORR->GetId(), wxEVT_SPINCTRL, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinTX_PHCORR->GetId(), wxEVT_SPIN, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    wxFlexGridSizer* rx_correctorsSizer = new wxFlexGridSizer(0, 2, 0, 5);
    rx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Rx GCORRQ")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    spinRX_GCORRQ = new wxSpinCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, spinBoxSize, spinBoxStyle, 0, 255, 255);;
    rx_correctorsSizer->Add(spinRX_GCORRQ, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(spinRX_GCORRQ->GetId(), wxEVT_TEXT_ENTER, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinRX_GCORRQ->GetId(), wxEVT_SPINCTRL, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinRX_GCORRQ->GetId(), wxEVT_SPIN, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    rx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Rx GCORRI")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    spinRX_GCORRI = new wxSpinCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, spinBoxSize, spinBoxStyle, 0, 255, 255);;
    rx_correctorsSizer->Add(spinRX_GCORRI, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(spinRX_GCORRI->GetId(), wxEVT_TEXT_ENTER, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinRX_GCORRI->GetId(), wxEVT_SPINCTRL, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinRX_GCORRI->GetId(), wxEVT_SPIN, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    rx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Rx PHCORR")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    spinRX_PHCORR = new wxSpinCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, spinBoxSize, spinBoxStyle, -2048, 2047, 0);
    rx_correctorsSizer->Add(spinRX_PHCORR, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(spinRX_PHCORR->GetId(), wxEVT_TEXT_ENTER, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinRX_PHCORR->GetId(), wxEVT_SPINCTRL, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);
    Connect(spinRX_PHCORR->GetId(), wxEVT_SPIN, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    rx_correctorsSizer->Add(new wxStaticText(this, wxID_ANY, _("Rx DCCORR")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    cmbRX_DCCORR = new wxComboBox(this, wxNewId(), wxEmptyString);
    for (int i = 0; i < 8; ++i)
        cmbRX_DCCORR->Append(wxString::Format(_("2^%i"), i + 12));
    cmbRX_DCCORR->SetSelection(7);
    rx_correctorsSizer->Add(cmbRX_DCCORR, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    Connect(cmbRX_DCCORR->GetId(), wxEVT_COMBOBOX, wxCommandEventHandler(pnlLMS6002USB::RegisterParameterChangeHandler), NULL, this);

    wxFlexGridSizer* correctorsSizer = new wxFlexGridSizer(0, 2, 0, 5);
    correctorsSizer->Add(tx_correctorsSizer, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    correctorsSizer->Add(rx_correctorsSizer, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);

    wxStaticBoxSizer* correctorsGroup = new wxStaticBoxSizer(wxVERTICAL, this, _T("Correctors"));
    correctorsGroup->Add(correctorsSizer, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);
    FlexGridSizer1->Add(correctorsGroup, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);

    btnUpdateAll = new wxButton(this, ID_BUTTON_UPDATEALL, _T("Refresh All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Connect(ID_BUTTON_UPDATEALL, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&pnlLMS6002USB::OnbtnUpdateAll);
    FlexGridSizer1->Add(btnUpdateAll, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);

    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Layout();

    controlsPtr2Registers.clear();
    controlsPtr2Registers[chkRX_DCCORR_BYP] = Register(0x0010, 4, 4, 0);
    controlsPtr2Registers[chkRX_PHCORR_BYP] = Register(0x0010, 3, 3, 0);
    controlsPtr2Registers[chkRX_GCORR_BYP] = Register(0x0010, 2, 2, 0);
    controlsPtr2Registers[chkTX_PHCORR_BYP] = Register(0x0010, 1, 1, 0);
    controlsPtr2Registers[chkTX_GCORR_BYP] = Register(0x0010, 0, 0, 0);

    controlsPtr2Registers[spinTX_GCORRQ] = Register(0x0011, 15, 8, 255);
    controlsPtr2Registers[spinTX_GCORRI] = Register(0x0011, 7, 0, 255);
    controlsPtr2Registers[spinTX_PHCORR] = Register(0x0012, 11, 0, 0);

    controlsPtr2Registers[spinRX_GCORRQ] = Register(0x0013, 15, 8, 255);
    controlsPtr2Registers[spinRX_GCORRI] = Register(0x0013, 7, 0, 255);
    controlsPtr2Registers[cmbRX_DCCORR] = Register(0x0014, 14, 12, 7);
    controlsPtr2Registers[spinRX_PHCORR] = Register(0x0013, 11, 0, 0);
}

void pnlLMS6002USB::RegisterParameterChangeHandler(wxCommandEvent& event)
{
    if (controlsPtr2Registers.find(event.GetEventObject()) == controlsPtr2Registers.end())
        return; //control not found in the table

    /*if (m_serPort->IsOpen() == false)
    {
        wxMessageBox(_("device not connected"), _("Error"), wxICON_ERROR | wxOK);
        return;
    }*/

    Register reg = controlsPtr2Registers[event.GetEventObject()];
    unsigned short mask = (~(~0 << (reg.msb - reg.lsb + 1))) << reg.lsb; // creates bit mask
    unsigned short regValue = m_serPort->mSPI_read(reg.address);
    regValue &= ~mask;
    regValue |= (event.GetInt() << reg.lsb) & mask;
    m_serPort->mSPI_write(reg.address, regValue);
}

pnlLMS6002USB::~pnlLMS6002USB()
{
    mPanelStreamPLL->Disconnect(wxEVT_BUTTON, btnConfigurePLL->GetId(), wxCommandEventHandler(pnlLMS6002USB::OnConfigurePLL), 0, this);
}

void pnlLMS6002USB::OnbtnUpdateAll(wxCommandEvent& event)
{
    UpdatePanel();
    map<wxObject*, Register>::iterator iter;
    wxClassInfo* spinctr = wxClassInfo::FindClass("wxSpinCtrl");
    wxClassInfo* checkboxctr = wxClassInfo::FindClass("wxCheckBox");
    wxClassInfo* comboboxctr = wxClassInfo::FindClass("wxComboBox");
    for (iter = controlsPtr2Registers.begin(); iter != controlsPtr2Registers.end(); ++iter)
    {
        Register reg = iter->second;
        unsigned short mask = (~(~0 << (reg.msb - reg.lsb + 1))) << reg.lsb; // creates bit mask
        unsigned short value = m_serPort->mSPI_read(reg.address);
        value = value & mask;
        value = value >> reg.lsb;
        if (iter->first->IsKindOf(spinctr))
            reinterpret_cast<wxSpinCtrl*>(iter->first)->SetValue(value);
        else if(iter->first->IsKindOf(checkboxctr))
            reinterpret_cast<wxCheckBox*>(iter->first)->SetValue(value);
        else if (iter->first->IsKindOf(comboboxctr))
            reinterpret_cast<wxComboBox*>(iter->first)->SetSelection(value);
    }
}

void pnlLMS6002USB::ParameterChangeHandler(wxCommandEvent& event)
{
    GenericPacket pkt;
    pkt.cmd = CMD_ANALOG_VAL_WR;
    pkt.outLen = 4;
    pkt.outBuffer[0] = 0x00;
    pkt.outBuffer[1] = 0x00;
    int value = cmbVCXOcontrolVoltage->GetSelection();
    pkt.outBuffer[2] = 0;
    pkt.outBuffer[3] = value;
    int status = STATUS_UNDEFINED;
    if (m_serPort)
        status = m_serPort->TransferPacket(pkt);
    if (status != STATUS_COMPLETED_CMD)
        wxMessageBox("Failed to send data", "Warning");
}

void pnlLMS6002USB::OnConfigurePLL(wxCommandEvent &event)
{
    double FreqTxMHz, FreqRxMHz;
    txtPllFreqTxMHz->GetValue().ToDouble(&FreqTxMHz);
    txtPllFreqRxMHz->GetValue().ToDouble(&FreqRxMHz);
    double phaseOffset;
    txtPhaseOffsetDeg->GetValue().ToDouble(&phaseOffset);
    if (ConfigurePLL(m_serPort, FreqTxMHz, FreqRxMHz, phaseOffset) != SUCCESS)
        wxMessageBox(_("Failed to configure PLL"), _("WARNING"), wxICON_ERROR | wxOK);
}

pnlLMS6002USB::Status pnlLMS6002USB::ConfigurePLL(ConnectionManager *serPort, const float fOutTx_MHz, const float fOutRx_MHz, const float phaseShift_deg)
{
    if (serPort == NULL)
        return FAILURE;
    const float vcoLimits_MHz[2] = { 650, 1250 };    
    const float Fref_Limits[] = { 5, 325 };
    const short bufSize = 64;
    unsigned char outBuffer[bufSize];
    unsigned char inBuffer[bufSize];

    float Fin_MHz = 30.72;
    //max freq 80, min 5,  defaults 61.44 15.36 90
    int N, M;
    int c0, c1, c2, c3;

    int minC = fOutTx_MHz > fOutRx_MHz ? (vcoLimits_MHz[0] / fOutTx_MHz) : (vcoLimits_MHz[0] / fOutRx_MHz);
    int maxC = fOutTx_MHz < fOutRx_MHz ? (vcoLimits_MHz[1] / fOutTx_MHz) : (vcoLimits_MHz[1] / fOutRx_MHz);  
    if (maxC > 255)
        maxC = 255;

    vector<float> deviations;
    vector<int> Ncoefs;
    vector<int> Mcoefs;
    vector<float> vcos;
    for (int i = minC; i <= maxC; ++i)
    {
        float ratio = (fOutTx_MHz*i) / Fin_MHz;
            
        M = 255 * ratio;
        N = 255;

        float NcoefDiff = (N / ratio) - (int)((N / ratio) + 0.5);
        //is integer N closer to rounding up or rounding down
        if (NcoefDiff < 0)
        {
            N = (int)((N / ratio) + 0.5) / 2;
            M = (int)((M / ratio) / 2 + 0.5);
        }
        else
        {
            N = (int)(N / ratio + 0.5);
            M = (int)(M / ratio + 0.5);
        }        
        float Fvco = Fin_MHz*M / N;
        if (Fvco < vcoLimits_MHz[0] || Fvco > vcoLimits_MHz[1])
            continue;

        if (Fin_MHz / N < Fref_Limits[0] || Fin_MHz / N > Fref_Limits[1])
            continue;

        vcos.push_back(Fvco);
        Ncoefs.push_back(N);
        Mcoefs.push_back(M);

        c0 = Fvco / 100 + 0.5;
        c1 = Fvco / fOutTx_MHz + 0.5;
        c2 = Fvco / fOutTx_MHz + 0.5;
        c3 = Fvco / fOutRx_MHz + 0.5;

        float realFX3 = Fin_MHz*M / N / c0;            
        float realTx = Fin_MHz*M / N / c1;        
        float realRx = Fin_MHz*M / N / c3;
        deviations.push_back(abs(fOutTx_MHz - realTx) + abs(fOutRx_MHz - realRx));
    }
    int minIndex = 0;
    if (deviations.size() == 0)
        return FAILURE;

    float minDeviation = deviations[0];
    float devVCO = vcos[0];
    for (int i = 0; i < deviations.size(); ++i)
    {
        if (deviations[i] < minDeviation && vcos[i] > devVCO)
        {
            minDeviation = deviations[i];
            devVCO = vcos[i];
            minIndex = i;
        }
    }

    M = Mcoefs[minIndex];
    N = Ncoefs[minIndex];
        
    float Fvco = Fin_MHz*M / N;
    c0 = Fvco / 100 + 0.5;
    c1 = Fvco / fOutTx_MHz + 0.5;
    c2 = Fvco / fOutTx_MHz + 0.5;
    c3 = Fvco / fOutRx_MHz + 0.5;

    float realTx = Fin_MHz*M / N / c1;
    float realRx = Fin_MHz*M / N / c3;

    lblRealFreqTx->SetLabel(wxString::Format(_("Real: %.3f MHz"), realTx));
    lblRealFreqRx->SetLabel(wxString::Format(_("Real: %.3f MHz"), realRx));

    short index = 8;
    memset(outBuffer, 0, bufSize);
    outBuffer[0] = CMD_BRDSPI16_WR;

    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x08;
    outBuffer[index++] = (N / 2) + (N % 2); //N_high_cnt
    outBuffer[index++] = N / 2;//N_low_cnt
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x09;
    outBuffer[index++] = (M / 2) + (M % 2); //M_high_cnt
    outBuffer[index++] = M / 2;	 //M_low_cnt

    //C0
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x0A;
    outBuffer[index++] = (c0 / 2) + (c0 % 2); //cX_high_cnt
    outBuffer[index++] = (c0) / 2;	 //cX_low_cnt

    //C1
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x0B;
    outBuffer[index++] = (c1 / 2) + (c1 % 2); //cX_high_cnt
    outBuffer[index++] = (c1) / 2;	 //cX_low_cnt

    //C2
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x0C;
    outBuffer[index++] = (c2 / 2) + (c2 % 2); //cX_high_cnt
    outBuffer[index++] = (c2) / 2;	 //cX_low_cnt

    //C3
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x0D;
    outBuffer[index++] = (c3 / 2) + (c3 % 2); //cX_high_cnt
    outBuffer[index++] = (c3) / 2;	 //cX_low_cnt

    //odd divs, bypasses
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x0F;
    outBuffer[index++] = 0x10 | ((c3 % 2) ? 0x08 : 0) | ((c2 % 2) ? 0x02 : 0); //c4_bypassed
    outBuffer[index++] = ((c1 % 2) ? 0x80 : 0x00) | ((c0 % 2) ? 0x20 : 0) | ((M % 2) ? 0x08 : 0x00) | ((N % 2) ? 0x02 : 0x00) | ((N == 1) ? 0x01 : 0x00); //N_bypassed

    float Fstep_us = 1 / (8 * fOutTx_MHz*c1);
    float Fstep_deg = (360 * Fstep_us) / (1 / fOutTx_MHz);
    short nSteps = phaseShift_deg / Fstep_deg;
    unsigned short reg2 = 0x0400 | (nSteps & 0x3FF);
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x02;
    outBuffer[index++] = (reg2 >> 8);
    outBuffer[index++] = reg2; //phase

    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x03;
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x08;

    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x03;
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x00;

    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x02;
    outBuffer[index++] = (reg2 >> 8);
    outBuffer[index++] = reg2;

    reg2 = reg2 | 0x2000;
    outBuffer[index++] = 0x00;
    outBuffer[index++] = 0x02;
    outBuffer[index++] = (reg2 >> 8);
    outBuffer[index++] = reg2;

    outBuffer[2] = index / 4;

    serPort->Port_write_direct(outBuffer, bufSize);
    long toRead = bufSize;
    serPort->Port_read_direct(inBuffer, toRead);
    if (inBuffer[1] != STATUS_COMPLETED_CMD)
        return FAILURE;
    return SUCCESS;
}
