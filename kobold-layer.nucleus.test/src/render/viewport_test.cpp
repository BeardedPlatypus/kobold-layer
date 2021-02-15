#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "render/viewport_implementation.hpp"

#include "kobold-layer.nucleus.mock/render/world_mock.hpp"

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Eq;

namespace kobold_layer::nucleus::render
{
	TEST(viewport_test, constructor_expected_results)
	{
		// Setup
		std::shared_ptr<world> p_world = std::make_shared<world_mock>();

		unsigned int const render_width = 5;
		unsigned int const render_height = 6;

		rectangle<float> const viewport_coordinates =
			rectangle<float>(7.F, 8.F, 9.F, 10.F);

		// Call
		auto const viewport = viewport_implementation(
			p_world,
			render_width,
			render_height,
			viewport_coordinates);

		// Assert
		
		ASSERT_THAT(
			viewport.get_viewport_coordinates(),
			AllOf(Field(&rectangle<float>::x,      viewport_coordinates.x),
				  Field(&rectangle<float>::y,      viewport_coordinates.y),
				  Field(&rectangle<float>::width,  viewport_coordinates.width),
				  Field(&rectangle<float>::height, viewport_coordinates.height)));

		ASSERT_THAT(viewport.get_render_width(), Eq(render_width));
		ASSERT_THAT(viewport.get_render_height(), Eq(render_height));
	}

	TEST(viewport_test, set_render_width_expected_results)
	{
		// Setup
		std::shared_ptr<world> p_world = std::make_shared<world_mock>();

		auto viewport = viewport_implementation(
			p_world,
			1,
			2,
			rectangle<float>(7.F, 8.F, 9.F, 10.F));

		unsigned int const new_render_width = 21;
		
		// Call
		viewport.set_render_width(new_render_width);

		// Assert
		ASSERT_THAT(viewport.get_render_width(), Eq(new_render_width));
	}

	TEST(viewport_test, set_render_height_expected_results)
	{
		// Setup
		std::shared_ptr<world> p_world = std::make_shared<world_mock>();

		auto viewport = viewport_implementation(
			p_world,
			1,
			2,
			rectangle<float>(7.F, 8.F, 9.F, 10.F));

		unsigned int const new_render_height = 21;
		
		// Call
		viewport.set_render_height(new_render_height);

		// Assert
		ASSERT_THAT(viewport.get_render_height(), Eq(new_render_height));
	}

	TEST(viewport_test, set_viewport_coordinates_expected_results)
	{
		// Setup
		std::shared_ptr<world> p_world = std::make_shared<world_mock>();


		auto viewport = viewport_implementation(
			p_world,
			1,
			2,
			rectangle<float>(7.F, 8.F, 9.F, 10.F));

		rectangle<float> const viewport_coordinates =
			rectangle<float>(17.F, 18.F, 19.F, 110.F);
		
		// Call
		viewport.set_viewport_coordinates(viewport_coordinates);
		
		// Assert
		ASSERT_THAT(
			viewport.get_viewport_coordinates(),
			AllOf(Field(&rectangle<float>::x,      viewport_coordinates.x),
				  Field(&rectangle<float>::y,      viewport_coordinates.y),
				  Field(&rectangle<float>::width,  viewport_coordinates.width),
				  Field(&rectangle<float>::height, viewport_coordinates.height)));

	}

	class viewport_clip_to_viewport_data final
	{
	public:
		viewport_clip_to_viewport_data(unsigned int const render_width,
                                       unsigned int const render_height,
                                       rectangle<float> const world_boundaries,
                                       rectangle<float> const viewport_coordinates,
                                       rectangle<int> const source,
                                       rectangle<float> const world_destination,
			                           std::optional<viewport::clipped_rects> result) :
		render_width(render_width),
		render_height(render_height),
		world_boundaries(world_boundaries),
		viewport_coordinates(viewport_coordinates),
		source(source),
		world_destination(world_destination),
		result(result) {}
		
		unsigned int const render_width;
		unsigned int const render_height;
		
		rectangle<float> world_boundaries;
		rectangle<float> viewport_coordinates;

		rectangle<int> source;
		rectangle<float> world_destination;

		std::optional<viewport::clipped_rects> result;
	};

	class viewport_clip_test : public ::testing::TestWithParam<viewport_clip_to_viewport_data>
	{
	public:
		[[nodiscard]] static std::vector<viewport_clip_to_viewport_data> get_data()
		{
			return {
				get_inside_viewport(),
				get_outside_viewport_left(),
				get_outside_viewport_right(),
				get_outside_viewport_down(),
				get_outside_viewport_up(),
				get_clipped_viewport_left(),
				get_clipped_viewport_right(),
				get_clipped_viewport_down(),
				get_clipped_viewport_up(),
			};
		}

