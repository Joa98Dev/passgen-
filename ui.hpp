#pragma once
#include <wx/wx.h>
#include <string>
#include <random>

/**
 * @class MyFrame
 * Main application window handling password generation UI
 *
 * Inherits from wxFrame to create the main application window with:
 * - Password length slider
 * - Generated password display
 * - Copy and Generate buttons
 * - Menu bar
 * */
class MyFrame : public wxFrame {

	public:
		/**
		 * Constructs the main application frame
		 * param title window title to display
		 * */
		MyFrame(const wxString& title);

	private:
		// UI Controls
		wxSlider* m_slider; ///< Controls password length (4-16 chars)
		wxStaticText* m_sliderValue; ///< Display current length
		wxTextCtrl* m_passwordDisplay; ///< Shows generated password
		wxButton* m_generateBtn; ///< Triggers password generation
		wxButton* m_copyBtn; ///< Copies password to clipboard

		// Event handler
		void OnExit(wxCommandEvent& event); ///< Close application
		void OnAbout(wxCommandEvent& event); ///< Shows abaout dialog
		void OnSliderChanged(wxCommandEvent& event); ///< Hanldes slider movement
		void OnGenerateClicked(wxCommandEvent& event); ///< Generate new password

		/**
		 * Generates a random password
		 * length desired passowrd length
		 * return the generated password
		 * */
		std::string GeneratePassword(int lenght);

		DECLARE_EVENT_TABLE(); ///< Required for wxWidgets event handling

};
