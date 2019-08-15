#include "Character.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace MotionParser;

Character::Character() : name_("Anonymous"), root_(nullptr)
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

void MotionParser::Character::PrintHierarchy()
{
	if (root_->children.size() == 0)
		return;
	
	std::cout << "Print hierarchy:\nRoot\n";
	// print root childs
	for (size_t i = 0; i < root_->children.size(); ++i)
	{
		std::cout << root_->children[i]->data->name << " ";
		PrintHierarchyInternal(root_->children[i]);
	}
}

void MotionParser::Character::PrintHierarchyInternal(BoneNode* node)
{
	std::string parent_name = (node->parent) ? node->parent->data->name : "root";
	std::cout << parent_name << " -> " << node->data->name << "\n";
	if (node->child.size() == 0)
		return;

	for (size_t i = 0; i < node->child.size(); ++i)
	{
		auto child = node->child[i];
		PrintHierarchyInternal(child);
	}
	
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
        //std::cout << ref_node->data->name << std::endl;
        
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

    // re-create root information
	for (size_t i = 0; i < root->children.size(); ++i)
	{
		std::string child_name = root->children[i]->data->name;
		root_->children.push_back(bone_name_map_[child_name]);
	}


}

void Character::SetKeyframes(const BoneNameFrameMap& input)
{
    for(auto it = input.cbegin(); it != input.cend(); ++it)
    {
        auto input_frames = it->second;
        std::vector<KeyframeState*> frames;
        for(size_t i =0 ; i < input_frames.size(); ++i)
        {
            KeyframeState* state = new KeyframeState( (*input_frames[i]) );
            frames.push_back(state);
        }

        keyframes_.emplace(it->first, frames);        
    }

    // Cache out root keyframes
    root_keyframes_ = keyframes_["root"];
}

void Character::SetName(const std::string &name)
{
    this->name_ = name;
}
