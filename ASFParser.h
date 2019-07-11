#ifndef _ASF_PARSER_H_
#define _ASF_PARSER_H_

#include "Character.h"
#include <glm/common.hpp>

class ASFParser
{
public: 
    ASFParser();
    void ReadASF();

    Character* Create_Character();
private:
    // subroutine of ReadASF()
    void Read_BoneData();
    void Read_Heirarchy();
    
};

#endif