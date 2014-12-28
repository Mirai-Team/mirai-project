#ifndef WINDOWMANAGER_HPP_INCLUDED
#define WINDOWMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

namespace mp
{
    /**
     * Static class to handle the main window.
     * Call create() to start using the main window.
     */

    class WindowManager
    {
        protected:
            static sf::RenderWindow window_;
            static sf::View defaultView_;
			
			static bool fullscreen_;
			static bool verticalSync_;
			static bool cursorVisible_;

			static int optimalWinWidth_;
			static int optimalWinHeight_;

			static int videomodeWidth_;
			static int videomodeHeight_;
			
			static std::string windowName_;
			

        public:
            /** Create or re-create the main window by using general configuration. */
            static void create();

            /** Setup black_borders sprite by loading black border texture (only once),
              * and setup the default_view based on main window (new) dimensions.
              */
            static void setup();

            /** Return a reference to the main window. */
            static sf::RenderWindow& getWindow();

            /** Return a const reference to the default view. */
            static const sf::View& getDefaultView();
			
			
			/** Return whether the main window is configured to be fullscreen or not. */
			static const bool& isFullscreen();
			
			/** Configure the main window be fullscreen or not. */
			static void setFullscreen(const bool& value);
			
			/** Return whether the main window is configured to be vertical synchronized or not. */
			static const bool& isVerticalSync();
			
			/** Configure the main window to be vertical synchronized or not. */
			static void setVerticalSync(const bool& value);
			
			/** Return whether the main window is configured to hide mouse cursor or not. */
			static const bool& isCursorVisible();
			
			/** Configure the main window to hide mouse cursor or not. */
			static void setCursorVisible(const bool& value);
			
			
			/** Return the main window optimal width. */
			static const int& getOptimalWinWidth();
			
			/** Configure the main window optimal width. */
			static void setOptimalWinWidth(const int& value);
			
			/** Return the main window optimal height. */
			static const int& getOptimalWinHeight();
			
			/** Configure the main window optimal height. */
			static void setOptimalWinHeight(const int& value);
			
			
			/** Return the main window videomode width. */
			static const int& getVideomodeWidth();
			
			/** Configure the main window videomode width. */
			static void setVideomodeWidth(const int& value);
			
			/** Return the main window videomode height. */
			static const int& getVideomodeHeight();
			
			/** Configure the main window videomode height. */
			static void setVideomodeHeight(const int& value);
			
			
			/** Return the main window name. */
			static const std::string& getWindowName();
			
			/** Configure the main window name. */
			static void setVideomodeHeight(const std::string& value);
    };
}

#endif // WINDOWMANAGER_HPP_INCLUDED
