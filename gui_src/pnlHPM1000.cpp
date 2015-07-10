#include "pnlHPM1000.h"

//(*InternalHeaders(pnlHPM1000)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

#include "ConnectionManager.h"
#include <sstream>
#include "ComboBoxMap.h"

//(*IdInit(pnlHPM1000)
const long pnlHPM1000::ID_STATICTEXT1 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL1 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT9 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL3 = wxNewId();
const long pnlHPM1000::ID_BUTTON1 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT5 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT6 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT2 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL2 = wxNewId();
const long pnlHPM1000::ID_BUTTON2 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT3 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT7 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT8 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT14 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX1 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT10 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT11 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL5 = wxNewId();
const long pnlHPM1000::ID_BUTTON3 = wxNewId();
const long pnlHPM1000::ID_BUTTON4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT15 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT16 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT17 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT18 = wxNewId();
const long pnlHPM1000::ID_BUTTON5 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX1 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX2 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX3 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX4 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX5 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX6 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX7 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX8 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT12 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX2 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT13 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX3 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX9 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX10 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX11 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT19 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT20 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX5 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX12 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX13 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX14 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT21 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX6 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT22 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX7 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX15 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT23 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlHPM1000,wxPanel)
    EVT_CHAR_HOOK(pnlHPM1000::OnKeyDown)
	//(*EventTable(pnlHPM1000)
	//*)
END_EVENT_TABLE()

