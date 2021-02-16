#include "pch.h"
#include "texture_implementation.hpp"

namespace kobold_layer::nucleus::texture
{
	texture_implementation::texture_implementation(
		std::unique_ptr<sdl_util::resource_wrapper<SDL_Texture>> p_texture,
		std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher) :
		p_texture_(std::move(p_texture)),
		p_dispatcher_(std::move(p_dispatcher))
	{
	}


	void texture_implementation::render(
		std::shared_ptr<render::canvas> const p_canvas,
		render::rectangle<int> const& clip,
		render::rectangle<float> const& dst,
		float const angle,
		bool const flip_horizontally,
		bool const flip_vertically) const
	{
		p_canvas->render_copy(
			this->p_texture_->get_resource(),
			clip,
			dst,
			angle,
			flip_horizontally,
			flip_vertically);
	}


	render::rectangle<int> texture_implementation::get_dimensions() const
	{
		int width;
		int height;

		this->p_dispatcher_->query_texture(this->p_texture_->get_resource(),
			nullptr,
			nullptr,
			&width,
			&height);

		return render::rectangle(0, 0, width, height);
	}
}
