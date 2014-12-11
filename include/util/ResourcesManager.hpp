#ifndef RESOUCESMANAGER_HPP_INCLUDED
#define RESOUCESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace mp
{
    /** A static class to handle resources through the program. */

    class ResourcesManager
    {
        private:
            static std::map<std::string, std::weak_ptr<sf::Texture>> textures_cache;
            static std::map<std::string, std::weak_ptr<sf::SoundBuffer>> sound_buffer_cache;

        public:
            /** Return the texture related to the given filename. */
            static std::shared_ptr<sf::Texture> get_texture(const std::string &filename);

            /** Return the sound buffer related to the given filename. */
            static std::shared_ptr<sf::SoundBuffer> get_sound_buffer(const std::string &filename);

            /** Clean textures and sound buffer cache. */
            static void clean();
    };
}

#endif // RESOUCESMANAGER_HPP_INCLUDED
