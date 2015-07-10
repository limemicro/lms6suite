#ifndef PNLREPEATER_H
#define PNLREPEATER_H

//(*Headers(pnlRepeater)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)
#include "GUIPanel.h"
#include "PluginPanel.h"
#include "RepeaterRegistersMap.h"
#include "ComboBoxMap.h"
#include "RadioGroupMap.h"

class ConnectionManager;

class pnlRepeater: public wxPanel, public PluginPanel
{
	public:
		pnlRepeater(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		void Initialize(ConnectionManager* serPort);
		virtual ~pnlRepeater();

		void UpdateGUI(wxWindow *pwnd);
		void UpdateTooltips(wxWindow *pwnd);

		RepeaterRegistersMap mRegMap;

		//(*Declarations(pnlRepeater)
		wxStaticText* StaticText9;
		wxButton* btnRegTest;
		ComboBoxMap* cmbDCCORRQ;
		ComboBoxMap* cmbGCORRQ_RX;
		wxStaticText* lblIQCORR_RX;
		ComboBoxMap* cmbGCORRQ_TX;
		wxCheckBox* chkINVSINC_BYP_TX;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxRadioBox* rgrINSEL;
		wxStaticText* StaticText6;
		wxCheckBox* chkFIR_BYP_RX;
		wxCheckBox* chkDC_BYP_TX;
		ComboBoxMap* cmbGCORRI_RX;
		wxCheckBox* chkENABLE_RX;
		wxCheckBox* chkFIR_BYP_TX;
		ComboBoxMap* cmbIQCORR_RX;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxButton* btnDownloadAll;
		wxStaticText* StaticText1;
		wxCheckBox* chkGC_BYP_TX;
		wxButton* btnLoadCoeffsTX;
		ComboBoxMap* cmbDCCORRI;
		ComboBoxMap* cmbIQCORR_TX;
		wxCheckBox* chkGC_BYP_RX;
		wxCheckBox* chkPHC_BYP_RX;
		wxStaticText* lblIQCORR_TX;
		RadioGroupMap* rgrTNCO;
		wxCheckBox* chkENABLE_TX;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxCheckBox* chkPHC_BYP_TX;
		wxStaticText* StaticText12;
		wxCheckBox* chkDC_BYP_RX;
		wxButton* btnUploadAll;
		ComboBoxMap* cmbDCCORR;
		wxStaticText* StaticText4;
		wxButton* btnLoadCoeffsRX;
		ComboBoxMap* cmbGCORRI_TX;
		//*)

		//(*Identifiers(pnlRepeater)
		static const long ID_INSEL;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_IQCORR_TX;
		static const long ID_STATICTEXT3;
		static const long ID_TNCO;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_GCORRI_TX;
		static const long ID_GCORRQ_TX;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_DCCORRI;
		static const long ID_DCCORRQ;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_IQCORR_RX;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_GCORRI_RX;
		static const long ID_GCORRQ_RX;
		static const long ID_STATICTEXT13;
		static const long ID_DCCORR;
		static const long ID_BUTTON2;
		static const long ID_PHC_BYP_TX;
		static const long ID_GC_BYP_TX;
		static const long ID_DC_BYP_TX;
		static const long ID_FIR_BYP_TX;
		static const long ID_INVSINC_BYP_TX;
		static const long ID_PHC_BYP_RX;
		static const long ID_GC_BYP_RX;
		static const long ID_DC_BYP_RX;
		static const long ID_FIR_BYP_RX;
		static const long ID_ENABLE_TX;
		static const long ID_ENABLE_RX;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		//*)

		//(*Handlers(pnlRepeater)
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnbtnLoadCoeffsTXClick(wxCommandEvent& event);
		void OnbtnLoadCoeffsRXClick(wxCommandEvent& event);
		void OnbtnEnableTXClick(wxCommandEvent& event);
		void OnbtnDisableTXClick(wxCommandEvent& event);
		void OnbtnDownloadAllClick(wxCommandEvent& event);
		void OnbtnUploadAllClick(wxCommandEvent& event);
		void OnbtnRegTestClick(wxCommandEvent& event);
		//*)

	protected:
	    ConnectionManager *mSerPort;
	    std::set<long> m_checkboxIDToInvert;
        std::map<long, eRepeaterParameter> wndId2Enum;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
