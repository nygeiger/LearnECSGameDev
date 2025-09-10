
#include <map>
#include <string>
#include <vector>

static const float PIXEL_DIM_SIZE = 64.0f;

// struct PlayerStates {
//     inline static const std::string STAND = "Stand";
//     inline static const std::string JUMP = "Jump";
//     inline static const std::string RUN = "Run";
// };

// /*
// Prior to C++17, you have to define your static member outside the class definition and provide the initializer there.

// // In a header file (if it is in a header file in your case)
// class A {   
// private:      
//   static const string RECTANGLE;
// };
// // In one of the implementation files
// const string A::RECTANGLE = "rectangle
// */

// namespace PlayerStates {
//     static const std::string STAND = "Stand";
//     static const std::string JUMP = "Jump";
//     static const std::string RUN = "Run";
// };

// namespace EntityType
// {
//     static const std::string PLAYER = "player";
//     static const std::string ENEMY = "enemy";
//     static const std::string TILE = "tile";
//     static const std::string DECORATION = "decoration";
//     static const std::string BULLET = "bullet";
//     static const std::string SPECIAL_WEAPON = "special_weapon";
//     static const std::string SMALL_ENEMY = "small_enemy";
//     static const std::string COLLISION_VISUAL = "collision_visual";
// };

// namespace AnimationType
// {
//     static const std::string STAND = "Stand";
//     static const std::string RUN = "Run";
//     static const std::string JUMP = "Jump";
//     static const std::string BRICK = "Brick";
//     static const std::string BLOCK = "Block";
//     static const std::string QUESTION = "Question";
// };


static const bool compareStrings(const std::string& str1, const std::string& str2)
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
