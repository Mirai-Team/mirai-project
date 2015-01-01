#ifndef RESOUCESMANAGER_HPP_INCLUDED
#define RESOUCESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        private:
            std::map<std::string, std::shared_ptr<sf::Texture>> texturesCache;
            std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBufferCache;

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

            /** \brief Return whether the given sound buffer related to the given file name exists. 
			 *
			 * \param fileName : the file name related to the wanted sound buffer.
			 *
			 * \return a boolean about sound buffer existence.
			 */
            bool soundBufferIsAvailable(const std::string &fileName);
			
			
			/** \brief Automatically clean unused textures and sound buffers cache. */
			void clean();
    };
}

#endif // RESOUCESMANAGER_HPP_INCLUDED
