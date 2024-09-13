#include "CreateBackupFrame.h"
#include "MainFrame.h"
#include "Backup.h"

#include <wx/wx.h>

enum IDs
{
	DIRECTORY_BUTTON = 2,
	LOCATION_BUTTON ,
	CREATE_BACKUP_BUTTON

};

wxBEGIN_EVENT_TABLE(CreateBackupFrame, wxFrame)
	EVT_BUTTON(DIRECTORY_BUTTON, CreateBackupFrame::onSelectDirectoryButtonClicked)
	EVT_BUTTON(LOCATION_BUTTON, CreateBackupFrame::onSelectBackupLocationButtonClicked)
	EVT_BUTTON(CREATE_BACKUP_BUTTON,CreateBackupFrame::onCreateBackupButtonClicked)
wxEND_EVENT_TABLE()

CreateBackupFrame::CreateBackupFrame(wxWindow* parentFrame,const wxString& title) : wxFrame(parentFrame,wxID_ANY,title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	p_panel = new wxPanel(this);

	p_name = new wxTextCtrl(p_panel, wxID_ANY,"Backup Name",wxPoint(10,10),wxSize(580,35));
	
	p_selectDirectory = new wxButton(p_panel,DIRECTORY_BUTTON,"Select directory", wxPoint(10, 55), wxSize(580, 35));
	p_directory = new wxStaticText(p_panel, wxID_ANY, "Directory : No directory selected!", wxPoint(10, 90), wxSize(580, 10));
	p_directory->SetFont(p_directory->GetFont().Scale(0.7));
	p_directory->SetForegroundColour(wxColour(255, 15, 15,1));

	p_selectLocation = new wxButton(p_panel,LOCATION_BUTTON,"Select backup location", wxPoint(10, 110), wxSize(580, 35));
	p_backupLocation = new wxStaticText(p_panel, wxID_ANY, "Backup Location : No location selected!", wxPoint(10, 145), wxSize(580, 10));
	p_backupLocation->SetFont(p_backupLocation->GetFont().Scale(0.7));
	p_backupLocation->SetForegroundColour(wxColour(255, 15, 15, 1));

	p_autoBackup = new wxCheckBox(p_panel,wxID_ANY,"Automatically backup directory on changes",wxPoint(10,165),wxSize(580,35));

	p_createBackup = new wxButton(p_panel, CREATE_BACKUP_BUTTON , "Create Backup" , wxPoint(10,210),wxSize(580,35));

}

void CreateBackupFrame::onSelectDirectoryButtonClicked(wxCommandEvent& evt)
{
	wxDirDialog* dirDialog = new wxDirDialog(this);

	if (dirDialog->ShowModal() == wxID_OK)
	{
		wxString selectedDir = dirDialog->GetPath();
		directoryPath = selectedDir;
		p_directory->SetForegroundColour(wxColour(33, 255, 100, 1));
		p_directory->SetLabelText("Directory : " + selectedDir);
		wxLogStatus("Directory Path :" + selectedDir);
	}
	dirDialog->Destroy();
}

void CreateBackupFrame::onSelectBackupLocationButtonClicked(wxCommandEvent& evt)
{
	wxDirDialog* dirDialog = new wxDirDialog(this);

	if (dirDialog->ShowModal() == wxID_OK)
	{
		wxString selectedDir = dirDialog->GetPath();
		backupLocation = selectedDir;
		p_backupLocation->SetForegroundColour(wxColour(33, 255, 100, 1));
		p_backupLocation->SetLabelText("Backup Location : " + selectedDir);
		wxLogStatus("Backup Location :" + selectedDir);
	}
	dirDialog->Destroy();
}

void CreateBackupFrame::onCreateBackupButtonClicked(wxCommandEvent& evt)
{
	Backup* createBackup = new Backup(p_name->GetValue(),directoryPath,backupLocation,p_autoBackup->GetValue());
	createBackup->saveToFile();
	this->Destroy();
}
