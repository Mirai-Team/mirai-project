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

#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED

#include <memory>
#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace mp
{
    class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
    {
        public:
            /** \brief Class constructor **/
            SceneNode();

            /** \brief Class destructor **/
            virtual ~SceneNode();

            void attachChild(std::unique_ptr<SceneNode> child);

            std::unique_ptr<SceneNode> detachChild(const SceneNode& node);

            sf::Vector2f getWorldPosition() const;

            sf::Transform getWorldTransform() const;

            float distance(const SceneNode& otherNode) const;

        private:
            SceneNode* parent_;
            std::vector<std::unique_ptr<SceneNode>> children_;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

            void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // SCENENODE_HPP_INCLUDED
