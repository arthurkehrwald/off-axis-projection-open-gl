#include "OffAxisProjection.h"	

/// <summary>
/// Constructs a projection matrix from view space corner positions of an arbitrarily positioned and rotated projection plane
/// </summary>
/// <param name="screenBL_VS">View space (relative to camera) position of bottom left corner of screen</param>
/// <param name="screenBR_VS">View space (relative to camera) position of bottom right corner of screen</param>
/// <param name="screenTL_VS">View space (relative to camera) position of top left corner of screen</param>
/// <param name="nearDist">Desired distance between the camera and the near clipping plane</param>
/// <param name="farDist">Desired distance between the camera and the far clipping plane</param>
/// <returns>Projection matrix</returns>
glm::mat4 OffAxisProjection::offAxisFrustum(const glm::vec3 screenBL_VS, const glm::vec3 screenBR_VS, const glm::vec3 screenTL_VS, float nearDist, float farDist)
{
	glm::vec3 screenRightDir = glm::normalize(screenBR_VS - screenBL_VS);
	glm::vec3 screenUpDir = glm::normalize(screenTL_VS - screenBL_VS);
	glm::vec3 screenFwdDir = glm::normalize(glm::cross(screenRightDir, screenUpDir));

	float viewToScreenOriginDist = -glm::dot(screenFwdDir, screenBL_VS);
	
	float screenOriginToLeftEdgeDist = glm::dot(screenRightDir, screenBL_VS) * nearDist / viewToScreenOriginDist;
	float screenOriginToRightEdgeDist = glm::dot(screenRightDir, screenBR_VS) * nearDist / viewToScreenOriginDist;
	float screenOriginToTopEdgeDist = glm::dot(screenUpDir, screenTL_VS) * nearDist / viewToScreenOriginDist;
	float screenOriginToBotEdgeDist = glm::dot(screenUpDir, screenBL_VS) * nearDist / viewToScreenOriginDist;

	glm::mat4 projection = glm::frustum(screenOriginToLeftEdgeDist, screenOriginToRightEdgeDist, screenOriginToBotEdgeDist, screenOriginToTopEdgeDist, nearDist, farDist);	
	return projection;
}

glm::mat4 OffAxisProjection::offAxisView(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS)
{
	glm::vec3 screenRightDir_WS = glm::normalize(screenBR_WS - screenBL_WS);
	glm::vec3 screenUpDir_WS = glm::normalize(screenTL_WS - screenBL_WS);
	glm::vec3 screenFwdDir_WS = glm::normalize(glm::cross(screenRightDir_WS, screenUpDir_WS));
	glm::mat4 viewMat = glm::lookAt(viewPos_WS, viewPos_WS - screenFwdDir_WS, screenUpDir_WS);
	return viewMat;
}

glm::mat4 OffAxisProjection::offAxisViewManual(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS)
{
	glm::vec3 screenRightDir_WS = glm::normalize(screenBR_WS - screenBL_WS);
	glm::vec3 screenUpDir_WS = glm::normalize(screenTL_WS - screenBL_WS);
	glm::vec3 screenFwdDir_WS = glm::normalize(glm::cross(screenRightDir_WS, screenUpDir_WS));

	glm::mat4 viewMatrix = glm::mat4(1.0);

	// COLUMN MAJOR COLUMN MAJOR COLUMN MAJOR
	viewMatrix[0][0] = screenRightDir_WS.x;
    viewMatrix[0][1] = screenRightDir_WS.y;
    viewMatrix[0][2] = screenRightDir_WS.z;

    viewMatrix[1][0] = screenUpDir_WS.x;
	viewMatrix[1][1] = screenUpDir_WS.y;
	viewMatrix[1][2] = screenUpDir_WS.z;

    viewMatrix[2][0] = screenFwdDir_WS.x;
	viewMatrix[2][1] = screenFwdDir_WS.y;
	viewMatrix[2][2] = screenFwdDir_WS.z;

	glm::vec3 p = glm::inverse(viewMatrix) * glm::vec4(viewPos_WS, 1.0f);

    viewMatrix[3][0] = p.x;
	viewMatrix[3][1] = p.y;
	viewMatrix[3][2] = p.z;

    return viewMatrix;
}

glm::mat4 OffAxisProjection::offAxisViewManual2(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS)
{
	glm::vec3 screenRightDir_WS = glm::normalize(screenBR_WS - screenBL_WS);
	glm::vec3 screenUpDir_WS = glm::normalize(screenTL_WS - screenBL_WS);
	glm::vec3 screenFwdDir_WS = glm::normalize(glm::cross(screenRightDir_WS, screenUpDir_WS));

	glm::mat4 viewMatrix = glm::mat4(1.0);

	// COLUMN MAJOR COLUMN MAJOR COLUMN MAJOR
	viewMatrix[0][0] = screenRightDir_WS.x;
	viewMatrix[1][0] = screenRightDir_WS.y;
	viewMatrix[2][0] = screenRightDir_WS.z;

	viewMatrix[0][1] = screenUpDir_WS.x;
	viewMatrix[1][1] = screenUpDir_WS.y;
	viewMatrix[2][1] = screenUpDir_WS.z;

	viewMatrix[0][2] = screenFwdDir_WS.x;
	viewMatrix[1][2] = screenFwdDir_WS.y;
	viewMatrix[2][2] = screenFwdDir_WS.z;

	return glm::translate(viewMatrix, -viewPos_WS);
}

glm::mat4 OffAxisProjection::onAxisViewManual(const glm::vec3 viewPos_WS, const glm::vec3 right_WS, const glm::vec3 up_WS, const glm::vec3 fwd_WS)
{
	glm::mat4 viewMatrix = glm::mat4(1.0);

	// COLUMN MAJOR COLUMN MAJOR COLUMN MAJOR
	viewMatrix[0][0] = right_WS.x;
	viewMatrix[0][1] = right_WS.y;
	viewMatrix[0][2] = right_WS.z;

	viewMatrix[1][0] = up_WS.x;
	viewMatrix[1][1] = up_WS.y;
	viewMatrix[1][2] = up_WS.z;

	viewMatrix[2][0] = fwd_WS.x;
	viewMatrix[2][1] = fwd_WS.y;
	viewMatrix[2][2] = fwd_WS.z;

	viewMatrix[3][0] = viewPos_WS.x;
	viewMatrix[3][1] = viewPos_WS.y;
	viewMatrix[3][2] = viewPos_WS.z;

	return viewMatrix;
}