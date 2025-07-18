#include <string>
#include <sstream>
#include <map>

static const float PI = 3.14159265;

static const float ENEMY_PLAYER_RADIUS = 32.0f;     // Needed after config file?
static const int ENTITY_COLLISION_DISTANCE = 24;    // Needed after config file?

static const int SPECIAL_WEAPON_DELAY_FRAMES = 30.0f;

enum EntityType
{
    PLAYER,
    ENEMY,
    BULLET,
    SPECIAL_WEAPON,
    SMALL_ENEMY
};
static const std::map<EntityType, const std::string> EntityTypeMap = { // Needs static to prevent multiple definition error when included & used
    {EntityType::PLAYER, "player"},
    {EntityType::ENEMY, "enemy"},
    {EntityType::BULLET, "bullet"},
    {EntityType::SPECIAL_WEAPON, "special_weapon"},
    {EntityType::SMALL_ENEMY, "small_enemy"}
};
static const std::string getEntityTypeTag(EntityType entityType) { // Needs static to prevent multiple definition error when included & used
    return EntityTypeMap.at(entityType); 
}

static const float degreesToRadians (float degreesAngle) {
    return (degreesAngle * PI) / 180;
}



bool static stringIsEqual(std::string str1, std::string str2)
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

std::vector<std::string> static splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
