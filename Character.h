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
    BoneData(){};
    BoneData(const BoneData& b): id(b.id),
                                  name(b.name),
                                  direction(b.direction),
                                  length(b.length),
                                  euler_roataion_axis(b.euler_roataion_axis),
                                  rotation_order(b.rotation_order),
                                  dofs(b.dofs),
                                  joint_limit(b.joint_limit)
    {

    };
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
    BoneNode():data(nullptr), parent(nullptr){};
    BoneNode(BoneData* input):data(input),parent(nullptr){};
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
    {};

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
    ~Character();
    void SetSkeletal(const Root* const,
                     const std::vector<BoneData*>&,
                     const std::vector<BoneNode*>&,
                     const std::map<std::string, BoneNode*>&);
    void SetName(const std::string&);
    inline std::string GetName(){return name_;};

private:
    std::vector<BoneNode*> bone_nodes_;
    std::vector<BoneData*> bone_data_;
    std::map<std::string, BoneNode*> bone_name_map_;
    Root* root_;
    std::string name_;
};

#endif