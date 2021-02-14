#include "pch.h"
#include "viewport_implementation.hpp"

namespace kobold_layer::nucleus::render
{
	viewport_implementation::viewport_implementation(std::shared_ptr<world> p_world,
		                                             unsigned int const render_width,
		                                             unsigned int const render_height,
	                                                 rectangle<float> const& viewport_coordinates) :
	    p_world_(std::move(p_world)),
	    p_viewport_coordinates_(std::make_unique<rectangle<float>>(viewport_coordinates.x, 
			                                                       viewport_coordinates.y,
			                                                       viewport_coordinates.width,
			                                                       viewport_coordinates.height)),
	    render_width_(render_width),
	    render_height_(render_height) { }

	unsigned int viewport_implementation::get_render_width() const
	{
		return this->render_width_;
	}

	void viewport_implementation::set_render_width(unsigned int const new_render_width)
	{
		this->render_width_ = new_render_width;
	}

	unsigned int viewport_implementation::get_render_height() const
	{
		return this->render_height_;
	}

	void viewport_implementation::set_render_height(unsigned int const new_render_height)
	{
		this->render_height_ = new_render_height;
	}

	
	rectangle<float> viewport_implementation::get_viewport_coordinates() const
	{
		return *this->p_viewport_coordinates_;
	}
	void viewport_implementation::set_viewport_coordinates(rectangle<float> const& new_coordinates)
	{
		this->p_viewport_coordinates_ = 
			std::make_unique<rectangle<float>>(
				new_coordinates.x,
				new_coordinates.y,
				new_coordinates.width,
				new_coordinates.height);
	}

	std::optional<viewport::clipped_rects> viewport_implementation::clip_to_viewport(
			rectangle<int> const& tex_source,
			rectangle<float> const& world_destination) const
	{
		// TODO: implement this behaviour correctly.
		return {};
	}
}
