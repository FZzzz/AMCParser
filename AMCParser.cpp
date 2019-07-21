#include "AMCParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


AMCParser::AMCParser()
{

}

AMCParser::~AMCParser()
{

}

void AMCParser::ReadAMC(std::string path)
{
    path_ = path;
    ReadFileContent();
    Parse_Header();
    Parse_Frames();
}

void AMCParser::SetCharacterKeyFrames(Character* character)
{
    if(character == nullptr)
        return;
    // check mapping keys all exist in character
    auto character_map = character->GetBoneNameMap();
    bool status = true;
    for(auto it = raw_name_dof_map_.cbegin();
             it != raw_name_dof_map_.cend();
             ++it)
    {
        if(it->first == "root")
            continue;
        auto find_it = character_map.find(it->first);
        status &= (find_it != character_map.end()) ? true: false;
    }

    // stop if not match
    assert(status);

    // If match then compute quaternion
    for(auto it = raw_name_dof_map_.cbegin();
             it != raw_name_dof_map_.cend();
             ++it)
    {
        if(it->first == "root")
        {
            SetKeyframeStates(it->first, DOF_ENUM::DOF_NONE);
        }
        auto target = character_map.find(it->first);
        SetKeyframeStates(it->first, target->second->data->dof_type);
    }

    character->SetKeyframes(bone_keyframes_map_);

}

bool AMCParser::ReadFileContent()
{
    std::cout << "Read File Content..." << std::endl;
    std::ifstream file(path_.c_str(), std::ios::in);

    if(!file || !file.is_open())
    {
        return false;
    }
    
    // Access whole file content
    std::stringstream buffer;
    buffer << file.rdbuf();
    file_content_ = buffer.str();
    
    file.close();
    std::cout << "Load Success!\n";
    return true;
}

void AMCParser::Parse_Header()
{
    char buf[128];

    ss_ << file_content_;
    
    while(ss_.getline(buf,128))
    {
        if(buf[0] == '#' || buf[0] == ':')
            continue;
        else    
            break;
    }

}

void AMCParser::Parse_Frames()
{
    std::stringstream line_ss;
    char line_str[128];

    while(ss_.getline(line_str, 128))
    {
        int frame_id;
        std::string keyword;

        line_ss.clear();
        line_ss.str(line_str);    
        line_ss >> frame_id;

        if(line_ss.fail())
        {
            float angle;
            std::vector<float> angles_vec;

            line_ss >> keyword;
            auto iter = raw_name_dof_map_.find(keyword);
            bool find_key = (iter != raw_name_dof_map_.end());

            while(line_ss >> angle)
            {
                angles_vec.push_back(angle);
            }

            if(find_key)
            {
                // add to second
                iter->second.push_back(std::move(angles_vec));
            }
            else
            {
                std::vector<std::vector<float>> frames_vec;
                frames_vec.push_back(std::move(angles_vec));
                // create new one using emplace()
                raw_name_dof_map_.emplace(keyword, std::move(frames_vec));
            }

        }
        
    }
}

void AMCParser::SetKeyframeStates(const std::string& key, DOF_ENUM dof_type)
{
    const auto& frames = raw_name_dof_map_[key];

    if(key == "root")
    {
        glm::vec3 trans(0,0,0);
        glm::vec3 euler_rotation(0,0,0);
        //auto root_frames = raw_name_dof_map_["root"];
        for(size_t i =0 ; i< frames.size(); ++i)
        {
            const std::vector<float>& frame_info = frames[i];
            trans = glm::vec3(frame_info[0], 
                                    frame_info[1], 
                                    frame_info[2]);
            euler_rotation = glm::vec3(frame_info[3], 
                                       frame_info[4], 
                                       frame_info[5]);
            
            glm::quat rot(euler_rotation);
            
            KeyframeState* frame_state = new KeyframeState(trans, rot);
            bone_keyframes_map_[key].push_back(frame_state);   
        }
        
        return;
    }

    for(size_t i =0 ; i< frames.size(); ++i)
    {
        SetKeyframeStateInfo(key, dof_type, i);
    }
    

}

void AMCParser::SetKeyframeStateInfo(const std::string& key, 
                                     DOF_ENUM dof_type,
                                     size_t idx)
{
    glm::vec3 trans(0,0,0);
    glm::vec3 euler_rotation(0,0,0);

    const auto& frames = raw_name_dof_map_[key];
    const std::vector<float>& frame_info = frames[idx];

    switch(dof_type)
        {
            case DOF_ENUM::DOF_NONE:
            {
                break;
            }
            case DOF_ENUM::DOF_RX:
            {
                euler_rotation = glm::vec3(frame_info[0], 0, 0);
                break;
            }
            case DOF_ENUM::DOF_RY:
            {
                euler_rotation = glm::vec3(0, frame_info[0], 0);
                break;
            }
            case DOF_ENUM::DOF_RZ:
            {
                euler_rotation = glm::vec3(0, 0, frame_info[0]);
                break;
            }
            case DOF_ENUM::DOF_RX_RY:
            {
                euler_rotation = glm::vec3(frame_info[0], 
                                           frame_info[1], 
                                           0);
                break;
            }
            case DOF_ENUM::DOF_RY_RZ:
            {
                euler_rotation = glm::vec3(0, 
                                           frame_info[0], 
                                           frame_info[1]);
                break;
            }
            case DOF_ENUM::DOF_RX_RZ:
            {
                euler_rotation = glm::vec3(frame_info[0], 
                                           0, 
                                           frame_info[1]);
                break;
            }
            case DOF_ENUM::DOF_RX_RY_RZ:
            {
                euler_rotation = glm::vec3(frame_info[0], 
                                           frame_info[1], 
                                           frame_info[2]);
                break;
            }
        }        

        glm::quat rot(euler_rotation);
            
        KeyframeState* frame_state = new KeyframeState(trans, rot);
        bone_keyframes_map_[key].push_back(frame_state);
}
