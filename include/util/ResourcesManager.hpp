#ifndef RESOUCESMANAGER_HPP_INCLUDED
#define RESOUCESMANAGER_HPP_INCLUDED

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

namespace mp
{
    /** A static class to handle resources through the program. */

    class ResourcesManager
    {
        private:
            static map<string, weak_ptr<sf::Texture>> textures_cache;
            static map<string, weak_ptr<sf::SoundBuffer>> sound_buffer_cache;

        public:
            /** Return the texture related to the given filename. */
            static shared_ptr<sf::Texture> get_texture(const string &filename);

            /** Return the sound buffer related to the given filename. */
            static shared_ptr<sf::SoundBuffer> get_sound_buffer(const string &filename);

            /** Clean textures and sound buffer cache. */
            static void clean();
    };
}

#endif // RESOUCESMANAGER_HPP_INCLUDED
