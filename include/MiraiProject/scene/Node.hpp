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

#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <memory>
#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace mp
{
    class Node : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
    {
        public:
            typedef std::shared_ptr<Node> childPtr;

            /** \brief Class constructor **/
            Node(const std::string& name="NA");

            /** \brief Class destructor **/
            virtual ~Node();

            sf::Vector2f getWorldPosition() const;

            sf::Transform getWorldTransform() const;

            float distance(const Node& otherNode) const;

            void addFrontChild(childPtr child);

            void addBackChild(childPtr child);

            void removeChildByName(const std::string& name);

            void removeChildById(const unsigned int& id);

            void clearChildren();

            std::vector<childPtr> getChildren();

            void setName(const std::string& newName);

            std::string getName();

            unsigned int getId();

        private:
            Node* parent_;

            std::vector<childPtr> frontChildren_;
            std::vector<childPtr> backChildren_;

            std::string name_;
            const unsigned int id_;

            static unsigned int sLastId;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

            void drawFrontChildren(sf::RenderTarget& target, sf::RenderStates states) const;

            void drawBackChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // NODE_HPP_INCLUDED
