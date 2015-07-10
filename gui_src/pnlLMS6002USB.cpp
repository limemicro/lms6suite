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
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON_UPDATEALL, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&pnlLMS6002USB::OnbtnUpdateAll);
    Connect(ID_VCXOCV, wxEVT_COMMAND_COMBOBOX_SELECTED, (wxObjectEventFunction)&pnlLMS6002USB::ParameterChangeHandler);
}

pnlLMS6002USB::~pnlLMS6002USB()
{
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
