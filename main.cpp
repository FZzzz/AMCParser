#include <iostream>
#include <fstream>
#include "MotionParser.h"
#include "Character.h"
#include "ASFParser.h"
#include "AMCParser.h"

int main()
{
    std::cout << "ASF/ACM Loader\n" << std::endl;

    MotionParser::ASFParser* skeleton_parser = new MotionParser::ASFParser();
    skeleton_parser->ReadASF("./Asset/walk.asf");

    MotionParser::Character* character = skeleton_parser->Create_Character();
    
    MotionParser::AMCParser* anim_parser = new MotionParser::AMCParser();
    anim_parser->ReadAMC("./Asset/walk_01.amc");
    anim_parser->SetCharacterKeyFrames(character);

    delete skeleton_parser;
    delete anim_parser;
    delete character;

    skeleton_parser = nullptr;
    anim_parser = nullptr;
    character = nullptr;

#ifdef _WIN32
	system("pause");
#endif 

    return 0;
}