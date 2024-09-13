#pragma once

#include <wx/frame.h>	
#include <wx/wx.h>

class MainFrame :  public wxFrame
{
public:

	MainFrame(const wxString& title);
	wxListBox* p_backups;

private:

	void onAddButtonClicked(wxCommandEvent& evt);
	void onStartButtonClicked(wxCommandEvent& evt);
	void onDeleteButtonClicked(wxCommandEvent& evt);
	// void onEditButtonClicked(wxCommandEvent& evt);
	void openAboutFrame(wxCommandEvent& evt);
	void menuQuit(wxCommandEvent& evt);
	void menuRefresh(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

	wxMenuBar* p_MenuBar;
	wxMenu* p_FileMenu;
	wxMenu* p_HelpMenu;

	wxPanel* p_panel;
	wxStaticText* p_text;

	wxButton* p_editButton;
	wxButton* p_deleteButton;
	wxButton* p_addButton;
	wxButton* p_startButton;

	

	wxArrayString backup_array;

};

