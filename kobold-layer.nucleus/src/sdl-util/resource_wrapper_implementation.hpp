#pragma once
#include <SDL2/SDL.h>
#include <memory>

#include "kobold-layer.nucleus/sdl-util/resource_wrapper.hpp"
#include "sdl_destructor.hpp"

namespace kobold_layer::nucleus::sdl_util {
	/// <summary>
	/// <see cref="resource_wrapper_implementation"/> implements the wrapper
	/// for SDL resources such that they can be stored within smart pointers.
	/// </summary>
	/// <typeparam name="T">The type of the resource being wrapped. </typeparam>
	template <typename T>
	class resource_wrapper_implementation final : public resource_wrapper<T> {
	public:
		/// <summary>
		/// Creates a new <see cref="resource_wrapper_implementation"/>.
		/// </summary>
		/// <param name="p_resource">A pointer to the resource to be wrapped.</param>
		explicit resource_wrapper_implementation(T* p_resource);
		~resource_wrapper_implementation() = default;

		resource_wrapper_implementation(const resource_wrapper_implementation&) = delete;
		resource_wrapper_implementation& operator=(const resource_wrapper_implementation&) = delete;

		resource_wrapper_implementation(resource_wrapper_implementation&& resource_wrapper) noexcept = default;
		resource_wrapper_implementation& operator=(resource_wrapper_implementation&& resource_wrapper) noexcept = default;


		T* get_resource() const override;

	private:
		std::unique_ptr<T, sdl_destructor<T>> p_resource_;
	};

	template class resource_wrapper_implementation<SDL_Window>;
	template class resource_wrapper_implementation<SDL_Renderer>;
	template class resource_wrapper_implementation<SDL_Texture>;
}