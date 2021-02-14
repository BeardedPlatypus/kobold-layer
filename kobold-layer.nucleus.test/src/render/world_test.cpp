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
		rectangle<float> const new_boundaries = { 2.0f, 3.0f, 4.0f, 5.0f };

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
		auto world = world_implementation({ 2.0f, 3.0f, 4.0f, 5.0f });
		rectangle<float> const new_boundaries = { 2.5f, 3.5f, 4.5f, 5.5f };

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

