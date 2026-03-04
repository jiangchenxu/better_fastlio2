#pragma once

#include "core/types.hpp"
#include "io/interfaces.hpp"

namespace bfl2::core {

class OdometryPipeline {
public:
    OdometryPipeline(io::ILidarSource& lidar, io::IImuSource& imu, io::IMapSink& sink);

    void run();

private:
    Pose estimatePose(const LidarFrame& frame);

    io::ILidarSource& lidar_;
    io::IImuSource& imu_;
    io::IMapSink& sink_;

    Pose last_pose_{};
    bool initialized_{false};
};

} // namespace bfl2::core

