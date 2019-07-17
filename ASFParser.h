#ifndef _ASF_PARSER_H_
#define _ASF_PARSER_H_

#include "Character.h"
#include <glm/common.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <map>

class ASFParser
{
public: 
    ASFParser();
    ~ASFParser();

    void ReadASF(std::string);

    Character* Create_Character();

private:
    
    bool ReadFileContent();
    // subroutine of ReadASF()
    void Parse_Header();
    void Parse_Root();
    void Parse_BoneData();
    void Create_Bone_Name_Map();
    void Parse_Hierarchy();
    void FetchRelation(std::stringstream&, std::vector<BoneNode*>&, BoneNode* parent=nullptr);

    void CleanUpLimitString(std::string&);
    void PrintHierarchy();
    
    std::stringstream ss_;
    std::string path_;
    std::string file_content_;
    
    std::string documentation_;
    std::string version_;
    std::string name_;
    bool have_root_;

    Root* root_info_;
    std::vector<BoneData*> bone_datas_;
    std::vector<BoneNode*> bone_nodes_;
    std::map<std::string, BoneNode*> bone_name_map_;


};

#endif