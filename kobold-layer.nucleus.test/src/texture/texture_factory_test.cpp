#include "kobold-layer.nucleus.mock/sdl-util/resource_wrapper_mock.hpp"
#include "kobold-layer.nucleus.mock/sdl-util/sdl_dispatcher_mock.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "texture/texture_factory_implementation.hpp"

using ::testing::Return;
using ::testing::ByMove;

namespace kobold_layer::nucleus::texture {
	TEST(texture_factory_test, construct_texture_expected_result)
	{
		// Setup
		SDL_Renderer* const sdl_renderer = reinterpret_cast<SDL_Renderer*>(24);

		auto p_resource_renderer = std::make_unique<resource_wrapper_mock<SDL_Renderer>>();
		EXPECT_CALL(*(p_resource_renderer.get()), get_resource())
			.Times(1)
			.WillOnce(Return(sdl_renderer));

		auto p_resource_texture = std::make_unique<resource_wrapper_mock<SDL_Texture>>();

		const auto texture_path = std::filesystem::path("path/to/texture.png");

		const auto p_dispatcher = std::make_shared<sdl_dispatcher_mock>();
		EXPECT_CALL(*(p_dispatcher.get()), load_texture(sdl_renderer, texture_path.string()))
			.Times(1)
			.WillOnce(Return(ByMove(std::move(p_resource_texture))));

		const auto factory = texture_factory_implementation(std::move(p_resource_renderer),
			p_dispatcher);

		// Call | Assert
		auto result = factory.construct_texture(texture_path);
	}
}
