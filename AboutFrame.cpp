#include "AboutFrame.h"

AboutFrame::AboutFrame(wxWindow* parentFrame , const wxString& title) : wxFrame(parentFrame, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	panel = new wxPanel(this);
	
	wxString imagePath = "res//banner.png";
	wxInitAllImageHandlers();
	wxImage originalImage(imagePath, wxBITMAP_TYPE_ANY);

	wxImage resizedImage = originalImage.Scale(270, 100);
	wxBitmap bitmap(resizedImage);
	wxStaticBitmap* image;
	image = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(85, 10), wxSize(270, 100));

	text = new wxStaticText(panel, wxID_ANY, "Made with love by github.com/arhmm7", wxPoint(10, 120), wxSize(440, 40), wxALIGN_CENTER);
}