#pragma once

#include <wx/wx.h>

class Backup
{
public:

	wxString name = "NULL";
	wxString directoryPath = "NULL";
	wxString backupLocation = "NULL";
	bool autoBackup = 0;

	Backup(wxString name , wxString directoryPath , wxString backupLocation , bool autoBackup);

	
	void saveToFile();
};

std::vector<Backup*> readFromFile();