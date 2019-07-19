#include <iostream>
#include <fstream>
#include "Character.h"
#include "ASFParser.h"

int main()
{
    std::cout << "ASF/ACM Loader\n" << std::endl;

    ASFParser* skeleton_parser = new ASFParser();
    skeleton_parser->ReadASF("./Asset/walk.asf");

    Character* character = skeleton_parser->Create_Character();
    
    delete skeleton_parser;
    delete character;

    skeleton_parser = nullptr;
    character = nullptr;

    glm::vec3 v(1,2,3);
    v.y = 5;
    std::cout << v.x << ", " << v.y << ", " << v.z << "\n";
    std::cout << v.r << ", " << v.g << ", " << v.b << "\n";

    return 0;
}