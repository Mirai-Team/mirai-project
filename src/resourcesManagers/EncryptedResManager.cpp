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

#include "MiraiProject/resourcesManagers/EncryptedResManager.hpp"
#include "MiraiProject/encryption/Encryption.hpp"

using namespace std;

// ______________________________ Textures ______________________________
shared_ptr<sf::Texture> mp::EncryptedResManager::getTexture(const string &fileName, const string &inputFile, const string &key)
{
	mp::Encryption encryptMotor(key);
	string fileData = encryptMotor.loadFile(inputFile, fileName);
	
	size_t fileSize = fileData.size();
    // Automatically load the texture if needed.
	if (textureIsAvailable(fileName) == false)
		loadTextureFromMemory(fileName, &fileData, fileSize);
    
	return mp::BaseResManager::getTexture(fileName, false);
}

// ______________________________ Sound Buffers ______________________________
shared_ptr<sf::SoundBuffer> mp::EncryptedResManager::getSoundBuffer(const string &fileName, const string &inputFile, const string &key)
{
    mp::Encryption encryptMotor(key);
	string fileData = encryptMotor.loadFile(inputFile, fileName);
	
	size_t fileSize = fileData.size();
    // Automatically load the texture if needed.
	if (soundBufferIsAvailable(fileName) == false)
		loadSoundBufferFromMemory(fileName, &fileData, fileSize);
    
	return mp::BaseResManager::getSoundBuffer(fileName, false);
}

