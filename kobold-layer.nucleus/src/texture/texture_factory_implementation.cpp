#include "pch.h"
#include "texture_factory_implementation.hpp"
#include "texture_implementation.hpp"


namespace kobold_layer::nucleus::texture
{
	texture_factory_implementation::texture_factory_implementation(
		std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> const p_sdl_renderer,
		std::shared_ptr<sdl_util::sdl_dispatcher> const p_dispatcher) :
		p_renderer_(p_sdl_renderer),
		p_dispatcher_(p_dispatcher)
	{
	}

	std::unique_ptr<texture> texture_factory_implementation::construct_texture(
		std::filesystem::path const& texture_path) const
	{
		std::unique_ptr<sdl_util::resource_wrapper<struct SDL_Texture>> p_texture =
			p_dispatcher_->load_texture(
				this->p_renderer_->get_resource(),
				texture_path.string());

		return std::make_unique<texture_implementation>(std::move(p_texture),
			this->p_dispatcher_);
	}
}
