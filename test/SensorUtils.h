#pragma once
#include <optional>

struct Location {
	double x, y, z;
};

Location CombineSensors(const std::optional<Location>& gps,
    const std::optional<Location>& imu,
    const std::optional<Location>& radar)
{
    return {
        gps->x + imu->x + radar->x / 3.0,
        gps->y + imu->y + radar->y / 3.0,
        gps->z + imu->z + radar->z / 3.0
    };
}