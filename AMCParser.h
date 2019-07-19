#ifndef _AMC_PARSER_H_
#define _AMC_PARSER_H_

#include "ASFParser.h"
#include <map>
#include <vector>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>


class AMCParser
{
public:
    AMCParser();
    ~AMCParser();

    void ReadAMC(std::string, ASFParser*);

private:
    bool ReadFileContent();
    void Parse_Header();
    void Parse_Frames();

    std::stringstream ss_;
    std::string path_;
    std::string file_content_;

    BoneNameFrameMap bone_keyframes_map_;
    ASFParser* asf_parser_;
};


#endif