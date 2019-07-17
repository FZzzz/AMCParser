#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <glm/common.hpp>
#include <vector>
#include <map>

struct JointLimit
{
    float min;
    float max;
};

struct BoneData
{
    int id;
    std::string name;
    glm::vec3 direction;
    float length;
    glm::vec3 euler_roataion_axis;
    std::string rotation_order;
    
    // Map? Fixed array? Max 6
    std::vector<std::string> dofs;
    std::vector<JointLimit> joint_limit;

};

struct BoneNode;

// Bidirectional
struct BoneNode
{
    BoneData* data;
    BoneNode* parent;
    std::vector<BoneNode*> child;
};

struct Root
{
    Root(){};
    Root(const Root& r): order(r.order), 
                         axis(r.axis),
                         position(r.position),
                         orientation(r.orientation)
    {}

    std::string order;
    std::string axis;
    
    glm::vec3 position;
    glm::vec3 orientation;
    std::vector<BoneNode*> children;
};


class Character
{
public:
    Character();
    void SetSkeletal(const Root* const,
                     const std::vector<BoneData*>&,
                     const std::vector<BoneNode*>&,
                     const std::map<std::string, BoneNode*>&);
    void SetName(const std::string&);
    
private:
    
    std::map<std::string, BoneNode*> bone_name_map_;
    Root* root_;
    std::string name_;
};

#endif