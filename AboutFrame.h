#pragma once

#include <wx/frame.h>	
#include <wx/wx.h>

class AboutFrame : public wxFrame
{
public:
	AboutFrame(wxWindow* parentFrame,const wxString& title);
private:
	wxPanel* panel;
	wxStaticText* text;

};

