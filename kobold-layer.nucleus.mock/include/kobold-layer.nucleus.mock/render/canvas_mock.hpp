#pragma once
#include "kobold-layer.nucleus/render/canvas.hpp"
#include <gmock/gmock.h>

class canvas_mock final : public kobold_layer::nucleus::render::canvas
{
public:
	MOCK_METHOD(void, render_copy,
		(SDL_Texture*,
         kobold_layer::nucleus::render::rectangle<int> const&,
         kobold_layer::nucleus::render::rectangle<float> const&,
         float, bool, bool),
		(const));

	MOCK_METHOD(void, present, (), (const));
	MOCK_METHOD(void, clear, (), (const));
};