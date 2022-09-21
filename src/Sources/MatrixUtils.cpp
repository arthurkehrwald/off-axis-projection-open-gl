#include "MatrixUtils.h"

glm::mat4 MatrixUtils::createTransformation(glm::vec3 translation, glm::vec3 eulerAngles, glm::vec3 scale)
{
	glm::mat4 m = glm::mat4(1.0);
	m = glm::translate(m, translation);
	eulerAngles = glm::radians(eulerAngles);
	m = glm::rotate(m, eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m = glm::rotate(m, eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m = glm::rotate(m, eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, scale);
	return m;
}