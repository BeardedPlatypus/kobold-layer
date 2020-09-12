#pragma once
#include "kobold-layer.nucleus/sdl-util/resource_wrapper.hpp"
#include <gmock/gmock.h>

template<typename T>
class resource_wrapper_mock final : public kobold_layer::nucleus::sdl_util::resource_wrapper<T>
{
public:
	MOCK_METHOD(T*, get_resource, (), (const));
};

template class resource_wrapper_mock<SDL_Window>;
template class resource_wrapper_mock<SDL_Renderer>;
template class resource_wrapper_mock<SDL_Texture>;

