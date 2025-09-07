#include "../headers/Physics.h"
#include "../headers/Components.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    //  TODO: return the overlap rectangle size of the bounding boxes of entity a and b

    /* Methodology:
    *  CTransform.pos = the CENTER of the Entity NOT the TOP-LEFT
    *
    * Step 1:   Find the distance between the two origins (dx)
    *               - abs(x1 - x2)
    * Step 2:   Compare dx to the sum of the widths (half widths since the cetner is at half the width be definition)
    *               - (W1/2 + w2/2) - dx
    *                   - essentially tests which is larger. The sum of the widths? Or the distance between the origins
    *                   - If negative, distance between them is larger, so no overlap
    * 
    * Step 3:   Apply same logic to heights (y-axis). There is overlap if, and only if, the results in the X & Y axis is positive.
    *           You can also calculate the dimensions of the overlap.
    */

    const Vec2& posA = a->getComponent<CTransform>().pos;
    const Vec2& posB = b->getComponent<CTransform>().pos;

    const CBoundingBox bBoxA = a->getComponent<CBoundingBox>();
    const CBoundingBox bBoxB = b->getComponent<CBoundingBox>();

    const float xAxisDistance = std::abs(posA.x - posB.x);
    const float xOverlap = (bBoxA.halfsize.x + bBoxB.halfsize.x) - xAxisDistance;

    const float yAxisDistance = std::abs(posA.y - posB.y);
    const float yOverlap = (bBoxA.halfsize.y + bBoxB.halfsize.y) - yAxisDistance;

    return Vec2(xOverlap, yOverlap);  // TODO: What should be returned if there is no overlap?
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    //  TODO: return the previous overlap rectangle size of the bounding bixes of entity a and b
    //      previous overlap uses entity's previous position

    const Vec2& prevPosA = a->getComponent<CTransform>().prevPos;
    const Vec2& prePosB = b->getComponent<CTransform>().prevPos;

    const CBoundingBox bBoxA = a->getComponent<CBoundingBox>();
    const CBoundingBox bBoxB = b->getComponent<CBoundingBox>();

    const float xAxisDistance = std::abs(prevPosA.x - prePosB.x);
    const float xOverlap = (bBoxA.halfsize.x + bBoxB.halfsize.x) - xAxisDistance;

    const float yAxisDistance = std::abs(prevPosA.y - prePosB.y);
    const float yOverlap = (bBoxA.halfsize.y + bBoxB.halfsize.y) - yAxisDistance;
    return Vec2(xOverlap, yOverlap);
}

 // ### Potential Helper Functions/Wrappers ####
bool Physics::IsOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    const Vec2 overlapVec = GetOverlap(a, b);
    return (overlapVec.x > 0 && overlapVec.y > 0);
}

bool Physics::IsOverlap(const Vec2& overlapVec) {
    return (overlapVec.x > 0 && overlapVec.y > 0);
}

bool Physics::IsPrevOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    const Vec2 prevOverlapVec = GetPreviousOverlap(a, b);
    return (prevOverlapVec.x > 0 && prevOverlapVec.y > 0);
}

bool Physics::IsPrevOverlap(const Vec2& prevOverlapVec) {
return (prevOverlapVec.x > 0 && prevOverlapVec.y > 0);
}