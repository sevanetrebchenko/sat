
#include "sat.h"

[[nodiscard]] glm::vec2 ProjectPointsOntoAxis(const glm::vec2& axis, const std::vector<glm::vec2>& points) {
	// No projection possible.
	if (points.empty()) {
		return glm::vec2(0.0f);
	}

	float minimum = glm::dot(axis, points[0]);
	float maximum = minimum;

	for (const glm::vec2& point : points) {
		float projection = glm::dot(axis, point);

		minimum = glm::min(minimum, projection);
		maximum = glm::max(maximum, projection);
	}

	return { minimum, maximum };
}

[[nodiscard]] float GetMinimumProjectionDistance(const glm::vec2& projection1, const glm::vec2& projection2) {
	float minimum1 = projection1.x;
	float maximum1 = projection1.y;

	float minimum2 = projection2.x;
	float maximum2 = projection2.y;

	return (minimum1 < minimum2) ? (maximum1 - minimum2) : (maximum2 - minimum1);
}

[[nodiscard]] glm::vec2 GetShapeCentroid(const std::vector<glm::vec2>& shapePoints) {
	glm::vec2 centroid(0.0f);

	for (const glm::vec2& point : shapePoints) {
		centroid += point;
	}

	return centroid /= static_cast<float>(shapePoints.size());
}

CollisionResult SAT(const std::vector<glm::vec2>& shape1Normals, const std::vector<glm::vec2>& shape1Points, const std::vector<glm::vec2>& shape2Normals, const std::vector<glm::vec2>& shape2Points) {
	// *All* projections between both shapes need to overlap if objects are colliding.
	// Objective: get the smallest possible separation along a shape axis.
	glm::vec2 separationAxis(0.0f);
	float minimumIntersectionDistance = std::numeric_limits<float>::max();

	for (const glm::vec2& axis : shape1Normals) {
		// Project points from both shapes.
		glm::vec2 projection1 = ProjectPointsOntoAxis(axis, shape1Points);
		glm::vec2 projection2 = ProjectPointsOntoAxis(axis, shape2Points);

		// Check for overlap.
		if ((projection1.y < projection2.x) || (projection2.y < projection1.x)) {
			return CollisionResult(false); // No overlap in one axis = no collision.
		}

		// Look for the minimum separation distance along this axis.
		float currentMinimumDistance = GetMinimumProjectionDistance(projection1, projection2);

		if (currentMinimumDistance < minimumIntersectionDistance) {
			minimumIntersectionDistance = currentMinimumDistance;
			separationAxis = axis;
		}
	}

	for (const glm::vec2& axis : shape2Normals) {
		// Project points from both shapes.
		glm::vec2 projection1 = ProjectPointsOntoAxis(axis, shape1Points);
		glm::vec2 projection2 = ProjectPointsOntoAxis(axis, shape2Points);

		// Check for overlap.
		if ((projection1.y < projection2.x) || (projection2.y < projection1.x)) {
			return CollisionResult(false); // No overlap in one axis = no collision.
		}

		// Look for the minimum separation distance along this axis.
		float currentMinimumDistance = GetMinimumProjectionDistance(projection1, projection2);

		if (currentMinimumDistance < minimumIntersectionDistance) {
			minimumIntersectionDistance = currentMinimumDistance;
			separationAxis = axis;
		}
	}

	// Objects are colliding.
	// Determine direction of separation axis.
	// Resolution needs to push the position of entity1 away from the position of entity2 along the separation axis.
	glm::vec2 shape1Centroid = GetShapeCentroid(shape1Points);
	glm::vec2 shape2Centroid = GetShapeCentroid(shape2Points);
	glm::vec2 difference = shape2Centroid - shape1Centroid; // Separation vector needs to point away from this.

	if (glm::dot(separationAxis, difference) > 0.0f) {
		separationAxis *= -1.0f;
	}

	separationAxis = glm::normalize(separationAxis);

	return CollisionResult(true, separationAxis, -separationAxis, minimumIntersectionDistance);
}
