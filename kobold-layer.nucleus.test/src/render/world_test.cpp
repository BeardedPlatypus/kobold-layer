#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "render/world_implementation.hpp"

using ::testing::AllOf;
using ::testing::Field;

namespace kobold_layer::nucleus::render
{
	TEST(world_test, constructor_sets_boundaries_correctly)
	{
		// Setup
		rectangle<float> const new_boundaries = { 2.0F, 3.0F, 4.0F, 5.0F };

		// Call
		auto const world = world_implementation(new_boundaries);

		// Assert
		ASSERT_THAT(
			world.get_boundaries(),
			AllOf(Field(&rectangle<float>::x, new_boundaries.x),
				  Field(&rectangle<float>::y, new_boundaries.y),
				  Field(&rectangle<float>::width, new_boundaries.width),
				  Field(&rectangle<float>::height, new_boundaries.height)));
	}

	TEST(world_test, set_boundaries_expected_results)
	{
		// Setup
		auto world = world_implementation({ 2.0F, 3.0F, 4.0F, 5.0F });
		rectangle<float> const new_boundaries = { 2.5F, 3.5F, 4.5F, 5.5F };

		// Call
		world.set_boundaries(new_boundaries);

		// Assert
		ASSERT_THAT(
			world.get_boundaries(),
			AllOf(Field(&rectangle<float>::x, new_boundaries.x),
				  Field(&rectangle<float>::y, new_boundaries.y),
				  Field(&rectangle<float>::width, new_boundaries.width),
				  Field(&rectangle<float>::height, new_boundaries.height)));
	}
}

