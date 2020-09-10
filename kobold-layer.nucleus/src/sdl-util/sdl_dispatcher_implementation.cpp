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


    int sdl_dispatcher_implementation::init_sdl(const unsigned int flags) const
    {
        return SDL_Init(flags);
    }


    int sdl_dispatcher_implementation::init_img(const int flags) const
    {
        return IMG_Init(flags);
    }


    void sdl_dispatcher_implementation::sdl_quit() const
    {
        SDL_Quit();
    }


    std::unique_ptr<resource_wrapper<SDL_Window>> sdl_dispatcher_implementation::create_window(
        const std::string& title,
        const int x, const int y,
        const int width, const int height,
        const unsigned int flags) const
    {
        const auto p_window = SDL_CreateWindow(
            title.c_str(),
            x, y,
            width, height,
            flags);

        return construct_resource(p_window);
    }


    std::unique_ptr<resource_wrapper<SDL_Window>> sdl_dispatcher_implementation::create_window(
        const void* p_native_window) const
    {
	    auto* const p_window = SDL_CreateWindowFrom(p_native_window);
        return construct_resource(p_window);
    }


    std::unique_ptr<resource_wrapper<SDL_Renderer>> sdl_dispatcher_implementation::create_renderer(
        SDL_Window* p_window,
        const int index,
        const unsigned int flags) const
    {
	    auto* const p_renderer = SDL_CreateRenderer(p_window, index, flags);
        return construct_resource(p_renderer);
    }


    void sdl_dispatcher_implementation::render_copy_ex(
        SDL_Renderer* p_renderer,
        SDL_Texture* p_texture,
        const SDL_Rect* p_src_rect,
        const SDL_Rect* p_dst_rect,
        const double angle,
        const SDL_Point* p_center,
        const SDL_RendererFlip flip) const
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
        const std::string& file_path) const
    {
        const auto p_texture = IMG_LoadTexture(p_renderer, file_path.c_str());
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
