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
