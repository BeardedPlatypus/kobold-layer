#pragma once
#include "kobold-layer.nucleus/render/viewport.hpp"
#include <gmock/gmock.h>

class viewport_mock final : public kobold_layer::nucleus::render::viewport
{
public:
    MOCK_METHOD(unsigned int, get_render_width, (), (const));
    MOCK_METHOD(void, set_render_width, (unsigned int));
	
    MOCK_METHOD(unsigned int, get_render_height, (), (const));
    MOCK_METHOD(void, set_render_height, (unsigned int));

    MOCK_METHOD(kobold_layer::nucleus::render::rectangle<float>, get_viewport_coordinates, (), (const));
    MOCK_METHOD(void, set_viewport_coordinates, (kobold_layer::nucleus::render::rectangle<float> const&));
};