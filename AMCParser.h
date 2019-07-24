#ifndef _AMC_PARSER_H_
#define _AMC_PARSER_H_

#include "MotionParser.h"
#include "Character.h"
#include <map>
#include <vector>
#include <sstream>


namespace MotionParser
{
	using NameDOFMap = std::map<std::string, std::vector<std::vector<float>>>;

	class AMCParser
	{
	public:
		AMCParser();
		~AMCParser();

		void ReadAMC(std::string);
		void SetCharacterKeyFrames(Character*);

	private:
		bool ReadFileContent();
		void Parse_Header();
		void Parse_Frames();
		void SetKeyframeStates(const std::string&, DOF_ENUM);
		void SetKeyframeStateInfo(const std::string&, DOF_ENUM, size_t);

		std::stringstream ss_;
		std::string path_;
		std::string file_content_;

		NameDOFMap raw_name_dof_map_;
		BoneNameFrameMap bone_keyframes_map_;

	};


#endif
}
