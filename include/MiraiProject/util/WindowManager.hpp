#ifndef WINDOWMANAGER_HPP_INCLUDED
#define WINDOWMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

namespace mp
{
    /**
     * Class to handle a window.
     * Call create() to start using the window.
     */

    class WindowManager
    {
        protected:
            sf::RenderWindow window_;
            sf::View defaultView_;
			
			bool fullscreen_;
			bool verticalSync_;
			bool cursorVisible_;

			int optimalWinWidth_;
			int optimalWinHeight_;

			int videoModeWidth_;
			int videoModeHeight_;
			
			std::string windowName_;
			

        public:
			/** Class Constructor. */
			WindowManager(const bool& fullscreen=false, const bool& verticalSync=false, const bool& cursorVisible=false,
						  const int& optimalWinWidth=1024, const int& optimalWinHeight=768, 
						  const int& videoModeWidth=1024, const int& videoModeHeight=768,
						  const std::string& windowName="SFML Window");
			
			virtual ~WindowManager();
			
		
            /** Create or re-create the window by using general configuration. */
            void create();

            /** Setup black_borders sprite by loading black border texture (only once),
              * and setup the default_view based on window (new) dimensions.
              */
            void setup();

            /** Return a reference to the window. */
            sf::RenderWindow& getWindow();

            /** Return a const reference to the default view. */
            const sf::View& getDefaultView() const;
			
			
			/** Return whether the window is configured to be fullscreen or not. */
			const bool& isFullscreen() const;
			
			/** Configure the window be fullscreen or not. */
			void setFullscreen(const bool& value);
			
			/** Return whether the window is configured to be vertical synchronized or not. */
			const bool& isVerticalSync() const;
			
			/** Configure the window to be vertical synchronized or not. */
			void setVerticalSync(const bool& value);
			
			/** Return whether the window is configured to hide mouse cursor or not. */
			const bool& isCursorVisible() const;
			
			/** Configure the window to hide mouse cursor or not. */
			void setCursorVisible(const bool& value);
			
			
			/** Return the window optimal width. */
			const int& getOptimalWinWidth() const;
			
			/** Configure the window optimal width. */
			void setOptimalWinWidth(const int& value);
			
			/** Return the window optimal height. */
			const int& getOptimalWinHeight() const;
			
			/** Configure the window optimal height. */
			void setOptimalWinHeight(const int& value);
			
			
			/** Return the window videomode width. */
			const int& getVideomodeWidth() const;
			
			/** Configure the window videomode width. */
			void setVideomodeWidth(const int& value) ;
			
			/** Return the main window videomode height. */
			const int& getVideomodeHeight() const;
			
			/** Configure the main window videomode height. */
			void setVideomodeHeight(const int& value);
			
			
			/** Return the main window name. */
			const std::string& getWindowName() const;
			
			/** Configure the main window name. */
			void setVideomodeHeight(const std::string& value);
    };
}

#endif // WINDOWMANAGER_HPP_INCLUDED
