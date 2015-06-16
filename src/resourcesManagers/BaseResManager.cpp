////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "MiraiProject/resourcesManagers/BaseResManager.hpp"
#include "MiraiProject/util/Logger.hpp"

using namespace std;

mp::BaseResManager::BaseResManager() : texturesCache{ },
                                       soundBufferCache{ },
                                       fontCache{ },
                                       log_ { }
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
        log_ << mp::Logger::priorityError << "File " << fileName << " was not found... (for texture)";
        success = false;
    }

    texturesCache[fileName] = ptr_texture;

    return success;
}

bool mp::BaseResManager::loadTextureFromMemory(const string &fileName, const void *fileData, size_t fileSize)
{
    bool success{ true };

    shared_ptr<sf::Texture> ptr_texture{ new sf::Texture };
    ptr_texture->setSmooth(false);

    if (!ptr_texture->loadFromMemory(fileData, fileSize))
    {
        // File not found...
        log_ << mp::Logger::priorityError << "File " << fileName << " was not found... (for texture)";
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
        log_ << mp::Logger::priorityError << "File " << fileName << " was not found... (for sound)";
        success = false;
    }

    soundBufferCache[fileName] = ptr_sound_buffer;

    return success;
}

bool mp::BaseResManager::loadSoundBufferFromMemory(const string &fileName, const void *fileData, size_t fileSize)
{
    bool success{ true };

    shared_ptr<sf::SoundBuffer> ptr_sound_buffer{ new sf::SoundBuffer };

    if (!ptr_sound_buffer->loadFromMemory(fileData, fileSize))
    {
        // Sound not found...
        log_ << mp::Logger::priorityError << "File " << fileName << " was not found... (for sound)";
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

// ______________________________ Font ______________________________
shared_ptr<sf::Font> mp::BaseResManager::getFont(const string &fileName, const bool &safeMode)
{
    // Check if the font already exists...
    if (safeMode == false or fontIsAvailable(fileName))
        return fontCache[fileName];
    else
    {
        // The font doesen't exist. Return an empty font.
        shared_ptr<sf::Font> ptrFont{ new sf::Font };
        return move(ptrFont);
    }
}

bool mp::BaseResManager::loadFontFromFile(const string &fileName)
{
    bool success{ true };

    shared_ptr<sf::Font> ptrFont{ new sf::Font };

    if (!ptrFont->loadFromFile(fileName))
    {
        // Font not found...
        log_ << mp::Logger::priorityError << "File " << fileName << " was not found... (for font)";
        success = false;
    }

    fontCache[fileName] = ptrFont;

    return success;
}

bool mp::BaseResManager::loadFontFromMemory(const string &fileName, const void *fileData, size_t fileSize)
{
    bool success{ true };

    shared_ptr<sf::Font> ptrFont{ new sf::Font };

    if (!ptrFont->loadFromMemory(fileData, fileSize))
    {
        // Font not found...
        log_ << mp::Logger::priorityError << "File " << fileName << " was not found... (for font)";
        success = false;
    }

    fontCache[fileName] = ptrFont;

    return success;
}

bool mp::BaseResManager::fontIsAvailable(const string &fileName)
{
    // Check if the font already exists...
    if (fontCache.find(fileName) != fontCache.end())
        return true;
    else
        return false;
}

void mp::BaseResManager::clean()
{
    // ___________________ Clean textures cache... ___________________
    log_ << mp::Logger::priorityInfo << "Cleaning textures cache.";

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
    log_ << mp::Logger::priorityInfo << "Cleaning sound buffers cache.";

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

    // ___________________ Clean font cache... ___________________
    log_ << mp::Logger::priorityInfo << "Cleaning fonts cache.";

    keysToErase.clear(); // Clear keys_to_erase vector.

    for (map<string, shared_ptr<sf::Font>>::const_iterator it = fontCache.begin() ;
         it != fontCache.end() ;
         it++)
    {
        if (it->second.unique()) // If the last reference is keep by the resource manager.
            keysToErase.push_back(it->first);
    }

    for (const string &key : keysToErase)
        fontCache.erase(key);
}
