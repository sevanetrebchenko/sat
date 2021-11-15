
#include "collision_result.h"

CollisionResult::CollisionResult(bool inCollided,
								 const glm::vec2& inCollisionNormal1,
								 const glm::vec2& inCollisionNormal2,
								 float inSeparationDistance) : collided(inCollided),
															   collisionNormal1(glm::normalize(inCollisionNormal1)),
															   collisionNormal2(glm::normalize(inCollisionNormal2)),
															   separationDistance(inSeparationDistance)
{
}

CollisionResult::~CollisionResult() = default;

bool CollisionResult::Collided() const {
	return collided;
}

const glm::vec2& CollisionResult::GetEntity1CollisionNormal() const {
	return collisionNormal1;
}

const glm::vec2& CollisionResult::GetEntity2CollisionNormal() const {
	return collisionNormal2;
}

float CollisionResult::GetSeparationDistance() const {
	return separationDistance;
}

