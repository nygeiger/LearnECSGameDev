#ifndef ASSETS_H
#define ASSETS_H

#include "Animation.h"

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class Assets
{
    std::map<std::string, sf::Texture> m_textureMap;
    std::map<std::string, Animation> m_animationMap;
    std::map<std::string, sf::Font> m_fontMap;

    void addTexture(const std::string &textureName, const std::string &path, const bool smooth);
    void addAnimation(const std::string &animationName, std::string &texture, size_t frameCount, size_t speed);
    void addAnimation(const std::string &animationName, std::string &textureName, size_t frameCount, size_t speed, size_t xPos, size_t yPos, size_t textCols, size_t textRows);
    void addFont(const std::string &fontName, const std::string &path);

    public:
        Assets() = default;
        void loadFromFile(const std::string &path);
        const sf::Texture &getTexture(const std::string &textureName) const;
        const Animation &getAnimation(const std::string &animationName) const;
        const sf::Font &getFont(const std::string &fontName) const;
        const std::map<std::string, sf::Texture> &getTextures() const;
        const std::map<std::string, Animation> &getAnimations() const;
};

#endif