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

#ifndef CHECK_BOX_HPP
#define CHECK_BOX_HPP

#include <functional>
#include <memory>

#include "MiraiProject/gui/ClickableWidget.hpp"

namespace mp
{
    class CheckBox : public ClickableWidget
    {
        public:
            CheckBox();

            void setNormalTexture(const std::shared_ptr<sf::Texture> &texture);

            void setCheckedTexture(const std::shared_ptr<sf::Texture> &texture);

            void setHoverTexture(const std::shared_ptr<sf::Texture> &texture);

            void setCheckedHoverTexture(const std::shared_ptr<sf::Texture> &texture);

            void setDownTexture(const std::shared_ptr<sf::Texture> &texture);

            void setCheckedDownTexture(const std::shared_ptr<sf::Texture> &texture);

            void setFunction(std::function<void()> funct);

            void setChecked(bool state);

            bool isChecked() const;

            void update(sf::Vector2i mousePosition);

        private:
            virtual void onClick();

            bool isChecked_;

            std::function<void()> funct_;

            std::shared_ptr<sf::Texture> activeTexture_;
            std::shared_ptr<sf::Texture> checkedTexture_;
            std::shared_ptr<sf::Texture> normalTexture_;

            std::shared_ptr<sf::Texture> activeHoverTexture_;
            std::shared_ptr<sf::Texture> hoverCheckedTexture_;
            std::shared_ptr<sf::Texture> hoverTexture_;

            std::shared_ptr<sf::Texture> activeDownTexture_;
            std::shared_ptr<sf::Texture> downCheckedTexture_;
            std::shared_ptr<sf::Texture> downTexture_;
    };
}

#endif // CHECK_BOX_HPP
