#include "pnlLMS6002USB.h"
#include "ConnectionManager.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/string.h>

const long pnlLMS6002USB::ID_BUTTON_UPDATEALL = wxNewId();
const long pnlLMS6002USB::ID_VCXOCV = wxNewId();

BEGIN_EVENT_TABLE(pnlLMS6002USB,wxPanel)
END_EVENT_TABLE()

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
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);

    wxStaticBoxSizer* namedBox = new wxStaticBoxSizer(wxVERTICAL, this, "VCXO Control Voltage");
    wxArrayString choices;
    for (int i = 0; i < 256; ++i)
        choices.push_back(wxString::Format("%.3f V", i*3.3 / 256));
    cmbVCXOcontrolVoltage = new wxComboBox(this, ID_VCXOCV, "", wxDefaultPosition, wxDefaultSize, choices);

    namedBox->Add(cmbVCXOcontrolVoltage, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

    btnUpdateAll = new wxButton(this, ID_BUTTON_UPDATEALL, _T("Refresh"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer1->Add(btnUpdateAll, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);
    FlexGridSizer1->Add(namedBox, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	

    Connect(ID_BUTTON_UPDATEALL, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&pnlLMS6002USB::OnbtnUpdateAll);
    Connect(ID_VCXOCV, wxEVT_COMMAND_COMBOBOX_SELECTED, (wxObjectEventFunction)&pnlLMS6002USB::ParameterChangeHandler);


    mPanelStreamPLL = new wxPanel(this, wxNewId());
    wxFlexGridSizer* sizerPllControls = new wxFlexGridSizer(0, 2, 5, 5);
    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Tx Freq(MHz):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPllFreqTxMHz = new wxTextCtrl(mPanelStreamPLL, wxNewId());
    sizerPllControls->Add(txtPllFreqTxMHz, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Rx Freq(MHz):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPllFreqRxMHz = new wxTextCtrl(mPanelStreamPLL, wxNewId());
    sizerPllControls->Add(txtPllFreqRxMHz, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Phase offset(Deg):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPhaseOffsetDeg = new wxTextCtrl(mPanelStreamPLL, wxNewId());
    sizerPllControls->Add(txtPhaseOffsetDeg, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    btnConfigurePLL = new wxButton(mPanelStreamPLL, wxNewId(), _("Configure"));
    sizerPllControls->Add(btnConfigurePLL, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    Connect(btnConfigurePLL->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(pnlLMS6002USB::OnConfigurePLL), NULL, this);

    wxStaticBoxSizer* streamPllGroup = new wxStaticBoxSizer(wxHORIZONTAL, mPanelStreamPLL, _T("Stream PLL"));
    mPanelStreamPLL->SetSizer(streamPllGroup);
    streamPllGroup->Add(sizerPllControls, 1, wxALIGN_LEFT | wxALIGN_TOP, 5);
    streamPllGroup->Fit(mPanelStreamPLL);
    FlexGridSizer1->Add(mPanelStreamPLL, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 5);

    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Layout();
}

pnlLMS6002USB::~pnlLMS6002USB()
{
    mPanelStreamPLL->Disconnect(wxEVT_BUTTON, btnConfigurePLL->GetId(), wxCommandEventHandler(pnlLMS6002USB::OnConfigurePLL), 0, this);
}

void pnlLMS6002USB::OnbtnUpdateAll(wxCommandEvent& event)
{
    UpdatePanel();
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
    const float vcoLimits_MHz[2] = { 1000, 1300 };    
    const short bufSize = 64;
    unsigned char outBuffer[bufSize];
    unsigned char inBuffer[bufSize];

    float Fin_MHz = 30.72;

    int N, M;
    int c0, c1, c2, c3;
    bool c0ok, c1ok, c2ok, c3ok;
    bool success = false;
    float delta_prec = 0.1;
    for (N = 1; N<255; ++N)
    {
        float fref = Fin_MHz / N;
        for (M = 1; M<255; ++M)
        {
            c0ok = false;
            c1ok = false;
            c2ok = false;
            c3ok = false;
            float fVco = fref*M;

            if (fVco < vcoLimits_MHz[0] || fVco > vcoLimits_MHz[1])
                continue;
            for (c1 = 1; c1 < 255; ++c1)
            {
                float fout = fVco / c1;
                float delta = abs(fout - fOutTx_MHz);
                if (fout == fOutTx_MHz || delta < delta_prec)
                {
                    c1ok = true;
                    break;
                }
            }
            for (c2 = 1; c2 < 255; ++c2)
            {
                float fout = fVco / c2;
                float delta = abs(fout - fOutTx_MHz);
                if (fout == fOutTx_MHz || delta < delta_prec)
                {
                    c2ok = true;
                    break;
                }
            }
            for (c3 = 1; c3 < 255; ++c3)
            {
                float fout = fVco / c3;
                float delta = abs(fout - fOutRx_MHz);
                if (fout == fOutRx_MHz || delta < delta_prec)
                {
                    c3ok = true;
                    break;
                }
            }
            for (c0 = 1; c0 < 255; ++c0)
            {
                float fout = fVco / c0;
                float delta = fout - 100;
                if (fout == 100 || (delta < delta_prec && delta < 0 ))
                {
                    c0ok = true;
                    break;
                }
            }

            if (c0ok && c1ok && c2ok && c3ok)
                goto foundCoefs;
        }
    }
    foundCoefs:

    if (!(c0ok && c1ok && c2ok && c3ok))
        return FAILURE;

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