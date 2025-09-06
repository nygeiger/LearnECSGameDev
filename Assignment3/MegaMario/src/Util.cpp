
#include <map>
#include <string>
#include <vector>

static const float PIXEL_DIM_SIZE = 64.0f;

// enum struct PlayerStates {STAND, JUMP, RUN};
struct PlayerStates {
    inline static const std::string STAND = "Stand";
    inline static const std::string JUMP = "Jump";
    inline static const std::string RUN = "Run";
};

/*
Prior to C++17, you have to define your static member outside the class definition and provide the initializer there.

// In a header file (if it is in a header file in your case)
class A {   
private:      
  static const string RECTANGLE;
};
// In one of the implementation files
const string A::RECTANGLE = "rectangle
*/

struct EntityType
{
    inline static const std::string PLAYER = "player";
    inline static const std::string ENEMY = "enemy";
    inline static const std::string TILE = "tile";
    inline static const std::string DECORATION = "decoration";
    inline static const std::string BULLET = "bullet";
    inline static const std::string SPECIAL_WEAPON = "special_weapon";
    inline static const std::string SMALL_ENEMY = "small_enemy";
};
// enum struct EntityType
// {
//     PLAYER,
//     ENEMY,
//     TILE,
//     DECORATION,
//     BULLET,
//     SPECIAL_WEAPON,
//     SMALL_ENEMY
// };
// static const std::map<EntityType, const std::string> EntityTypeMap = { // Needs static to prevent multiple definition error when included & used
//     {EntityType::PLAYER, "player"},
//     {EntityType::ENEMY, "enemy"},
//     {EntityType::BULLET, "bullet"},
//     {EntityType::SPECIAL_WEAPON, "special_weapon"},
//     {EntityType::SMALL_ENEMY, "small_enemy"},
//     {EntityType::TILE, "tile"},
//     {EntityType::DECORATION, "decoration"}};
// static const std::string getEntityTypeTag(EntityType entityType)
// { // Needs static to prevent multiple definition error when included & used
//     return EntityTypeMap.at(entityType);
// }

struct AnimationType
{
    inline static const std::string STAND = "Stand";
    inline static const std::string RUN = "Run";
    inline static const std::string JUMP = "Jump";
    inline static const std::string BRICK = "Brick";
    inline static const std::string BLOCK = "Block";
    inline static const std::string QUESTION = "Question";
};
// enum struct AnimationType
// {
//     STAND,
//     RUN,
//     JUMP,
//     BRICK,
//     BLOCK,
//     QUESTION,
// };
// // Values must match the names found in the assets file
// static const std::map<AnimationType, const std::string> AnimationTypeMap = { // Needs static to prevent multiple definition error when included & used
//     {AnimationType::STAND, "Stand"},
//     {AnimationType::RUN, "Run"},
//     {AnimationType::JUMP, "Jump"},
//     {AnimationType::BRICK, "Brick"},
//     {AnimationType::BLOCK, "Block"},
//     {AnimationType::QUESTION, "Question"}};
// static const std::string &getAnimationType(AnimationType animationType)
// { // Needs static to prevent multiple definition error when included & used
//     return AnimationTypeMap.at(animationType);
// }

// enum ActionType {START, END};

// static const std::map<std::string, PlayerStates> PlayerStatesMap = {

// };

// const std::vector<PlayerStates> getPlayerStatesList() {
//     std::vector<PlayerStates> playerStatesList;

//     for (int i = 0; i++; i<static_cast<int>(PlayerStates::RUN)) {

//     }

//     return playerStatesList
// };

// static const std::vector<PlayerStates> PlayerStatesList = getPlayerStatesList();

// bool compareStrings(std::string& str1, std::string& str2)
// {
//     if (str1.length() != str2.length())
//         return false;

//     for (int i = 0; i < str1.length(); ++i) {
//         if (tolower(str1[i]) != tolower(str2[i]))
//             return false;
//     }

//     return true;
// }

static const bool compareStrings(std::string str1, std::string str2)
{
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }

    return true;
}

// getAnimationType\((.*::\w+)\)
