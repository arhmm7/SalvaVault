#include "App.h"
#include "MainFrame.h"

#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("SalvaVault");
	mainFrame->Show();
	mainFrame->SetClientSize(540,605);
	mainFrame->Center();
	return true;
}