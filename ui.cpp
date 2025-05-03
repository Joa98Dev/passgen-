#include "ui.hpp"
#include <algorithm>
#include <wx/clipbrd.h>
#include <wx/aboutdlg.h>

// Create event tables maps GUI to handler functions
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_SLIDER(wxID_ANY, MyFrame::OnSliderChanged) ///< Slider value changes
	EVT_MENU(wxID_EXIT, MyFrame::OnExit) ///< File -> Exit
	EVT_MENU(wxID_ABOUT, MyFrame::OnAbout) ///< Help -> About
	EVT_BUTTON(wxID_ANY, MyFrame::OnGenerateClicked) ///< Generate button
wxEND_EVENT_TABLE()

// Constructor implementation: Sets up all UI Components
MyFrame::MyFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title) {
   
    // Main container panel
    wxPanel* panel = new wxPanel(this);

    // Create a vertical sizer for layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Password length slider (4-16 chars, default 8)
    m_slider = new wxSlider(
        panel, wxID_ANY,
        8, 4, 16,  // Initial, min, max
        wxDefaultPosition, wxSize(300, -1),
        wxSL_HORIZONTAL | wxSL_LABELS
    );

    // Current lenght display
    m_sliderValue = new wxStaticText(
        panel, wxID_ANY, "8",
        wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTRE_HORIZONTAL
    );

    wxFont font = m_sliderValue->GetFont();
    font.SetPointSize(16);
    m_sliderValue->SetFont(font);

    // Password display (read-only centered text)
    m_passwordDisplay = new wxTextCtrl(panel, wxID_ANY, "",
        wxDefaultPosition, wxSize(300, -1),
        wxTE_READONLY | wxTE_CENTRE
    );
    
    m_passwordDisplay->SetFont(wxFont(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // Generate buttons
    m_generateBtn = new wxButton(panel, wxID_ANY, "Generate Password");
    m_copyBtn = new wxButton(panel, wxID_ANY, "Copy");
    m_generateBtn->SetMinSize(wxSize(-1, 30));
    m_copyBtn->SetMinSize(wxSize(-1, 30));

    // UI layout
    sizer->Add(m_slider, 0, wxALIGN_CENTER | wxALL, 10);
    sizer->Add(m_sliderValue, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(m_passwordDisplay, 0, wxALIGN_CENTER | wxALL, 10);
    sizer->Add(m_generateBtn, 0, wxALIGN_CENTER | wxTOP, 15);
    sizer->Add(m_copyBtn, 0, wxALIGN_CENTER | wxTOP, 15);

    // Event bindings
    m_generateBtn->Bind(wxEVT_BUTTON, &MyFrame::OnGenerateClicked, this);

    // Copy buttons: copies password to clipboard
    m_copyBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        if (wxTheClipboard->Open()) {
            wxTheClipboard->SetData(new wxTextDataObject(m_passwordDisplay->GetValue()));
            wxTheClipboard->Close();
            wxLogStatus("Password copied to clipboard!");
        }
    });

    // Disale copy button by default
    m_copyBtn->Disable();

    // Add stretchable space to push everything up
    sizer->AddStretchSpacer();

    panel->SetSizerAndFit(sizer);  ///< Use SetSizerAndFit instead of SetSizer
    Centre();
    
    // Create menu bar and menus here
    wxMenuBar *menuBar = new wxMenuBar();
    
    // File Menu
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT, "&Exit\tCtrl+Q");
    
    // Help Menu
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&About");
    
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar); 

}

// Password Generator Loginc
std::string MyFrame::GeneratePassword(int length) {
	/**
	 * Character pool containing:
	 * - Numbers 0-9
	 * - Upper/lowercase letters
	 * - Common symbols
	 * */
	const std::string chars = 
		"0123456789"
		"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ"
		"abcdefghijklmnñopqrstuvwxyz"
		"!@#$%^&*()";

	// Initialize random number generator
	std::random_device rd; ///< Hardwar-based seed
	std::mt19937 generator(rd()); ///< Mersenne twister engine
	std::uniform_int_distribution<> dist(0, chars.size() - 1); ///< Even distribution

	std::string password;
	for(int i = 0; i < length; ++i) {
		password += chars[dist(generator)]; ///< Append random character

	}

	return password;

}

// Event Handlers
//
// Slider Value Changed
void MyFrame::OnSliderChanged(wxCommandEvent& event) {

	int value = m_slider->GetValue();
	m_sliderValue->SetLabel(wxString::Format("%d", value));

	/**
	 * Visual feedback based on length:
	 * - Red (weak)
	 * - Yellow (medium)
	 * - Green (strong)
	 * */
	if(value <= 6) {
		m_sliderValue->SetForegroundColour(*wxRED);

	} else if(value <= 10) {

		m_sliderValue->SetForegroundColour(*wxYELLOW);
	} else {

		m_sliderValue->SetForegroundColour(*wxGREEN);
	}
	
	m_sliderValue->Refresh();

}

// Generate Button Clicked
void MyFrame::OnGenerateClicked(wxCommandEvent& event) {
 
	if (!m_slider || !m_passwordDisplay || !m_copyBtn) return;
    
    
	int length = m_slider->GetValue();
    	std::string password = GeneratePassword(length);
    	m_passwordDisplay->ChangeValue(password);
    	m_copyBtn->Enable(!password.empty());
}

// Exit Menu Selected
void MyFrame::OnExit(wxCommandEvent& event) {


	Close(true);
}

// About Menu Selected
void MyFrame::OnAbout(wxCommandEvent& event) {
    wxAboutDialogInfo aboutInfo;
    
    // Core Information
    aboutInfo.SetName("PassGen++");
    aboutInfo.SetVersion("1.0.4");
    aboutInfo.SetDescription(_("A secure password generator\n"
                             "Built with wxWidgets"));
    
    // Copyright
    aboutInfo.SetCopyright("(C) 2025 Joa98 <joaquinpuente98@gmail.com>");

    // License Info (GPL-3.0)
    aboutInfo.SetLicense(_("This program is free software: you can redistribute it and/or modify "
                        "it under the terms of the GNU General Public License as published by "
                        "the Free Software Foundation, either version 3 of the License, or "
                        "(at your option) any later version.\n\n"
                        "See LICENSE file for full details."));
    
    // Website/GitHub Link
    aboutInfo.SetWebSite("https://github.com/Joa98Dev/passgen-.git");
    
    // Optional: Add developer credits
    wxArrayString developers;
    developers.Add("Joaquin Puente <joaquinpuente98@gmail.com>");
    aboutInfo.SetDevelopers(developers);
    
    // Show the about dialog
    wxAboutBox(aboutInfo);
}
