#include "Backup.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Backup::Backup(wxString name, wxString directoryPath, wxString backupLocation , bool autoBackup) : name(name) , directoryPath(directoryPath) , backupLocation(backupLocation) , autoBackup(autoBackup)
{

}

std::vector<Backup*> readFromFile()
{
	std::ifstream readFile("backups.sv");

	if(!readFile)
	{
		std::ofstream newFile("backups.sv");
		newFile.close();
	}

	std::vector<Backup*> backups;

	std::string line;
	std::string data[4];
	int index = 0;

	while (std::getline(readFile,line))
	{
		std::string buffer;
		for (char c : line)
		{
			if (c!='%')
			{
				buffer.push_back(c);
			}
			else
			{
				if(index < 4)
				{
					data[index] = buffer;
					buffer.clear();
					index += 1;
				}
			}
		}

		if (index < 4)
		{
			data[index] = buffer;
			buffer.clear();
			index += 1;
		}


		if(index == 4)
		{
			Backup* temp = new Backup(data[0], data[1], data[2], std::stoi(data[3]));
			backups.push_back(temp);
		}

		index = 0;
	}

	readFile.close();
	return backups;
}

void Backup::saveToFile()
{
	std::ofstream saveFile;
	saveFile.open("backups.sv",std::ios::app);
	if (!(name.IsEmpty() || directoryPath.IsEmpty() || backupLocation.IsEmpty()))
	{
		saveFile << name << "%" << directoryPath << "%" << backupLocation << "%" << autoBackup << std::endl;
		wxLogStatus("New backup created");
	}
	else
	{
		wxLogStatus("Invalid Inputs!");
	}
	saveFile.close();
}