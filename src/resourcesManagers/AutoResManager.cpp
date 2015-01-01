////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
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

#include "MiraiProject/resourcesManagers/AutoResManager.hpp"
#include "MiraiProject/util/log.hpp"

using namespace std;

// ______________________________ Textures ______________________________
shared_ptr<sf::Texture> mp::AutoResManager::getTexture(const string &fileName)
{
    // Automatically load the texture if needed.
	if (textureIsAvailable(fileName) == false)
		loadTextureFromFile(fileName);
    
	return mp::BaseResManager::getTexture(fileName, false);
}

// ______________________________ Sound Buffers ______________________________
shared_ptr<sf::SoundBuffer> mp::AutoResManager::getSoundBuffer(const string &fileName)
{
    // Automatically load the sound buffer if needed.
	if (soundBufferIsAvailable(fileName) == false)
		loadSoundBufferFromFile(fileName);
    
	return mp::BaseResManager::getSoundBuffer(fileName, false);
}
