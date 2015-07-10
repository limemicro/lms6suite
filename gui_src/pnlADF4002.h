#ifndef PNLADF4002_H
#define PNLADF4002_H

//(*Headers(pnlADF4002)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "PluginPanel.h"
class ADF_module;

class pnlADF4002: public wxPanel, public PluginPanel
{
	public:

		pnlADF4002(ADF_module* pModule, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlADF4002();

		//(*Declarations(pnlADF4002)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxComboBox* cmbTC_f;
		wxRadioBox* rgrPDP_i;
		wxComboBox* cmbCS2_i;
		wxComboBox* cmbMOC_i;
		wxButton* btnSend;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxSpinCtrl* spinNCnt;
		wxStaticText* StaticText14;
		wxComboBox* cmbCS2_f;
		wxStaticText* StaticText6;
		wxComboBox* cmbLDP;
		wxStaticText* StaticText19;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxRadioBox* rgrPD1_f;
		wxButton* btnCalcSend;
		wxStaticText* StaticText1;
		wxRadioBox* rgrCPS_f;
		wxStaticText* StaticText3;
		wxComboBox* cmbFL_i;
		wxTextCtrl* txtFref;
		wxComboBox* cmbCS1_i;
		wxRadioBox* rgrPDP_f;
		wxSpinCtrl* spinRCnt;
		wxRadioBox* rgrCPS_i;
		wxComboBox* cmbCPG;
		wxComboBox* cmbMOC_f;
		wxRadioBox* rgrPD2_f;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxComboBox* cmbCS1_f;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxRadioBox* rgrPD1_i;
		wxStaticText* lblFcomp;
		wxComboBox* cmbTC_i;
		wxRadioBox* rgrCR_f;
		wxTextCtrl* txtFvco;
		wxStaticText* StaticText17;
		wxComboBox* cmbFL_f;
		wxStaticText* StaticText4;
		wxComboBox* cmbABW;
		wxRadioBox* rgrCR_i;
		wxStaticText* lblFvco;
		wxStaticText* StaticText16;
		wxRadioBox* rgrPD2_i;
		//*)

	protected:

		//(*Identifiers(pnlADF4002)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX3;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX8;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX4;
		static const long ID_RADIOBOX5;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX9;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_COMBOBOX11;
		static const long ID_COMBOBOX12;
		static const long ID_STATICTEXT21;
		static const long ID_COMBOBOX13;
		static const long ID_RADIOBOX6;
		static const long ID_RADIOBOX7;
		static const long ID_RADIOBOX8;
		static const long ID_RADIOBOX9;
		static const long ID_RADIOBOX10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(pnlADF4002)
		void OnbtnCalcSendClick(wxCommandEvent& event);
		void OnbtnSendClick(wxCommandEvent& event);
		//*)

	protected:
	    ADF_module* control;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
