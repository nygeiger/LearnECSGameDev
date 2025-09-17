#ifndef PHYSICS_H
#define PHYSICS_H

#include "Entity.h"
#include "Vec2.h"

namespace Physics {
    Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);

     // ### Potential Helper Functions/Wrappers ####
    bool IsOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    bool IsOverlap(const Vec2& overlapVec);
    bool IsPrevOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    bool IsPrevOverlap(const Vec2& prevOverlapVec);
}

#endif