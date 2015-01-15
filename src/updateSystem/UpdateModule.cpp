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

#include <algorithm>

#include "MiraiProject/updateSystem/UpdateModule.hpp"
#include "MiraiProject/updateSystem/Updatable.hpp"

std::list<mp::Updatable*> mp::UpdateModule::updatableList_;

void mp::UpdateModule::update(float deltaTime)
{
	if(updatableList_.size() > 0)
	{
		for_each(updatableList_.begin(), updatableList_.end(), [&](mp::Updatable* p)
		{
			p->update(deltaTime);
		});
	}
}

void mp::UpdateModule::addUpdater(mp::Updatable* updatable)
{
	updatableList_.push_back(updatable);
}

void mp::UpdateModule::removeUpdater(Updatable* updatable)
{
	updatableList_.remove_if([updatable] (Updatable* p) { 
		return p == updatable;
	});
}
