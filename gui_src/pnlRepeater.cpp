#include "pnlRepeater.h"

#include "RepeaterRegistersMap.h"
#include "ConnectionManager.h"
#include "CoefficientFileParser.h"

//(*InternalHeaders(pnlRepeater)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlRepeater)
const long pnlRepeater::ID_INSEL = wxNewId();
const long pnlRepeater::ID_STATICTEXT1 = wxNewId();
const long pnlRepeater::ID_STATICTEXT2 = wxNewId();
const long pnlRepeater::ID_IQCORR_TX = wxNewId();
const long pnlRepeater::ID_STATICTEXT3 = wxNewId();
const long pnlRepeater::ID_TNCO = wxNewId();
const long pnlRepeater::ID_STATICTEXT4 = wxNewId();
const long pnlRepeater::ID_STATICTEXT5 = wxNewId();
const long pnlRepeater::ID_GCORRI_TX = wxNewId();
const long pnlRepeater::ID_GCORRQ_TX = wxNewId();
const long pnlRepeater::ID_STATICTEXT6 = wxNewId();
const long pnlRepeater::ID_STATICTEXT7 = wxNewId();
const long pnlRepeater::ID_DCCORRI = wxNewId();
const long pnlRepeater::ID_DCCORRQ = wxNewId();
const long pnlRepeater::ID_BUTTON1 = wxNewId();
const long pnlRepeater::ID_STATICTEXT8 = wxNewId();
const long pnlRepeater::ID_STATICTEXT9 = wxNewId();
const long pnlRepeater::ID_IQCORR_RX = wxNewId();
const long pnlRepeater::ID_STATICTEXT10 = wxNewId();
const long pnlRepeater::ID_STATICTEXT11 = wxNewId();
const long pnlRepeater::ID_STATICTEXT12 = wxNewId();
const long pnlRepeater::ID_GCORRI_RX = wxNewId();
const long pnlRepeater::ID_GCORRQ_RX = wxNewId();
const long pnlRepeater::ID_STATICTEXT13 = wxNewId();
const long pnlRepeater::ID_DCCORR = wxNewId();
const long pnlRepeater::ID_BUTTON2 = wxNewId();
const long pnlRepeater::ID_PHC_BYP_TX = wxNewId();
const long pnlRepeater::ID_GC_BYP_TX = wxNewId();
const long pnlRepeater::ID_DC_BYP_TX = wxNewId();
const long pnlRepeater::ID_FIR_BYP_TX = wxNewId();
const long pnlRepeater::ID_INVSINC_BYP_TX = wxNewId();
const long pnlRepeater::ID_PHC_BYP_RX = wxNewId();
const long pnlRepeater::ID_GC_BYP_RX = wxNewId();
const long pnlRepeater::ID_DC_BYP_RX = wxNewId();
const long pnlRepeater::ID_FIR_BYP_RX = wxNewId();
const long pnlRepeater::ID_ENABLE_TX = wxNewId();
const long pnlRepeater::ID_ENABLE_RX = wxNewId();
const long pnlRepeater::ID_BUTTON5 = wxNewId();
const long pnlRepeater::ID_BUTTON6 = wxNewId();
const long pnlRepeater::ID_BUTTON7 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRepeater,wxPanel)
	//(*EventTable(pnlRepeater)
	//*)
END_EVENT_TABLE()

