#pragma once
#include <SDL2/SDL.h>

namespace kobold_layer::nucleus::sdl_util
{
    /// <summary>
    /// <see cref="resource_wrapper"/> provides a wrapper for SDL resources
    /// such that they can be stored within smart pointers.
    /// </summary>
    /// <typeparam name="T">The type of the resource being wrapped. </typeparam>
    template <typename T>
    class resource_wrapper
    {
    public:
        resource_wrapper(const resource_wrapper&) = delete;
        resource_wrapper& operator=(const resource_wrapper&) = delete;

        resource_wrapper(resource_wrapper&&) noexcept = delete;
        resource_wrapper& operator=(resource_wrapper&&) noexcept = delete;

        virtual ~resource_wrapper() = default;

        /// <summary>
        /// Gets the resource.
        /// </summary>
        /// <returns>
        /// A pointer to the wrapped resource.
        /// </returns>
        [[nodiscard]] virtual T* get_resource() const = 0;

    protected:
        resource_wrapper() = default;
    };

    template class resource_wrapper<SDL_Window>;
    template class resource_wrapper<SDL_Renderer>;
    template class resource_wrapper<SDL_Texture>;
}