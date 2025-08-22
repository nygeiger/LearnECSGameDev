#ifndef PHYSICS_H
#define PHYSICS_H

#include "Entity.h"
#include "Vec2.h"

// class Physics {
//     public:
//         Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
//         Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
// };

namespace Physics {
    Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
}

#endif