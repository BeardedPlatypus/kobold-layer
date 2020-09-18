#pragma once
#include <kobold-layer.nucleus/sdl-util/sdl_dispatcher.hpp>
#include <gmock/gmock.h>

class sdl_dispatcher_mock final : public kobold_layer::nucleus::sdl_util::sdl_dispatcher
{
public:
    MOCK_METHOD(int, init_sdl, (unsigned int), (const));
    MOCK_METHOD(int, init_img, (int), (const));
    MOCK_METHOD(void, sdl_quit, (), (const));

    using sdl_window_ptr = std::unique_ptr<kobold_layer::nucleus::sdl_util::resource_wrapper<SDL_Window>>;
    
    MOCK_METHOD(sdl_window_ptr,
        create_window,
        (std::string const&, int, int, int, int, unsigned int),
        (const));

    MOCK_METHOD(sdl_window_ptr,
        create_window,
        (const void*),
        (const));

    using sdl_renderer_ptr = std::unique_ptr<kobold_layer::nucleus::sdl_util::resource_wrapper<
        SDL_Renderer>>;
    MOCK_METHOD(sdl_renderer_ptr,
        create_renderer,
        (SDL_Window*, int, unsigned int),
        (const));

    MOCK_METHOD(void,
        render_copy_ex,
        (SDL_Renderer*, SDL_Texture*, SDL_Rect const*, const SDL_Rect*, double, SDL_Point const*,
            SDL_RendererFlip),
        (const));

    MOCK_METHOD(void, render_present, (SDL_Renderer*), (const));

    MOCK_METHOD(void, render_clear, (SDL_Renderer*), (const));

    using sdl_texture_ptr = std::unique_ptr<kobold_layer::nucleus::sdl_util::resource_wrapper<
        SDL_Texture>>;
    MOCK_METHOD(sdl_texture_ptr,
        load_texture,
        (SDL_Renderer*, std::string const&),
        (const));

    MOCK_METHOD(void,
        query_texture,
        (SDL_Texture*, unsigned int*, int*, int*, int*),
        (const));


    MOCK_METHOD(void, get_window_size, (SDL_Window*, int*, int*), (const));
};
