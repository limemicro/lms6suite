#include "pnlADF4002.h"

//(*InternalHeaders(pnlADF4002)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "ADF_module.h"

//(*IdInit(pnlADF4002)
const long pnlADF4002::ID_STATICTEXT1 = wxNewId();
const long pnlADF4002::ID_STATICTEXT2 = wxNewId();
const long pnlADF4002::ID_STATICTEXT3 = wxNewId();
const long pnlADF4002::ID_COMBOBOX1 = wxNewId();
const long pnlADF4002::ID_COMBOBOX2 = wxNewId();
const long pnlADF4002::ID_SPINCTRL1 = wxNewId();
const long pnlADF4002::ID_STATICTEXT4 = wxNewId();
const long pnlADF4002::ID_STATICTEXT5 = wxNewId();
const long pnlADF4002::ID_COMBOBOX3 = wxNewId();
const long pnlADF4002::ID_SPINCTRL2 = wxNewId();
const long pnlADF4002::ID_STATICTEXT6 = wxNewId();
const long pnlADF4002::ID_STATICTEXT7 = wxNewId();
const long pnlADF4002::ID_COMBOBOX4 = wxNewId();
const long pnlADF4002::ID_COMBOBOX5 = wxNewId();
const long pnlADF4002::ID_STATICTEXT8 = wxNewId();
const long pnlADF4002::ID_STATICTEXT9 = wxNewId();
const long pnlADF4002::ID_COMBOBOX6 = wxNewId();
const long pnlADF4002::ID_COMBOBOX7 = wxNewId();
const long pnlADF4002::ID_STATICTEXT10 = wxNewId();
const long pnlADF4002::ID_COMBOBOX8 = wxNewId();
const long pnlADF4002::ID_RADIOBOX1 = wxNewId();
const long pnlADF4002::ID_RADIOBOX2 = wxNewId();
const long pnlADF4002::ID_RADIOBOX3 = wxNewId();
const long pnlADF4002::ID_RADIOBOX4 = wxNewId();
const long pnlADF4002::ID_RADIOBOX5 = wxNewId();
const long pnlADF4002::ID_STATICTEXT17 = wxNewId();
const long pnlADF4002::ID_STATICTEXT18 = wxNewId();
const long pnlADF4002::ID_COMBOBOX9 = wxNewId();
const long pnlADF4002::ID_COMBOBOX10 = wxNewId();
const long pnlADF4002::ID_STATICTEXT19 = wxNewId();
const long pnlADF4002::ID_STATICTEXT20 = wxNewId();
const long pnlADF4002::ID_COMBOBOX11 = wxNewId();
const long pnlADF4002::ID_COMBOBOX12 = wxNewId();
const long pnlADF4002::ID_STATICTEXT21 = wxNewId();
const long pnlADF4002::ID_COMBOBOX13 = wxNewId();
const long pnlADF4002::ID_RADIOBOX6 = wxNewId();
const long pnlADF4002::ID_RADIOBOX7 = wxNewId();
const long pnlADF4002::ID_RADIOBOX8 = wxNewId();
const long pnlADF4002::ID_RADIOBOX9 = wxNewId();
const long pnlADF4002::ID_RADIOBOX10 = wxNewId();
const long pnlADF4002::ID_STATICTEXT11 = wxNewId();
const long pnlADF4002::ID_STATICTEXT12 = wxNewId();
const long pnlADF4002::ID_TEXTCTRL1 = wxNewId();
const long pnlADF4002::ID_TEXTCTRL2 = wxNewId();
const long pnlADF4002::ID_STATICTEXT13 = wxNewId();
const long pnlADF4002::ID_STATICTEXT14 = wxNewId();
const long pnlADF4002::ID_STATICTEXT15 = wxNewId();
const long pnlADF4002::ID_STATICTEXT16 = wxNewId();
const long pnlADF4002::ID_BUTTON1 = wxNewId();
const long pnlADF4002::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlADF4002,wxPanel)
	//(*EventTable(pnlADF4002)
	//*)
END_EVENT_TABLE()

pnlADF4002::pnlADF4002(ADF_module* pModule, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name):
    PluginPanel(this)
{
    control = pModule;
	BuildContent(parent,id,pos,size);
}

