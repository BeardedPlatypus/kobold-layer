#include "pch.h"
#include "canvas_implementation.hpp"

namespace kobold_layer::nucleus::render
{
	canvas_implementation::canvas_implementation(std::unique_ptr<renderer> p_renderer, 
		                                         std::shared_ptr<viewport const> p_viewport) :
	    p_renderer_(std::move(p_renderer)),
	    p_viewport_(std::move(p_viewport)) { }

	void canvas_implementation::render_copy(SDL_Texture* p_texture, 
		                                    rectangle<int> const& texture_clip, 
		                                    rectangle<float> const& destination, 
		                                    float const angle, 
		                                    bool const flip_horizontally,
		                                    bool const flip_vertically) const
	{
		if (auto clipped_rects = this->p_viewport_->clip_to_viewport(texture_clip, destination))
		{
			this->p_renderer_->render_copy(
				p_texture,
				clipped_rects->source,
				clipped_rects->target,
				angle, 
				flip_horizontally, 
				flip_vertically);
		}
	}

	void canvas_implementation::present() const
	{
		this->p_renderer_->render_present();
	}

	void canvas_implementation::clear() const
	{
		this->p_renderer_->render_clear();
	}
}

	
