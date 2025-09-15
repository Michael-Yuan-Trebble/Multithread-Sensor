#pragma warning(push)
#pragma(disable: VCR003)
#include <gtest/gtest.h>
#pragma warning(pop)
#include <optional>
#include "SensorUtils.h"

TEST(CombineTest, CorrectAverage) {
	std::optional<Location> gps = Location{ 1,1,1 };
	std::optional<Location> imu = Location{ 2,2,2 };
	std::optional<Location> radar = Location{ 3,3,3 };

	Location combined = CombineSensors(gps, imu, radar);

	EXPECT_DOUBLE_EQ(combined.x, 1 + 2 + 3 / 3.0);
	EXPECT_DOUBLE_EQ(combined.y, 1 + 2 + 3 / 3.0);
	EXPECT_DOUBLE_EQ(combined.z, 1 + 2 + 3 / 3.0);

}