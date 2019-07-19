#include "AMCParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

AMCParser::AMCParser()
{

}

AMCParser::~AMCParser()
{

}

void AMCParser::ReadAMC(std::string path, ASFParser* asf_parser)
{
    path_ = path;
    asf_parser_ = asf_parser;
}

bool AMCParser::ReadFileContent()
{
    std::cout << "Read File Content..." << std::endl;
    std::ifstream file(path_.c_str(), std::ios::in);

    if(!file || !file.is_open())
    {
        return false;
    }
    
    // Access whole file content
    std::stringstream buffer;
    buffer << file.rdbuf();
    file_content_ = buffer.str();
    
    file.close();
    std::cout << "Load Success!\n";
    return true;
}

void AMCParser::Parse_Header()
{
    char buf[128];

    ss_ << file_content_;
    
    while(ss_.getline(buf,128))
    {
        if(buf[0] == '#' || buf[0] == ':')
            continue;
        else    
            break;
    }

}

void AMCParser::Parse_Frames()
{
    std::map<std::string, BoneNode*> bone_name_map = asf_parser_->GetBoneNameMap();
    
    auto asf_bone_name_map = asf_parser_->GetBoneNameMap();
    std::stringstream line_ss;
    char line_str[128];

        
    while(ss_.getline(line_str, 128))
    {
        int frame_id;
        std::string keyword;

        line_ss.clear();
        line_ss.str(line_str);    
        line_ss >> frame_id;

        if(line_ss.fail())
        {
            // parse segment info
            // TODO: Arrange dof types(Character.h enum)
            // switch(enum dof_type)
        }

        
    }
}