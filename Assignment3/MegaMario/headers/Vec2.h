#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
    float x=0;
    float y=0;

    Vec2();
    Vec2(const float x, const float y);

    bool operator==(const Vec2 & rhs) const;
    bool operator!=(const Vec2 & rhs) const;

    Vec2 operator+(const Vec2 & rhs) const;
    Vec2 operator-(const Vec2 & rhs) const;
    Vec2 operator/(const float val) const;
    Vec2 operator*(const float val) const;

    void operator+=(const Vec2 & rhs);
    void operator-=(const Vec2 & rhs);
    void operator/=(const float val);
    void operator*=(const float val);
    void operator=(const Vec2 & rhs);

    float dist(const Vec2 & rhs) const;
    float length() const;
    void normalize();
    
};

#endif