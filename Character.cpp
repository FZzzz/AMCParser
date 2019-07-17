#include "Character.h"
#include <iostream>

Character::Character() : root_(nullptr), name_("")
{

}

void Character::SetSkeletal(const Root* const root,
                     const std::vector<BoneData*>& bone_data,
                     const std::vector<BoneNode*>& bone_node_list,
                     const std::map<std::string, BoneNode*>& bone_name_map)
{
    assert(root);
    assert(bone_data.size()>0);
    assert(bone_node_list.size()>0);
    assert(bone_name_map.size()>0);

    // Create root node using copy constructor
    this->root_ = new Root(*root);
    // TODO: relink children 
    // (Copy constructer "does not" copy the children!!)
    // I am starving

}


void Character::SetName(const std::string &name)
{
    this->name_ = name;
}
