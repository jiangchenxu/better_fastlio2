#include "core/odometry_pipeline.hpp"

#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <utility>

namespace bfl2 {

class FakeLidarSource final : public io::ILidarSource {
public:
    std::optional<core::LidarFrame> next() override {
        if (idx_ >= 5) {
            return std::nullopt;
        }
        core::LidarFrame f;
        f.timestamp = static_cast<double>(idx_) * 0.1;
        f.cloud.push_back({0.f, 0.f, 0.f, 1.f});
        f.cloud.push_back({1.f, 0.f, 0.f, 1.f});
        ++idx_;
        return f;
    }

private:
    int idx_{0};
};

class FakeImuSource final : public io::IImuSource {
public:
    std::optional<core::ImuSample> next() override {
        if (idx_ >= 100) {
            return std::nullopt;
        }
        core::ImuSample s;
        s.timestamp = static_cast<double>(idx_) * 0.01;
        s.acc = {0.0, 0.0, 9.81};
        s.gyr = {0.0, 0.0, 0.0};
        ++idx_;
        return s;
    }

private:
    int idx_{0};
};

class FileMapSink final : public io::IMapSink {
public:
    explicit FileMapSink(std::string path) : path_(std::move(path)) {}

    void writeKeyFrame(const core::KeyFrame& frame) override {
        poses_.push_back(frame.pose);
    }

    void flush() override {
        std::ofstream out(path_);
        for (const auto& p : poses_) {
            out << p.timestamp << ' '
                << p.t[0] << ' ' << p.t[1] << ' ' << p.t[2] << ' '
                << p.q[0] << ' ' << p.q[1] << ' ' << p.q[2] << ' ' << p.q[3] << '\n';
        }
        std::cout << "[ros_free] wrote " << poses_.size() << " poses to " << path_ << "\n";
    }

private:
    std::string path_;
    std::vector<core::Pose> poses_;
};

} // namespace bfl2

int main() {
    bfl2::FakeLidarSource lidar;
    bfl2::FakeImuSource imu;
    bfl2::FileMapSink sink("trajectory.txt");

    bfl2::core::OdometryPipeline pipeline(lidar, imu, sink);
    pipeline.run();
    return 0;
}

