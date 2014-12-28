#ifndef AUTORESMANAGER_HPP_INCLUDED
#define AUTORESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MiraiProject/resourcesManagers/BaseResManager.hpp"

namespace mp
{
    /** A class to automatically handle resources through the program. */

    class AutoResManager : public BaseResManager
    {
		public:
			/** Return the texture related to the given filename.
			 * If no texture found, it automatically load it.
			 */
			std::shared_ptr<sf::Texture> getTexture(const std::string &fileName);
			
			/** Return the sound buffer related to the given filename. 
			 * If no sound buffer found, it automatically load it.
			 */
			std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string &fileName);
    };
}

#endif // AUTORESMANAGER_HPP_INCLUDED
