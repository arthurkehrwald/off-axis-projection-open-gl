#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OffAxisProjection
{
	glm::mat4 offAxisFrustum(const glm::vec3& viewPos, const glm::vec3 screenBL, const glm::vec3 screenBR, const glm::vec3 screenTL, float nearDist, float farDist);
}