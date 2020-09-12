#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "kobold-layer.nucleus/render/rectangle.hpp"

using ::testing::Eq;

namespace kobold_layer::nucleus::render {
	TEST(rectangle_test, constructor_expected_results)
	{
		// Setup
		const int x = 1;
		const int y = 2;
		const int width = 3;
		const int height = 4;

		// Call
		const auto rect = rectangle(x, y, width, height);

		// Assert
		ASSERT_THAT(rect.x, Eq(x));
		ASSERT_THAT(rect.y, Eq(y));
		ASSERT_THAT(rect.width, Eq(width));
		ASSERT_THAT(rect.height, Eq(height));
	}
}