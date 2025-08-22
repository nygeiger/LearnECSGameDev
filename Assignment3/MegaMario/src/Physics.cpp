#include "../headers/Physics.h"
#include "../headers/Components.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    //  TODO: return the overlap rectangle size of the bounding boxes of entity a and b
    const Vec2& posA = a->getComponent<CTransform>().pos;
    const Vec2& PosB = b->getComponent<CTransform>().pos;

    return Vec2(0, 0);
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    //  TODO: return the previous overlap rectangle size of the bouning boces of entity a and b
    //      previous overlap uses entity's previous position

    const Vec2& posA = a->getComponent<CTransform>().prevPos;
    const Vec2& PosB = b->getComponent<CTransform>().prevPos;

    return Vec2(0,0);
}