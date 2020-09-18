#pragma once
#include <memory>
#include <string>

#include "resource_wrapper.hpp"

namespace kobold_layer::nucleus::sdl_util
{
    /// <summary>
    /// <see cref="sdl_dispatcher_implementation"/> acts as a facade for the different sdl
    /// functions used within this sprite_lib.
    /// </summary>
    class sdl_dispatcher
    {
    public:
        /// <summary>
        /// Constructs a new <see cref="sdl_dispatcher"/>.
        /// </summary>
        /// <returns>
        /// A <see cref="std::unique_ptr{sdl_dispatcher}"/> containing the
        /// newly created <see cref="sdl_dispatcher"/>.
        /// </returns>
        static std::unique_ptr<sdl_dispatcher> construct();

        sdl_dispatcher(const sdl_dispatcher&) = delete;
        sdl_dispatcher& operator=(const sdl_dispatcher&) = delete;

        sdl_dispatcher(sdl_dispatcher&&) noexcept = delete;
        sdl_dispatcher& operator=(sdl_dispatcher&&) noexcept = delete;

        virtual ~sdl_dispatcher() = default;

        /// <summary>
        /// Initializes the SDL2 context.
        /// </summary>
        /// <param name="flags">The flags to initialise the context with.</param>
        /// <returns>
        /// The return code of the initialisation call.
        /// </returns>
        [[nodiscard]] virtual int init_sdl(unsigned int flags) const = 0;

        /// <summary>
        /// Initializes the SDL2 IMG context.
        /// </summary>
        /// <param name="flags">The flags to initialise the context with.</param>
        /// <returns>
        /// The return code of the initialisation call.
        /// </returns>
        [[nodiscard]] virtual int init_img(int flags) const = 0;

        /// <summary>
        /// Destroys the SDL2 context.
        /// </summary>
        virtual void sdl_quit() const = 0;

        /// <summary>
        /// Creates a new SDL2 window from the given parameters.
        /// </summary>
        /// <param name="title">The title.</param>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        /// <param name="width">The width.</param>
        /// <param name="height">The height.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>
        /// A <see cref="resource_wrapper{SDL_Window}"/> containing the newly created
        /// SDL2 window.
        /// </returns>
        [[nodiscard]] virtual std::unique_ptr<resource_wrapper<SDL_Window>> create_window(
            std::string const& title,
            int x, int y,
            int width, int height,
            unsigned int flags) const = 0;

        /// <summary>
        /// Creates a new SDL2 window from the given native window pointer.
        /// </summary>
        /// <param name="p_native_window">A pointer to the native window to create a window from.</param>
        /// <returns>
        /// A <see cref="resource_wrapper{SDL_Window}"/> containing the newly created
        /// SDL2 window.
        /// </returns>
        virtual std::unique_ptr<resource_wrapper<SDL_Window>> create_window(void const* p_native_window) const = 0;

        /// <summary>
        /// Creates a new SDL2 renderer.
        /// </summary>
        /// <param name="p_window">A pointer to the SDL2 window the renderer should render in.</param>
        /// <param name="index">The index.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>
        /// A <see cref="resource_wrapper{SDL_Renderer}"/> containing the newly created
        /// SDL2 renderer.
        /// </returns>
        virtual std::unique_ptr<resource_wrapper<SDL_Renderer>> create_renderer(
            SDL_Window* p_window,
            int index,
            unsigned int flags) const = 0;

        /// <summary>
        /// Renders the <paramref name="p_src_rect"/> in <paramref name="p_texture"/>
        /// with the provided <paramref name="p_renderer"/> to the specified
        /// <paramref name="p_dist_rect"/>.
        /// </summary>
        /// <param name="p_renderer">A pointer to the renderer.</param>
        /// <param name="p_texture">A pointer to the texture.</param>
        /// <param name="p_src_rect">A pointer to the source rectangle.</param>
        /// <param name="p_dst_rect">A pointer to the destination rectangle.</param>
        /// <param name="angle">The angle.</param>
        /// <param name="p_center">
        /// A pointer to the specified center around which the render should be rotated.
        /// </param>
        /// <param name="flip">
        /// Flag indicating whether the rendering should be flipped.
        /// </param>
        virtual void render_copy_ex(
            SDL_Renderer* p_renderer,
            SDL_Texture* p_texture,
            SDL_Rect const* p_src_rect,
            SDL_Rect const* p_dst_rect,
            double angle,
            SDL_Point const* p_center,
            SDL_RendererFlip flip) const = 0;

        /// <summary>
        /// Presents the current rendered image to the view.
        /// </summary>
        /// <param name="p_renderer">
        /// The renderer of which the rendered area will be presented.
        /// </param>
        virtual void render_present(SDL_Renderer* p_renderer) const = 0;

        /// <summary>
        /// Clears the current rendered image from the specified <paramref name="p_renderer"/>
        /// </summary>
        /// <param name="p_renderer">
        /// The renderer of which the rendered area will be cleared.
        /// </param>
        virtual void render_clear(SDL_Renderer* p_renderer) const = 0;

        /// <summary>
        /// Loads the specified texture with the provided <paramref name="p_renderer"/>
        /// and create a new SDL2 texture.
        /// </summary>
        /// <param name="p_renderer">
        /// The renderer which will load the the specified texture.
        /// </param>
        /// <param name="file_path">The path to the texture to be loaded.</param>
        /// <returns>
        /// A <see cref="resource_wrapper{SDL_Texture}"/> containing the newly created
        /// SDL2 texture.
        /// </returns>
        virtual std::unique_ptr<resource_wrapper<SDL_Texture>> load_texture(
            SDL_Renderer* p_renderer,
            std::string const& file_path) const = 0;

        /// <summary>
        /// Queries the texture data of the provided <paramref name="p_texture"/>.
        /// </summary>
        /// <param name="p_texture">A pointer to the texture to query.</param>
        /// <param name="format">The format of the texture.</param>
        /// <param name="access">The access type of the texture.</param>
        /// <param name="width">The width of the texture.</param>
        /// <param name="height">The height of the texture.</param>
        virtual void query_texture(
            SDL_Texture* p_texture,
            unsigned int* format,
            int* access,
            int* width,
            int* height) const = 0;

        virtual void get_window_size(
            SDL_Window* p_window,
            int* p_width,
            int* p_height) const = 0;

    protected:
        /// <summary>
        /// Creates a new <see cref="sdl_dispatcher"/>.
        /// </summary>
        sdl_dispatcher() = default;
    };
}
