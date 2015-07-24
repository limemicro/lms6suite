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
    wxFlexGridSizer* sizerPllControls = new wxFlexGridSizer(0, 3, 5, 5);
    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Tx Freq(MHz):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPllFreqTxMHz = new wxTextCtrl(mPanelStreamPLL, wxNewId(), _("61.44"));
    sizerPllControls->Add(txtPllFreqTxMHz, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    lblRealFreqTx = new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Real: ? MHz"));
    sizerPllControls->Add(lblRealFreqTx, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Rx Freq(MHz):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPllFreqRxMHz = new wxTextCtrl(mPanelStreamPLL, wxNewId(), _("15.36"));
    sizerPllControls->Add(txtPllFreqRxMHz, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    lblRealFreqRx = new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Real: ? MHz"));
    sizerPllControls->Add(lblRealFreqRx, 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

    sizerPllControls->Add(new wxStaticText(mPanelStreamPLL, wxID_ANY, _("Phase offset(Deg):")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtPhaseOffsetDeg = new wxTextCtrl(mPanelStreamPLL, wxNewId(), _("90"));
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