#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OffAxisProjection
{
	glm::mat4 offAxisFrustum(const glm::vec3 screenBL_VS, const glm::vec3 screenBR_VS, const glm::vec3 screenTL_VS, float nearDist, float farDist);
	glm::mat4 offAxisView(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS);
	glm::mat4 offAxisViewManual(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS);
	glm::mat4 offAxisViewManual2(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS);
	glm::mat4 onAxisViewManual(const glm::vec3 viewPos_WS, const glm::vec3 right_WS, const glm::vec3 up_WS, const glm::vec3 fwd_WS);
}