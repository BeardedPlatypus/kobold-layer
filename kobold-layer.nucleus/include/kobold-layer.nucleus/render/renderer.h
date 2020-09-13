#pragma once

#include "kobold-layer.nucleus/render/rectangle.hpp"
#include <SDL2/SDL.h>

namespace kobold_layer::nucleus::render
{
    /// <summary>
    /// <see cref="renderer"/> defines the interface with which to render
    /// a <see cref="SDL_Texture"/>.
    /// </summary>
    class renderer
    {
    public:
        renderer(const renderer&) = delete;
        renderer& operator=(const renderer&) = delete;

        renderer(renderer&&) noexcept = delete;
        renderer& operator=(renderer&&) noexcept = delete;

        virtual ~renderer() = default;

        /// <summary>
        /// Copy the section specified with <paramref name="p_texture_clip"/> of the
        /// texture <paramref name="p_texture"/> to the the section of the render
        /// buffer specified with <paramref name="p_destination"/> with the given
        /// <paramref name="angle"/> and flip booleans.
        /// </summary>
        /// <param name="p_texture">A pointer to the texture to render.</param>
        /// <param name="texture_clip">The section of the texture to render.</param>
        /// <param name="destination">The section of the render buffer to render to.</param>
        /// <param name="angle">The angle.</param>
        /// <param name="flip_horizontally">if <c>true</c> flip the rendered content horizontally.</param>
        /// <param name="flip_vertically">if set to <c>true</c> flip the rendered content vertically.</param>
        virtual void render_copy(
            SDL_Texture* p_texture,
            const rectangle& texture_clip,
            const rectangle& destination,
            float angle,
            bool flip_horizontally,
            bool flip_vertically) const = 0;

        /// <summary>
        /// Present the current render buffer contents.
        /// </summary>
        virtual void render_present() const = 0;

        /// <summary>
        /// Clear the current render buffer contents.
        /// </summary>
        virtual void render_clear() const = 0;
        
    protected:		
        /// <summary>
        /// Creates a new <see cref="renderer"/>.
        /// </summary>
        renderer() = default;
    };
}
