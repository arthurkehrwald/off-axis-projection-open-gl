#include "OffAxisProjection.h"	

/// <summary>
/// 
/// </summary>
/// <param name="viewPos">Camera position in world space</param>
/// <param name="screenBLPos">Bottom left corner of the screen in world space</param>
/// <param name="screenBRPos">Bottom right corner of the screen in world space</param>
/// <param name="screenTLPos">Top left corner of the screen in world space</param>
/// <returns>Projection Matrix</returns>
glm::mat4 OffAxisProjection::offAxisFrustum(const glm::vec3& viewPos, const glm::vec3 screenBLPos, const glm::vec3 screenBRPos, const glm::vec3 screenTLPos, float nearDist, float farDist)
{
	glm::vec3 screenRightDir = glm::normalize(screenBRPos - screenBLPos);
	glm::vec3 screenUpDir = glm::normalize(screenTLPos - screenBLPos);
	glm::vec3 screenFwdDir = glm::normalize(glm::cross(screenRightDir, screenUpDir));

	glm::vec3 viewToScreenBL = screenBLPos - viewPos;
	glm::vec3 viewToScreenBR = screenBRPos - viewPos;
	glm::vec3 viewToScreenTL = screenTLPos - viewPos;

	float viewToScreenOriginDist = -glm::dot(screenFwdDir, viewToScreenBL);
	
	float screenOriginToLeftEdgeDist = glm::dot(screenRightDir, viewToScreenBL) * nearDist / viewToScreenOriginDist;
	float screenOriginToRightEdgeDist = glm::dot(screenRightDir, viewToScreenBR) * nearDist / viewToScreenOriginDist;
	float screenOriginToTopEdgeDist = glm::dot(screenUpDir, viewToScreenTL) * nearDist / viewToScreenOriginDist;
	float screenOriginToBotEdgeDist = glm::dot(screenUpDir, viewToScreenBL) * nearDist / viewToScreenOriginDist;

	glm::mat4 projection = glm::frustum(screenOriginToLeftEdgeDist, screenOriginToRightEdgeDist, screenOriginToBotEdgeDist, screenOriginToTopEdgeDist, nearDist, farDist);
		
	glm::mat4 projectionPlaneOrientation = glm::mat4(0.0);
	projectionPlaneOrientation[0][0] = screenRightDir.x;
	projectionPlaneOrientation[1][0] = screenRightDir.y;
	projectionPlaneOrientation[2][0] = screenRightDir.z;
	projectionPlaneOrientation[0][1] = screenUpDir.x;
	projectionPlaneOrientation[1][1] = screenUpDir.y;
	projectionPlaneOrientation[2][1] = screenUpDir.z;
	projectionPlaneOrientation[0][2] = screenFwdDir.x;
	projectionPlaneOrientation[1][2] = screenFwdDir.y;
	projectionPlaneOrientation[2][2] = screenFwdDir.z;
	projectionPlaneOrientation[3][3] = 1.0f;

	glm::mat4 viewOffset = glm::mat4();
	viewOffset[3][0] = -viewPos.x;
	viewOffset[3][1] = -viewPos.y;
	viewOffset[3][2] = -viewPos.z;

	return projection * projectionPlaneOrientation;	
}
