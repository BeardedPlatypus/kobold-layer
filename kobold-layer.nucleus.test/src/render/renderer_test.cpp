#include "kobold-layer.nucleus.mock/sdl-util/resource_wrapper_mock.hpp"
#include "kobold-layer.nucleus.mock/sdl-util/sdl_dispatcher_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "render/renderer_implementation.hpp"

using ::testing::Return;
using ::testing::AllOf;
using ::testing::Pointee;
using ::testing::Field;

namespace kobold_layer::nucleus::render
{
    class render_copy_data final
    {
    public:
        render_copy_data(
            const bool flip_horizontally,
            const bool flip_vertically,
            const SDL_RendererFlip expected_flip) :
            flip_horizontally(flip_horizontally),
            flip_vertically(flip_vertically),
            expected_flip(expected_flip)
        {
        }

        const bool flip_horizontally;
        const bool flip_vertically;
        const SDL_RendererFlip expected_flip;
    };

    class render_copy_test : public ::testing::TestWithParam<render_copy_data>
    {
    public:
        static std::vector<render_copy_data> get_data()
        {
            return {
                render_copy_data(false, false, SDL_FLIP_NONE),
                render_copy_data(true, false, SDL_FLIP_HORIZONTAL),
                render_copy_data(false, true, SDL_FLIP_VERTICAL),
                render_copy_data(true, true, static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL)),
            };
        }
    };

    TEST_P(render_copy_test, render_copy_expected_results)
    {
        // Setup
        const auto p_sdl_renderer = reinterpret_cast<SDL_Renderer*>(24);

        auto p_resource = std::make_shared<resource_wrapper_mock<SDL_Renderer>>();
        EXPECT_CALL(*(p_resource.get()), get_resource())
            .Times(1)
            .WillOnce(Return(p_sdl_renderer));

        const auto p_sdl_texture = reinterpret_cast<SDL_Texture*>(48);
        const rectangle src = rectangle(1, 2, 3, 4);
        const rectangle target = rectangle(5, 6, 7, 8);
        const float angle = 96.F;

        const auto p_dispatcher = std::make_shared<sdl_dispatcher_mock>();


        EXPECT_CALL(*(p_dispatcher.get()), render_copy_ex(p_sdl_renderer,
            p_sdl_texture,
            Pointee(AllOf(
                Field(&SDL_Rect::x, src.x),
                Field(&SDL_Rect::y, src.y),
                Field(&SDL_Rect::w, src.width),
                Field(&SDL_Rect::h, src.height))),
            Pointee(AllOf(
                Field(&SDL_Rect::x, target.x),
                Field(&SDL_Rect::y, target.y),
                Field(&SDL_Rect::w, target.width),
                Field(&SDL_Rect::h, target.height))),
            angle,
            nullptr,
            GetParam().expected_flip))
            .Times(1);

        const auto renderer = renderer_implementation(std::move(p_resource),
            p_dispatcher);

        // Call | Assert
        renderer.render_copy(p_sdl_texture,
            src, target, angle,
            GetParam().flip_horizontally, GetParam().flip_vertically);
    }

    INSTANTIATE_TEST_SUITE_P(renderer_test,
        render_copy_test,
        ::testing::ValuesIn(render_copy_test::get_data()));


    TEST(renderer_test, render_clear_expected_results)
    {
        // Setup
        const auto p_sdl_renderer = reinterpret_cast<SDL_Renderer*>(24);

        auto p_resource = std::make_shared<resource_wrapper_mock<SDL_Renderer>>();
        EXPECT_CALL(*(p_resource.get()), get_resource())
            .Times(1)
            .WillOnce(Return(p_sdl_renderer));

        const auto p_dispatcher = std::make_shared<sdl_dispatcher_mock>();
        EXPECT_CALL(*(p_dispatcher.get()), render_clear(p_sdl_renderer))
            .Times(1);

        const auto renderer = renderer_implementation(std::move(p_resource),
            p_dispatcher);

        // Call | Assert
        renderer.render_clear();
    }


    TEST(renderer_test, render_present_expected_results)
    {
        // Setup
        auto p_sdl_renderer = reinterpret_cast<SDL_Renderer*>(24);

        auto p_resource = std::make_shared<resource_wrapper_mock<SDL_Renderer>>();
        EXPECT_CALL(*(p_resource.get()), get_resource())
            .Times(1)
            .WillOnce(Return(p_sdl_renderer));

        const auto p_dispatcher = std::make_shared<sdl_dispatcher_mock>();
        EXPECT_CALL(*(p_dispatcher.get()), render_present(p_sdl_renderer))
            .Times(1);

        const auto renderer = renderer_implementation(std::move(p_resource),
                                                      p_dispatcher);

        // Call | Assert
        renderer.render_present();
    }
}
