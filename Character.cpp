#include "Character.h"
#include <iostream>
#include <algorithm>
#include <map>

Character::Character() : root_(nullptr), name_("Anonymous")
{

}

Character::~Character()
{
    bone_name_map_.clear();

    for(auto it = bone_nodes_.begin(); it != bone_nodes_.end(); ++it)
    {
        delete (*it);
    }
    bone_nodes_.clear();

    for(auto it = bone_data_.begin(); it != bone_data_.end(); ++it)
    {
        delete (*it);
    }
    bone_data_.clear();

    delete root_;
    root_ = nullptr;

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
    // (Copy constructer "does not" copy children nodes!!)
    // Solution: Copy bone_data and map first
    
    // BoneData copy
    for(size_t i = 0; i < bone_data.size(); ++i)
    {
        BoneData* bone = new BoneData(*(bone_data[i]));
        BoneNode* node = new BoneNode(bone);
        
        bone_data_.push_back(bone);
        bone_nodes_.push_back(node);

    }

    // Reconstruct Map
    for(size_t i = 0; i<bone_nodes_.size(); ++i)
    {
        bone_name_map_.emplace(bone_nodes_[i]->data->name, 
                                bone_nodes_[i]);
    }    

    assert(bone_node_list.size() == bone_nodes_.size());

    // Using bone_name_map_ to reconstruct relationship
    for(size_t i = 0; i<bone_nodes_.size(); ++i)
    {
        BoneNode* ref_node = bone_node_list[i];
        std::cout << ref_node->data->name << std::endl;
        
        // child
        for(auto iter = ref_node->child.begin(); 
                 iter != ref_node->child.end(); 
                 ++iter)
        {
            const std::string child_name = (*iter)->data->name;
            BoneNode* child_node = bone_name_map_.find(child_name)->second;
            bone_nodes_[i]->child.push_back(child_node);
        }

        // parent
        if(ref_node->parent == nullptr)
        {
            bone_nodes_[i]->parent = nullptr;
        }
        else
        {
            const std::string parent_name = ref_node->parent->data->name;
            BoneNode* parent_node = bone_name_map_.find(parent_name)->second;
            bone_nodes_[i]->parent = parent_node;            
        }
    }
}

void Character::SetName(const std::string &name)
{
    this->name_ = name;
}
