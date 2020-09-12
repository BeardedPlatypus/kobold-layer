#pragma once
#include "kobold-layer.nucleus/render/renderer.h"

#include <SDL2/SDL.h>

#include "kobold-layer.nucleus/sdl-util/resource_wrapper.hpp"
#include "kobold-layer.nucleus/sdl-util/sdl_dispatcher.hpp"

#include <memory>

namespace kobold_layer::nucleus::render
{
    /// <summary>
    /// <see cref="renderer"/> implements the interface with which to render
    /// a <see cref="SDL_Texture"/>.
    /// </summary>
    class renderer_implementation final : public renderer
    {
    public:
        /// <summary>
        /// Creates a new <see cref="renderer_implementation"/>.
        /// </summary>
        /// <param name="p_sdl_renderer">A pointer to the underlying <see cref="SDL_Renderer"/>.</param>
        /// <param name="p_sdl_dispatcher">A pointer to the underlying <see cref="sdl_util::sdl_dispatcher"/>.</param>
        renderer_implementation(std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> p_sdl_renderer,
                                std::shared_ptr<sdl_util::sdl_dispatcher> p_sdl_dispatcher);

        void render_copy(
            SDL_Texture* p_texture,
            const rectangle& p_texture_clip,
            const rectangle& p_destination,
            float angle,
            bool flip_horizontally,
            bool flip_vertically) const override;

        void render_present() const override;
        void render_clear() const override;

    private:
        std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> p_sdl_renderer_;
        std::shared_ptr<sdl_util::sdl_dispatcher> p_sdl_dispatcher_;
    };
}