pnlRepeater::pnlRepeater(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    : PluginPanel(this)
{
    mSerPort = NULL;
	BuildContent(parent,id,pos,size);
    wndId2Enum[ID_ENABLE_TX]=ENABLE_TX;
    wndId2Enum[ID_ENABLE_RX]=ENABLE_RX;
    wndId2Enum[ID_GCORRQ_TX]=GCORRQ_TX;
    wndId2Enum[ID_GCORRI_TX]=GCORRI_TX;
    wndId2Enum[ID_INSEL]=INSEL;
    wndId2Enum[ID_IQCORR_TX]=IQCORR_TX;
    wndId2Enum[ID_DCCORRI]=DCCORRI_TX;
    wndId2Enum[ID_DCCORRQ]=DCCORRQ_TX;
    wndId2Enum[ID_DC_BYP_TX]=DC_BYP_TX;
    wndId2Enum[ID_INVSINC_BYP_TX]=INVSINC_BYP;
    wndId2Enum[ID_FIR_BYP_TX]=FIR_BYP_TX;
    wndId2Enum[ID_GC_BYP_TX]=GC_BYP_TX;
    wndId2Enum[ID_PHC_BYP_TX]=PHC_BYP_TX;
    wndId2Enum[ID_TNCO]=TNCO;
    wndId2Enum[ID_GCORRQ_RX]=GCORRQ_RX;
    wndId2Enum[ID_GCORRI_RX]=GCORRI_RX;
    wndId2Enum[ID_IQCORR_RX]=IQCORR_RX;
    wndId2Enum[ID_DCCORR]=DCCORR;
    wndId2Enum[ID_FIR_BYP_RX]=FIR_BYP_RX;
    wndId2Enum[ID_DC_BYP_RX]=DC_BYP_RX;
    wndId2Enum[ID_PHC_BYP_RX]=PHC_BYP_RX;
    wndId2Enum[ID_GC_BYP_RX]=GC_BYP_RX;

    vector<cmbKeyValuePair> keyvalues;
    for(int i=-2048; i<=2047; ++i)
        keyvalues.push_back( pair<int, wxString>(i, wxString::Format("%i", i)));
    cmbIQCORR_TX->Set(keyvalues);
    cmbIQCORR_RX->Set(keyvalues);

    keyvalues.clear();
    for(int i=0; i<2048; ++i)
        keyvalues.push_back( pair<int, wxString>(i, wxString::Format("%i", i)));
    cmbGCORRI_TX->Set(keyvalues);
    cmbGCORRQ_TX->Set(keyvalues);
    cmbGCORRI_RX->Set(keyvalues);
    cmbGCORRQ_RX->Set(keyvalues);

    keyvalues.clear();
    for(int i=-128; i<128; ++i)
        keyvalues.push_back( pair<int, wxString>(i, wxString::Format("%i", i)));
    cmbDCCORRI->Set(keyvalues);
    cmbDCCORRQ->Set(keyvalues);

    keyvalues.clear();
    for(int i=0; i<8; ++i)
        keyvalues.push_back( pair<int, wxString>(i, wxString::Format("2^%i", i+12)));
    cmbDCCORR->Set(keyvalues);

    UpdateGUI(this);
    int values[] = {1, 2};
    rgrTNCO->SetIndexValues(values, 2);
    UpdateTooltips(this);
}

void pnlRepeater::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlRepeater)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxStaticBoxSizer* StaticBoxSizer12;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer9;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer13;
	wxStaticBoxSizer* StaticBoxSizer10;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxStaticBoxSizer* StaticBoxSizer11;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxFlexGridSizer* FlexGridSizer17;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 5, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Tx Modules"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 5, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_T("CW NCO"),
		_T("RX Output")
	};
	rgrINSEL = new wxRadioBox(this, ID_INSEL, _T("Input Source"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_INSEL"));
	FlexGridSizer2->Add(rgrINSEL, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer16 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer16->AddGrowableCol(0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("IQ Phase Corrector"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("tan(alpha/2):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Alpha:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbIQCORR_TX = new ComboBoxMap(this, ID_IQCORR_TX, wxEmptyString, wxDefaultPosition, wxSize(78,-1), 0, 0, 0, wxDefaultValidator, _T("ID_IQCORR_TX"));
	FlexGridSizer3->Add(cmbIQCORR_TX, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblIQCORR_TX = new wxStaticText(this, ID_STATICTEXT3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer3->Add(lblIQCORR_TX, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer16->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_T("Fclk/16"),
		_T("Fclk/8")
	};
	rgrTNCO = new RadioGroupMap(this, ID_TNCO, _T("CW NCO Frequency"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TNCO"));
	FlexGridSizer16->Add(rgrTNCO, 1, wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer16, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("IQ Gain Corrector"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("Gain I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer5->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("Gain Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbGCORRI_TX = new ComboBoxMap(this, ID_GCORRI_TX, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRI_TX"));
	FlexGridSizer5->Add(cmbGCORRI_TX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbGCORRQ_TX = new ComboBoxMap(this, ID_GCORRQ_TX, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRQ_TX"));
	FlexGridSizer5->Add(cmbGCORRQ_TX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("DC Corrector"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _T("DC I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _T("DC Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer6->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCCORRI = new ComboBoxMap(this, ID_DCCORRI, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DCCORRI"));
	FlexGridSizer6->Add(cmbDCCORRI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCCORRQ = new ComboBoxMap(this, ID_DCCORRQ, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DCCORRQ"));
	FlexGridSizer6->Add(cmbDCCORRQ, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("FIR Filter"));
	btnLoadCoeffsTX = new wxButton(this, ID_BUTTON1, _T("Load RCoeffs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBoxSizer5->Add(btnLoadCoeffsTX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer15 = new wxFlexGridSizer(0, 1, 5, 0);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Rx Modules"));
	FlexGridSizer7 = new wxFlexGridSizer(0, 1, 5, 0);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("IQ Phase Corrector"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer8->AddGrowableCol(0);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _T("tan(alpha/2):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer8->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _T("Alpha:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer8->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbIQCORR_RX = new ComboBoxMap(this, ID_IQCORR_RX, wxEmptyString, wxDefaultPosition, wxSize(78,-1), 0, 0, 0, wxDefaultValidator, _T("ID_IQCORR_RX"));
	FlexGridSizer8->Add(cmbIQCORR_RX, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblIQCORR_RX = new wxStaticText(this, ID_STATICTEXT10, _T("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer8->Add(lblIQCORR_RX, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(StaticBoxSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("IQ Gain Corrector"));
	FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _T("Gain I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer10->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _T("Gain Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer10->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbGCORRI_RX = new ComboBoxMap(this, ID_GCORRI_RX, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRI_RX"));
	FlexGridSizer10->Add(cmbGCORRI_RX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbGCORRQ_RX = new ComboBoxMap(this, ID_GCORRQ_RX, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRQ_RX"));
	FlexGridSizer10->Add(cmbGCORRQ_RX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8->Add(FlexGridSizer10, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("DC Corrector"));
	FlexGridSizer11 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _T("DC AVG:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer11->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCCORR = new ComboBoxMap(this, ID_DCCORR, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DCCORR"));
	FlexGridSizer11->Add(cmbDCCORR, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9->Add(FlexGridSizer11, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer9, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(FlexGridSizer9, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("FIR Filter"));
	btnLoadCoeffsRX = new wxButton(this, ID_BUTTON2, _T("Load RCoeffs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticBoxSizer10->Add(btnLoadCoeffsRX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer15->Add(StaticBoxSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Tx Bypass"));
	FlexGridSizer13 = new wxFlexGridSizer(0, 1, 0, 0);
	chkPHC_BYP_TX = new wxCheckBox(this, ID_PHC_BYP_TX, _T("IQ Corr"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PHC_BYP_TX"));
	chkPHC_BYP_TX->SetValue(false);
	FlexGridSizer13->Add(chkPHC_BYP_TX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGC_BYP_TX = new wxCheckBox(this, ID_GC_BYP_TX, _T("Gain Corr"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GC_BYP_TX"));
	chkGC_BYP_TX->SetValue(false);
	FlexGridSizer13->Add(chkGC_BYP_TX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDC_BYP_TX = new wxCheckBox(this, ID_DC_BYP_TX, _T("DC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DC_BYP_TX"));
	chkDC_BYP_TX->SetValue(false);
	FlexGridSizer13->Add(chkDC_BYP_TX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkFIR_BYP_TX = new wxCheckBox(this, ID_FIR_BYP_TX, _T("GFIR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FIR_BYP_TX"));
	chkFIR_BYP_TX->SetValue(false);
	FlexGridSizer13->Add(chkFIR_BYP_TX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer11->Add(FlexGridSizer13, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkINVSINC_BYP_TX = new wxCheckBox(this, ID_INVSINC_BYP_TX, _T("ISINC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_INVSINC_BYP_TX"));
	chkINVSINC_BYP_TX->SetValue(false);
	StaticBoxSizer11->Add(chkINVSINC_BYP_TX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer12->Add(StaticBoxSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer12 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Rx Bypass"));
	FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
	chkPHC_BYP_RX = new wxCheckBox(this, ID_PHC_BYP_RX, _T("IQ Corr"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PHC_BYP_RX"));
	chkPHC_BYP_RX->SetValue(false);
	FlexGridSizer14->Add(chkPHC_BYP_RX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGC_BYP_RX = new wxCheckBox(this, ID_GC_BYP_RX, _T("Gain Corr"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GC_BYP_RX"));
	chkGC_BYP_RX->SetValue(false);
	FlexGridSizer14->Add(chkGC_BYP_RX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDC_BYP_RX = new wxCheckBox(this, ID_DC_BYP_RX, _T("DC Corr"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DC_BYP_RX"));
	chkDC_BYP_RX->SetValue(false);
	FlexGridSizer14->Add(chkDC_BYP_RX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkFIR_BYP_RX = new wxCheckBox(this, ID_FIR_BYP_RX, _T("GFIR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FIR_BYP_RX"));
	chkFIR_BYP_RX->SetValue(false);
	FlexGridSizer14->Add(chkFIR_BYP_RX, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer12->Add(FlexGridSizer14, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(StaticBoxSizer12, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer15->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer15, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer17 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer13 = new wxStaticBoxSizer(wxVERTICAL, this, _T("FPGA"));
	chkENABLE_TX = new wxCheckBox(this, ID_ENABLE_TX, _T("Tx Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ENABLE_TX"));
	chkENABLE_TX->SetValue(false);
	StaticBoxSizer13->Add(chkENABLE_TX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkENABLE_RX = new wxCheckBox(this, ID_ENABLE_RX, _T("Rx Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ENABLE_RX"));
	chkENABLE_RX->SetValue(false);
	StaticBoxSizer13->Add(chkENABLE_RX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer17->Add(StaticBoxSizer13, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnDownloadAll = new wxButton(this, ID_BUTTON5, _T("Download All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer17->Add(btnDownloadAll, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnUploadAll = new wxButton(this, ID_BUTTON6, _T("Upload All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer17->Add(btnUploadAll, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnRegTest = new wxButton(this, ID_BUTTON7, _T("RegTest"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer17->Add(btnRegTest, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer17, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_INSEL,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_IQCORR_TX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_TNCO,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_GCORRI_TX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_GCORRQ_TX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_DCCORRI,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_DCCORRQ,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRepeater::OnbtnLoadCoeffsTXClick);
	Connect(ID_IQCORR_RX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_GCORRI_RX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_GCORRQ_RX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_DCCORR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRepeater::OnbtnLoadCoeffsRXClick);
	Connect(ID_PHC_BYP_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_GC_BYP_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_DC_BYP_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_FIR_BYP_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_INVSINC_BYP_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_PHC_BYP_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_GC_BYP_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_DC_BYP_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_FIR_BYP_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_ENABLE_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_ENABLE_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRepeater::ParameterChangeHandler);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRepeater::OnbtnDownloadAllClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRepeater::OnbtnUploadAllClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRepeater::OnbtnRegTestClick);
	//*)
}

void pnlRepeater::Initialize(ConnectionManager* serPort)
{
    mSerPort = serPort;
    mRegMap.SetComms(mSerPort);
}

pnlRepeater::~pnlRepeater()
{
	//(*Destroy(pnlRepeater)
	//*)
}

void pnlRepeater::ParameterChangeHandler(wxCommandEvent& event)
{
    unsigned long value = event.GetInt();
    char ctemp[80];
    sprintf(ctemp, "%s", event.GetString().ToStdString().c_str());
    if(m_checkboxIDToInvert.find( ((wxWindow*)event.GetEventObject())->GetId()) != m_checkboxIDToInvert.end())
    {
        if(value == true)
            value = 0;
        else
            value = 1;
    }
    if(mSerPort == NULL)
    {
        std::cout << "Module not initialized" << std::endl;
        return;
    }

    eRepeaterParameter parameter;
    try
    {
        parameter = wndId2Enum.at(event.GetId());
    }
    catch( std::out_of_range &e )
    {
        std::cout << "Control element(ID = " << event.GetId() << ") don't have assigned LMS parameter enumeration." << std::endl;
        return;
    }
    switch(parameter)
    {
    case IQCORR_RX:
        {
            long signedVal = (value&0x800) ? (value | ~0x7FF) : value;
            double rez = atan(signedVal/2048.0); //Result in radians
            rez *= 2*180.0/3.14;  //To degrees
            lblIQCORR_RX->SetLabel(wxString::Format("%.3f", rez));
            mRegMap.SetParameterValue(parameter, value);
        }
        break;
    case IQCORR_TX:
        {
            long signedVal = (value&0x800) ? (value | ~0x7FF) : value;
            double rez = atan(signedVal/2048.0); //Result in radians
            rez *= 2*180.0/3.14;  //To degrees
            lblIQCORR_TX->SetLabel(wxString::Format("%.3f", rez));
        }
        mRegMap.SetParameterValue(parameter, value);
        break;
    default:
        //lmsControl->SetParam( parameter, value);
        mRegMap.SetParameterValue(parameter, value);

    }
    //UpdateGUI(this);
}

void pnlRepeater::OnbtnLoadCoeffsTXClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open coefficients file"), "", "", "FIR Coeffs (*.fir)|*.fir", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;

    int cbuf[200];
    int coefCount = Parser::getcoeffs((const char*)dlg.GetPath().ToStdString().c_str(), cbuf, 200);

    switch(coefCount)
    {
    case -2:
        wxMessageDialog(this, "syntax error within the file", "Warning");
        break;
    case -3:
        wxMessageDialog(this, "filename is empty string", "Warning");
        break;
    case -4:
        wxMessageDialog(this, "can not open the file", "Warning");
        break;
    case -5:
        wxMessageDialog(this, "too many coefficients in the file", "Warning");
        break;
    }
    if(coefCount < 0)
        return;

    if(coefCount > 15)
        coefCount = 15;

    GenericPacket pkt;
    pkt.cmd = CMD_BRDSPI16_WR;
    pkt.outLen = 2*coefCount*sizeof(unsigned short);
    short* shortBuf = (short*)&pkt.outBuffer[0];
    for(int i=0; i<coefCount; ++i)
    {
        shortBuf[2*i] = 0x100+i; //address
        shortBuf[2*i+1] = cbuf[i]; //value
    }
    mSerPort->TransferPacket(pkt);
}

void pnlRepeater::OnbtnLoadCoeffsRXClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open coefficients file"), "", "", "FIR Coeffs (*.fir)|*.fir", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;

    int cbuf[200];
    int coefCount = Parser::getcoeffs((const char*)dlg.GetPath().ToStdString().c_str(), cbuf, 200);

    switch(coefCount)
    {
    case -2:
        wxMessageDialog(this, "syntax error within the file", "Warning");
        break;
    case -3:
        wxMessageDialog(this, "filename is empty string", "Warning");
        break;
    case -4:
        wxMessageDialog(this, "can not open the file", "Warning");
        break;
    case -5:
        wxMessageDialog(this, "too many coefficients in the file", "Warning");
        break;
    }
    if(coefCount < 0)
        return;

    if(coefCount > 15)
        coefCount = 15;

    GenericPacket pkt;
    pkt.cmd = CMD_BRDSPI16_WR;
    pkt.outLen = 2*coefCount*sizeof(unsigned short);
    short* shortBuf = (short*)&pkt.outBuffer[0];
    for(int i=0; i<coefCount; ++i)
    {
        shortBuf[2*i] = 0x300+i; //address
        shortBuf[2*i+1] = cbuf[i]; //value
    }
    mSerPort->TransferPacket(pkt);
}

void pnlRepeater::OnbtnEnableTXClick(wxCommandEvent& event)
{

}

void pnlRepeater::OnbtnDisableTXClick(wxCommandEvent& event)
{

}

void pnlRepeater::OnbtnDownloadAllClick(wxCommandEvent& event)
{
    mRegMap.DownloadAll();
    UpdateGUI(this);
}

void pnlRepeater::OnbtnUploadAllClick(wxCommandEvent& event)
{
    mRegMap.UploadAll();
}

void pnlRepeater::OnbtnRegTestClick(wxCommandEvent& event)
{
    int status1 = mRegMap.RegistersTest(0, 0xFFFF, true, 0xFFFF);
    int status2 = mRegMap.RegistersTest(0x0100, 0x010E, false, 0xFFFF);
    int status3 = mRegMap.RegistersTest(0x0300, 0x030E, false, 0xFFFF);

    mRegMap.UploadAll(); //restore register values after tests

    if(status1 == 1 && status2 == 1 && status3 == 1)
        wxMessageBox("Registers Test OK", "Registers Test");
    else
        wxMessageBox("Registers Test FAILED", "Registers Test");
    UpdateGUI(this);
}

void pnlRepeater::UpdateGUI(wxWindow *pwnd)
{
    wxWindowList childs;
    childs = pwnd->GetChildren();
    wxWindow *wnd;
    wxWindowList::iterator iter;

    std::map<long, eRepeaterParameter>::iterator id_param_pair;
    unsigned long value = 0;
    wxClassInfo *wndClass;
    wxClassInfo *cmbInfo =  wxClassInfo::FindClass(_("wxComboBox"));
    wxClassInfo *cmbMapInfo =  wxClassInfo::FindClass(_("ComboBoxMap"));
    wxClassInfo *chkInfo =  wxClassInfo::FindClass(_("wxCheckBox"));
    wxClassInfo *rgrInfo =  wxClassInfo::FindClass(_("wxRadioBox"));
    wxClassInfo *notebookInfo =  wxClassInfo::FindClass(_("wxNotebook"));
    wxClassInfo *panelInfo =  wxClassInfo::FindClass(_("wxPanel"));
    wxClassInfo *labelInfo =  wxClassInfo::FindClass(_("wxStaticText"));

    for(iter = childs.begin(); iter != childs.end(); ++iter)
    {
        wnd = *iter;
        wndClass = wnd->GetClassInfo();
        if(wndClass->IsKindOf(notebookInfo) || wndClass->IsKindOf(panelInfo))
        {
            UpdateGUI(wnd); //recursive call needed because getChildren returns child notebooks and panels, without their inner childs
        }
        id_param_pair = wndId2Enum.find(wnd->GetId());

        if(id_param_pair == wndId2Enum.end())
            continue; //skip controls that don't have assigned LMS parameter
        value = mRegMap.GetParameterValue(id_param_pair->second);
        //cast window to specific control, to set value, or set selection
        if(wndClass->IsKindOf(cmbInfo))
        {
            wxComboBox *box = wxStaticCast(wnd, wxComboBox);
            if(box->GetCount() < value)
            {
                ControlParameter cp = mRegMap.GetParameterInfo(id_param_pair->second );
                wxString str;
                str = wxString::Format("%s value(%i) is out of range [0-%i]", cp.name, value, box->GetCount()-1);
                wxMessageBox(str, "WARNING!");
                value = 0;
            }
            box->SetSelection(value);
        }
        else if(wndClass->IsKindOf(cmbMapInfo))
        {
            wxStaticCast(wnd, ComboBoxMap)->SetSelection(value);
        }
        else if(wndClass->IsKindOf(chkInfo))
        {
            if(m_checkboxIDToInvert.find(wnd->GetId()) != m_checkboxIDToInvert.end())
            {
                if(value == true)
                    value = 0;
                else
                    value = 1;
            }
            wxStaticCast(wnd, wxCheckBox)->SetValue(value);
        }
        else if(wndClass->IsKindOf(rgrInfo))
        {
            wxRadioBox *box = wxStaticCast(wnd, wxRadioBox);
            if(box->GetCount() < value)
            {
                ControlParameter cp = mRegMap.GetParameterInfo(id_param_pair->second );
                wxString str;
                str = wxString::Format("%s value(%i) is out of range [0-%i]", cp.name, value, box->GetCount()-1);
                wxMessageBox(str, "WARNING!");
                value = 0;
            }
            box->SetSelection(value);
        }
        else if(wndClass->IsKindOf(labelInfo))
        {
            wxStaticCast(wnd, wxStaticText)->SetLabel( wxString::Format(_("%li"), value) );
        }
    }
}

void pnlRepeater::UpdateTooltips(wxWindow* panel)
{
    wxWindow *field = NULL;
    std::map<long, eRepeaterParameter>::iterator fieldIds;
    wxString sttip = "";
    for(fieldIds = wndId2Enum.begin(); fieldIds != wndId2Enum.end(); ++fieldIds)
    {
        field = panel->FindWindow(fieldIds->first);
        wxToolTip *ttip = NULL;
        ttip = field->GetToolTip();
        if(ttip)
            sttip = ttip->GetTip();
        else
            sttip = "";

        ControlParameter cp = mRegMap.GetParameterInfo( fieldIds->second );
        if(cp.bitsCount == 0)
            cout << "Warning: bit count = 0" << endl;
        char cname[64];
        sprintf(cname, "%s", cp.name.c_str());
        char caddr[64];
        memset(caddr, 0, sizeof(caddr));
        if(cp.bitsCount == 1)
            sprintf(caddr, "0x%.4X[%i]", cp.registers[0].addr, cp.registers[0].lsb);
        else
        {
            char ctemp[64];
            memset(ctemp, 0, sizeof(ctemp));
            for(int i=cp.piecesCount-1; i>=0; --i)
            {
                sprintf(ctemp, "%s 0x%.4X[%i:%i]", caddr, cp.registers[i].addr, cp.registers[i].msb, cp.registers[i].lsb);
                strcpy(caddr, ctemp);
            }
        }
        if(sttip.length() > 0)
            field->SetToolTip( wxString::Format("%s.\n %s %s", sttip.c_str(), caddr, cname) );
        else
            field->SetToolTip( wxString::Format("%s %s", caddr, cname) );
        ttip = field->GetToolTip();
    }
}