	private:
		[[nodiscard]] static viewport_clip_to_viewport_data get_inside_viewport()
		{
			rectangle<int> source = rectangle<int>(30, 40, 10, 20);
			
			viewport::clipped_rects result = { source, rectangle<int>(25, 25, 10, 20) };
			
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
				source,
				rectangle<float>(5.F, 5.F, 1.F, 2.F),
				std::make_optional(result));
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_outside_viewport_left()
		{
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
				rectangle<int>(30, 40, 10, 20),
				rectangle<float>(0.F, 5.F, 1.F, 2.F),
				std::optional<viewport::clipped_rects>());
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_outside_viewport_right()
		{
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
				rectangle<int>(30, 40, 10, 20),
				rectangle<float>(10.5F, 5.F, 1.F, 2.F),
				std::optional<viewport::clipped_rects>());
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_outside_viewport_up()
		{
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
				rectangle<int>(30, 40, 10, 20),
				rectangle<float>(5.0F, 0.F, 2.F, 1.F),
				std::optional<viewport::clipped_rects>());
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_outside_viewport_down()
		{
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
				rectangle<int>(30, 40, 10, 20),
				rectangle<float>(5.0F, 10.5F, 2.F, 1.F),
				std::optional<viewport::clipped_rects>());
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_clipped_viewport_left()
		{
			viewport::clipped_rects result = {
				rectangle<int>(35, 40, 5, 20),
				rectangle<int>(0, 50, 5, 20)
			};
			
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
			    rectangle<int>(30, 40, 10, 20),
				rectangle<float>(2.F, 5.F, 1.F, 2.F),
				std::make_optional(result));
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_clipped_viewport_right()
		{
			viewport::clipped_rects result = {
				rectangle<int>(30, 40, 5, 20),
				rectangle<int>(95, 50, 5, 20)
			};
			
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
			    rectangle<int>(30, 40, 10, 20),
				rectangle<float>(12.0F, 5.F, 1.F, 2.F),
				std::make_optional(result));
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_clipped_viewport_up()
		{
			viewport::clipped_rects result = {
				rectangle<int>(30, 50, 10, 10),
				rectangle<int>(50, 0, 10, 10)
			};
			
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
			    rectangle<int>(30, 40, 10, 20),
				rectangle<float>(5.F, 1.5F, 1.F, 2.F),
				std::make_optional(result));
		}
		
		[[nodiscard]] static viewport_clip_to_viewport_data get_clipped_viewport_down()
		{
			viewport::clipped_rects result = {
				rectangle<int>(30, 40, 10, 10),
				rectangle<int>(50, 90, 10, 10)
			};
			
			return viewport_clip_to_viewport_data(
				100, 
				100,
				rectangle<float>(0.F, 0.F, 15.F, 15.F),
				rectangle<float>(2.5F, 2.5F, 10.F, 10.F),
			    rectangle<int>(30, 40, 10, 20),
				rectangle<float>(5.F, 11.5F, 1.F, 2.F),
				std::make_optional(result));
		}
	};

	// clipped viewport left
	// clipped viewport right
	// clipped viewport up
	// clipped viewport down
	TEST_P(viewport_clip_test, clip_to_viewport_expected_results)
	{
		// Setup
		auto p_world = std::make_shared<world_mock>();
		ON_CALL(*(p_world.get()), get_boundaries())
		    .WillByDefault(Return(GetParam().world_boundaries));

		auto const viewport = viewport_implementation(
			p_world,
			GetParam().render_width,
			GetParam().render_height,
			GetParam().viewport_coordinates);

		// Call
		std::optional<viewport::clipped_rects> result =
			viewport.clip_to_viewport(
				GetParam().source, 
				GetParam().world_destination);

		// Result
		ASSERT_THAT(result.has_value(), Eq(GetParam().result.has_value()));

		if (GetParam().result.has_value())
		{
            ASSERT_THAT(
                result->source,
                AllOf(Field(&rectangle<int>::x,      GetParam().result->source.x),
                      Field(&rectangle<int>::y,      GetParam().result->source.y),
                      Field(&rectangle<int>::width,  GetParam().result->source.width),
                      Field(&rectangle<int>::height, GetParam().result->source.height)));
			
            ASSERT_THAT(
                result->target,
                AllOf(Field(&rectangle<int>::x,      GetParam().result->target.x),
                      Field(&rectangle<int>::y,      GetParam().result->target.y),
                      Field(&rectangle<int>::width,  GetParam().result->target.width),
                      Field(&rectangle<int>::height, GetParam().result->target.height)));
		}
	}

	INSTANTIATE_TEST_SUITE_P(viewport_test,
		                     viewport_clip_test,
		                     ::testing::ValuesIn(viewport_clip_test::get_data()));
}
