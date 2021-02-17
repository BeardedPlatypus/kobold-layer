#include "pch.h"
#include "viewport_implementation.hpp"

#include <algorithm>

namespace kobold_layer::nucleus::render
{
	viewport_implementation::viewport_implementation(std::shared_ptr<world const> p_world,
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
		if (!this->has_intersection_with(world_destination)) {
			return {};
		}

		auto const [ clipped_destination, clipped_source ] =
			this->clip_viewport_coordinates(world_destination, tex_source);

		clipped_rects result = {
			clipped_source,
			this->translate_to_render_coordinates(clipped_destination),
		};
		
		return result;
	}

	bool viewport_implementation::has_intersection_with(rectangle<float> const& rect) const
	{
		return !(rect.x > this->p_viewport_coordinates_->x + this->p_viewport_coordinates_->width  ||
			     rect.x + rect.width < this->p_viewport_coordinates_->x                            ||
			     rect.y > this->p_viewport_coordinates_->y + this->p_viewport_coordinates_->height ||
			     rect.y + rect.height < this->p_viewport_coordinates_->y);
	}

	bool viewport_implementation::has_fully_enclosed(rectangle<float> const& rect) const
	{
		return rect.x + rect.width <= this->p_viewport_coordinates_->x + this->p_viewport_coordinates_->width   &&
			   rect.x >= this->p_viewport_coordinates_->x                                                       &&
			   rect.y + rect.height <= this->p_viewport_coordinates_->y + this->p_viewport_coordinates_->height &&
			   rect.y >= this->p_viewport_coordinates_->y;
	}

	inline int to_int(float const in)
	{
		return static_cast<int>(truncf(in));
	}

	std::tuple<float, float, int, int> clip_dimensions(float const pos, float const len, 
		                                               float const vp_pos, float const vp_len, 
		                                               int const src_pos, int const src_len)
	{
		float const pos_min = std::max(pos, vp_pos);
		float const pos_max = std::min(pos + len, vp_pos + vp_len);
		float const len_new = pos_max - pos_min;

		int const new_src_pos = to_int((pos_min - pos) / len * static_cast<float>(src_len) + static_cast<float>(src_pos));
		int const new_src_len = to_int(static_cast<float>(src_len) - (len - len_new) / len * static_cast<float>(src_len));

		return { pos_min, len_new, new_src_pos, new_src_len };
	}

	std::tuple<rectangle<float>, rectangle<int>> viewport_implementation::clip_viewport_coordinates(rectangle<float> const& world_dest, 
		                                                                                           rectangle<int> const& source) const
	{
		if (this->has_fully_enclosed(world_dest))
		{
			return std::make_tuple(world_dest, source);
		}

		auto const [clipped_x, clipped_width, clipped_source_x, clipped_source_width] =
			clip_dimensions(world_dest.x, world_dest.width,
				            this->p_viewport_coordinates_->x, this->p_viewport_coordinates_->width,
				            source.x, source.width);
		
		auto const [clipped_y, clipped_height, clipped_source_y, clipped_source_height] =
			clip_dimensions(world_dest.y, world_dest.height,
				            this->p_viewport_coordinates_->y, this->p_viewport_coordinates_->height,
				            source.y, source.height);

        return std::make_tuple(rectangle<float>(clipped_x, clipped_y, clipped_width, clipped_height), 
			                   rectangle<int>(clipped_source_x, clipped_source_y, clipped_source_width, clipped_source_height));
	}

	inline int calc_pixel_pos(float const pos, 
		                      float const viewport_pos, 
		                      float const viewport_length, 
		                      unsigned int const pixel_length)
	{
		return to_int((pos - viewport_pos) / viewport_length * static_cast<float>(pixel_length));
	}

	inline int calc_pixel_dim(float const length, 
		                      float const viewport_length, 
		                      unsigned int const pixel_length)
	{
		return to_int(length / viewport_length * static_cast<float>(pixel_length));
	}

	rectangle<int> viewport_implementation::translate_to_render_coordinates(rectangle<float> const& world_dest) const
	{
		int const x = calc_pixel_pos(world_dest.x, 
			                         this->p_viewport_coordinates_->x, 
			                         this->p_viewport_coordinates_->width, 
			                         this->get_render_width());
		int const y = calc_pixel_pos(world_dest.y, 
			                         this->p_viewport_coordinates_->y, 
			                         this->p_viewport_coordinates_->height, 
			                         this->get_render_height());
		int const width = calc_pixel_dim(world_dest.width, 
			                             this->p_viewport_coordinates_->width, 
			                             this->get_render_width());
		int const height = calc_pixel_dim(world_dest.height, 
			                              this->p_viewport_coordinates_->height, 
			                              this->get_render_height());
		
		return rectangle<int>(x, y, width, height);
	}
}
