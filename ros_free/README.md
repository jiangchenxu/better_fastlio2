# ROS-free 迁移骨架（阶段一）

这个目录给出 **去 ROS 的结构化代码模板**，目标是把原有系统拆成：

1. **core/**：算法核心（不依赖 ROS）
2. **io/**：输入输出接口层（可对接 rosbag / pcap / 自定义驱动）
3. **runner**：可执行入口（CLI）

## 目录结构

```text
ros_free/
├── CMakeLists.txt
├── include
│   ├── core
│   │   ├── odometry_pipeline.hpp
│   │   └── types.hpp
│   └── io
│       └── interfaces.hpp
└── src
    ├── main.cpp
    └── odometry_pipeline.cpp
```

## 设计说明

- `core::OdometryPipeline` 作为统一主流程，负责时间同步、状态估计、关键帧输出。
- `io::ILidarSource / IImuSource / IMapSink` 负责解耦平台依赖。
- 当前 `main.cpp` 内置 `Fake*` 实现，确保先可编译、可运行、可输出轨迹文件。

## 下一步迁移建议（对应原仓库功能）

- 将 `src/preprocess.*` 的点云预处理逻辑迁入 `core/preprocess`。
- 将 `src/IMU_Processing.hpp` 的预积分/EKF迁入 `core/imu`。
- 将 `include/ikd-Tree` 作为独立子模块迁入 `core/map`。
- 将 `include/sc-relo` 与 `include/multi-session` 迁入 `core/relocalization` 和 `core/graph`。
- 在 `io/` 下补充 `pcd+txt`、`rosbag2`、`udp` 三类 adapter。


## 在本地生成工程文件

```bash
cd ros_free
./scripts/generate_project.sh            # 默认生成到 ros_free/build
# 或指定目录
./scripts/generate_project.sh build-clang
```

随后可继续编译：

```bash
cmake --build build -j
```

## 构建

```bash
cd ros_free
cmake -S . -B build
cmake --build build -j
./build/lio_runner
```

运行后会在当前目录写出 `trajectory.txt`。
