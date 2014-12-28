#ifndef RESOUCESMANAGER_HPP_INCLUDED
#define RESOUCESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace mp
{
    /** A class to handle resources through the program. */

    class BaseResManager
    {
        private:
            std::map<std::string, std::shared_ptr<sf::Texture>> texturesCache;
            std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBufferCache;

        public:
            /** Class constructor **/
            BaseResManager();

			virtual ~BaseResManager();
			
            /** Return the texture related to the given filename.
			 * Set safe_mode parameter to false if you want avoid checking the texture existence.
			 * Do it only if you know what you're doing, it could make your program crash if you try to get
			 * a non loaded texture.
			 */
            std::shared_ptr<sf::Texture> getTexture(const std::string &fileName, const bool &safeMode);

            /** Load texture from file by the filename. */
            bool loadTextureFromFile(const std::string &fileName);

            /** Return whether the given texture related to the given filename exists. */
            bool textureIsAvailable(const std::string &fileName);

            /** Return the sound buffer related to the given filename.
			 * Set safe_mode parameter to false if you want avoid checking the sound buffer existence.
			 * Do it only if you know what you're doing, it could make your program crash if you try to get
			 * a non loaded sound buffer.
			 */
            std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string &fileName, const bool &safeMode);

            /** Load sound buffer from file by the filename. */
            bool loadSoundBufferFromFile(const std::string &fileName);

            /** Return whether the given sound buffer related to the given filename exists. */
            bool soundBufferIsAvailable(const std::string &fileName);
			
			/** Clean textures and sound buffer cache. */
			void clean();
    };
}

#endif // RESOUCESMANAGER_HPP_INCLUDED
