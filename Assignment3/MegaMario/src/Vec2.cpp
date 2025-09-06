#include <math.h>

#include "../headers/Vec2.h"

Vec2::Vec2(){};

// Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {};
Vec2::Vec2(const float xin, const float yin) : x(xin), y(yin){}
// Vec2::Vec2(const int xin, const int yin) : x(static_cast<float>(xin)), y(static_cast<float>(yin)){}

bool Vec2::operator==(const Vec2 & rhs) const {
    return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator!=(const Vec2 & rhs) const{
    return (x != rhs.x || y != rhs.y);
}

Vec2 Vec2::operator+(const Vec2 & rhs) const{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 & rhs) const{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator/(const float val) const{
    return Vec2(x / val, y / val);
}

Vec2 Vec2::operator*(const float val) const{
    return Vec2(x * val, y * val);
}

void Vec2::operator+=(const Vec2 & rhs){
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2 & rhs){
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator/=(const float val){
    x /= val;
    y /= val;
}

void Vec2::operator*=(const float val){
    x *= val;
    y *= val;
}

void Vec2::operator=(const Vec2 & rhs){
    x = rhs.x;
    y = rhs.y;
}

float Vec2::dist(const Vec2 & rhs)const {
    // with square root
    return sqrtf(((rhs.x - x) * (rhs.x - x)) + ((rhs.y - y) * (rhs.y - y)));
}

float Vec2::length() const{
    return sqrtf( this->x * this->x + this->y * this->y);
}

void Vec2::normalize(){
}
