#pragma once
#include "kobold-layer.nucleus/render/world.hpp"
#include <gmock/gmock.h>

class world_mock final : public kobold_layer::nucleus::render::world
{
public:
	MOCK_METHOD(kobold_layer::nucleus::render::rectangle<float>, get_boundaries, (), (const));
	MOCK_METHOD(void, set_boundaries, (kobold_layer::nucleus::render::rectangle<float> const&), ());
};