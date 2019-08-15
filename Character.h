#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "MotionParser.h"
#include <string>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <map>

namespace MotionParser {
	struct JointLimit
	{
		float min;
		float max;
	};

	enum DOF_ENUM
	{
		DOF_NONE,
		DOF_RX,
		DOF_RY,
		DOF_RZ,
		DOF_RX_RY,
		DOF_RY_RZ,
		DOF_RX_RZ,
		DOF_RX_RY_RZ,
	};

	struct BoneData
	{
		BoneData() {};
		BoneData(const BoneData& b) : id(b.id),
			name(b.name),
			direction(b.direction),
			length(b.length),
			euler_rotation_degree(b.euler_rotation_degree),
			rotation_order(b.rotation_order),
			dof_type(b.dof_type),
			dofs(b.dofs),
			joint_limit(b.joint_limit)
		{

		};
		int id;
		std::string name;
		glm::vec3 direction;
		float length;
		glm::vec3 euler_rotation_degree;
		std::string rotation_order;

		// Map? Fixed array? Max 6
		DOF_ENUM dof_type;
		std::vector<std::string> dofs;
		std::vector<JointLimit> joint_limit;

	};

	struct BoneNode;

	// Bidirectional
	struct BoneNode
	{
		BoneNode() :data(nullptr), parent(nullptr) {};
		BoneNode(BoneData* input) :data(input), parent(nullptr) {};
		BoneData* data;
		BoneNode* parent;
		std::vector<BoneNode*> child;
	};

	struct Root
	{
		Root() {};
		Root(const Root& r) : order(r.order),
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

	// DO NOT store euler angle, even asf provide euler angle
	struct KeyframeState
	{
		KeyframeState() {};
		KeyframeState(glm::vec3 trans, glm::quat rot)
			: translation(trans), rotation(rot) {};
		//Copy constructor
		KeyframeState(const KeyframeState& state)
			: translation(state.translation), rotation(state.rotation) {};

		glm::vec3 translation;
		glm::quat rotation;
	};

	typedef std::map<std::string, std::vector<KeyframeState*>> BoneNameFrameMap;

	class Character
	{
	public:
		Character();
		~Character();
		
		void PrintHierarchy();

		void SetSkeletal(const Root* const,
			const std::vector<BoneData*>&,
			const std::vector<BoneNode*>&,
			const std::map<std::string, BoneNode*>&);
		void SetKeyframes(const BoneNameFrameMap&);

		void SetName(const std::string&);
		inline std::string GetName() { return name_; };
		inline const std::map<std::string, BoneNode*>& GetBoneNameMap()
		{
			return bone_name_map_;
		}
		inline const BoneNameFrameMap& GetKeyFrames()
		{
			return keyframes_;
		}


	private:
		void PrintHierarchyInternal(BoneNode* node);

		std::string name_;

		std::vector<BoneNode*> bone_nodes_;
		std::vector<BoneData*> bone_data_;
		std::map<std::string, BoneNode*> bone_name_map_;
		Root* root_;

		std::vector<KeyframeState*> root_keyframes_;
		BoneNameFrameMap keyframes_;
	};
}
#endif
