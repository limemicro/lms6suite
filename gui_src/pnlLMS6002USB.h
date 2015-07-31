#ifndef PNLLMS6002USBSTICK_H
#define PNLLMS6002USBSTICK_H

#include <map>
#include <wx/panel.h>
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxSpinCtrl;
class wxComboBox;
class wxCheckBox;

#include "PluginPanel.h"
class ConnectionManager;

class pnlLMS6002USB: public wxPanel, public PluginPanel
{
	public:
        pnlLMS6002USB(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int style = 0, wxString name = "");
		void Initialize( ConnectionManager *pControl);
        virtual ~pnlLMS6002USB();
        virtual void UpdatePanel();

		wxButton* btnUpdateAll;		
        wxComboBox* cmbVCXOcontrolVoltage;

        wxPanel* mPanelStreamPLL;
        wxTextCtrl* txtPllFreqRxMHz;
        wxStaticText* lblRealFreqTx;
        wxStaticText* lblRealFreqRx;
        wxTextCtrl* txtPllFreqTxMHz;
        wxTextCtrl* txtPhaseOffsetDeg;
        wxButton* btnConfigurePLL;

        wxCheckBox* chkRX_DCCORR_BYP;
        wxCheckBox* chkRX_PHCORR_BYP;
        wxCheckBox* chkRX_GCORR_BYP;
        wxCheckBox* chkTX_PHCORR_BYP;
        wxCheckBox* chkTX_GCORR_BYP;
        wxSpinCtrl* spinTX_GCORRQ;
        wxSpinCtrl* spinTX_GCORRI;
        wxSpinCtrl* spinTX_PHCORR;
        wxSpinCtrl* spinRX_GCORRQ;
        wxSpinCtrl* spinRX_GCORRI;
        wxSpinCtrl* spinRX_PHCORR;
        wxComboBox* cmbRX_DCCORR;
		
		static const long ID_BUTTON_UPDATEALL;		
        static const long ID_VCXOCV;

		void OnbtnUpdateAll(wxCommandEvent& event);
        void ParameterChangeHandler(wxCommandEvent& event);
    protected:
        void OnConfigurePLL(wxCommandEvent &event);        
        enum Status
        {
            SUCCESS,
            FAILURE,
        };
        Status ConfigurePLL(ConnectionManager *serPort, const float fOutTx_MHz, const float fOutRx_MHz, const float phaseShift_deg);

        struct Register
        {
            Register();
            Register(unsigned short address, unsigned char msb, unsigned char lsb, unsigned short defaultValue);
            unsigned short address;
            unsigned char msb;
            unsigned char lsb;
            unsigned short defaultValue;
        };

        std::map<wxObject*, Register> controlsPtr2Registers;
        void RegisterParameterChangeHandler(wxCommandEvent& event);

	protected:
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
