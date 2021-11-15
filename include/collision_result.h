
#pragma once

#include <glm/glm.hpp>

class CollisionResult {
	public:
		explicit CollisionResult(bool inCollided,
								 const glm::vec2& inCollisionNormal1 = glm::vec2(0.0f),
								 const glm::vec2& inCollisionNormal2 = glm::vec2(0.0f),
								 float separationDistance = 0.0f);
		~CollisionResult();

		// Returns if the two entities have collided or not.
		[[nodiscard]] bool Collided() const;

		// Collision normals are based on the perspective.
		// Returned collision normals are normalized (direction only).
		// Distance to separate is judged by the type of collision (static-static, static-dynamic, dynamic-dynamic).
		[[nodiscard]] const glm::vec2& GetEntity1CollisionNormal() const; // Separation normal for first entity passed into Colliding(..) call.
		[[nodiscard]] const glm::vec2& GetEntity2CollisionNormal() const; // Separation normal for second entity passed winto Colliding(...) call.
		[[nodiscard]] float GetSeparationDistance() const;

	private:
		bool collided;
		glm::vec2 collisionNormal1;
		glm::vec2 collisionNormal2;
		float separationDistance;
};

