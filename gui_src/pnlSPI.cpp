// -----------------------------------------------------------------------------
// FILE: 		pnlSPI.cpp
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "pnlSPI.h"
#include "CommonUtilities.h"
#include "LMS6002_MainControl.h"
#include "ConnectionManager.h"
#include "RegistersMap.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <wx/filedlg.h>

extern unsigned char bestOfThree(const unsigned char A, const unsigned char B, const unsigned char C);

//(*InternalHeaders(pnlSPI)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSPI)
const long pnlSPI::ID_STATICTEXT1 = wxNewId();
const long pnlSPI::ID_TEXTCTRL1 = wxNewId();
const long pnlSPI::ID_STATICTEXT9 = wxNewId();
const long pnlSPI::ID_TEXTCTRL3 = wxNewId();
const long pnlSPI::ID_BUTTON1 = wxNewId();
const long pnlSPI::ID_STATICTEXT5 = wxNewId();
const long pnlSPI::ID_STATICTEXT6 = wxNewId();
const long pnlSPI::ID_STATICTEXT2 = wxNewId();
const long pnlSPI::ID_TEXTCTRL2 = wxNewId();
const long pnlSPI::ID_BUTTON2 = wxNewId();
const long pnlSPI::ID_STATICTEXT3 = wxNewId();
const long pnlSPI::ID_STATICTEXT4 = wxNewId();
const long pnlSPI::ID_STATICTEXT7 = wxNewId();
const long pnlSPI::ID_STATICTEXT8 = wxNewId();
const long pnlSPI::ID_STATICTEXT10 = wxNewId();
const long pnlSPI::ID_TEXTCTRL4 = wxNewId();
const long pnlSPI::ID_STATICTEXT11 = wxNewId();
const long pnlSPI::ID_TEXTCTRL5 = wxNewId();
const long pnlSPI::ID_BUTTON3 = wxNewId();
const long pnlSPI::ID_STATICTEXT12 = wxNewId();
const long pnlSPI::ID_STATICTEXT13 = wxNewId();
const long pnlSPI::ID_STATICTEXT14 = wxNewId();
const long pnlSPI::ID_TEXTCTRL6 = wxNewId();
const long pnlSPI::ID_BUTTON4 = wxNewId();
const long pnlSPI::ID_STATICTEXT15 = wxNewId();
const long pnlSPI::ID_STATICTEXT16 = wxNewId();
const long pnlSPI::ID_STATICTEXT17 = wxNewId();
const long pnlSPI::ID_STATICTEXT18 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSPI,wxPanel)
    //(*EventTable(pnlSPI)
    //*)
END_EVENT_TABLE()

pnlSPI::pnlSPI(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name):
    PluginPanel(this)
{
    m_serPort = NULL;
    BuildContent(parent, id);
}

void pnlSPI::Initialize(ConnectionManager *pControl)
{
    m_serPort = pControl;
}

