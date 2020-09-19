#pragma once
#include <filesystem>

#include "kobold-layer.nucleus/sdl-util/resource_wrapper.hpp"
#include "kobold-layer.nucleus/sdl-util/sdl_dispatcher.hpp"
#include "kobold-layer.nucleus/texture/texture.hpp"

#include "texture_factory.hpp"


namespace kobold_layer::nucleus::texture
{
	/// <summary>
	/// <see cref="texture_factory_implementation"/> implements the interface to
	/// construct <see cref="texture"/> objects.
	/// </summary>
	class texture_factory_implementation final : public texture_factory
	{
	public:
		/// <summary>
		/// Creates a new <see cref="texture_factory_implementation"/>.
		/// </summary>
		/// <param name="p_sdl_renderer">A pointer to the <see cref="SDL_Renderer"/>.</param>
		/// <param name="p_dispatcher">The <see cref="sdl_dispatcher"/>.</param>
		texture_factory_implementation(
			std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> p_sdl_renderer,
			std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher);

		[[nodiscard]] std::unique_ptr<texture> construct_texture(std::filesystem::path const& texture_path) const override;

	private:
		std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> p_renderer_;
		std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher_;
	};
}
