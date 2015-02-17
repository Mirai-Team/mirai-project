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

#include <cassert>
#include <cmath>

#include "MiraiProject/scene/SceneNode.hpp"

using namespace mp;

SceneNode::SceneNode() : parent_{ nullptr },
                         children_{ }
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::attachChild(std::unique_ptr<SceneNode> child)
{
    child->parent_ = this;
    children_.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(children_.begin(), children_.end(), 
                                [&] (std::unique_ptr<SceneNode>& child) -> bool 
                                { 
                                    return child.get() == &node; 
                                }
                             );

    // Check for validity.
    assert(found != children_.end());

    std::unique_ptr<SceneNode> result { std::move(*found) };
    result->parent_ = nullptr;

    // Erase empty element from children_ vector.
    children_.erase(found);

    return result;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->parent_)
        transform = node->getTransform() * transform;

    return transform;
}

float SceneNode::distance(const SceneNode& otherNode) const
{
    sf::Vector2f vector { getWorldPosition() - otherNode.getWorldPosition() };
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const std::unique_ptr<SceneNode>& child : children_)
        child->draw(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Do nothing by default
}
