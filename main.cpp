/**
 * @file main.cpp
 * Main application entry for PassGen password generator app
 *
 * Creates the application instance and launches the main window.
 * Uses wxWidgets framework for cross-platform GUI functionality.
 */

#include "ui.hpp" // Main application window class
#include <wx/wx.h> // wxWidgets library

/**
 * @class MyApp
 * The main application class inheriting from wxApp
 *
 * Handle application lifecycle events and initialization.
 * wxWidgets requires this class as the entry point for all GUI application.
 * */

class MyApp : public wxApp {

	public:
		/**
		 * Initialize the application
		 * return bool true if initialization succeeded, false to abort
		 *
		 * Overrides wxApp::OnInit() to:
		 * 1. Create the main frame window
		 * 2. Set initial window size
		 * 3. Display the window
		 * */

		virtual bool OnInit() override;
};

// Application Initialization
bool MyApp::OnInit() {
	// Create the main application window
	MyFrame *frame = new MyFrame("PassGen++ 1.0.4");

	// Set window dimensions (width, height)
	// Recommended size for proper control visibility
	frame->SetSize(500, 435);

	// Make the window visible
	frame->Show(true);

	// Return true to continue execution (false would exit the app).
	return true;
}

/**
 * Macro that implements main() and starts the application
 *
 * This wxWidgets macro:
 * 1. Generates the platform-specific main() entry point
 * 2. Creates an instance of MyApp
 * 3. Starts the event loop
 * */

wxIMPLEMENT_APP(MyApp);
