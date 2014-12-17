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

            /** Return the texture related to the given filename. */
            std::shared_ptr<sf::Texture> get_texture(const std::string &filename);

            /** Load texture from file by the filename. */
            void load_texture_from_file(const std::string &filename);

            /** Return whether the given texture related to the given filename exists. */
            bool texture_is_available(const std::string &filename);

            /** Return the sound buffer related to the given filename. */
            std::shared_ptr<sf::SoundBuffer> get_sound_buffer(const std::string &filename);

            /** Load sound buffer from file by the filename. */
            void load_sound_buffer_from_file(const std::string &filename);

            /** Return whether the given sound buffer related to the given filename exists. */
            bool sound_buffer_is_available(const std::string &filename);

            /** Clean textures and sound buffer cache. */
            void clean();
    };
}

#endif // RESOUCESMANAGER_HPP_INCLUDED