void pnlADF4002::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlADF4002)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer15;
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
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADF4002"));
	FlexGridSizer3 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer4->AddGrowableCol(0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Reference Counter Latch"));
	FlexGridSizer5 = new wxFlexGridSizer(2, 3, 0, 5);
	FlexGridSizer5->AddGrowableCol(0);
	FlexGridSizer5->AddGrowableCol(1);
	FlexGridSizer5->AddGrowableCol(2);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Lock Detect Precision:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Anti-Backlash:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer5->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Reference Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbLDP = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbLDP->SetSelection( cmbLDP->Append(_("Three Cycles")) );
	cmbLDP->Append(_("Five Cycles"));
	FlexGridSizer5->Add(cmbLDP, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbABW = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	cmbABW->SetSelection( cmbABW->Append(_("2.9ns")) );
	cmbABW->Append(_("6.0ns"));
	cmbABW->Append(_("2.9ns"));
	FlexGridSizer5->Add(cmbABW, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinRCnt = new wxSpinCtrl(this, ID_SPINCTRL1, _T("125"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000000000, 125, _T("ID_SPINCTRL1"));
	spinRCnt->SetValue(_T("125"));
	FlexGridSizer5->Add(spinRCnt, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("N Counter Latch"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 2, 0, 5);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableCol(1);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("CP Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("N Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCPG = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(65,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	cmbCPG->SetSelection( cmbCPG->Append(_("0")) );
	cmbCPG->Append(_("1"));
	FlexGridSizer6->Add(cmbCPG, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinNCnt = new wxSpinCtrl(this, ID_SPINCTRL2, _T("384"), wxDefaultPosition, wxSize(70,-1), 0, 0, 1000000000, 384, _T("ID_SPINCTRL2"));
	spinNCnt->SetValue(_T("384"));
	FlexGridSizer6->Add(spinNCnt, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Function Latch"));
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer8 = new wxFlexGridSizer(4, 2, 0, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Current Setting 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer8->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Timer Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer8->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS1_f = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	cmbCS1_f->Append(_("0"));
	cmbCS1_f->Append(_("1"));
	cmbCS1_f->Append(_("2"));
	cmbCS1_f->Append(_("3"));
	cmbCS1_f->Append(_("4"));
	cmbCS1_f->Append(_("5"));
	cmbCS1_f->Append(_("6"));
	cmbCS1_f->SetSelection( cmbCS1_f->Append(_("7")) );
	FlexGridSizer8->Add(cmbCS1_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbTC_f = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	cmbTC_f->SetSelection( cmbTC_f->Append(_("3")) );
	cmbTC_f->Append(_("7"));
	cmbTC_f->Append(_("11"));
	cmbTC_f->Append(_("15"));
	cmbTC_f->Append(_("19"));
	cmbTC_f->Append(_("23"));
	cmbTC_f->Append(_("27"));
	cmbTC_f->Append(_("31"));
	cmbTC_f->Append(_("35"));
	cmbTC_f->Append(_("39"));
	cmbTC_f->Append(_("43"));
	cmbTC_f->Append(_("47"));
	cmbTC_f->Append(_("51"));
	cmbTC_f->Append(_("55"));
	cmbTC_f->Append(_("59"));
	cmbTC_f->Append(_("63"));
	FlexGridSizer8->Add(cmbTC_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Current Setting 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer8->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Fastlock:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer8->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS2_f = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	cmbCS2_f->Append(_("0"));
	cmbCS2_f->Append(_("1"));
	cmbCS2_f->Append(_("2"));
	cmbCS2_f->Append(_("3"));
	cmbCS2_f->Append(_("4"));
	cmbCS2_f->Append(_("5"));
	cmbCS2_f->Append(_("6"));
	cmbCS2_f->SetSelection( cmbCS2_f->Append(_("7")) );
	FlexGridSizer8->Add(cmbCS2_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbFL_f = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	cmbFL_f->SetSelection( cmbFL_f->Append(_("Disabled")) );
	cmbFL_f->Append(_("Mode 1"));
	cmbFL_f->Append(_("Mode 2"));
	FlexGridSizer8->Add(cmbFL_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(3, 1, 0, 0);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Muxout Control"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer9->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbMOC_f = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	cmbMOC_f->Append(_("Three-State Output"));
	cmbMOC_f->SetSelection( cmbMOC_f->Append(_("Digital Lock Detect")) );
	cmbMOC_f->Append(_("N Divider Output"));
	cmbMOC_f->Append(_("DVdd"));
	cmbMOC_f->Append(_("R Divider Output"));
	cmbMOC_f->Append(_("N-Chan OD Lock Detect"));
	cmbMOC_f->Append(_("Serial Data Output"));
	cmbMOC_f->Append(_("DGND"));
	FlexGridSizer9->Add(cmbMOC_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Negative"),
		_("Positive")
	};
	rgrPDP_f = new wxRadioBox(this, ID_RADIOBOX1, _("PD Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrPDP_f->SetSelection(1);
	FlexGridSizer9->Add(rgrPDP_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer10 = new wxFlexGridSizer(2, 2, 0, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("0"),
		_("1")
	};
	rgrPD1_f = new wxRadioBox(this, ID_RADIOBOX2, _("PD1"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrPD1_f->SetSelection(0);
	FlexGridSizer10->Add(rgrPD1_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Normal"),
		_("R && N Reset")
	};
	rgrCR_f = new wxRadioBox(this, ID_RADIOBOX3, _("Counter Reset"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX3"));
	rgrCR_f->SetSelection(0);
	FlexGridSizer10->Add(rgrCR_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("0"),
		_("1")
	};
	rgrPD2_f = new wxRadioBox(this, ID_RADIOBOX4, _("PD2"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX4"));
	rgrPD2_f->SetSelection(0);
	FlexGridSizer10->Add(rgrPD2_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[2] =
	{
		_("Normal"),
		_("Three-State")
	};
	rgrCPS_f = new wxRadioBox(this, ID_RADIOBOX5, _("CP State"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	rgrCPS_f->SetSelection(0);
	FlexGridSizer10->Add(rgrCPS_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Initialization Latch"));
	FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer14 = new wxFlexGridSizer(4, 2, 0, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT17, _("Current Setting 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer14->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT18, _("Timer Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer14->Add(StaticText16, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS1_i = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
	cmbCS1_i->Append(_("0"));
	cmbCS1_i->Append(_("1"));
	cmbCS1_i->Append(_("2"));
	cmbCS1_i->Append(_("3"));
	cmbCS1_i->Append(_("4"));
	cmbCS1_i->Append(_("5"));
	cmbCS1_i->Append(_("6"));
	cmbCS1_i->SetSelection( cmbCS1_i->Append(_("7")) );
	FlexGridSizer14->Add(cmbCS1_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbTC_i = new wxComboBox(this, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX10"));
	cmbTC_i->SetSelection( cmbTC_i->Append(_("3")) );
	cmbTC_i->Append(_("7"));
	cmbTC_i->Append(_("11"));
	cmbTC_i->Append(_("15"));
	cmbTC_i->Append(_("19"));
	cmbTC_i->Append(_("23"));
	cmbTC_i->Append(_("27"));
	cmbTC_i->Append(_("31"));
	cmbTC_i->Append(_("35"));
	cmbTC_i->Append(_("39"));
	cmbTC_i->Append(_("43"));
	cmbTC_i->Append(_("47"));
	cmbTC_i->Append(_("51"));
	cmbTC_i->Append(_("55"));
	cmbTC_i->Append(_("59"));
	cmbTC_i->Append(_("63"));
	FlexGridSizer14->Add(cmbTC_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT19, _("Current Setting 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer14->Add(StaticText17, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT20, _("Fastlock:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer14->Add(StaticText18, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS2_i = new wxComboBox(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
	cmbCS2_i->Append(_("0"));
	cmbCS2_i->Append(_("1"));
	cmbCS2_i->Append(_("2"));
	cmbCS2_i->Append(_("3"));
	cmbCS2_i->Append(_("4"));
	cmbCS2_i->Append(_("5"));
	cmbCS2_i->Append(_("6"));
	cmbCS2_i->SetSelection( cmbCS2_i->Append(_("7")) );
	FlexGridSizer14->Add(cmbCS2_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbFL_i = new wxComboBox(this, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX12"));
	cmbFL_i->SetSelection( cmbFL_i->Append(_("Disabled")) );
	cmbFL_i->Append(_("Mode 1"));
	cmbFL_i->Append(_("Mode 2"));
	FlexGridSizer14->Add(cmbFL_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer15 = new wxFlexGridSizer(3, 1, 0, 0);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT21, _("Muxout Control"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	FlexGridSizer15->Add(StaticText19, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbMOC_i = new wxComboBox(this, ID_COMBOBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX13"));
	cmbMOC_i->Append(_("Three-State Output"));
	cmbMOC_i->SetSelection( cmbMOC_i->Append(_("Digital Lock Detect")) );
	cmbMOC_i->Append(_("N Divider Output"));
	cmbMOC_i->Append(_("DVdd"));
	cmbMOC_i->Append(_("R Divider Output"));
	cmbMOC_i->Append(_("N-Chan OD Lock Detect"));
	cmbMOC_i->Append(_("Serial Data Output"));
	cmbMOC_i->Append(_("DGND"));
	FlexGridSizer15->Add(cmbMOC_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("Negative"),
		_("Positive")
	};
	rgrPDP_i = new wxRadioBox(this, ID_RADIOBOX6, _("PD Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_6, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	rgrPDP_i->SetSelection(0);
	FlexGridSizer15->Add(rgrPDP_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer15, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer16 = new wxFlexGridSizer(2, 2, 0, 5);
	wxString __wxRadioBoxChoices_7[2] =
	{
		_("0"),
		_("1")
	};
	rgrPD1_i = new wxRadioBox(this, ID_RADIOBOX7, _("PD1"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_7, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX7"));
	rgrPD1_i->SetSelection(0);
	FlexGridSizer16->Add(rgrPD1_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_8[2] =
	{
		_("Normal"),
		_("R && N Reset")
	};
	rgrCR_i = new wxRadioBox(this, ID_RADIOBOX8, _("Counter Reset"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_8, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX8"));
	rgrCR_i->SetSelection(0);
	FlexGridSizer16->Add(rgrCR_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_9[2] =
	{
		_("0"),
		_("1")
	};
	rgrPD2_i = new wxRadioBox(this, ID_RADIOBOX9, _("PD2"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_9, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX9"));
	rgrPD2_i->SetSelection(0);
	FlexGridSizer16->Add(rgrPD2_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_10[2] =
	{
		_("Normal"),
		_("Three-State")
	};
	rgrCPS_i = new wxRadioBox(this, ID_RADIOBOX10, _("CP State"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_10, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX10"));
	rgrCPS_i->SetSelection(0);
	FlexGridSizer16->Add(rgrCPS_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer16, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Calculation of R & N"));
	FlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer11 = new wxFlexGridSizer(4, 2, 0, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Fref, MHz"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer11->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Fvco, MHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer11->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txtFref = new wxTextCtrl(this, ID_TEXTCTRL1, _("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer11->Add(txtFref, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFvco = new wxTextCtrl(this, ID_TEXTCTRL2, _("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer11->Add(txtFvco, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Fvco (MHz) ="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer11->Add(StaticText13, 1, wxTOP|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco = new wxStaticText(this, ID_STATICTEXT14, _("Fvco"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer11->Add(lblFvco, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("LCM ="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer11->Add(StaticText15, 1, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblFcomp = new wxStaticText(this, ID_STATICTEXT16, _("Fcomp"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer11->Add(lblFcomp, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer11, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCalcSend = new wxButton(this, ID_BUTTON1, _("Calculate R, N && Upload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer12->Add(btnCalcSend, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSend = new wxButton(this, ID_BUTTON2, _("Upload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer12->Add(btnSend, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxLEFT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlADF4002::OnbtnCalcSendClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlADF4002::OnbtnSendClick);
	//*)
}

pnlADF4002::~pnlADF4002()
{
	//(*Destroy(pnlADF4002)
	//*)
}


void pnlADF4002::OnbtnCalcSendClick(wxCommandEvent& event)
{
    control->CalculateRN();
    control->SendConfig();
}

void pnlADF4002::OnbtnSendClick(wxCommandEvent& event)
{
    control->SendConfig();
}
