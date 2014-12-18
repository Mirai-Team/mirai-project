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
            static sf::RenderWindow window;
            static sf::View default_view;
			
			static bool fullscreen;
			static bool vertical_sync;
			static bool cursor_visible;

			static int optimal_win_width;
			static int optimal_win_height;

			static int videomode_width;
			static int videomode_height;
			
			static std::string window_name;
			

        public:
            /** Create or re-create the main window by using general configuration. */
            static void create();

            /** Setup black_borders sprite by loading black border texture (only once),
              * and setup the default_view based on main window (new) dimensions.
              */
            static void setup();

            /** Return a reference to the main window. */
            static sf::RenderWindow& get_window();

            /** Return a const reference to the default view. */
            static const sf::View& get_default_view();
			
			
			/** Return whether the main window is configured to be fullscreen or not. */
			static const bool& is_fullscreen();
			
			/** Configure the main window be fullscreen or not. */
			static void set_fullscreen(const bool& value);
			
			/** Return whether the main window is configured to be vertical synchronized or not. */
			static const bool& is_vertical_sync();
			
			/** Configure the main window to be vertical synchronized or not. */
			static void set_vertical_sync(const bool& value);
			
			/** Return whether the main window is configured to hide mouse cursor or not. */
			static const bool& is_cursor_visible();
			
			/** Configure the main window to hide mouse cursor or not. */
			static void set_cursor_visible(const bool& value);
			
			
			/** Return the main window optimal width. */
			static const int& get_optimal_win_width();
			
			/** Configure the main window optimal width. */
			static void set_optimal_win_width(const int& value);
			
			/** Return the main window optimal height. */
			static const int& get_optimal_win_height();
			
			/** Configure the main window optimal height. */
			static void set_optimal_win_height(const int& value);
			
			
			/** Return the main window videomode width. */
			static const int& get_videomode_width();
			
			/** Configure the main window videomode width. */
			static void set_videomode_width(const int& value);
			
			/** Return the main window videomode height. */
			static const int& get_videomode_height();
			
			/** Configure the main window videomode height. */
			static void set_videomode_height(const int& value);
			
			
			/** Return the main window name. */
			static const std::string& get_window_name();
			
			/** Configure the main window name. */
			static void set_videomode_height(const std::string& value);
    };
}

#endif // WINDOWMANAGER_HPP_INCLUDED
