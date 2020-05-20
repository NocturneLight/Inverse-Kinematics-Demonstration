#include "Bone_Animation.h"


Bone_Animation::Bone_Animation()
{
}


Bone_Animation::~Bone_Animation()
{
}

void Bone_Animation::init()
{
	root_position = { 2.0f, 0.5f, 2.0f };

	// My matrix for position.
	positionVector =
	{
		{ 2.0f, 3.0f, 2.0f },
		{ 2.0f, 6.5f, 2.0f },
		{ 2.0f, 9.0f, 2.0f }
	};

	scale_vector =
	{
		{1.0f,1.0f,1.0f},
		{0.5f,4.0f,0.5f},
		{0.5f,3.0f,0.5f},
		{0.5f,2.0f,0.5f}
	};

	rotation_degree_vector = 
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	colors = 
	{
		{0.7f,0.0f,0.0f,1.0f},
		{0.7f,0.7f,0.0f,1.0f},
		{0.7f,0.0f,0.7f,1.0f},
		{0.0f,0.7f,0.7f,1.0f}
	};

}

void Bone_Animation::update(float delta_time)
{
	// Create variables exclusive to the update function here.
	glm::mat4 globalRedTranslMat = getTranslationMatrix(root_position.x, root_position.y, root_position.z);
	glm::mat4 localYellowMatrix = getTranslationMatrix(0.0f, 0.5f, 0.0f) * getRotationMatrix(yellowLimb.x, yellowLimb.y, yellowLimb.z);
	glm::mat4 localPinkMatrix = getTranslationMatrix(0.0f, 2.0f, 0.0f) * getRotationMatrix(pinkLimb.x, pinkLimb.y, pinkLimb.z);
	glm::mat4 localBlueMatrix = getTranslationMatrix(0.0f, 1.5f, 0.0f) * getRotationMatrix(blueLimb.x, blueLimb.y, blueLimb.z);

	// Translate the matrices to correct their positioning.
	localYellowMatrix = glm::translate(localYellowMatrix, glm::vec3{ 0.0f, 2.0f, 0.0f });
	localPinkMatrix = glm::translate(localPinkMatrix, glm::vec3{ 0.0f, 1.5f, 0.0f });
	localBlueMatrix = glm::translate(localBlueMatrix, glm::vec3{ 0.0f, 1.0f, 0.0f });

	// Create the children of the red limb.
	glm::mat4 globalYellow = globalRedTranslMat * localYellowMatrix;
	glm::mat4 globalPink = globalYellow * localPinkMatrix;
	glm::mat4 globalBlue = globalPink * localBlueMatrix;

	
	// Get the r'_i value of the Jacobian Matrix for each object.
	yellowPivotPosition = globalYellow[3];
	pinkPivotPosition = globalPink[3];
	bluePivotPosition = globalBlue[3];
	
	// Get the a'_i value of the Jacobian Matrix for each object.
	yellowX = globalYellow[0];
	yellowY = globalYellow[1];
	yellowZ = globalYellow[2];

	pinkX = globalPink[0];
	pinkY = globalPink[1];
	pinkZ = globalPink[2];

	blueX = globalBlue[0];
	blueY = globalBlue[1];
	blueZ = globalBlue[2];
	
	// Get the e value of the Jacobian Matrix. 
	e = (globalBlue * getTranslationMatrix(0.0f, 1.0f, 0.0f))[3];
	
	// First, we get the cross product of each axis and the pivot positions.
	crossProduct1 = cross((glm::vec3)yellowX, (glm::vec3)(e - yellowPivotPosition));
	crossProduct2 = cross((glm::vec3)yellowY, (glm::vec3)(e - yellowPivotPosition));
	crossProduct3 = cross((glm::vec3)yellowZ, (glm::vec3)(e - yellowPivotPosition));
	crossProduct4 = cross((glm::vec3)pinkX, (glm::vec3)(e - pinkPivotPosition));
	crossProduct5 = cross((glm::vec3)pinkY, (glm::vec3)(e - pinkPivotPosition));
	crossProduct6 = cross((glm::vec3)pinkZ, (glm::vec3)(e - pinkPivotPosition));
	crossProduct7 = cross((glm::vec3)blueX, (glm::vec3)(e - bluePivotPosition));
	crossProduct8 = cross((glm::vec3)blueY, (glm::vec3)(e - bluePivotPosition));
	crossProduct9 = cross((glm::vec3)blueZ, (glm::vec3)(e - bluePivotPosition));

	// Then we add these cross products to the jacobian array to create a 3x9 matrix.
	float jacobian[3][9];
	jacobian[0][0] = crossProduct1.x;
	jacobian[1][0] = crossProduct1.y;
	jacobian[2][0] = crossProduct1.z;
	jacobian[0][1] = crossProduct2.x;
	jacobian[1][1] = crossProduct2.y;
	jacobian[2][1] = crossProduct2.z;
	jacobian[0][2] = crossProduct3.x;
	jacobian[1][2] = crossProduct3.y;
	jacobian[2][2] = crossProduct3.z;
	jacobian[0][3] = crossProduct4.x;
	jacobian[1][3] = crossProduct4.y;
	jacobian[2][3] = crossProduct4.z;
	jacobian[0][4] = crossProduct5.x;
	jacobian[1][4] = crossProduct5.y;
	jacobian[2][4] = crossProduct5.z;
	jacobian[0][5] = crossProduct6.x;
	jacobian[1][5] = crossProduct6.y;
	jacobian[2][5] = crossProduct6.z;
	jacobian[0][6] = crossProduct7.x;
	jacobian[1][6] = crossProduct7.y;
	jacobian[2][6] = crossProduct7.z;
	jacobian[0][7] = crossProduct8.x;
	jacobian[1][7] = crossProduct8.y;
	jacobian[2][7] = crossProduct8.z;
	jacobian[0][8] = crossProduct9.x;
	jacobian[1][8] = crossProduct9.y;
	jacobian[2][8] = crossProduct9.z;

	// Next, we transpose the jacobian matrix and store it in jacobianTranspose.
	float jacobianTranspose[9][3];

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			jacobianTranspose[i][j] = jacobian[j][i];
		}
	}

	// Reset values, create a dot array and get the difference between g and e.
	float sum = 0.0f;
	float dot[9];
	geDifference = (g - (glm::vec3)e);

	// Multiply the jacobianTranspose variable with the geDifference variable
	// and then add them to the sum to get our dot product.
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sum += geDifference[j] * jacobianTranspose[i][j];
		}
		dot[i] = sum;
		sum = 0.0f;
	}

	// Next we calculate the frobenius norm.
	float frobenius = 0.0f;

	for (int i = 0; i < 9; i++)
	{
		sum += dot[i] * dot[i];
	}

	// We get the square root of the sum variable to get our
	// final value for the frobenius norm. Then we reset sum.
	frobenius = sqrtf(sum);
	sum = 0.0f;

	// Next we multiply the dot array with the jacobian and then add
	// it to sum. This gives us our dot2 array contents for the next
	// frobenius norm.
	float dot2[3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sum += dot[j] * jacobian[i][j];
		}
		dot2[i] = sum;
		sum = 0.0f;
	}

	// Now we calculate the frobenius norm a second time.
	float frobenius2 = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		sum += dot2[i] * dot2[i];
	}

	frobenius2 = sqrtf(sum);
	sum = 0.0f;
	
	// Now that we have our two frobenius norm values, we can
	// finally get our step size value by dividing the first
	// frobenius with the second frobenius.
	float step = powf(frobenius, 2) / powf(frobenius2, 2);

	// Update the limb values if we're in Inverse Kinematics mode. 
	if (activateInvKine)
	{
		yellowLimb.x += step * dot[0];
		yellowLimb.y += step * dot[1];
		yellowLimb.z += step * dot[2];
		pinkLimb.x += step * dot[3];
		pinkLimb.y += step * dot[4];
		pinkLimb.z += step * dot[5];
		blueLimb.x += step * dot[6];
		blueLimb.y += step * dot[7];
		blueLimb.z += step * dot[8];
	}

	// Display the limbs on screen.
	bone1 = globalYellow;
	bone1 = glm::scale(globalYellow, scale_vector[1]);

	bone2 = globalPink;
	bone2 = glm::scale(globalPink, scale_vector[2]);

	bone3 = globalBlue;
	bone3 = glm::scale(globalBlue, scale_vector[3]);
}

