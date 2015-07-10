#ifndef PNLHPM1000_H
#define PNLHPM1000_H

//(*Headers(pnlHPM1000)
#include <wx/panel.h>
class wxCheckBox;
class wxTextCtrl;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)
class ConnectionManager;
class ComboBoxMap;
#include "PluginPanel.h"

class pnlHPM1000: public wxPanel, public PluginPanel
{
	public:

		pnlHPM1000(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
		void Initialize( ConnectionManager *pControl);
		virtual ~pnlHPM1000();
		virtual void UpdatePanel();

		//(*Declarations(pnlHPM1000)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxCheckBox* chkGPIO2;
		wxCheckBox* chkSW2_0;
		wxStaticText* lblReadVal;
		ComboBoxMap* cmbDTC2_1;
		wxCheckBox* chkSW1_0;
		wxCheckBox* chkSW3_2;
		wxComboBox* cmbMIPIId;
		wxCheckBox* chkGPIO1;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxStaticText* StaticText14;
		wxCheckBox* chkSW2_2;
		wxStaticText* StaticText6;
		wxCheckBox* chkGPIO0;
		wxButton* btnWriteMIPI;
		ComboBoxMap* cmbDTC2_0;
		ComboBoxMap* cmbDTC1_1;
		wxButton* btnWrite;
		wxStaticText* StaticText8;
		wxCheckBox* chkSW2_1;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* lblRstatus;
		wxTextCtrl* txtAddrMIPI;
		wxTextCtrl* txtValueMIPI;
		wxCheckBox* chkSW1_2;
		wxStaticText* lblStatusMIPI;
		ComboBoxMap* cmbDTC2_2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxCheckBox* chkGPIO3;
		wxCheckBox* chkSW1_1;
		wxTextCtrl* txtWvalue;
		ComboBoxMap* cmbDTC1_0;
		wxCheckBox* chkSW3_1;
		wxCheckBox* chkGPIO4;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxCheckBox* chkSW3_0;
		wxButton* btnReadMIPI;
		wxCheckBox* chkEnableShortcuts;
		ComboBoxMap* cmbDTC1_2;
		wxButton* btnReadGPIO;
		wxButton* btnRead;
		wxTextCtrl* txtWriteAddr;
		wxStaticText* lblReadValMipi;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxTextCtrl* txtReadAddr;
		wxStaticText* lblWstatus;
		wxStaticText* StaticText16;
		//*)

		//(*Identifiers(pnlHPM1000)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT14;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL5;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_BUTTON5;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_STATICTEXT12;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX3;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_STATICTEXT19;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT20;
		static const long ID_COMBOBOX5;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_STATICTEXT21;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT22;
		static const long ID_COMBOBOX7;
		static const long ID_CHECKBOX15;
		static const long ID_STATICTEXT23;
		//*)

		//(*Handlers(pnlHPM1000)
		void OnchkGPIOClick(wxCommandEvent& event);
		void OnbtnWriteClick(wxCommandEvent& event);
		void OnbtnReadClick(wxCommandEvent& event);
		void OnbtnWriteNCOClick(wxCommandEvent& event);
		void OnbtnReadNCOClick(wxCommandEvent& event);
		void OnrgrNCOFCWUPDSelect(wxCommandEvent& event);
		void OnbtnWriteMIPIClick(wxCommandEvent& event);
		void OnbtnReadMIPIClick(wxCommandEvent& event);
		void OnbtnReadGPIOClick(wxCommandEvent& event);
		void OnConfigure_0(wxCommandEvent& event);
		void OnConfigure_1(wxCommandEvent& event);
		void OnConfigure_2(wxCommandEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void OnKeyUp(wxKeyEvent& event);
		//*)

	protected:
	    unsigned int mipiRead(unsigned id, unsigned addr);
	    int ConfigurePE636040(unsigned id, bool sw1, bool sw2, bool sw3, unsigned dtc1, unsigned dtc2);
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
