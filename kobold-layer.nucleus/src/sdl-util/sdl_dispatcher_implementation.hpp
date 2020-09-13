#pragma once
#include "kobold-layer.nucleus/sdl-util/sdl_dispatcher.hpp"

namespace kobold_layer::nucleus::sdl_util
{
    /// <summary>
    /// <see cref="sdl_dispatcher_implementation"/> acts as a facade for the different sdl
    /// functions used within this sprite_lib.
    /// </summary>
    class sdl_dispatcher_implementation final : public sdl_dispatcher
    {
    public:
        /// <summary>
        /// Creates a new <see cref="sdl_dispatcher_implementation"/>.
        /// </summary>
        sdl_dispatcher_implementation() = default;

        [[nodiscard]] int init_sdl(unsigned int flags) const override;
        [[nodiscard]] int init_img(int flags) const override;

        void sdl_quit() const override;

        [[nodiscard]] std::unique_ptr<resource_wrapper<SDL_Window>> create_window(
            const std::string& title,
            int x, int y,
            int width, int height,
            unsigned int flags) const override;

        std::unique_ptr<resource_wrapper<SDL_Window>> create_window(
            const void* p_native_window) const override;

        std::unique_ptr<resource_wrapper<SDL_Renderer>> create_renderer(
            SDL_Window* p_window,
            int index,
            unsigned int flags) const override;

        void render_copy_ex(
            SDL_Renderer* p_renderer,
            SDL_Texture* p_texture,
            const SDL_Rect* p_src_rect,
            const SDL_Rect* p_dst_rect,
            double angle,
            const SDL_Point* p_center,
            SDL_RendererFlip flip) const override;

        void render_present(SDL_Renderer* p_renderer) const override;
        void render_clear(SDL_Renderer* p_renderer) const override;

        std::unique_ptr<resource_wrapper<SDL_Texture>> load_texture(
            SDL_Renderer* p_renderer,
            const std::string& file_path) const override;

        void query_texture(SDL_Texture* p_texture,
            unsigned int* format,
            int* access,
            int* w,
            int* h) const override;

        void get_window_size(
            SDL_Window* p_window,
            int* p_width,
            int* p_height) const override;
    };
};
