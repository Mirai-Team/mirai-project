#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "resourcesManagers/BaseResManager.hpp"
#include "util/log.hpp"

using namespace std;

mp::BaseResManager::BaseResManager() : textures_cache{ },
                                       sound_buffer_cache{ }
{
}

// ______________________________ Textures ______________________________
shared_ptr<sf::Texture> mp::BaseResManager::get_texture(const string &filename, const bool &safe_mode)
{
    // Check if the texture already exists...
    if (safe_mode == false or texture_is_available(filename))
        return textures_cache[filename];
    else
    {
        // The texture doesen't exist. Return a empty texture.
        shared_ptr<sf::Texture> ptr_texture{ new sf::Texture };
        return move(ptr_texture);
    }
}

bool mp::BaseResManager::load_texture_from_file(const string &filename)
{
	bool success{ true };
	
    shared_ptr<sf::Texture> ptr_texture{ new sf::Texture };
    ptr_texture->setSmooth(false);

    if (!ptr_texture->loadFromFile(filename))
	{
		// File not found...
        mp::log("mirai_project.log", mp::level_warning, "File " + filename + " was not found... (for texture)");
		success = false;
	}

    textures_cache[filename] = ptr_texture;
	
	return success;
}

bool mp::BaseResManager::texture_is_available(const string &filename)
{
    // Check if the texture is available in the resource manager.
    if (textures_cache.find(filename) != textures_cache.end())
        return true;
    else
        return false;
}

// ______________________________ Sound Buffers ______________________________
shared_ptr<sf::SoundBuffer> mp::BaseResManager::get_sound_buffer(const string &filename, const bool &safe_mode)
{
    // Check if the sound buffer already exists...
    if (safe_mode == false or sound_buffer_is_available(filename))
        return sound_buffer_cache[filename];
    else
    {
        // The sound buffer doesen't exist. Return an empty sound buffer.
        shared_ptr<sf::SoundBuffer> ptr_sound_buffer{ new sf::SoundBuffer };
        return move(ptr_sound_buffer);
    }

}

bool mp::BaseResManager::load_sound_buffer_from_file(const string &filename)
{
	bool success{ true };
	
    shared_ptr<sf::SoundBuffer> ptr_sound_buffer{ new sf::SoundBuffer };

    if (!ptr_sound_buffer->loadFromFile(filename))
	{
		// Sound not found...
        mp::log("mirai_project.log", mp::level_error, "File " + filename + " was not found... (for sound)");
		success = false;
	}

    sound_buffer_cache[filename] = ptr_sound_buffer;
	
	return success;
}

bool mp::BaseResManager::sound_buffer_is_available(const string &filename)
{
    // Check if the sound buffer already exists...
    if (sound_buffer_cache.find(filename) != sound_buffer_cache.end())
        return true;
    else
        return false;
}

void mp::BaseResManager::clean()
{
    // ___________________ Clean textures cache... ___________________
    mp::log("mirai_project.log", mp::level_info, "Cleaning textures cache.");

    vector<string> keys_to_erase;

    for (map<string, shared_ptr<sf::Texture>>::const_iterator it = textures_cache.begin() ;
         it != textures_cache.end() ;
         it++)
    {
        if (it->second.unique()) // If the last reference is keep by the resource manager.
            keys_to_erase.push_back(it->first);
    }

    for (const string &key : keys_to_erase)
        textures_cache.erase(key);

    // ___________________ Clean sound buffers cache... ___________________
    mp::log("mirai_project.log", mp::level_info, "Cleaning sound buffers cache.");

    keys_to_erase.clear(); // Clear keys_to_erase vector.

    for (map<string, shared_ptr<sf::SoundBuffer>>::const_iterator it = sound_buffer_cache.begin() ;
         it != sound_buffer_cache.end() ;
         it++)
    {
        if (it->second.unique()) // If the last reference is keep by the resource manager.
            keys_to_erase.push_back(it->first);
    }

    for (const string &key : keys_to_erase)
        sound_buffer_cache.erase(key);
}
