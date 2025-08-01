#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Animation.h"
#include "Assets.h"
#include "Vec2.h"

#include <SFML/Graphics.hpp>



class Component {
    public:
        bool has = false;
        // bool exists = false; // In 2024 lecture
};

class CTransform : public Component {
    public:
        Vec2 pos = {0.0, 0.0};
        Vec2 prevPos = {0.0, 0.0};
        Vec2 scale = {1.0, 1.0};
        Vec2 velocity = {0.0, 0.0};
        float angle = 0.0f;

    // Position, Velocity, angle
    CTransform() = default;
    CTransform(const Vec2& p) :pos(p) {}
    CTransform(const Vec2 & p, const Vec2 scale, const Vec2 & v, float a) : pos(p), scale(scale), velocity(v), angle(a) {};
};

class CShape : public Component {

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

class CCollision : public Component {
    public:
        float radius = 0;

        CCollision(float r) : radius(r){}
};

class CScore : public Component {
    public:

        int score = 0;
    
        CScore(int s) : score(s){}

};

// class CLifespan : public Component {
//     // public:
//         // int remaining = 0;
//         // int total = 0;

//         // CLifespan(int total) : total(total), remaining(total) {}
//     public:
//         int lifespan = 0;
//         int frameCreated = 0;
//         // CLifeSpan() = default;
//         CLifespan(int duration, int frame) : lifespan(duration), frameCreated(frame){}
// };

class CLifespan : public Component {
    public :
        int lifespan = 0;
        int frameCreated = 0;
        CLifespan() = default;
        CLifespan(const int duration, const int frame) : lifespan(duration), frameCreated(frame){}
};

class CInput : public Component {
    public:
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        // bool w = false;
        // bool s = false;
        // bool a = false;
        // bool d = false;
        bool shoot = false;
        // bool special = false;
        bool canShoot = true;
        bool canJump = true;

        CInput() = default;

};


class CBoundingBox : public Component {
    public:
        Vec2 size;
        Vec2 halfsize;

        CBoundingBox() = default;
        CBoundingBox(const Vec2& s) : size(s), halfsize(s.x/2, s.y/2){}
};

class CAnimation : public Component {
    public:
        Animation animation;
        bool repeat = false;
        CAnimation() = default;
        CAnimation(const Animation& animation, bool r) : animation(animation), repeat(r){}

};

class CGravity : public Component {
    public :
        float gravity = 0;
        CGravity() = default;
        CGravity(float g) : gravity(g){}
};

class CState : public Component {
    public :
        std::string state = "jumping";
        CState() = default;
        CState(const std::string s) : state(s){}
};


#endif


