#ifndef ANIMATION_H
#define ANIMATION_H

#include "Vec2.h"

#include <vector>
#include <SFML/Graphics.hpp>

/*
Animation Asset Specification:
Animation N T F S
- Animation Name | N | std::sting
- Texture Name | T | std::string
- Frame Count | F | int (number of frames in the animation)
- Anim Speed | S | int (number of game frames between anim frames)
*/

/*
Animation Asset Specification (2): Account for animations within a collective sprite sheet (Texture "T" is a collection of related & unrelated sprites)
Animation N T F S X Y Cols Rows
- Animation Name | N | std::sting
- Texture (map) Name | T | std::string
- Frame Count | F | int (number of frames in the animation)
- Anim Speed | S | int (number of game frames between anim frames)
- First Frame X-Cord | X | size_t
- First Frame Y-Cord | Y | size_t
- Columns in Texture (map) | Cols | size_t
- Rows in Texture (map) | Rows | size_t
*/
class Animation {
    // sf::Sprite  m_sprite;
    size_t      m_frameCount = 0;       // total number of frames of anmation               // what about still "animations"
    size_t      m_currentFrame = 0;     // the current frame of animation being played      // what about still "animations"
    size_t      m_initialFrameXPos = 0; // Imagine a matrix of sprites. Which column the sprite is in
    size_t      m_initialFrameYPos = 0; // Imagine a matrix of sprites. Which row the sprite is in
    int         m_TextCols, m_TextRows = -1;
    bool        m_onSpriteMap = false;
    size_t      m_speed = 0;            // the speed to play this animation
    Vec2        m_size = {1, 1};        // size of the animation frame
    // std::string m_name = "none";

    public:
        std::string m_name = "none"; // moved to public so that there can be a default constructor
        sf::Sprite  m_sprite; // moved to public so that there can be a default constructor
        Animation();
        Animation(const std::string& name, const sf::Texture& t);
        Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);
        Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed, size_t currentFrameXPos, size_t currentFrameYPos, size_t cols, size_t rows);

        void update();
        bool hasEnded() const;
        const std::string& getName() const;
        const Vec2& getSize() const;
        sf::Sprite& getSprite(); //should this not be () const{}?

};

namespace AnimationType
{
    static const std::string STAND = "Stand";
    static const std::string RUN = "Run";
    static const std::string JUMP = "Jump";
    static const std::string BRICK = "Brick";
    static const std::string BLOCK = "Block";
    static const std::string QUESTION = "Question";
};

#endif