////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef WINDOWMANAGER_HPP_INCLUDED
#define WINDOWMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

/** \file WindowManager.hpp
 * \brief This file contains the WindowManager class definition.
 */

namespace mp
{
	/** \class WindowManager
	 * \brief A class to handle a window.
	 *
	 * Call create() method to start using a new window.
	 * This class handle window ratio problems automatically.
	 */

    class WindowManager
    {
        public:
            /** \brief Class constructor.
             *
             * \param fullscreen : set fullscreen mode or not.
             * \param verticalSync : set verticalSync mode or not.
			 * \param cursorVisible : set cursor visible or not.
			 * \param optimalWinWidth : set optimal window width value.
			 * \param optimalWinHeight : set optimal window height value.
			 * \param videoModeWidth : set video mode width value.
			 * \param videoModeHeight : set video mode height value.
			 * \param windowName : set window name.
             */
			WindowManager(const bool& fullscreen=false, const bool& verticalSync=false, const bool& cursorVisible=false,
						  const int& optimalWinWidth=1024, const int& optimalWinHeight=768, 
						  const int& videoModeWidth=1024, const int& videoModeHeight=768,
						  const std::string& windowName="SFML Window");
			
			/** \brief Class destructor **/
			virtual ~WindowManager();
			
		
            /** \brief Create or re-create the window by using general configuration. */
            void create();

            /** \brief Prepare the window to be used. */
            void setup();

            /** \return a reference to the window. */
            sf::RenderWindow& getWindow();

            /** \return a const reference to the default view. */
            const sf::View& getDefaultView() const;
			
			
			/** \return whether the window is configured to be fullscreen or not. */
			const bool& isFullscreen() const;
			
			/** \brief Configure the window be fullscreen or not. 
			 *
			 * \param fullscreen : value to set for fullscreen.
			 */
			void setFullscreen(const bool& fullscreen);
			
			/** \return whether the window is configured to be vertical synchronized or not. */
			const bool& isVerticalSync() const;
			
			/** \brief Configure the window to be vertical synchronized or not. 
			 *
			 * \param verticalSync : value to set for verticalSync.
			 */
			void setVerticalSync(const bool& verticalSync);
			
			/** \return whether the window is configured to hide mouse cursor or not. */
			const bool& isCursorVisible() const;
			
			/** \brief Configure the window to hide mouse cursor or not. 
			 *
			 * \param cursorVisible : value to set for cursor visibility.
			 */
			void setCursorVisible(const bool& cursorVisible);
			
			
			/** \return the window optimal width. */
			const int& getOptimalWinWidth() const;
			
			/** \brief Configure the window optimal width. 
			 *
			 * \param optimalWinWidth : value to set for optimal window width.
			 */
			void setOptimalWinWidth(const int& optimalWinWidth);
			
			/** \return the window optimal height. */
			const int& getOptimalWinHeight() const;
			
			/** \brief Configure the window optimal height. 
			 *
			 * \param optimalWinHeight : value to set for optimal window height.
			 */
			void setOptimalWinHeight(const int& optimalWinHeight);
			
			
			/** \return the window videomode width. */
			const int& getVideomodeWidth() const;
			
			/** \brief Configure the window videomode width. 
			 *
			 * \param videoModeWidth : value to set for video mode width.
			 */
			void setVideomodeWidth(const int& videoModeWidth) ;
			
			/** \return the main window videomode height. */
			const int& getVideomodeHeight() const;
			
			/** \brief Configure the main window videomode height. 
			 *
			 * \param videoModeHeight : value to set for video mode height.
			 */
			void setVideomodeHeight(const int& videoModeHeight);
			
			
			/** \return the main window name. */
			const std::string& getWindowName() const;
			
			/** \brief Configure the main window name. 
			 *
			 * \param windowName : the new window's name.
			 */
			void setWindowName(const std::string& windowName);
			
        private:
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
    };
}

#endif // WINDOWMANAGER_HPP_INCLUDED
