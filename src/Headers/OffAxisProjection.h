#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OffAxisProjection
{
	glm::mat4 offAxisFrustum(const glm::vec3 screenBL_VS, const glm::vec3 screenBR_VS, const glm::vec3 screenTL_VS, float nearDist, float farDist);
	glm::mat4 offAxisView(const glm::vec3 viewPos_WS, const glm::vec3 screenBL_WS, const glm::vec3 screenBR_WS, const glm::vec3 screenTL_WS);
}