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