#pragma once
#include "kobold-layer.nucleus/render/renderer.hpp"
#include <gmock/gmock.h>

class renderer_mock final : public kobold_layer::nucleus::render::renderer
{
public:
	MOCK_METHOD(void, render_copy,
		(SDL_Texture*,
         kobold_layer::nucleus::render::rectangle const&,
         kobold_layer::nucleus::render::rectangle const&,
         float, bool, bool),
		(const));

	MOCK_METHOD(void, render_present, (), (const));
	MOCK_METHOD(void, render_clear, (), (const));
};
