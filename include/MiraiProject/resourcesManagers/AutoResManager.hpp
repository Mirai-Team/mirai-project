#ifndef AUTORESMANAGER_HPP_INCLUDED
#define AUTORESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MiraiProject/resourcesManagers/BaseResManager.hpp"

/** \file AutoResManager.hpp
 * \brief This file contains AutoResManager class definition.
 */

namespace mp
{
	/** \class AutoResManager
	 * \brief A class to automatically handle resources (images and sounds).
	 * Though, you still have to clean resources using clean method.
	 */

    class AutoResManager : public BaseResManager
    {
		public:
            /** \brief Automatically load the texture if necessary and return it.
			 *
			 * \param fileName : the file name related to the wanted texture.
			 *
			 * \return the texture related to the given file name.
			 */
			std::shared_ptr<sf::Texture> getTexture(const std::string &fileName);
			
            /** \brief Automatically load the sound buffer if necessary and return it.
			 *
			 * \param fileName : the file name related to the wanted sound buffer.
			 *
			 * \return the sound buffer related to the given file name.
			 */
			std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string &fileName);
    };
}

#endif // AUTORESMANAGER_HPP_INCLUDED
