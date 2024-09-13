#include "MainFrame.h"
#include "CreateBackupFrame.h"
#include "AboutFrame.h"
#include "Backup.h"

#include <wx/wx.h>
#include <boost/filesystem.hpp>
#include <vector>

enum IDs
{
	ADDBUTTON_ID = 2 ,
    DELETEBUTTON_ID,
    EDITBUTTON_ID,
    STARTBUTTON_ID,

    ABOUT_MENU ,
    REFRESH_MENU ,
    QUIT_MENU ,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(ADDBUTTON_ID, MainFrame::onAddButtonClicked)
    EVT_BUTTON(STARTBUTTON_ID, MainFrame::onStartButtonClicked)
    EVT_BUTTON(DELETEBUTTON_ID, MainFrame::onDeleteButtonClicked)
    // EVT_BUTTON(EDITBUTTON_ID, MainFrame::onEditButtonClicked)
    EVT_MENU(REFRESH_MENU, MainFrame::menuRefresh)
    EVT_MENU(QUIT_MENU, MainFrame::menuQuit)
    EVT_MENU(ABOUT_MENU, MainFrame::openAboutFrame)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{

    p_MenuBar = new wxMenuBar();

    p_FileMenu = new wxMenu();
    p_FileMenu->Append(REFRESH_MENU, _T("&Refresh"));
    
    p_FileMenu->AppendSeparator();

    p_FileMenu->Append(QUIT_MENU, _T("&Quit"));
    p_MenuBar->Append(p_FileMenu, _T("&File"));

    p_HelpMenu = new wxMenu();
    p_HelpMenu->Append(ABOUT_MENU, _T("&About"));
    p_MenuBar->Append(p_HelpMenu, _T("&Help"));

    SetMenuBar(p_MenuBar);
    CreateStatusBar();

    p_panel = new wxPanel(this);

    

    wxString imagePath = "res//banner.png";
    wxInitAllImageHandlers();
    wxImage originalImage(imagePath, wxBITMAP_TYPE_ANY);

    wxImage resizedImage = originalImage.Scale(270, 100);
    wxBitmap bitmap(resizedImage);
    wxStaticBitmap* image;
    image = new wxStaticBitmap(p_panel, wxID_ANY, bitmap, wxPoint(135, 10), wxSize(270, 100));

    std::vector<Backup*> backups = readFromFile();
    for (Backup* b : backups)
    {
        backup_array.Add(b->name);
    }
	
    p_text = new wxStaticText(p_panel,wxID_ANY,"Your Backups",wxPoint(10,120),wxSize(520,35));
	p_backups = new wxListBox(p_panel,wxID_ANY, wxPoint(10,165), wxSize(520, 320),backup_array);
    p_editButton = new wxButton(p_panel, EDITBUTTON_ID, "Edit", wxPoint(10, 495), wxSize(160, 45));
    p_deleteButton = new wxButton(p_panel, DELETEBUTTON_ID, "Delete", wxPoint(180, 495), wxSize(160, 45));
    p_addButton = new wxButton(p_panel, ADDBUTTON_ID, "Create Backup", wxPoint(350, 495), wxSize(180, 45));
    p_startButton = new wxButton(p_panel, STARTBUTTON_ID, "Start", wxPoint(10, 550), wxSize(520, 45));

}

void MainFrame::onAddButtonClicked(wxCommandEvent& evt)
{

    CreateBackupFrame* backupFrame = new CreateBackupFrame(this,"Create Backup");
    backupFrame->SetClientSize(600,255);
    backupFrame->Center();
    backupFrame->Show();

}

void copyDirectory(const boost::filesystem::path& src, const boost::filesystem::path& dst)
{
    try {
        if (boost::filesystem::exists(dst)) {
            std::cout << std::endl;
        }
        else {
            boost::filesystem::create_directories(dst);
        }

        for (boost::filesystem::directory_iterator file(src); file != boost::filesystem::directory_iterator(); ++file) {
            boost::filesystem::path current(file->path());
            boost::filesystem::path destination = dst / current.filename();

            if (boost::filesystem::is_directory(current)) {
                copyDirectory(current, destination);
            }
            else {
                boost::filesystem::copy_file(current, destination);
            }
        }
    }
    catch (const boost::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}

void MainFrame::onStartButtonClicked(wxCommandEvent& evt)
{
    std::vector<Backup*> backups = readFromFile();
    int size = backups.size();
    int sno = 0;
    for (Backup* b : backups)
    {
        sno += 1;
        wxString log = std::to_string(sno) + "/" + std::to_string(size);
        wxLogStatus(log);
        boost::filesystem::path source(b->directoryPath);
        boost::filesystem::path destination(b->backupLocation+"/" + b->name + "/");
        copyDirectory(source,destination);
        
    }
}

void MainFrame::menuRefresh(wxCommandEvent& evt)
{
    p_backups->Clear();
    std::vector<Backup*> backups = readFromFile();
    for (Backup* b : backups)
    {
        p_backups->Insert(b->name,p_backups->GetCount());
    }
}


void MainFrame::menuQuit(wxCommandEvent& evt)
{
    this->Destroy();
}

void MainFrame::openAboutFrame(wxCommandEvent& evt)
{
    AboutFrame* aboutFrame = new AboutFrame(this,"About");
    aboutFrame->SetClientSize(440,170);
    aboutFrame->Center();
    aboutFrame->Show();
}

void MainFrame::onDeleteButtonClicked(wxCommandEvent& evt)
{

    wxString del_name = backup_array[p_backups->GetSelection()];

    std::vector<Backup*> backups = readFromFile();
    std::vector<Backup*> updated_backups; 
    for (Backup* b : backups)
    {
        if (!(b->name == del_name))
        {
            updated_backups.push_back(b);
        }
    }

    int status = remove("backups.sv");

    for (Backup* c : updated_backups)
    {
        c->saveToFile();
    }

    wxLogStatus("Backup deleted succesfully!");
}

void onEditButtonClicked(wxCommandEvent& evt)
{
    wxLogStatus("Coming soon!");
}