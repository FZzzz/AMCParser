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
    
    return 0;
}