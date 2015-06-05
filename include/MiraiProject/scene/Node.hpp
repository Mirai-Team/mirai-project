////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
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

/** \file Node.hpp
 * \brief This file contains Node class definition.
 */

namespace mp
{
    /** \class Node
     * \brief A class to represent and manage a scene graph.
     *
     * A node can have front and back children. Children are drawn
     * with the parent. Front children are drawn after the parent,
     * and back children are drawn before.
     *
     * The virtual method drawCurrent() should be overloaded (just to
     * draw THIS node, not to draw children, operation which is
     * automatically performed).
     */

    class Node : public sf::Transformable, public sf::Drawable
    {
        public:
            typedef std::shared_ptr<Node> childPtr;

            /** \brief Class constructor **/
            Node(const std::string& name="NA");

            /** \brief Class destructor **/
            virtual ~Node();

            /** \brief Make class non-copyable **/
            Node(const Node&) = delete;

            /** \brief Make class non-copyable **/
            Node& operator=(const Node&) = delete;

            /** \brief Return node's absolute position.
             *
             * \return the absolute position.
             */
            sf::Vector2f getWorldPosition() const;

            /** \brief Return node's absolute transform.
             *
             * \return the absolute transform.
             */
            sf::Transform getWorldTransform() const;

            /** \brief Return the distance between this node and another one.
             *
             * \param otherNode : this other one.
             *
             * \return the distance between them.
             */
            float distance(const Node& otherNode) const;

            /** \brief Add a front child
             *
             * \param child : the child to add on the front.
             */
            void addFrontChild(childPtr child);

            /** \brief Add a back child
             *
             * \param child : the child to add on the back.
             */
            void addBackChild(childPtr child);

            /** \brief Remove children matching the given name.
             *
             * \param name : the name.
             */
            void removeChildByName(const std::string& name);

            /** \brief Remove the child matching the given id.
             *
             * \param id : the id.
             */
            void removeChildById(const unsigned int& id);

            /** \brief Remove all children. */
            void clearChildren();

            /** \brief Return a vector containing pointer to all children.
             *
             * \return the vector containing pointer to all children.
             */
            std::vector<childPtr> getChildren();

            /** \brief Change node's name.
             *
             * \param newName : the new name.
             */
            void setName(const std::string& newName);

            /** \brief Return node's name.
             *
             * \return the name.
             */
            std::string getName();

            /** \brief Return node's id.
             *
             * \return the id.
             */
            unsigned int getId();

        protected:
            /** \brief Draw the node to a render target.
             *
             * This is a pure virtual function that has to be implemented by the derived
             * class to define how the node should be drawn.
             *
             * \param target : the render target.
             * \param states : the current states.
             */
            virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

            void drawFrontChildren(sf::RenderTarget& target, sf::RenderStates states) const;

            void drawBackChildren(sf::RenderTarget& target, sf::RenderStates states) const;

            Node* parent_;

            std::vector<childPtr> frontChildren_;
            std::vector<childPtr> backChildren_;

            std::string name_;
            const unsigned int id_;

            static unsigned int sLastId;
    };
}

#endif // NODE_HPP_INCLUDED
