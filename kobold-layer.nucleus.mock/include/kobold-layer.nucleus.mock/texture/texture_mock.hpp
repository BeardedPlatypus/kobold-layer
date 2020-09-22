﻿#pragma once
#include "kobold-layer.nucleus/texture/texture.hpp"
#include <gmock/gmock.h>


class texture_mock final : public kobold_layer::nucleus::texture::texture
{
public:
    MOCK_METHOD(
        void,
        render,
        (std::shared_ptr<kobold_layer::nucleus::render::renderer>,
         kobold_layer::nucleus::render::rectangle const&,
         kobold_layer::nucleus::render::rectangle const&,
         float, bool, bool),
        (const));
    MOCK_METHOD(kobold_layer::nucleus::render::rectangle, get_dimensions, (), (const));
};