#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	


class Bone_Animation
{
public:
	Bone_Animation();
	~Bone_Animation();

	void init();
	void update(float delta_time);
	void reset();

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;
	std::vector<glm::vec4> colors;

	glm::vec3 root_position;


	// My variables go here.
	std::vector<glm::vec3> positionVector;

	glm::vec3 yellowLimb = { 0.0f, 0.0f, 30.0f };
	glm::vec3 pinkLimb = { 0.0f, 0.0f, 30.0f };
	glm::vec3 blueLimb = { 0.0f, 0.0f, 30.0f };

	glm::mat4 bone1 = glm::mat4(1.0f);
	glm::mat4 bone2 = glm::mat4(1.0f);
	glm::mat4 bone3 = glm::mat4(1.0f);

	glm::vec4 yellowPivotPosition = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 pinkPivotPosition = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 bluePivotPosition = { 0.0f, 0.0f, 0.0f, 0.0f };

	glm::vec4 yellowX = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 yellowY = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 yellowZ = { 0.0f, 0.0f, 0.0f, 0.0f };

	glm::vec4 pinkX = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 pinkY = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 pinkZ = { 0.0f, 0.0f, 0.0f, 0.0f };

	glm::vec4 blueX = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 blueY = { 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 blueZ = { 0.0f, 0.0f, 0.0f, 0.0f };

	glm::vec3 g = { 3.0f, 8.0f, 3.0f };
	glm::vec4 e = { -4.6f, 5.96f, 2.0f, 1 };

	glm::vec3 geDifference;
	glm::vec3 crossProduct1 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct2 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct3 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct4 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct5 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct6 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct7 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct8 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 crossProduct9 = { 0.0f, 0.0f, 0.0f };

	bool activateInvKine = false;

	// My function prototypes go here.
	void viewMatrix(std::vector<std::vector<float>> matrix, int row, int column);
	glm::mat4 getTranslationMatrix(float X, float Y, float Z);
	glm::mat4 getRotationMatrix(float X, float Y, float Z);
	glm::mat4 getXRotationMatrix(float X);
	glm::mat4 getYRotationMatrix(float Y);
	glm::mat4 getZRotationMatrix(float Z);
};

