#pragma once

#include "core/types.hpp"

#include <optional>

namespace bfl2::io {

class ILidarSource {
public:
    virtual ~ILidarSource() = default;
    virtual std::optional<core::LidarFrame> next() = 0;
};

class IImuSource {
public:
    virtual ~IImuSource() = default;
    virtual std::optional<core::ImuSample> next() = 0;
};

class IMapSink {
public:
    virtual ~IMapSink() = default;
    virtual void writeKeyFrame(const core::KeyFrame& frame) = 0;
    virtual void flush() = 0;
};

} // namespace bfl2::io

