#include "pch.h"
#include "resource_wrapper_implementation.hpp"

#include <memory>

#include "sdl_destructor.hpp"

namespace kobold_layer::nucleus::sdl_util {
	template <typename T>
	resource_wrapper_implementation<T>::resource_wrapper_implementation(T* p_resource) :
	    p_resource_(std::unique_ptr<T, sdl_destructor<T>>(p_resource)) { }

	template <typename T>
	T* resource_wrapper_implementation<T>::get_resource() const {
		return this->p_resource_.get();
	}
}