pnlHPM1000::pnlHPM1000(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
 : PluginPanel(this)
{
    m_serPort = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlHPM1000::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlHPM1000)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 5, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Write"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 7, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtWriteAddr = new wxTextCtrl(this, ID_TEXTCTRL1, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(txtWriteAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT9, _T("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtWvalue = new wxTextCtrl(this, ID_TEXTCTRL3, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer3->Add(txtWvalue, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnWrite = new wxButton(this, ID_BUTTON1, _T("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnWrite, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblWstatus = new wxStaticText(this, ID_STATICTEXT6, _T("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT6"));
	FlexGridSizer3->Add(lblWstatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Read"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 7, 0, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtReadAddr = new wxTextCtrl(this, ID_TEXTCTRL2, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer4->Add(txtReadAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnRead = new wxButton(this, ID_BUTTON2, _T("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer4->Add(btnRead, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText3, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblReadVal = new wxStaticText(this, ID_STATICTEXT4, _T("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer5->Add(lblReadVal, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _T("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer5->Add(StaticText6, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblRstatus = new wxStaticText(this, ID_STATICTEXT8, _T("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT8"));
	FlexGridSizer5->Add(lblRstatus, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("MIPI"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 10, 0, 0);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT14, _T("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer6->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbMIPIId = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbMIPIId->SetSelection( cmbMIPIId->Append(_T("0-TXRFOUT1 to RFin1 tuner")) );
	cmbMIPIId->Append(_T("1-RFout1 to RFin2 tuner"));
	cmbMIPIId->Append(_T("2-RFout2 to TXOUTPA tuner"));
	FlexGridSizer6->Add(cmbMIPIId, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _T("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer6->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtAddrMIPI = new wxTextCtrl(this, ID_TEXTCTRL4, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer6->Add(txtAddrMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT11, _T("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer6->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtValueMIPI = new wxTextCtrl(this, ID_TEXTCTRL5, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer6->Add(txtValueMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnWriteMIPI = new wxButton(this, ID_BUTTON3, _T("Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer6->Add(btnWriteMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnReadMIPI = new wxButton(this, ID_BUTTON4, _T("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer6->Add(btnReadMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT15, _T("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer1->Add(StaticText11, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblReadValMipi = new wxStaticText(this, ID_STATICTEXT16, _T("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer1->Add(lblReadValMipi, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT17, _T("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer1->Add(StaticText13, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblStatusMIPI = new wxStaticText(this, ID_STATICTEXT18, _T("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT18"));
	FlexGridSizer1->Add(lblStatusMIPI, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer12->AddGrowableCol(0);
	btnReadGPIO = new wxButton(this, ID_BUTTON5, _T("Read All Values"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer12->Add(btnReadGPIO, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("GPIO"));
	chkGPIO4 = new wxCheckBox(this, ID_CHECKBOX1, _T("GPIO4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkGPIO4->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO3 = new wxCheckBox(this, ID_CHECKBOX2, _T("GPIO3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkGPIO3->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO2 = new wxCheckBox(this, ID_CHECKBOX3, _T("GPIO2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkGPIO2->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO1 = new wxCheckBox(this, ID_CHECKBOX4, _T("GPIO1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkGPIO1->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO0 = new wxCheckBox(this, ID_CHECKBOX5, _T("GPIO0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkGPIO0->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO0, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(StaticBoxSizer4, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(FlexGridSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("0-TXRFOUT1 to RFin1 tuner"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 7, 0, 0);
	chkSW1_0 = new wxCheckBox(this, ID_CHECKBOX6, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkSW1_0->SetValue(false);
	FlexGridSizer8->Add(chkSW1_0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSW2_0 = new wxCheckBox(this, ID_CHECKBOX7, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkSW2_0->SetValue(false);
	FlexGridSizer8->Add(chkSW2_0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSW3_0 = new wxCheckBox(this, ID_CHECKBOX8, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkSW3_0->SetValue(false);
	FlexGridSizer8->Add(chkSW3_0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT12, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer8->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1_0 = new ComboBoxMap(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer8->Add(cmbDTC1_0, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer8->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2_0 = new ComboBoxMap(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer8->Add(cmbDTC2_0, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(StaticBoxSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("1-RFout1 to RFin2 tuner"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 7, 0, 0);
	chkSW1_1 = new wxCheckBox(this, ID_CHECKBOX9, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkSW1_1->SetValue(false);
	FlexGridSizer9->Add(chkSW1_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSW2_1 = new wxCheckBox(this, ID_CHECKBOX10, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkSW2_1->SetValue(false);
	FlexGridSizer9->Add(chkSW2_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSW3_1 = new wxCheckBox(this, ID_CHECKBOX11, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkSW3_1->SetValue(false);
	FlexGridSizer9->Add(chkSW3_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT19, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer9->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1_1 = new ComboBoxMap(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer9->Add(cmbDTC1_1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT20, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer9->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2_1 = new ComboBoxMap(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer9->Add(cmbDTC2_1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(FlexGridSizer9, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(StaticBoxSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("2-RFout2 to TXOUTPA tuner"));
	FlexGridSizer10 = new wxFlexGridSizer(0, 7, 0, 0);
	chkSW1_2 = new wxCheckBox(this, ID_CHECKBOX12, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkSW1_2->SetValue(false);
	FlexGridSizer10->Add(chkSW1_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSW2_2 = new wxCheckBox(this, ID_CHECKBOX13, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkSW2_2->SetValue(false);
	FlexGridSizer10->Add(chkSW2_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSW3_2 = new wxCheckBox(this, ID_CHECKBOX14, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkSW3_2->SetValue(false);
	FlexGridSizer10->Add(chkSW3_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT21, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	FlexGridSizer10->Add(StaticText16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1_2 = new ComboBoxMap(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer10->Add(cmbDTC1_2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT22, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	FlexGridSizer10->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2_2 = new ComboBoxMap(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	FlexGridSizer10->Add(cmbDTC2_2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(FlexGridSizer10, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(StaticBoxSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer13->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
	chkEnableShortcuts = new wxCheckBox(this, ID_CHECKBOX15, _T("Activate shortcuts"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	chkEnableShortcuts->SetValue(false);
	FlexGridSizer14->Add(chkEnableShortcuts, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT23, _T("While shortcuts are activated keyboard will work only for switches:\n\n1,4,7 - SW1\n2,5,8 - SW2\n3,6,9 - SW3"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer14->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer14, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(FlexGridSizer13, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(this);
	FlexGridSizer2->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnWriteClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnReadClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnWriteMIPIClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnReadMIPIClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnReadGPIOClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_0);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_0);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_0);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_0);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_0);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_1);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_1);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_1);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_1);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_1);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_2);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_2);
	Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_2);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_2);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlHPM1000::OnConfigure_2);
	//*)
	vector<cmbKeyValuePair> dtc1KeyValues;
	for(int i=0; i<=15; ++i)
        dtc1KeyValues.push_back(cmbKeyValuePair(i, wxString::Format("%i", i)));

    vector<cmbKeyValuePair> dtc2KeyValues;
	for(int i=0; i<=31; ++i)
        dtc2KeyValues.push_back(cmbKeyValuePair(i, wxString::Format("%i", i)));

    cmbDTC1_0->Set(dtc1KeyValues);
    cmbDTC1_0->SetSelection(0);
    cmbDTC1_1->Set(dtc1KeyValues);
    cmbDTC1_1->SetSelection(0);
    cmbDTC1_2->Set(dtc1KeyValues);
    cmbDTC1_2->SetSelection(0);

    cmbDTC2_0->Set(dtc2KeyValues);
    cmbDTC2_0->SetSelection(0);
    cmbDTC2_1->Set(dtc2KeyValues);
    cmbDTC2_1->SetSelection(0);
    cmbDTC2_2->Set(dtc2KeyValues);
    cmbDTC2_2->SetSelection(0);
}

pnlHPM1000::~pnlHPM1000()
{
	//(*Destroy(pnlHPM1000)
	//*)
}

void pnlHPM1000::Initialize( ConnectionManager *pControl)
{
    m_serPort = pControl;
}

void pnlHPM1000::UpdatePanel()
{
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_RD;
    pkt.outLen = 1;
    pkt.outBuffer[0] = 0x10;
    int status = m_serPort->TransferPacket(pkt);
    lblWstatus->SetLabel(status2string(status));
    if(status == STATUS_COMPLETED_CMD)
    {
        int value = pkt.inBuffer[1];
        chkGPIO0->SetValue(value & 0x1);
        chkGPIO1->SetValue((value >> 1)&0x1);
        chkGPIO2->SetValue((value >> 2)&0x1);
        chkGPIO3->SetValue((value >> 3)&0x1);
        chkGPIO4->SetValue((value >> 4)&0x1);
    }

    unsigned int value = mipiRead(0, 1);
    cmbDTC1_0->SetSelection(value);
    value = mipiRead(0, 2);
    cmbDTC2_0->SetSelection(value & 0x1F);
    chkSW1_0->SetValue( (value >> 7) & 0x1);
    chkSW2_0->SetValue( (value >> 6) & 0x1);
    chkSW3_0->SetValue( (value >> 5) & 0x1);

    value = mipiRead(1, 1);
    cmbDTC1_1->SetSelection(value);
    value = mipiRead(1, 2);
    cmbDTC2_1->SetSelection(value & 0x1F);
    chkSW1_1->SetValue( (value >> 7) & 0x1);
    chkSW2_1->SetValue( (value >> 6) & 0x1);
    chkSW3_1->SetValue( (value >> 5) & 0x1);

    value = mipiRead(2, 1);
    cmbDTC1_2->SetSelection(value);
    value = mipiRead(2, 2);
    cmbDTC2_2->SetSelection(value & 0x1F);
    chkSW1_2->SetValue( (value >> 7) & 0x1);
    chkSW2_2->SetValue( (value >> 6) & 0x1);
    chkSW3_2->SetValue( (value >> 5) & 0x1);
}

void pnlHPM1000::OnchkGPIOClick(wxCommandEvent& event)
{
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outLen = 2;
    pkt.outBuffer[0] = 0x10;
    pkt.outBuffer[1] = chkGPIO0->GetValue();
    pkt.outBuffer[1] |= chkGPIO1->GetValue() << 1;
    pkt.outBuffer[1] |= chkGPIO2->GetValue() << 2;
    pkt.outBuffer[1] |= chkGPIO3->GetValue() << 3;
    pkt.outBuffer[1] |= chkGPIO4->GetValue() << 4;
    int status = m_serPort->TransferPacket(pkt);
    lblWstatus->SetLabel(status2string(status));
}

void pnlHPM1000::OnbtnWriteClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
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

void pnlHPM1000::OnbtnReadClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    stringstream ss;
    ss.str( txtReadAddr->GetValue().ToStdString() );
    string address = txtReadAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_RD;
    pkt.outBuffer[0] = sample & 0xFF;
    pkt.outLen = 1;
    int status = m_serPort->TransferPacket(pkt);
    lblRstatus->SetLabel(status2string(status));

    wxString txthex = "";
    txthex= wxString::Format("%02X", pkt.inBuffer[1]);
    lblReadVal->SetLabel(txthex);
}

void pnlHPM1000::OnbtnWriteMIPIClick(wxCommandEvent& event)
{
    unsigned int mipiId = cmbMIPIId->GetSelection();
    unsigned int mipiAddr = 0;
    unsigned int mipiValue = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    string address = txtAddrMIPI->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &mipiAddr);
    string value = txtValueMIPI->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &mipiValue);
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = mipiId;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = mipiAddr;
    pkt.outBuffer[4] = 0x22;
    pkt.outBuffer[5] = mipiValue;
    pkt.outBuffer[6] = 0x23;
    pkt.outBuffer[7] = 0x02; //write bit
    pkt.outLen = 8;
    int status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        pkt.cmd = CMD_MYRIAD_RD;
        pkt.outBuffer[0] = 0x24;
        pkt.outLen = 1;
        int status = m_serPort->TransferPacket(pkt);
        if(status == STATUS_COMPLETED_CMD)
        {
            lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[1]));
        }
        else
            lblStatusMIPI->SetLabel(status2string(status));
    }
    else
        lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[status]));
}

void pnlHPM1000::OnbtnReadMIPIClick(wxCommandEvent& event)
{
    unsigned int mipiId = cmbMIPIId->GetSelection();
    unsigned int mipiAddr = 0;
    string address = txtAddrMIPI->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &mipiAddr);
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = mipiId;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = mipiAddr;
    pkt.outBuffer[4] = 0x23;
    pkt.outBuffer[5] = 0x01; //read bits
    pkt.outLen = 6;
    if( m_serPort->TransferPacket(pkt) == STATUS_COMPLETED_CMD)
        lblStatusMIPI->SetLabel("Read ok");
    else
        lblStatusMIPI->SetLabel("Read failed");

    pkt.cmd = CMD_MYRIAD_RD;
    pkt.outBuffer[0] = 0x22;
    pkt.outBuffer[1] = 0x24;
    pkt.outLen = 2;
    int status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[3]));
        wxString txthex = "";
        txthex= wxString::Format("%02X", pkt.inBuffer[1]);
        lblReadValMipi->SetLabel(txthex);
    }
    else
        lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[status]));
}


void pnlHPM1000::OnbtnReadGPIOClick(wxCommandEvent& event)
{
    UpdatePanel();
}

void pnlHPM1000::OnConfigure_0(wxCommandEvent& event)
{
    bool sw1 = chkSW1_0->IsChecked();
    bool sw2 = chkSW2_0->IsChecked();
    bool sw3 = chkSW3_0->IsChecked();
    unsigned dtc1 = cmbDTC1_0->GetSelection();
    unsigned dtc2 = cmbDTC2_0->GetSelection();
    if(ConfigurePE636040(0, sw1, sw2, sw3, dtc1, dtc2) != 0)
        wxMessageBox("Failed to configure TXRFOUT1 to RFin1 tuner.", "ERROR");
}

void pnlHPM1000::OnConfigure_1(wxCommandEvent& event)
{
    bool sw1 = chkSW1_1->IsChecked();
    bool sw2 = chkSW2_1->IsChecked();
    bool sw3 = chkSW3_1->IsChecked();
    unsigned dtc1 = cmbDTC1_1->GetSelection();
    unsigned dtc2 = cmbDTC2_1->GetSelection();
    if(ConfigurePE636040(1, sw1, sw2, sw3, dtc1, dtc2) != 0)
        wxMessageBox("Failed to configure RFout1 to RFin2 tuner", "ERROR");
}

void pnlHPM1000::OnConfigure_2(wxCommandEvent& event)
{
    bool sw1 = chkSW1_2->IsChecked();
    bool sw2 = chkSW2_2->IsChecked();
    bool sw3 = chkSW3_2->IsChecked();
    unsigned dtc1 = cmbDTC1_2->GetSelection();
    unsigned dtc2 = cmbDTC2_2->GetSelection();
    if(ConfigurePE636040(2, sw1, sw2, sw3, dtc1, dtc2) != 0)
        wxMessageBox("Failed to configure RFout2 to TXOUTPA tuner.", "ERROR");
}

/** @brief writes configuration to PE636040
    @return 0: success, -1: failure
*/
int pnlHPM1000::ConfigurePE636040(unsigned id, bool sw1, bool sw2, bool sw3, unsigned dtc1, unsigned dtc2)
{
    unsigned int mipiId = id;
    unsigned int mipiValue1 = dtc1;
    unsigned int mipiValue2 = sw1 << 7 | sw2 << 6 | sw3 << 5 | (dtc2&0x1F);
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = mipiId;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = 0x01; //mipi address
    pkt.outBuffer[4] = 0x22;
    pkt.outBuffer[5] = mipiValue1;
    pkt.outBuffer[6] = 0x23;
    pkt.outBuffer[7] = 0x02; //write bit
    pkt.outLen = 8;
    int status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        pkt.cmd = CMD_MYRIAD_RD;
        pkt.outBuffer[0] = 0x24;
        pkt.outLen = 1;
        int status = m_serPort->TransferPacket(pkt);
        if(status != STATUS_COMPLETED_CMD)
            return -1;
    }
    else
        return -1;

    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = mipiId;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = 0x02; //mipi address
    pkt.outBuffer[4] = 0x22;
    pkt.outBuffer[5] = mipiValue2;
    pkt.outBuffer[6] = 0x23;
    pkt.outBuffer[7] = 0x02; //write bit
    pkt.outLen = 8;
    status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        pkt.cmd = CMD_MYRIAD_RD;
        pkt.outBuffer[0] = 0x24;
        pkt.outLen = 1;
        int status = m_serPort->TransferPacket(pkt);
        if(status != STATUS_COMPLETED_CMD)
            return -1;
    }
    else
        return -1;
    return 0;
}

unsigned int pnlHPM1000::mipiRead(unsigned id, unsigned addr)
{
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = id;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = addr;
    pkt.outBuffer[4] = 0x23;
    pkt.outBuffer[5] = 0x01; //read bits
    pkt.outLen = 6;
    if( m_serPort->TransferPacket(pkt) == STATUS_COMPLETED_CMD)
    {
        pkt.cmd = CMD_MYRIAD_RD;
        pkt.outBuffer[0] = 0x22;
        pkt.outBuffer[1] = 0x24;
        pkt.outLen = 2;
        int status = m_serPort->TransferPacket(pkt);
        if(status == STATUS_COMPLETED_CMD)
            return pkt.inBuffer[1];
    }
    return 0;
}

void pnlHPM1000::OnKeyDown(wxKeyEvent& event)
{
    if(chkEnableShortcuts->IsChecked() == false)
    {
        event.Skip();
        return;
    }
    printf("key down\n");
    wxCommandEvent evt;
    if(event.GetKeyCode() == '7' || event.GetKeyCode() == WXK_NUMPAD7)
    {
        chkSW1_0->SetValue(!chkSW1_0->GetValue());
        OnConfigure_0(evt);
    }
    if(event.GetKeyCode() == '8' || event.GetKeyCode() == WXK_NUMPAD8)
    {
        chkSW2_0->SetValue(!chkSW2_0->GetValue());
        OnConfigure_0(evt);
    }
    if(event.GetKeyCode() == '9' || event.GetKeyCode() == WXK_NUMPAD9)
    {
        chkSW3_0->SetValue(!chkSW3_0->GetValue());
        OnConfigure_0(evt);
    }

    if(event.GetKeyCode() == '4' || event.GetKeyCode() == WXK_NUMPAD4)
    {
        chkSW1_1->SetValue(!chkSW1_1->GetValue());
        OnConfigure_1(evt);
    }
    if(event.GetKeyCode() == '5' || event.GetKeyCode() == WXK_NUMPAD5)
    {
        chkSW2_1->SetValue(!chkSW2_1->GetValue());
        OnConfigure_1(evt);
    }
    if(event.GetKeyCode() == '6' || event.GetKeyCode() == WXK_NUMPAD6)
    {
        chkSW3_1->SetValue(!chkSW3_1->GetValue());
        OnConfigure_1(evt);
    }

    if(event.GetKeyCode() == '1' || event.GetKeyCode() == WXK_NUMPAD1)
    {
        chkSW1_2->SetValue(!chkSW1_2->GetValue());
        OnConfigure_2(evt);
    }
    if(event.GetKeyCode() == '2' || event.GetKeyCode() == WXK_NUMPAD2)
    {
        chkSW2_2->SetValue(!chkSW2_2->GetValue());
        OnConfigure_2(evt);
    }
    if(event.GetKeyCode() == '3' || event.GetKeyCode() == WXK_NUMPAD3)
    {
        chkSW3_2->SetValue(!chkSW3_2->GetValue());
        OnConfigure_2(evt);
    }
}

void pnlHPM1000::OnKeyUp(wxKeyEvent& event)
{

}
