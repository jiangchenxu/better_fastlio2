#include "core/odometry_pipeline.hpp"

#include <iostream>

namespace bfl2::core {

OdometryPipeline::OdometryPipeline(io::ILidarSource& lidar, io::IImuSource& imu, io::IMapSink& sink)
    : lidar_(lidar), imu_(imu), sink_(sink) {}

void OdometryPipeline::run() {
    while (auto frame = lidar_.next()) {
        while (auto imu = imu_.next()) {
            if (imu->timestamp > frame->timestamp) {
                break;
            }
            // TODO: replace with true preintegration + ESKF propagation.
        }

        Pose pose = estimatePose(*frame);

        KeyFrame keyframe;
        keyframe.pose = pose;
        keyframe.cloud = frame->cloud;
        sink_.writeKeyFrame(keyframe);

        std::cout << "[ros_free] keyframe @ " << pose.timestamp
                  << " | xyz = (" << pose.t[0] << ", " << pose.t[1] << ", " << pose.t[2] << ")\n";
    }

    sink_.flush();
}

Pose OdometryPipeline::estimatePose(const LidarFrame& frame) {
    Pose out;
    out.timestamp = frame.timestamp;

    if (!initialized_) {
        initialized_ = true;
        last_pose_ = out;
        return out;
    }

    // Placeholder: constant velocity-style drift, serves as non-ROS executable demo.
    out = last_pose_;
    out.timestamp = frame.timestamp;
    out.t[0] += 0.1;

    last_pose_ = out;
    return out;
}

} // namespace bfl2::core

