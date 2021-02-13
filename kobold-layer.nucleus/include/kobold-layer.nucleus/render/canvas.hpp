#pragma once

#include <SDL2/SDL.h>

#include "kobold-layer.nucleus/render/rectangle.hpp"

namespace kobold_layer::nucleus::render
{
    /// <summary>
    /// <see cref="canvas"/> defines the interface with which to render
    /// a <see cref="SDL_Texture"/> within world space.
    /// </summary>
    class canvas
    {
    public:
        canvas(const canvas&) = delete;
        canvas& operator=(const canvas&) = delete;

        canvas(canvas&&) noexcept = delete;
        canvas& operator=(canvas&&) noexcept = delete;

        virtual ~canvas() = default;

        /// <summary>
        /// Copy the section specified with <paramref name="p_texture_clip"/> of the
        /// texture <paramref name="p_texture"/> to the the section of the world
        /// specified with <paramref name="p_destination"/> with the given
        /// <paramref name="angle"/> and flip booleans.
        /// </summary>
        /// <param name="p_texture">A pointer to the texture to render.</param>
        /// <param name="texture_clip">The section of the texture to render.</param>
        /// <param name="destination">The section of the world to render to.</param>
        /// <param name="angle">The angle.</param>
        /// <param name="flip_horizontally">if <c>true</c> flip the rendered content horizontally.</param>
        /// <param name="flip_vertically">if set to <c>true</c> flip the rendered content vertically.</param>
        virtual void render_copy(
            SDL_Texture* p_texture,
            rectangle<int> const& texture_clip,
            rectangle<float> const& destination,
            float angle,
            bool flip_horizontally,
            bool flip_vertically) const = 0;

        /// <summary>
        /// Present this <see cref="canvas"/>.
        /// </summary>
        virtual void present() const = 0;

        /// <summary>
        /// Clear this <see cref="canvas"/>.
        /// </summary>
        virtual void clear() const = 0;
        
    protected:		
        /// <summary>
        /// Creates a new <see cref="canvas"/>.
        /// </summary>
        canvas() = default;
    };
}
