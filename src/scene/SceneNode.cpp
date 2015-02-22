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

unsigned int SceneNode::sLastId { 0 };

SceneNode::SceneNode(const std::string& name) : parent_{ nullptr },

                                                frontChildren_{ },
                                                backChildren_{ },
                                            
                                                name_{ name },
                                                id_{ sLastId + 1 }
{
    sLastId++;
}

SceneNode::~SceneNode()
{
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


void SceneNode::addFrontChild(childPtr child)
{
    child->parent_ = this;
    frontChildren_.push_back(child);
}

void SceneNode::addBackChild(childPtr child)
{
    child->parent_ = this;
    backChildren_.push_back(child);
}

void SceneNode::removeChildByName(const std::string& name)
{
    std::vector<childPtr> children{ getChildren() };

    for (unsigned int i = 0; i < children.size(); )
    {
        if (children[i]->name_ == name)
        {
            children[i]->parent_ = nullptr;

            if (i < frontChildren_.size())
                frontChildren_.erase(frontChildren_.begin() + i);
            else
                backChildren_.erase(frontChildren_.begin() + (i - frontChildren_.size()));
        }
        else
        {
            i++;
        }
    }
}

void SceneNode::removeChildById(const unsigned int& id)
{
    std::vector<childPtr> children{ getChildren() };

    for (unsigned int i = 0; i < children.size(); i++)
    {
        if (children[i]->id_ == id)
        {
            children[i]->parent_ = nullptr;

            if (i < frontChildren_.size())
                frontChildren_.erase(frontChildren_.begin() + i);
            else
                backChildren_.erase(frontChildren_.begin() + (i - frontChildren_.size()));

            break;
        }
    }
}

void SceneNode::clearChildren()
{
    for (childPtr child : getChildren())
        child->parent_ = nullptr;

    frontChildren_.clear();
    backChildren_.clear();
}

std::vector<SceneNode::childPtr> SceneNode::getChildren()
{
    std::vector<childPtr> children{ };
    children.insert(children.end(), frontChildren_.begin(), frontChildren_.end());
    children.insert(children.end(), backChildren_.begin(), backChildren_.end());

    return children;
}

void SceneNode::setName(const std::string& newName)
{
    name_ = newName;
}

std::string SceneNode::getName()
{
    return name_;
}

unsigned int SceneNode::getId()
{
    return id_;
}

///////////////
/// Private ///
///////////////

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    drawBackChildren(target, states);
    drawCurrent(target, states);
    drawFrontChildren(target, states);
}

void SceneNode::drawFrontChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const childPtr& child : frontChildren_)
        child->draw(target, states);
}

void SceneNode::drawBackChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const childPtr& child : backChildren_)
        child->draw(target, states);
}
