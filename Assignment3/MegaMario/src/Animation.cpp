#include "headers/Animation.h"
#include <cmath>

Animation::Animation()
    : Animation("none", sf::Texture(), 1, 0)
{
}

Animation::Animation(const std::string &name, const sf::Texture &t)
    : Animation(name, t, 1, 0)
{
}

Animation::Animation(const std::string &name, const sf::Texture &t, size_t frameCount, size_t speed)
    : m_name(name), m_sprite(t), m_frameCount(frameCount), m_currentFrame(0), m_speed(speed)
{
    m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
    m_sprite.setOrigin({m_size.x / 2.0f, m_size.y / 2.0f});
    m_sprite.setTextureRect(sf::IntRect({static_cast<int>(std::floor(m_currentFrame) * m_size.x), 0}, {static_cast<int>(m_size.x), static_cast<int>(m_size.y)}));
}

Animation::Animation(const std::string &name, const sf::Texture &t, size_t frameCount, size_t speed, size_t currentFrameXPos, size_t currentFrameYPos, size_t cols, size_t rows)
    : m_name(name), m_sprite(t), m_frameCount(frameCount), m_currentFrame(0), m_speed(speed), m_initialFrameXPos(currentFrameXPos), m_initialFrameYPos(currentFrameYPos), m_TextCols(cols), m_TextRows(rows), m_onSpriteMap(true)
{
    m_size = Vec2((float)t.getSize().x / cols, (float)t.getSize().y / rows);
    m_sprite.setOrigin({m_size.x / 2.0f, m_size.y / 2.0f});

    sf::Vector2i textureRectPosition = {static_cast<int>(m_initialFrameXPos * m_size.x), static_cast<int>(m_initialFrameYPos * m_size.y)};
    sf::Vector2i textureRectSize = {static_cast<int>(m_size.x), static_cast<int>(m_size.y)};
    m_sprite.setTextureRect({{textureRectPosition.x, textureRectPosition.y}, {textureRectSize.x, textureRectSize.y}});
}

// updates the animation to shoe the next frame, depending on its speed
// animation loops when it reaches the end
void Animation::update()
{
    // add the speed variable to the current frame

    if (m_frameCount > 1)
    {
        if (m_currentFrame == 0 || m_currentFrame % m_speed == 0)
        {
            const size_t currentAniFrame = m_currentFrame / m_speed;

            if (m_onSpriteMap)
            {
                size_t m_currentFrameXPos = m_initialFrameXPos + currentAniFrame;
                size_t m_currentFrameYPos = m_initialFrameYPos;

                if (m_currentFrameXPos > m_TextCols)
                {
                    int rowChange = m_currentFrameXPos / m_TextCols;
                    m_currentFrameXPos -= rowChange * m_TextCols;
                    m_currentFrameYPos += rowChange;
                }
                sf::Vector2i textureRectPosition = {static_cast<int>(m_size.x * m_currentFrameXPos), static_cast<int>(m_size.y * m_currentFrameYPos)};
                m_sprite.setTextureRect({{textureRectPosition.x, textureRectPosition.y}, {static_cast<int>(m_size.x), static_cast<int>(m_size.y)}});
            }
            else
            {
                m_sprite.setTextureRect({{static_cast<int>(std::floor(currentAniFrame) * m_size.x), 0}, {static_cast<int>(m_size.x), static_cast<int>(m_size.y)}});
            }
        }
        m_currentFrame++;
        if (hasEnded()) {
            m_currentFrame = 0;
        }
    }
}

const Vec2 &Animation::getSize() const
{
    return m_size;
}

const std::string &Animation::getName() const
{
    return m_name;
}

sf::Sprite &Animation::getSprite()
{
    return m_sprite;
}

size_t Animation::getFramecount() const
{
    return m_frameCount;
}

size_t Animation::getAnimationLifespan() const
{
    return m_frameCount * m_speed;
}

bool Animation::hasEnded() const
{
    // TODO: detect when animation has ended (last frame was played) and return true
    return m_frameCount <= 1 || m_frameCount <= m_currentFrame / static_cast<double>(m_speed); // TODO: double check logic
}