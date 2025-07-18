#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CTransform {
    public:
    Vec2 pos = {0.0, 0.0};
    Vec2 velocity = {0.0, 0.0};
    float angle = 0.0f;

    // Position, Velocity, angle
    CTransform(const Vec2 & p, const Vec2 & V, float a) : pos(p), velocity(V), angle(a) {};
};

class CShape {

    public:
        sf::CircleShape circle;

        CShape(float radius, int points, const sf::Color & fill, const sf::Color & outline, float thickness) :
            circle(radius, points) {
                circle.setFillColor(fill);
                circle.setOutlineColor(outline);
                circle.setOutlineThickness(thickness);
                circle.setOrigin({radius, radius});
            }


};

class CCollision {
    public:
        float radius = 0;

        CCollision(float r) : radius(r){}
};

class CScore {
    public:

        int score = 0;
    
        CScore(int s) : score(s){}

};

class CLifespan {
    public:
        int remaining = 0;
        int total = 0;

        CLifespan(int total) : total(total), remaining(total) {}
};

class CInput {
    public:
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        bool w = false;
        bool s = false;
        bool a = false;
        bool d = false;
        bool shoot = false;
        bool special = false;

        CInput(){}

};

#endif


