#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OffAxisProjection
{
	glm::mat4 offAxisFrustum(const glm::vec3 screenBL_VS, const glm::vec3 screenBR_VS, const glm::vec3 screenTL_VS, float nearDist, float farDist);
}