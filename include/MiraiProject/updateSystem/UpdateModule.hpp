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

#ifndef UPDATEMODULE_HPP_INCLUDED
#define UPDATEMODULE_HPP_INCLUDED

#include <memory>
#include <list>
#include <map>
#include <string>
#include <algorithm>

#include "MiraiProject/updateSystem/Updatable.hpp"

/** @file UpdateModule.hpp
 * 	\brief This file define UpdateModule class.
 */
 
namespace mp
{
	/** \class UpdateModule
	 * \brief Static class to update all Updatable based objects according to the map key.
	 */
	 
	class UpdateModule
	{
		// In order to prevent the user to call UpdateModule::AddUpdater, UpdateModule::RemoveUpdater, ...
		friend class Updatable;
		
		public:
			/** \brief Update all the Updatable stored in the update module by calling their update() method.
			 *
			 * \param deltaTime : time elapsed since last update.
			 * \param key : Map key to update.
			 */
			static void update(sf::Time deltaTime, std::string key);
			
		private:
			// Add an Updater in updatableList_
			static void addUpdater(Updatable* updatable, std::string key);
			
			// Remove an Updater from updatableList_
			static void removeUpdater(Updatable* updatable);
			
			// Objects list to update.
			static std::map<std::string, std::list<Updatable*>> updatableList_;
	};

}

#endif
