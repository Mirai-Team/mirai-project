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

#ifndef BASERESMANAGER_HPP_INCLUDED
#define BASERESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MiraiProject/util/Logger.hpp"

/** \file BaseResManager.hpp
 * \brief This file contains BaseResManager class definition.
 */

namespace mp
{
	/** \class BaseResManager
	 * \brief A class to handle resources (images and sounds).
	 */
	
    class BaseResManager
    {
        public:
            /** \brief Class constructor **/
            BaseResManager();

			/** \brief Class destructor **/
			virtual ~BaseResManager();
			
			
            /** \brief Get back a loaded texture.
			 *
			 * \param fileName : the file name related to the wanted texture.
			 * \param safeMode : set to false if you want to disable the texture existence check (faster).
			 * 		Do it only if you know what you're doing, your program may crash if you try to get
			 * 		a non loaded texture.
			 *
			 * \return the texture related to the given file name.
			 */
            std::shared_ptr<sf::Texture> getTexture(const std::string &fileName, const bool &safeMode);

            /** \brief Load texture into cache from file by the file name. 
			 *
			 * \param fileName : the file name related to the wanted file.
			 *
			 * \return a boolean about operation success.
			 */
            bool loadTextureFromFile(const std::string &fileName);
            
            /** \brief Load texture into cache from memory. 
			 *
			 * \param fileName : the file name related to the wanted file.
			 * \param fileData : fileData ptr.
			 * \param fileSize : Size of file.
			 * 
			 * \return a boolean about operation success.
			 */
            bool loadTextureFromMemory(const std::string &fileName, const void *fileData, std::size_t fileSize);

            /** \brief Return whether the given texture related to the given file name exists. 
			 *
			 * \param fileName : the file name related to the wanted texture.
			 *
			 * \return a boolean about texture existence.
			 */
            bool textureIsAvailable(const std::string &fileName);
			
			
            /** \brief Get back a loaded sound buffer.
			 *
			 * \param fileName : the file name related to the wanted sound buffer.
			 * \param safeMode : set to false if you want to disable the sound buffer existence check (faster).
			 * 		Do it only if you know what you're doing, your program may crash if you try to get
			 * 		a non loaded sound buffer.
			 *
			 * \return the sound buffer related to the given file name.
			 */
            std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string &fileName, const bool &safeMode);

            /** \brief Load sound buffer into cache from file by the file name. 
			 *
			 * \param fileName : the file name related to the wanted file.
			 *
			 * \return a boolean about operation success.
			 */
            bool loadSoundBufferFromFile(const std::string &fileName);
            
            /** \brief Load sound buffer into cache from memory. 
			 *
			 * \param fileName : the file name related to the wanted file.
			 * \param fileData : fileData ptr.
			 * \param fileSize : Size of file.
			 * \return a boolean about operation success.
			 */
            bool loadSoundBufferFromMemory(const std::string &fileName, const void *fileData, std::size_t fileSize);

            /** \brief Return whether the given sound buffer related to the given file name exists. 
			 *
			 * \param fileName : the file name related to the wanted sound buffer.
			 *
			 * \return a boolean about sound buffer existence.
			 */
            bool soundBufferIsAvailable(const std::string &fileName);
			
			
            /** \brief Get back a loaded font.
             *
             * \param fileName : the file name related to the wanted font.
             * \param safeMode : set to false if you want to disable the font existence check (faster).
             *      Do it only if you know what you're doing, your program may crash if you try to get
             *      a non loaded font.
             *
             * \return the font related to the given file name.
             */
            std::shared_ptr<sf::Font> getFont(const std::string &fileName, const bool &safeMode);

            /** \brief Load Font into cache from file by the file name. 
             *
             * \param fileName : the file name related to the wanted file.
             *
             * \return a boolean about operation success.
             */
            bool loadFontFromFile(const std::string &fileName);
            
            /** \brief Load font into cache from memory. 
             *
             * \param fileName : the file name related to the wanted file.
             * \param fileData : fileData ptr.
             * \param fileSize : Size of file.
             * 
             * \return a boolean about operation success.
             */
            bool loadFontFromMemory(const std::string &fileName, const void *fileData, std::size_t fileSize);

            /** \brief Return whether the given font related to the given file name exists. 
             *
             * \param fileName : the file name related to the wanted font.
             *
             * \return a boolean about font existence.
             */
            bool fontIsAvailable(const std::string &fileName);


			/** \brief Automatically clean unused textures, sound buffers cache and fonts cache. */
			void clean();
			
        private:
            std::map<std::string, std::shared_ptr<sf::Texture>> texturesCache;
            std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBufferCache;
            std::map<std::string, std::shared_ptr<sf::Font>> fontCache;
            Logger log_;
    };
}

#endif // BASERESMANAGER_HPP_INCLUDED
