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

#include <iostream>
#include <algorithm> // for for_each

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "MiraiProject/animations/AnimatedSprite.hpp"
#include "MiraiProject/animations/Animation.hpp"

mp::AnimatedSprite::AnimatedSprite() :
    sprite_{ },

    frameSize_{ 64, 64 },

    currentFrame_{ 0 },

    numAnimations_{ 0 },
    currentAnimation_{ 0 },
    animations_{ },

    repeat_{ false },

    elapsedTime_{ sf::Time::Zero },
    defaultTimePerFrame_{ sf::seconds(1) }
{

}

mp::AnimatedSprite::AnimatedSprite(const sf::Texture& texture) :
    sprite_{ texture },

    frameSize_{ 64, 64 },

    currentFrame_{ 0 },

    numAnimations_{ 0 },
    currentAnimation_{ 0 },
    animations_{ },

    repeat_{ false },

    elapsedTime_{ sf::Time::Zero },
    defaultTimePerFrame_{ sf::seconds(1) }
{

}

mp::AnimatedSprite::~AnimatedSprite()
{

}

void mp::AnimatedSprite::update(sf::Time dt)
{
    sf::Vector2i textureBounds(sprite_.getTexture()->getSize());
    sf::IntRect textureRect{ sprite_.getTextureRect() };
    mp::Animation currentAnimation{ animations_[currentAnimation_] };

    elapsedTime_ += dt;

    while (elapsedTime_ >= currentAnimation.timePerFrame_ and
          (repeat_ or ((!reversed_ and (currentFrame_ + 1 < currentAnimation.numFrames_)) or (reversed_ and (currentFrame_ > 0 )))))
    {
        elapsedTime_ -= currentAnimation.timePerFrame_;

        if (repeat_)
        {
            if(reversed_)
            {
                currentFrame_ = (currentFrame_ - 1) % currentAnimation.numFrames_;
            }
            else
            {
                currentFrame_ = (currentFrame_ + 1) % currentAnimation.numFrames_;
            }
        }
        else
        {
            if(reversed_)
            {
                currentFrame_--;
            }
            else
            {
                currentFrame_++;
            }
        }
    }

    unsigned int realFrame{ currentFrame_ + currentAnimation.numStartingFrame_ }; // The actual frame number on the sprite sheet.

    textureRect.left = (frameSize_.x * realFrame) % textureBounds.x;
    textureRect.top = frameSize_.y * static_cast<int>((frameSize_.x * realFrame) / textureBounds.x);

    if (currentFrame_ == 0)
        textureRect = sf::IntRect(textureRect.left, textureRect.top, frameSize_.x, frameSize_.y);

    sprite_.setTextureRect(textureRect);
}

void mp::AnimatedSprite::addAnimation(const unsigned int& numStartingFrame, const unsigned int& numEndingFrame)
{
    mp::Animation animation{ };

    animation.numStartingFrame_ = numStartingFrame;
    animation.numEndingFrame_ = numEndingFrame;
    animation.update();

    animation.timePerFrame_ = defaultTimePerFrame_;

    addAnimation(animation);
}

void mp::AnimatedSprite::addAnimation(const std::string& name, const unsigned int& numStartingFrame, const unsigned int& numEndingFrame)
{
    mp::Animation animation{ name, numStartingFrame, numEndingFrame };
    animation.timePerFrame_ = defaultTimePerFrame_;
    addAnimation(animation);
}

void mp::AnimatedSprite::addAnimation(const mp::Animation& animation)
{
    animations_.push_back(animation);
    numAnimations_++;
}

void mp::AnimatedSprite::removeAnimation(const unsigned int& numAnimation)
{
    if (numAnimation < animations_.size())
    {
        animations_.erase(animations_.begin() + numAnimation);

        if (currentAnimation_ >= animations_.size())
            currentAnimation_ = static_cast<unsigned int>(animations_.size() - 1);
    }
}

