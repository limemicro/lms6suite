#ifndef PNLLMS6002USBSTICK_H
#define PNLLMS6002USBSTICK_H

#include <wx/panel.h>
class wxStaticText;
class wxFlexGridSizer;
class wxButton;

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

	protected:
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
