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
            std::map<std::string, std::shared_ptr<sf::Texture>> textures_cache;
            std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sound_buffer_cache;

        public:
            /** Class constructor **/
            BaseResManager();

            /** Return the texture related to the given filename.
			 * Set safe_mode parameter to false if you want avoid checking the texture existence.
			 * Do it only if you know what you're doing, it could make your program crash if you try to get
			 * a non loaded texture.
			 */
            std::shared_ptr<sf::Texture> get_texture(const std::string &filename, const bool &safe_mode);

            /** Load texture from file by the filename. */
            bool load_texture_from_file(const std::string &filename);

            /** Return whether the given texture related to the given filename exists. */
            bool texture_is_available(const std::string &filename);

            /** Return the sound buffer related to the given filename.
			 * Set safe_mode parameter to false if you want avoid checking the sound buffer existence.
			 * Do it only if you know what you're doing, it could make your program crash if you try to get
			 * a non loaded sound buffer.
			 */
            std::shared_ptr<sf::SoundBuffer> get_sound_buffer(const std::string &filename, const bool &safe_mode);

            /** Load sound buffer from file by the filename. */
            bool load_sound_buffer_from_file(const std::string &filename);

            /** Return whether the given sound buffer related to the given filename exists. */
            bool sound_buffer_is_available(const std::string &filename);
			
			/** Clean textures and sound buffer cache. */
			void clean();
    };
}

#endif // RESOUCESMANAGER_HPP_INCLUDED
