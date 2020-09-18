#include "pch.h"
#include "sdl_dispatcher_implementation.hpp"

#include <SDL2/SDL_image.h>
#include "resource_wrapper_implementation.hpp"

namespace kobold_layer::nucleus::sdl_util
{
    template <typename T>
    std::unique_ptr<resource_wrapper<T>> construct_resource(T* p_resource)
    {
        return std::make_unique<resource_wrapper_implementation<T>>(p_resource);
    }


    int sdl_dispatcher_implementation::init_sdl(unsigned int const flags) const
    {
        return SDL_Init(flags);
    }


    int sdl_dispatcher_implementation::init_img(int const flags) const
    {
        return IMG_Init(flags);
    }


    void sdl_dispatcher_implementation::sdl_quit() const
    {
        SDL_Quit();
    }


    std::unique_ptr<resource_wrapper<SDL_Window>> sdl_dispatcher_implementation::create_window(
        std::string const& title,
        int const x, int const y,
        int const width, int const height,
        unsigned int const flags) const
    {
        SDL_Window* const p_window = SDL_CreateWindow(
            title.c_str(),
            x, y,
            width, height,
            flags);

        return construct_resource(p_window);
    }


    std::unique_ptr<resource_wrapper<SDL_Window>> sdl_dispatcher_implementation::create_window(
        void const* p_native_window) const
    {
        auto* const p_window = SDL_CreateWindowFrom(p_native_window);
        return construct_resource(p_window);
    }


    std::unique_ptr<resource_wrapper<SDL_Renderer>> sdl_dispatcher_implementation::create_renderer(
        SDL_Window* p_window,
        int const index,
        unsigned int const flags) const
    {
        auto* const p_renderer = SDL_CreateRenderer(p_window, index, flags);
        return construct_resource(p_renderer);
    }


    void sdl_dispatcher_implementation::render_copy_ex(
        SDL_Renderer* p_renderer,
        SDL_Texture* p_texture,
        SDL_Rect const* p_src_rect,
        SDL_Rect const* p_dst_rect,
        double const angle,
        SDL_Point const* p_center,
        SDL_RendererFlip const flip) const
    {
        SDL_RenderCopyEx(
            p_renderer,
            p_texture,
            p_src_rect,
            p_dst_rect,
            angle,
            p_center,
            flip);
    }


    void sdl_dispatcher_implementation::render_present(SDL_Renderer* p_renderer) const
    {
        SDL_RenderPresent(p_renderer);
    }


    void sdl_dispatcher_implementation::render_clear(SDL_Renderer* p_renderer) const
    {
        SDL_RenderClear(p_renderer);
    }


    std::unique_ptr<resource_wrapper<SDL_Texture>> sdl_dispatcher_implementation::load_texture(
        SDL_Renderer* p_renderer,
        std::string const& file_path) const
    {
        SDL_Texture* const p_texture = IMG_LoadTexture(p_renderer, file_path.c_str());
        return construct_resource(p_texture);
    }


    void sdl_dispatcher_implementation::query_texture(
        SDL_Texture* p_texture,
        unsigned int* format,
        int* access,
        int* w,
        int* h) const
    {
        SDL_QueryTexture(p_texture, format, access, w, h);
    }


    void sdl_dispatcher_implementation::get_window_size(
        SDL_Window* p_window,
        int* p_width,
        int* p_height) const
    {
        SDL_GetWindowSize(p_window, p_width, p_height);
    }
}
