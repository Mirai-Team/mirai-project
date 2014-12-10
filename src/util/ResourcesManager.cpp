#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "util/ResourcesManager.hpp"
#include "util/log.hpp"

using namespace std;

map<string, weak_ptr<sf::Texture>> mp::ResourcesManager::textures_cache{ };
map<string, weak_ptr<sf::SoundBuffer>> mp::ResourcesManager::sound_buffer_cache{ };

// ______________________________ Textures ______________________________
shared_ptr<sf::Texture> mp::ResourcesManager::get_texture(const string &filename)
{
    // Check if the texture already exists...
    if (textures_cache.find(filename) != textures_cache.end())
    {
        if (textures_cache[filename].expired()) // Check if texture still exists.
            textures_cache.erase(filename);
        else
            return textures_cache[filename].lock();
    }

    // The texture doesen't exist. Create it and save it.
    shared_ptr<sf::Texture> ptr_texture{ new sf::Texture };
    ptr_texture->setSmooth(false);

    if (!ptr_texture->loadFromFile(filename))
    {
        // File not found...
        mp::log("mirai_project.log", mp::level_warning, "File " + filename + " was not found... (for texture)");
        //ptr_texture->loadFromFile("path/to/image/file_not_found.png"); // Set an not found image if no image found.
    }

    textures_cache[filename] = ptr_texture; // Convert into weak_ptr automatically.

    return move(ptr_texture);
}

// ______________________________ Sound Buffers ______________________________
shared_ptr<sf::SoundBuffer> mp::ResourcesManager::get_sound_buffer(const string &filename)
{
    // Check if the sound buffer already exists...
    if (sound_buffer_cache.find(filename) != sound_buffer_cache.end())
    {
        if (sound_buffer_cache[filename].expired()) // Check if texture still exists.
            sound_buffer_cache.erase(filename);
        else
            return sound_buffer_cache[filename].lock();
    }

    // The sound buffer doesen't exist. Create it and save it.
    shared_ptr<sf::SoundBuffer> ptr_sound_buffer{ new sf::SoundBuffer };

    if (!ptr_sound_buffer->loadFromFile(filename)) // Sound not found...
        mp::log("mirai_project.log", mp::level_error, "File " + filename + " was not found... (for sound)");

    sound_buffer_cache[filename] = ptr_sound_buffer; // Convert into weak_ptr automatically.

    return move(ptr_sound_buffer);
}

void mp::ResourcesManager::clean()
{
    // ___________________ Clean textures cache... ___________________
    mp::log("mirai_project.log", mp::level_info, "Cleaning textures cache.");

    vector<string> keys_to_erase;

    for (map<string, weak_ptr<sf::Texture>>::const_iterator it = textures_cache.begin() ;
         it != textures_cache.end() ;
         it++)
    {
        if (it->second.use_count() == 0)
            keys_to_erase.push_back(it->first);
    }

    for (const string &key : keys_to_erase)
        textures_cache.erase(key);

    // ___________________ Clean sound buffers cache... ___________________
    mp::log("mirai_project.log", mp::level_info, "Cleaning sound buffers cache.");

    keys_to_erase.clear(); // Clear keys_to_erase vector.

    for (map<string, weak_ptr<sf::SoundBuffer>>::const_iterator it = sound_buffer_cache.begin() ;
         it != sound_buffer_cache.end() ;
         it++)
    {
        if (it->second.use_count() == 0)
            keys_to_erase.push_back(it->first);
    }

    for (const string &key : keys_to_erase)
        sound_buffer_cache.erase(key);
}
