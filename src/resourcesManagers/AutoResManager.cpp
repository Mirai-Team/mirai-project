#include <memory>
#include <map>

#include "resourcesManagers/AutoResManager.hpp"
#include "util/log.hpp"

using namespace std;

// ______________________________ Textures ______________________________
shared_ptr<sf::Texture> mp::AutoResManager::get_texture(const string &filename)
{
    // Automatically load the texture if needed.
	if (texture_is_available(filename) == false)
		load_texture_from_file(filename);
    
	return mp::BaseResManager::get_texture(filename, false);
}

// ______________________________ Sound Buffers ______________________________
shared_ptr<sf::SoundBuffer> mp::AutoResManager::get_sound_buffer(const string &filename)
{
    // Automatically load the sound buffer if needed.
	if (sound_buffer_is_available(filename) == false)
		load_sound_buffer_from_file(filename);
    
	return mp::BaseResManager::get_sound_buffer(filename, false);
}
