#pragma once

#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>

class Transform {
public:

	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)):mPosition(position), mRotation(rotation), mScale(scale)
	{
	}

	inline glm::mat4 GetModel() const {
		glm::mat4 posMatrix = glm::translate(mPosition);
		glm::mat4 scaleMatrix = glm::scale(mScale);
		glm::mat4 rotXMatrix = glm::rotate(mRotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(mRotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(mRotation.z, glm::vec3(0, 0, 1));

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPosition() { return mPosition; }
	inline glm::vec3& GetRotation() { return mRotation; }
	inline glm::vec3& GetScale() { return mScale; }

	inline void SetPosition(const glm::vec3& position) { mPosition = position; }
	inline void SetRotation(const glm::vec3& rotation) { mRotation = rotation; }
	inline void SetScale(const glm::vec3& scale) { mScale = scale; }

private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;

};