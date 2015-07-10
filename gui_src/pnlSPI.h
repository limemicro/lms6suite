// -----------------------------------------------------------------------------
// FILE: 		pnlSPI.h
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef PNLSPI_H
#define PNLSPI_H

//(*Headers(pnlSPI)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "PluginPanel.h"
#include <string>

class ConnectionManager;

class pnlSPI: public wxPanel, public PluginPanel
{
	public:

		pnlSPI(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
		void Initialize( ConnectionManager *pControl);
		virtual ~pnlSPI();

		//(*Declarations(pnlSPI)
		wxStaticText* StaticText9;
		wxStaticText* lblReadVal;
		wxTextCtrl* txtReadAddrBrd;
		wxStaticText* StaticText2;
		wxStaticText* StaticText14;
		wxStaticText* StaticText6;
		wxButton* btnWrite;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxButton* btnReadBrd;
		wxTextCtrl* txtWvalueBrd;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* lblRstatus;
		wxStaticText* StaticText5;
		wxStaticText* lblWstatusBrd;
		wxStaticText* StaticText7;
		wxTextCtrl* txtWvalue;
		wxButton* btnWriteBrd;
		wxTextCtrl* txtWriteAddrBrd;
		wxStaticText* StaticText12;
		wxStaticText* lblReadValBrd;
		wxStaticText* lblRstatusBrd;
		wxButton* btnRead;
		wxTextCtrl* txtWriteAddr;
		wxStaticText* StaticText4;
		wxTextCtrl* txtReadAddr;
		wxStaticText* lblWstatus;
		//*)

	protected:

		//(*Identifiers(pnlSPI)
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
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL5;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_TEXTCTRL6;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		//*)

	private:

		//(*Handlers(pnlSPI)
		void OnbtnWriteClick(wxCommandEvent& event);
		void OnbtnReadClick(wxCommandEvent& event);
		void OnbtnWriteNCOClick(wxCommandEvent& event);
		void OnbtnReadNCOClick(wxCommandEvent& event);
		void OnrgrNCOFCWUPDSelect(wxCommandEvent& event);
		void OnbtnWriteBrdClick(wxCommandEvent& event);
		void OnbtnReadBrdClick(wxCommandEvent& event);
		//*)

	protected:
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow *parent, wxWindowID id);

		DECLARE_EVENT_TABLE()
};

#endif