void Bone_Animation::reset()
{
	// We reset the limbs by feeding the limb vectors all 0's.
	yellowLimb = { 0.0f, 0.0f, 30.0f };
	pinkLimb = { 0.0f, 0.0f, 30.0f };
	blueLimb = { 0.0f, 0.0f, 30.0f };
}

// My functions go here.
void Bone_Animation::viewMatrix(std::vector<std::vector<float>> matrix, int row, int column)
{
	std::cout << row << " by " << column << " Matrix Contents:\n__________________" << std::endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			std::cout << matrix[i][j] << " | ";
		}
		std::cout << std::endl;
	}
}

glm::mat4 Bone_Animation::getTranslationMatrix(float X, float Y, float Z)
{
	// Return a translation matrix. 
	return glm::mat4
	{
		{ 1, 0, 0, 0 }, // Column 1
		{ 0, 1, 0, 0 }, // Column 2
		{ 0, 0, 1, 0 }, // Column 3
		{ X, Y, Z, 1 }  // Column 4
	};
}

glm::mat4 Bone_Animation::getRotationMatrix(float X, float Y, float Z)
{
	// Return a rotation matrix representing a rotation about the X, Y, and Z axis.
	return getXRotationMatrix(X) * getZRotationMatrix(Z) * getYRotationMatrix(Y);
}

glm::mat4 Bone_Animation::getXRotationMatrix(float X)
{
	// Return an X rotation matrix.
	return glm::mat4
	{
		{ 1, 0, 0, 0 },											// Column 1
		{ 0, cos(glm::radians(X)), sin(glm::radians(X)), 0 },	// Column 2
		{ 0, -sin(glm::radians(X)), cos(glm::radians(X)), 0 },	// Column 3
		{ 0, 0, 0, 1 }											// Column 4
	};
}

glm::mat4 Bone_Animation::getYRotationMatrix(float Y)
{
	// Return a Y rotation matrix.
	return glm::mat4
	{
		{ cos(glm::radians(Y)), 0, -sin(glm::radians(Y)), 0 },	// Column 1
		{ 0, 1, 0, 0 },											// Column 2
		{ sin(glm::radians(Y)), 0, cos(glm::radians(Y)), 0 },	// Column 3
		{ 0, 0, 0, 1 }											// Column 4
	};
}

glm::mat4 Bone_Animation::getZRotationMatrix(float Z)
{
	// Return a Z rotation matrix.
	return glm::mat4
	{
		{ cos(glm::radians(Z)), sin(glm::radians(Z)), 0, 0 },	// Column 1
		{ -sin(glm::radians(Z)), cos(glm::radians(Z)), 0, 0 },	// Column 2
		{ 0, 0, 1, 0},											// Column 3
		{ 0, 0, 0, 1}											// Column 4
	};
}

