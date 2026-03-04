#pragma once

#include <array>
#include <cstdint>
#include <vector>

namespace bfl2::core {

struct PointXYZI {
    float x{0.f};
    float y{0.f};
    float z{0.f};
    float intensity{0.f};
};

using PointCloud = std::vector<PointXYZI>;

struct ImuSample {
    double timestamp{0.0};
    std::array<double, 3> acc{0.0, 0.0, 0.0};
    std::array<double, 3> gyr{0.0, 0.0, 0.0};
};

struct LidarFrame {
    double timestamp{0.0};
    PointCloud cloud;
};

struct Pose {
    double timestamp{0.0};
    std::array<double, 3> t{0.0, 0.0, 0.0};
    std::array<double, 4> q{1.0, 0.0, 0.0, 0.0}; // w, x, y, z
};

struct KeyFrame {
    Pose pose;
    PointCloud cloud;
};

} // namespace bfl2::core

