#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "kobold-layer.nucleus/render/rectangle.hpp"

using ::testing::Eq;

namespace kobold_layer::nucleus::render
{
    TEST(rectangle_test, constructor_int_expected_results)
    {
        // Setup
        int const x = 1;
        int const y = 2;
        int const width = 3;
        int const height = 4;

        // Call
        rectangle const rect = rectangle(x, y, width, height);

        // Assert
        ASSERT_THAT(rect.x, Eq(x));
        ASSERT_THAT(rect.y, Eq(y));
        ASSERT_THAT(rect.width, Eq(width));
        ASSERT_THAT(rect.height, Eq(height));
    }
	
    TEST(rectangle_test, constructor_float_expected_results)
    {
        // Setup
        float const x = 1.2F;
        float const y = 2.3F;
        float const width = 3.4F;
        float const height = 4.5F;

        // Call
        rectangle const rect = rectangle(x, y, width, height);

        // Assert
        ASSERT_THAT(rect.x, Eq(x));
        ASSERT_THAT(rect.y, Eq(y));
        ASSERT_THAT(rect.width, Eq(width));
        ASSERT_THAT(rect.height, Eq(height));
    }
}