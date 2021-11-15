
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "collision_result.h"
#include "sat.h"

int main() {

	std::vector<glm::vec2> shape1Vertices = { { -30, 30 },
											  { 30, 30 },
											  { 30, -30 },
											  { -30, -30 }};

	std::vector<glm::vec2> shape1Normals = { { -1, 0 },
											 { 0, 1},
											  { 1, 0 },
											  { 0, -1 }};

	std::vector<glm::vec2> shape2Vertices = { { 15, 55 },
											  { 55, 55 },
											  { 55, -15 },
											  { 15, -15 }};

	std::vector<glm::vec2> shape2Normals = { { -1, 0 },
											 { 0, 1 },
											 { 1, 0 },
											 { 0, -1 }};

	CollisionResult result = SAT(shape1Normals, shape1Vertices, shape2Normals, shape2Vertices);
	if (result.Collided()) {
		std::cout << "collision detected" << std::endl;
		std::cout << "total separation distance: " << result.GetSeparationDistance() << std::endl;

		const glm::vec2& collisionNormal1 = result.GetEntity1CollisionNormal();
		const glm::vec2& collisionNormal2 = result.GetEntity2CollisionNormal();
		std::cout << "first entity collision normal: (" << collisionNormal1.x << ", " << collisionNormal1.y << ")" << std::endl;
		std::cout << "second entity collision normal: (" << collisionNormal2.x << ", " << collisionNormal2.y << ")" << std::endl;
	}

	return 0;
}