void pnlSPI::BuildContent(wxWindow* parent, wxWindowID id)
{
    //(*Initialize(pnlSPI)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer5;

    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LMS SPI"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 5, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Write"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWriteAddr = new wxTextCtrl(this, ID_TEXTCTRL1, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer3->Add(txtWriteAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT9, _("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWvalue = new wxTextCtrl(this, ID_TEXTCTRL3, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer3->Add(txtWvalue, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnWrite = new wxButton(this, ID_BUTTON1, _("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(btnWrite, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblWstatus = new wxStaticText(this, ID_STATICTEXT6, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT6"));
    FlexGridSizer3->Add(lblWstatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Read"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtReadAddr = new wxTextCtrl(this, ID_TEXTCTRL2, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer4->Add(txtReadAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRead = new wxButton(this, ID_BUTTON2, _("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer4->Add(btnRead, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer5->Add(StaticText3, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblReadVal = new wxStaticText(this, ID_STATICTEXT4, _("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer5->Add(lblReadVal, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer5->Add(StaticText6, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblRstatus = new wxStaticText(this, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT8"));
    FlexGridSizer5->Add(lblRstatus, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Board SPI"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 5, 0);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Write"));
    FlexGridSizer7 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer7->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWriteAddrBrd = new wxTextCtrl(this, ID_TEXTCTRL4, _("FFFF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    FlexGridSizer7->Add(txtWriteAddrBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT11, _("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer7->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWvalueBrd = new wxTextCtrl(this, ID_TEXTCTRL5, _("FFFF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    FlexGridSizer7->Add(txtWvalueBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnWriteBrd = new wxButton(this, ID_BUTTON3, _("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer7->Add(btnWriteBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT12, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer7->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblWstatusBrd = new wxStaticText(this, ID_STATICTEXT13, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT13"));
    FlexGridSizer7->Add(lblWstatusBrd, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Read"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT14, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer8->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtReadAddrBrd = new wxTextCtrl(this, ID_TEXTCTRL6, _("FFFF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    FlexGridSizer8->Add(txtReadAddrBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnReadBrd = new wxButton(this, ID_BUTTON4, _("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer8->Add(btnReadBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT15, _("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer9->Add(StaticText12, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblReadValBrd = new wxStaticText(this, ID_STATICTEXT16, _("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer9->Add(lblReadValBrd, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(this, ID_STATICTEXT17, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer9->Add(StaticText14, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblRstatusBrd = new wxStaticText(this, ID_STATICTEXT18, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT18"));
    FlexGridSizer9->Add(lblRstatusBrd, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer9, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWriteClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnReadClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWriteBrdClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnReadBrdClick);
    //*)
}

pnlSPI::~pnlSPI()
{
    //(*Destroy(pnlSPI)
    //*)
}


void pnlSPI::OnbtnWriteClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
    pkt.outLen = 2;
    string address = txtWriteAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    pkt.outBuffer[0] = sample & 0xFF;
    string value = txtWvalue->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    pkt.outBuffer[1] = sample & 0xFF;
    int status = m_serPort->TransferPacket(pkt);
    lblWstatus->SetLabel(status2string(status));
}

void pnlSPI::OnbtnReadClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    stringstream ss;
    ss.str( txtReadAddr->GetValue().ToStdString() );
    string address = txtReadAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_RD;
    pkt.outBuffer[0] = sample & 0xFF;
    pkt.outLen = 1;

    int status = m_serPort->TransferPacket(pkt);
    lblRstatus->SetLabel(status2string(status));

    wxString txthex = "";
    txthex= wxString::Format("%02X", pkt.inBuffer[1]);
    lblReadVal->SetLabel(txthex);
}

void pnlSPI::OnbtnWriteBrdClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_BRDSPI16_WR;
    pkt.outLen = sizeof(unsigned short)*2;
    string address = txtWriteAddrBrd->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    sample &= 0xFFFF;
    memcpy(pkt.outBuffer, &sample, sizeof(unsigned short));
    string value = txtWvalueBrd->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    sample &= 0xFFFF;
    memcpy(pkt.outBuffer+sizeof(unsigned short), &sample, sizeof(unsigned short));
    int status = m_serPort->TransferPacket(pkt);
    lblWstatusBrd->SetLabel(status2string(status));
}

void pnlSPI::OnbtnReadBrdClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    string address = txtReadAddrBrd->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    GenericPacket pkt;
    pkt.cmd = CMD_BRDSPI16_RD;
    sample &= 0xFFFF;
    memcpy(pkt.outBuffer, &sample, sizeof(unsigned short));
    pkt.outLen = sizeof(unsigned short);

    int status = m_serPort->TransferPacket(pkt);
    lblRstatusBrd->SetLabel(status2string(status));

    wxString txthex = "";
    unsigned short val = *(unsigned short*)&pkt.inBuffer[2];
    txthex= wxString::Format("%04X", val);
    lblReadValBrd->SetLabel(txthex);
}
