#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <glm/common.hpp>
#include <vector>

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
    BoneNode* child;
};


class Character
{
public:
    Character();
    void SetBones();
    inline void SetName(std::string);
    inline void SetMass(float);
private:
    BoneNode* root;
    std::string name;
    float mass;
    float length;
};

#endif