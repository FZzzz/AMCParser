#include "ASFParser.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

ASFParser::ASFParser() : have_root(false)
{

}

void ASFParser::ReadASF(std::string path)
{
    this->path = path;
    ReadFileContent();
    Parse_Header();
    Parse_Root();
    Parse_BoneData();
    
    for(size_t i = 0; i < bone_datas.size(); ++i)
    {
        std::cout << bone_datas[i]->name << std::endl;
    }


    Parse_Heirarchy();
}

Character* ASFParser::Create_Character()
{
    return new Character();
}

bool ASFParser::ReadFileContent()
{
    std::cout << "Read File Content..." << std::endl;
    std::ifstream file(path.c_str(), std::ios::in);

    if(!file || !file.is_open())
    {
        return false;
    }
    
    // Access whole file content
    std::stringstream buffer;
    buffer << file.rdbuf();
    file_content = buffer.str();
    
    file.close();
    std::cout << "Load Success!\n";
    //std::cout << file_content << std::endl;
    return true;
}

void ASFParser::Parse_Header()
{
    std::cout << "Parse_BoneData" << std::endl;

    std::stringstream line_ss;
    char buf[128];

    ss << file_content;
    
    while(ss.getline(buf,128))
    {
        if(buf[0] == '#')
            continue;
        std::string token;
        std::string info_buf;

        line_ss.clear();
        line_ss.str(buf);
        line_ss >> token;
        
        std::cout << token << "\n";

        if(token == ":hierarchy")
            break;
        else if(token == ":version")
        {
            line_ss >> info_buf;
            this->version = info_buf;
        }
        else if(token == ":name")
        {
            line_ss >> info_buf;
            this->name = info_buf;
        }
        else if(token == ":root")
        {
            std::cout << "Parse Root" << std::endl;
            //Parse_Root();
            return;
        }
        else if (token == ":bonedata")
        {
            if(!have_root)
            {
                assert((std::cout << "Error: bonedata without root!!\n"));
                return;
            }
            //Parse_BoneData();
        }

        //std::cout << buf << std::endl;
    }
    
    std::cout << buf << std::endl;

}


void ASFParser::Parse_Root()
{
    std::stringstream line_ss;
    char line_str[128];

    while(ss.getline(line_str, 128))
    {
        std::string keyword;

        line_ss.clear();
        line_ss.str(line_str);    
        line_ss >> keyword;

        if(keyword == "order")
        {
            line_ss >> this->root_info.order;  
        }
        else if (keyword == "axis")
        {
            line_ss >> this->root_info.axis;
        }
        else if (keyword == "position")
        {
            float x, y, z;
            line_ss >> x >> y >> z;
            this->root_info.position = glm::vec3(x,y,z);
            std::cout << x << " " 
                      << y << " " 
                      << z << std::endl;
        }
        else if (keyword == "orientation")
        {
            float x, y, z;
            line_ss >> x >> y >> z;
            this->root_info.orientation = glm::vec3(x,y,z);
            std::cout << x << " " 
                      << y << " " 
                      << z << std::endl;
        }
        else if (keyword == ":bonedata")
        {
            std::cout << "Parsing bonedata\n";
            return;
        }
    }
}

void ASFParser::Parse_BoneData()
{
    std::stringstream line_ss;
    char line_str[128];
    bool is_illegal_format = false;

    BoneData* bone = nullptr;
    while(ss.getline(line_str, 128))
    {
        std::string keyword;
        

        line_ss.clear();
        line_ss.str(line_str);    
        line_ss >> keyword;

        

        if(keyword == "begin")
        {
            is_illegal_format = true;
            bone = new BoneData();
        }
        else if (keyword == "end")
        {
            if(!is_illegal_format)
            {
                assert((std::cout << "Found 'end' but without 'begin'\n"));
                return;
            }
            bone_datas.push_back(bone);
            is_illegal_format = false;
        }
        else if (keyword == "id")
        {
            line_ss >> bone->id;
            std::cout << "\nid " << bone->id << std::endl;
        }
        else if (keyword == "name")
        {
            line_ss >> bone->name;
            std::cout << bone->name << std::endl;
        }
        else if (keyword == "direction")
        {
            float x, y, z;
            line_ss >> x >> y >> z;
            bone->direction = glm::vec3(x,y,z);
            std::cout << x << " " 
                      << y << " " 
                      << z << std::endl;
        }
        else if (keyword == "length")
        {
            line_ss >> bone->length;
            std::cout << bone->length << std::endl;
        }
        else if (keyword == "axis")
        {
            float x, y, z;
            std::string rotation_order;

            line_ss >> x >> y >> z;
            bone->euler_roataion_axis = glm::vec3(x,y,z);
            std::cout << x << " " 
                      << y << " " 
                      << z << std::endl;
            line_ss >> rotation_order;
            std::cout << rotation_order << std::endl;
        }
        else if (keyword == "dof")
        {
            std::string dof_info;
            while(line_ss >> dof_info)
            {
                bone->dofs.push_back(dof_info);
            }
            std::cout << "dofs\n";
            for(size_t i=0;i < bone->dofs.size() ; ++i)
            {
                std::cout << bone->dofs[i] << " ";
            }
            std::cout << std::endl;
        }
        else if (keyword == "limits")
        {
            if(bone->dofs.size() == 0)
                continue;
/*
            std::string cleaned_str;
            line_ss << cleaned_str;
            
            CleanUpLimitString(cleaned_str);
            line_ss.clear();
            line_ss.str(cleaned_str);

            float min, max;
            line_ss >> min >> max;
*/          
            std::cout << "limits\n";
            for(size_t i = 0; i < bone->dofs.size(); ++i)
            {
                std::string cleaned_str = "";
                if( i!=0 )
                {
                    ss.getline(line_str, 128);
                    line_ss.clear();
                    line_ss.str(line_str);
                    cleaned_str = line_ss.str();
                    //std::cout << "Line: " << line_str << std::endl;
                }
                else
                {
                    std::string str1, str2;
                    line_ss >> str1 >> str2;
                    cleaned_str = str1 + " " + str2;
                }
                
                
            
                CleanUpLimitString(cleaned_str);
                line_ss.clear();
                line_ss.str(cleaned_str);

                //std::cout << "Cleaned " << cleaned_str << std::endl;

                float min, max;
                line_ss >> min >> max;

                JointLimit limit;
                limit.min = min;
                limit.max = max;

                bone->joint_limit.push_back(limit);
                std::cout << min << " " << max << std::endl;
            }

        }
        else if (keyword == ":hierarchy")
        {
            std::cout << "Parse Hierarchy\n";
            return;
        }
        else
        {
            std::cout << "Error Unrecoginized Keyword " << keyword << std::endl;
        }

    }
}

void ASFParser::Parse_Heirarchy()
{

}

void ASFParser::CleanUpLimitString(std::string& input)
{
    input.erase(std::find(  input.begin(),
                            input.end(),
                            '(' ));
    
    input.erase(std::find(  input.begin(),
                            input.end(),
                            ')' ));
}

