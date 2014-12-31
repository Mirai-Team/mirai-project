#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "MiraiProject/resourcesManagers/BaseResManager.hpp"
#include "MiraiProject/util/log.hpp"

using namespace std;

mp::BaseResManager::BaseResManager() : texturesCache{ },
                                       soundBufferCache{ }
{
	// constructor
}

mp::BaseResManager::~BaseResManager()
{
	// destructor
}

// ______________________________ Textures ______________________________
shared_ptr<sf::Texture> mp::BaseResManager::getTexture(const string &fileName, const bool &safeMode)
{
    // Check if the texture already exists...
    if (safeMode == false or textureIsAvailable(fileName))
        return texturesCache[fileName];
    else
    {
        // The texture doesen't exist. Return a empty texture.
        shared_ptr<sf::Texture> ptr_texture{ new sf::Texture };
        return move(ptr_texture);
    }
}

bool mp::BaseResManager::loadTextureFromFile(const string &fileName)
{
	bool success{ true };

    shared_ptr<sf::Texture> ptr_texture{ new sf::Texture };
    ptr_texture->setSmooth(false);

    if (!ptr_texture->loadFromFile(fileName))
	{
		// File not found...
        mp::log("mirai_project.log", mp::levelError, "File " + fileName + " was not found... (for texture)");
		success = false;
	}

    texturesCache[fileName] = ptr_texture;

	return success;
}

bool mp::BaseResManager::textureIsAvailable(const string &fileName)
{
    // Check if the texture is available in the resource manager.
    if (texturesCache.find(fileName) != texturesCache.end())
        return true;
    else
        return false;
}

// ______________________________ Sound Buffers ______________________________
shared_ptr<sf::SoundBuffer> mp::BaseResManager::getSoundBuffer(const string &fileName, const bool &safeMode)
{
    // Check if the sound buffer already exists...
    if (safeMode == false or soundBufferIsAvailable(fileName))
        return soundBufferCache[fileName];
    else
    {
        // The sound buffer doesen't exist. Return an empty sound buffer.
        shared_ptr<sf::SoundBuffer> ptr_sound_buffer{ new sf::SoundBuffer };
        return move(ptr_sound_buffer);
    }

}

bool mp::BaseResManager::loadSoundBufferFromFile(const string &fileName)
{
	bool success{ true };

    shared_ptr<sf::SoundBuffer> ptr_sound_buffer{ new sf::SoundBuffer };

    if (!ptr_sound_buffer->loadFromFile(fileName))
	{
		// Sound not found...
        mp::log("mirai_project.log", mp::levelError, "File " + fileName + " was not found... (for sound)");
		success = false;
	}

    soundBufferCache[fileName] = ptr_sound_buffer;

	return success;
}

bool mp::BaseResManager::soundBufferIsAvailable(const string &fileName)
{
    // Check if the sound buffer already exists...
    if (soundBufferCache.find(fileName) != soundBufferCache.end())
        return true;
    else
        return false;
}

void mp::BaseResManager::clean()
{
    // ___________________ Clean textures cache... ___________________
    mp::log("mirai_project.log", mp::levelInfo, "Cleaning textures cache.");

    vector<string> keysToErase;

    for (map<string, shared_ptr<sf::Texture>>::const_iterator it = texturesCache.begin() ;
         it != texturesCache.end() ;
         it++)
    {
        if (it->second.unique()) // If the last reference is keep by the resource manager.
            keysToErase.push_back(it->first);
    }

    for (const string &key : keysToErase)
        texturesCache.erase(key);

    // ___________________ Clean sound buffers cache... ___________________
    mp::log("mirai_project.log", mp::levelInfo, "Cleaning sound buffers cache.");

    keysToErase.clear(); // Clear keys_to_erase vector.

    for (map<string, shared_ptr<sf::SoundBuffer>>::const_iterator it = soundBufferCache.begin() ;
         it != soundBufferCache.end() ;
         it++)
    {
        if (it->second.unique()) // If the last reference is keep by the resource manager.
            keysToErase.push_back(it->first);
    }

    for (const string &key : keysToErase)
        soundBufferCache.erase(key);
}
