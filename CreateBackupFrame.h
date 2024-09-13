#pragma once

#include <wx/frame.h>	
#include <wx/wx.h>

class CreateBackupFrame : public wxFrame
{
public:

	CreateBackupFrame(wxWindow* parentFrame,const wxString& title);
	wxString backupName , directoryPath , backupLocation;

private:

	void onSelectDirectoryButtonClicked(wxCommandEvent& evt);
	void onSelectBackupLocationButtonClicked(wxCommandEvent& evt);
	void onCreateBackupButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

	wxPanel* p_panel;

	wxTextCtrl* p_name;

	wxStaticText* p_directory;
	wxButton* p_selectDirectory;

	wxStaticText* p_backupLocation;
	wxButton* p_selectLocation;

	wxCheckBox* p_autoBackup;

	wxButton* p_createBackup;

};

