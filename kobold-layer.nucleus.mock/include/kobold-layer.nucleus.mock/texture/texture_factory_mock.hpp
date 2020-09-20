#pragma once
#include "texture/texture_factory.hpp"
#include <gmock/gmock.h>


class texture_factory_mock final : public kobold_layer::nucleus::texture::texture_factory
{
public:
	MOCK_METHOD(
		std::unique_ptr<kobold_layer::nucleus::texture::texture>,
		construct_texture,
		(std::filesystem::path const&),
		(const));
};


