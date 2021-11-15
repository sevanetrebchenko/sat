
#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "collision_result.h"

[[nodiscard]] CollisionResult SAT(const std::vector<glm::vec2>& shape1Normals, const std::vector<glm::vec2>& shape1Points, const std::vector<glm::vec2>& shape2Normals, const std::vector<glm::vec2>& shape2Points);

