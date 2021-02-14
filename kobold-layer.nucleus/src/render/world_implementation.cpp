#include "pch.h"
#include "world_implementation.hpp"

namespace kobold_layer::nucleus::render
{
	world_implementation::world_implementation(rectangle<float> const& boundaries) :
	    p_boundaries_(std::make_unique<rectangle<float>>(boundaries.x, 
			                                             boundaries.y, 
			                                             boundaries.width, 
			                                             boundaries.height)) { }

	
	rectangle<float> world_implementation::get_boundaries() const
	{
		return *this->p_boundaries_;
	}

	void world_implementation::set_boundaries(rectangle<float> const& new_boundaries)
	{
		this->p_boundaries_ =
			std::make_unique<rectangle<float>>(
				new_boundaries.x,
				new_boundaries.y,
				new_boundaries.width,
				new_boundaries.height);
	}
}
