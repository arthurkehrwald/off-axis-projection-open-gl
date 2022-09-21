#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MatrixUtils
{
	glm::mat4 createTransformation(glm::vec3 translation, glm::vec3 eulerAngles, glm::vec3 scale);
}