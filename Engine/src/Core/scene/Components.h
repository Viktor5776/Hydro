#pragma once
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


namespace hydro
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag)
		{}
	};

	struct Transform
	{
		glm::vec3 Translation;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		Transform(
				const glm::vec3& translation = {0.0f,0.0f,0.0f}, 
				const glm::vec3& rotation = {0.0f,0.0f,0.0f}, 
				const glm::vec3& scale = {1.0f,1.0f,1.0f})
			:
			Translation(translation),
			Rotation(rotation),
			Scale(scale)
		{}
		Transform(const Transform&) = default;

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}