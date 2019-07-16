#ifndef _ASF_PARSER_H_
#define _ASF_PARSER_H_

#include "Character.h"
#include <glm/common.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <map>

struct Root
{
    std::string order;
    std::string axis;
    
    glm::vec3 position;
    glm::vec3 orientation;
    std::vector<BoneNode*> children;
};


class ASFParser
{
public: 
    ASFParser();
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
    
    std::stringstream ss;
    std::string path;
    std::string file_content;
    
    BoneNode* rootNode;
    std::string documentation;
    std::string version;
    std::string name;
    bool have_root;

    Root root_info;
    std::vector<BoneData*> bone_datas;
    std::vector<BoneNode*> bone_nodes;
    std::map<std::string, BoneNode*> bone_name_map;


};

#endif