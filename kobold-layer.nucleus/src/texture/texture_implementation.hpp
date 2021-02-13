#pragma once
#include "kobold-layer.nucleus/texture/texture.hpp"
#include "kobold-layer.nucleus/sdl-util/resource_wrapper.hpp"
#include "kobold-layer.nucleus/sdl-util/sdl_dispatcher.hpp"

namespace kobold_layer::nucleus::texture
{
	/// <summary>
	/// <see cref="texture_implementation"/> implements the interface of a single texture loaded
	/// from a single image.
	/// </summary>
	/// <seealso cref="texture_implementation" />
	class texture_implementation final : public texture
	{
	public:
		/// <summary>
		/// Creates a new <see cref="texture_implementation"/>.
		/// </summary>
		/// <param name="p_texture">The underlying SDL2 texture.</param>
		/// <param name="p_dispatcher">
		/// The <see cref="sdl_util::sdl_dispatcher"/> used to interact with the
		/// underlying texture.
		/// </param>
		texture_implementation(
			std::unique_ptr<sdl_util::resource_wrapper<SDL_Texture>> p_texture,
			std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher);

		void render(std::shared_ptr<render::renderer> p_renderer,
			        render::rectangle<int> const& clip,
			        render::rectangle<int> const& dst,
			        float angle,
			        bool flip_horizontally,
			        bool flip_vertically) const override;

		[[nodiscard]] render::rectangle<int> get_dimensions() const override;

	private:
		std::unique_ptr<sdl_util::resource_wrapper<SDL_Texture>> p_texture_;
		std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher_;
	};
}
