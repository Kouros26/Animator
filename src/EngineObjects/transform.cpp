#include "EngineObjects/transform.hpp"

Transform::Transform()
{
}

glm::mat4 Transform::GetMatrix() const
{
	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	const glm::mat4 rotationMatrix = glm::toMat4(rotation);
	const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	const glm::mat4 transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return transformMatrix;
}
