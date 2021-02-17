#include "kobold-layer.nucleus.mock/render/renderer_mock.hpp"
#include "kobold-layer.nucleus.mock/render/viewport_mock.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "render/canvas_implementation.hpp"

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;
using ::testing::AllOf;
using ::testing::Field;

namespace kobold_layer::nucleus::render
{
	TEST(canvas_test, present_calls_renderer)
	{
		// Setup
		auto p_renderer = std::make_unique<renderer_mock>();
		EXPECT_CALL(*(p_renderer.get()), render_present()).Times(1);

		auto p_viewport = std::make_shared<viewport_mock>();

		canvas_implementation canvas = 
			canvas_implementation(std::move(p_renderer), std::move(p_viewport));

		// Call | Assert
		canvas.present();
	}
	
	TEST(canvas_test, clear_calls_renderer)
	{
		// Setup
		auto p_renderer = std::make_unique<renderer_mock>();
		EXPECT_CALL(*(p_renderer.get()), render_clear()).Times(1);

		auto p_viewport = std::make_shared<viewport_mock>();

		canvas_implementation const canvas = 
			canvas_implementation(std::move(p_renderer), std::move(p_viewport));

		// Call | Assert
		canvas.clear();
	}

	TEST(canvas_test, render_copy_viewport_returns_none_does_not_call_renderer)
	{
		auto p_renderer = std::make_unique<renderer_mock>();
		EXPECT_CALL(*(p_renderer.get()), render_copy(_, _, _, _, _, _)).Times(0);
		
		rectangle<int> source_rect = { 1, 2, 3, 4 };
		rectangle<float> world_rect = { 1.0F, 2.0F, 3.0F, 4.0F };

		auto p_viewport = std::make_shared<viewport_mock>();
		EXPECT_CALL(*(p_viewport.get()), 
			clip_to_viewport(
                AllOf(
                    Field(&rectangle<int>::x,      source_rect.x),
                    Field(&rectangle<int>::y,      source_rect.y),
                    Field(&rectangle<int>::width,  source_rect.width),
                    Field(&rectangle<int>::height, source_rect.height)),
                AllOf(
                    Field(&rectangle<float>::x,      world_rect.x),
                    Field(&rectangle<float>::y,      world_rect.y),
                    Field(&rectangle<float>::width,  world_rect.width),
                    Field(&rectangle<float>::height, world_rect.height))))
		    .Times(1)
			.WillOnce(Return(std::optional<viewport::clipped_rects>()));
		
		canvas_implementation canvas = 
			canvas_implementation(std::move(p_renderer), std::move(p_viewport));

		auto* const p_sdl_texture = reinterpret_cast<SDL_Texture*>(48);

		// Call | Assert
		canvas.render_copy(p_sdl_texture, 
			               source_rect, 
			               world_rect, 
			               1.0F, 
			               true, 
			               true);
	}
	
	TEST(canvas_test, render_copy_viewport_returns_clipped_rects_calls_renderer)
	{
		auto* const p_sdl_texture = reinterpret_cast<SDL_Texture*>(48);
		viewport::clipped_rects clipped_rects = {
			{ 10, 20, 30, 40 },
			{ 11, 21, 31, 41 }
		};

		const float angle = 21.3F;
		const bool flip_horizontal = true;
		const bool flip_vertical = true;
		
		auto p_renderer = std::make_unique<renderer_mock>();
		EXPECT_CALL(*(p_renderer.get()), 
			render_copy(p_sdl_texture,
                        AllOf(
                            Field(&rectangle<int>::x,      clipped_rects.source.x),
                            Field(&rectangle<int>::y,      clipped_rects.source.y),
                            Field(&rectangle<int>::width,  clipped_rects.source.width),
                            Field(&rectangle<int>::height, clipped_rects.source.height)),
                        AllOf(
                            Field(&rectangle<int>::x,      clipped_rects.target.x),
                            Field(&rectangle<int>::y,      clipped_rects.target.y),
                            Field(&rectangle<int>::width,  clipped_rects.target.width),
                            Field(&rectangle<int>::height, clipped_rects.target.height)),
			            angle, 
			            flip_horizontal, 
			            flip_vertical))
		    .Times(1);
		
		rectangle<int> source_rect = { 1, 2, 3, 4 };
		rectangle<float> world_rect = { 1.0F, 2.0F, 3.0F, 4.0F };

		auto p_viewport = std::make_shared<viewport_mock>();
		EXPECT_CALL(*(p_viewport.get()), 
			clip_to_viewport(
                AllOf(
                    Field(&rectangle<int>::x, source_rect.x),
                    Field(&rectangle<int>::y, source_rect.y),
                    Field(&rectangle<int>::width, source_rect.width),
                    Field(&rectangle<int>::height, source_rect.height)),
                AllOf(
                    Field(&rectangle<float>::x, world_rect.x),
                    Field(&rectangle<float>::y, world_rect.y),
                    Field(&rectangle<float>::width, world_rect.width),
                    Field(&rectangle<float>::height, world_rect.height))))
		    .Times(1)
			.WillOnce(Return(std::make_optional(clipped_rects)));
		
		canvas_implementation canvas = 
			canvas_implementation(std::move(p_renderer), std::move(p_viewport));


		// Call | Assert
		canvas.render_copy(p_sdl_texture, 
			               source_rect, 
			               world_rect, 
			               angle, 
			               flip_horizontal, 
			               flip_vertical);
	}
}
