#pragma once

#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "gtx\transform.hpp"

class Camera {
public:
	Camera(const glm::vec3& Position, float FOV, float aspect, float Znear, float Zfar) {
		mPerspective = glm::perspective(FOV, aspect, Znear, Zfar);
		mPosition = Position;
		mForward = glm::vec3(0.0f, 0.0f, 1.0f);
		mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void SetPosition(const glm::vec3& MovementFactor = glm::vec3(0,0,0)) {
		mPosition += MovementFactor;
	}

	inline glm::mat4 GetViewProjection() const {
		return mPerspective * glm::lookAt(mPosition, mPosition + mForward, mUp);
	}

private:
	glm::mat4 mPerspective;
	glm::vec3 mPosition;
	glm::vec3 mForward;
	glm::vec3 mUp;
};