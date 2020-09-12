#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "sdl-util/sdl_conversion.hpp"
#include "kobold-layer.nucleus/render/rectangle.hpp"

using ::testing::Eq;

namespace kobold_layer::nucleus::sdl_util {
	TEST(sdl_conversion_test, to_sdl_rect_expected_results)
	{
		// Setup
		const auto rect = render::rectangle(1, 2, 3, 4);
		// Call
		const auto sdl_rect = to_sdl_rect(rect);

		// Assert
		ASSERT_THAT(sdl_rect.x, Eq(rect.x));
		ASSERT_THAT(sdl_rect.y, Eq(rect.y));
		ASSERT_THAT(sdl_rect.w, Eq(rect.width));
		ASSERT_THAT(sdl_rect.h, Eq(rect.height));
	}


	TEST(sdl_conversion_test, to_rectangle_expected_results)
	{
		// Setup
		SDL_Rect sdl_rect;
		sdl_rect.x = 1;
		sdl_rect.y = 2;
		sdl_rect.x = 3;
		sdl_rect.h = 4;

		// Call
		const auto rect = to_rectangle(&sdl_rect);

		// Assert
		ASSERT_THAT(rect.x, Eq(sdl_rect.x));
		ASSERT_THAT(rect.y, Eq(sdl_rect.y));
		ASSERT_THAT(rect.width, Eq(sdl_rect.w));
		ASSERT_THAT(rect.height, Eq(sdl_rect.h));
	}
}