void mp::AnimatedSprite::removeAnimation(const std::string& nameAnimation)
{
    int i{ 0 };

    for_each(animations_.begin(), animations_.end(), [&](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
        {
            animations_.erase(animations_.begin() + i);

            if (currentAnimation_ >= animations_.size())
                currentAnimation_ = static_cast<unsigned int>(animations_.size() - 1);
        }

        i++;
    });
}

sf::FloatRect mp::AnimatedSprite::getLocalBounds() const
{
    return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect mp::AnimatedSprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

/////////////
// Getters //
/////////////

sf::Vector2i mp::AnimatedSprite::getFrameSize() const
{
    return frameSize_;
}

int mp::AnimatedSprite::getNumFrames() const
{
    mp::Animation currentAnimation{ animations_[currentAnimation_] };
    return currentAnimation.numFrames_;
}

int mp::AnimatedSprite::getNumFrames(const unsigned int& numAnimation) const
{
    mp::Animation currentAnimation{ };

    if (numAnimation >= animations_.size())
    {
        currentAnimation = animations_[animations_.size() - 1];
    }
    else
    {
        currentAnimation = animations_[numAnimation];
    }

    return currentAnimation.numFrames_;
}

int mp::AnimatedSprite::getNumFrames(const std::string& nameAnimation) const
{
    int numFrames{ 0 };

    for_each(animations_.begin(), animations_.end(), [&](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
            numFrames = animation.numFrames_;
    });

    return numFrames;
}

int mp::AnimatedSprite::getCurrentFrame() const
{
    return currentFrame_;
}

bool mp::AnimatedSprite::isFinished() const
{
    mp::Animation currentAnimation{ animations_[currentAnimation_] };

    if(reversed_)
    {
        return currentFrame_ <= 0 and elapsedTime_ >= currentAnimation.timePerFrame_;
    }
    else
    {
        return currentFrame_ >= currentAnimation.numFrames_ - 1 and elapsedTime_ >= currentAnimation.timePerFrame_;
    }
}

int mp::AnimatedSprite::getNumAnimations() const
{
    return numAnimations_;
}

int mp::AnimatedSprite::getCurrentAnimation() const
{
    return currentAnimation_;
}

bool mp::AnimatedSprite::isRepeating() const
{
    return repeat_;
}

sf::Time mp::AnimatedSprite::getDuration() const
{
    mp::Animation currentAnimation{ animations_[currentAnimation_] };
    return currentAnimation.duration_;
}

sf::Time mp::AnimatedSprite::getDuration(const unsigned int& numAnimation) const
{
    mp::Animation currentAnimation{ };

    if (numAnimation >= animations_.size())
    {
        currentAnimation = animations_[animations_.size() - 1];
    }
    else
    {
        currentAnimation = animations_[numAnimation];
    }

    return currentAnimation.duration_;
}

sf::Time mp::AnimatedSprite::getDuration(const std::string& nameAnimation) const
{
    sf::Time duration{ sf::Time::Zero };

    for_each(animations_.begin(), animations_.end(), [&](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
            duration = animation.duration_;
    });

    return duration;
}

sf::Time mp::AnimatedSprite::getTimePerFrame() const
{
    mp::Animation currentAnimation{ animations_[currentAnimation_] };
    return currentAnimation.timePerFrame_;
}

sf::Time mp::AnimatedSprite::getTimePerFrame(const unsigned int& numAnimation) const
{
    mp::Animation currentAnimation{ };

    if (numAnimation >= animations_.size())
    {
        currentAnimation = animations_[animations_.size() - 1];
    }
    else
    {
        currentAnimation = animations_[numAnimation];
    }

    return currentAnimation.timePerFrame_;
}

sf::Time mp::AnimatedSprite::getTimePerFrame(const std::string& nameAnimation) const
{
    sf::Time timePerFrame{ sf::Time::Zero };

    for_each(animations_.begin(), animations_.end(), [&](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
            timePerFrame = animation.timePerFrame_;
    });

    return timePerFrame;
}

sf::Time mp::AnimatedSprite::getDefaultTimePerFrame() const
{
    return defaultTimePerFrame_;
}

const sf::Texture* mp::AnimatedSprite::getTexture() const
{
    return sprite_.getTexture();
}

bool mp::AnimatedSprite::getReversed() const
{
    return reversed_;
}
/////////////
// Setters //
/////////////

void mp::AnimatedSprite::setFrameSize(const sf::Vector2i& newFrameSize)
{
    frameSize_ = newFrameSize;
}

void mp::AnimatedSprite::setCurrentFrame(const unsigned int& newCurrentFrame)
{
    currentFrame_ = newCurrentFrame;
    elapsedTime_ = sf::Time::Zero;
}

void mp::AnimatedSprite::restart()
{
    if (reversed_)
    {
        mp::Animation currentAnimation{ animations_[currentAnimation_] };
        currentFrame_ = currentAnimation.numFrames_ - 1;
    }
    else
    {
        currentFrame_ = 0;
    }

    elapsedTime_ = sf::Time::Zero;
}

void mp::AnimatedSprite::setCurrentAnimation(const unsigned int& newCurrentAnimation)
{
    if (newCurrentAnimation >= animations_.size())
    {
        currentAnimation_ = static_cast<unsigned int>(animations_.size() - 1);
    }
    else
    {
        currentAnimation_ = newCurrentAnimation;
    }

    restart();
}

void mp::AnimatedSprite::setCurrentAnimation(const std::string& nameAnimation)
{
    int i{ 0 };

    for_each(animations_.begin(), animations_.end(), [&](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
            currentAnimation_ = i;

        i++;
    });

    restart();
}

void mp::AnimatedSprite::setRepeating(const bool& newRepeat)
{
    repeat_ = newRepeat;
}

void mp::AnimatedSprite::setDuration(const sf::Time& newDuration)
{
    mp::Animation currentAnimation{ animations_[currentAnimation_] };
    currentAnimation.setDuration(newDuration);
}

void mp::AnimatedSprite::setDuration(const sf::Time& newDuration, const unsigned int& numAnimation)
{
    mp::Animation currentAnimation{ };

    if (numAnimation >= animations_.size())
    {
        currentAnimation = animations_[animations_.size() - 1];
    }
    else
    {
        currentAnimation = animations_[numAnimation];
    }

    currentAnimation.setDuration(newDuration);
}

void mp::AnimatedSprite::setDuration(const sf::Time& newDuration, const std::string& nameAnimation)
{
    for_each(animations_.begin(), animations_.end(), [newDuration, nameAnimation](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
            animation.setDuration(newDuration);;
    });
}

void mp::AnimatedSprite::setTimePerFrame(const sf::Time& newTimePerFrame)
{
    mp::Animation currentAnimation{ animations_[currentAnimation_] };
    currentAnimation.setTimePerFrame(newTimePerFrame);
}

void mp::AnimatedSprite::setTimePerFrame(const sf::Time& newTimePerFrame, const unsigned int& numAnimation)
{
    mp::Animation currentAnimation{ };

    if (numAnimation >= animations_.size())
    {
        currentAnimation = animations_[animations_.size() - 1];
    }
    else
    {
        currentAnimation = animations_[numAnimation];
    }

    currentAnimation.setTimePerFrame(newTimePerFrame);
}

void mp::AnimatedSprite::setTimePerFrame(const sf::Time& newTimePerFrame, const std::string& nameAnimation)
{
    for_each(animations_.begin(), animations_.end(), [newTimePerFrame, nameAnimation](mp::Animation animation)
    {
        if (animation.name_ == nameAnimation)
            animation.setTimePerFrame(newTimePerFrame);;
    });
}

void mp::AnimatedSprite::setDefaultTimePerFrame(const sf::Time& newDefaultTimePerFrame)
{
    defaultTimePerFrame_ = newDefaultTimePerFrame;
}

void mp::AnimatedSprite::setTexture(const sf::Texture& texture)
{
    sprite_.setTexture(texture);
}

void mp::AnimatedSprite::setReversed(bool reversed)
{
    reversed_ = reversed;
}
/////////////
// Private //
/////////////

void mp::AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
}
