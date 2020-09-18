#include "kobold-layer.nucleus.mock/sdl-util/resource_wrapper_mock.hpp"
#include "kobold-layer.nucleus.mock/sdl-util/sdl_dispatcher_mock.hpp"
#include "kobold-layer.nucleus.mock/render/renderer_mock.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "texture/texture_implementation.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::Eq;
using ::testing::Ref;

namespace kobold_layer::nucleus::texture {
	TEST(texture_test, get_dimensions_returns_expected_results)
	{
		// Setup
		SDL_Texture* const sdl_tex = reinterpret_cast<SDL_Texture*>(24);

		auto p_resource_wrapper = std::make_unique<resource_wrapper_mock<SDL_Texture>>();
		EXPECT_CALL(*(p_resource_wrapper.get()), get_resource()).Times(1).WillOnce(Return(sdl_tex));

		int const expected_w = 10;
		int const expected_h = 11;

		std::shared_ptr<sdl_dispatcher_mock> const p_dispatcher = 
			std::make_shared<sdl_dispatcher_mock>();
		EXPECT_CALL(*(p_dispatcher.get()), query_texture(sdl_tex, nullptr, nullptr, _, _))
			.Times(1)
			.WillOnce(DoAll(SetArgPointee<3>(expected_w),
				SetArgPointee<4>(expected_h)));

		texture_implementation const texture = texture_implementation(std::move(p_resource_wrapper), p_dispatcher);

		// Call
		render::rectangle const result = texture.get_dimensions();

		// Assert
		ASSERT_THAT(result.x, Eq(0));
		ASSERT_THAT(result.y, Eq(0));
		ASSERT_THAT(result.width, Eq(expected_w));
		ASSERT_THAT(result.height, Eq(expected_h));
	}


	TEST(texture_test, render_calls_renderer_correctly)
	{
		// Setup
		SDL_Texture* const sdl_tex = reinterpret_cast<SDL_Texture*>(24);

		std::unique_ptr<resource_wrapper_mock<SDL_Texture>> p_resource_wrapper = 
			std::make_unique<resource_wrapper_mock<SDL_Texture>>();
		EXPECT_CALL(*(p_resource_wrapper.get()), get_resource()).Times(1).WillOnce(Return(sdl_tex));

		const auto p_dispatcher = std::make_shared<sdl_dispatcher_mock>();

		const auto texture = texture_implementation(std::move(p_resource_wrapper), p_dispatcher);

		render::rectangle const src = render::rectangle(0, 1, 2, 3);
		render::rectangle const dst = render::rectangle(4, 5, 6, 7);
		float const angle = 90.F;
		bool const flip_vertically = false;
		bool const flip_horizontally = true;

		std::shared_ptr<renderer_mock> const p_renderer = std::make_shared<renderer_mock>();
		EXPECT_CALL(
			*p_renderer.get(),
			render_copy(sdl_tex, Ref(src), Ref(dst), angle, flip_horizontally, flip_vertically)).Times(1);

		// Call | Assert
		texture.render(p_renderer, src, dst, angle, flip_horizontally, flip_vertically);
	}
}