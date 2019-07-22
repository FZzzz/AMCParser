#include <iostream>
#include <fstream>
#include "Character.h"
#include "ASFParser.h"
#include "AMCParser.h"

int main()
{
    std::cout << "ASF/ACM Loader\n" << std::endl;

    ASFParser* skeleton_parser = new ASFParser();
    skeleton_parser->ReadASF("./Asset/walk.asf");

    Character* character = skeleton_parser->Create_Character();
    
    AMCParser* anim_parser = new AMCParser();
    anim_parser->ReadAMC("./Asset/walk_01.amc");
    anim_parser->SetCharacterKeyFrames(character);

    delete skeleton_parser;
    delete anim_parser;
    delete character;

    skeleton_parser = nullptr;
    anim_parser = nullptr;
    character = nullptr;

    return 0;
}