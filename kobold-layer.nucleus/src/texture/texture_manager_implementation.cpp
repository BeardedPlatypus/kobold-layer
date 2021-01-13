#include "pch.h"
#include "texture_manager_implementation.hpp"

namespace kobold_layer::nucleus::texture
{
	texture_manager_implementation::texture_manager_implementation(std::unique_ptr<texture_factory> p_texture_factory) :
		p_texture_factory_(std::move(p_texture_factory))
	{
	}

	void texture_manager_implementation::load_texture(std::string const& key, std::filesystem::path const& texture_path)
	{
		if (this->has_texture(key)) return;

		this->texture_map_.emplace(
			key,
			this->p_texture_factory_->construct_texture(texture_path.string()));
	}

	void texture_manager_implementation::unload_texture(std::string const& key)
	{
		if (!this->has_texture(key)) return;
		
		this->texture_map_.erase(key);
	}


	bool texture_manager_implementation::has_texture(std::string const& key) const
	{
		return this->texture_map_.find(key) != this->texture_map_.end();
	}

	const texture* texture_manager_implementation::get_texture(std::string const& key) const
	{
		return this->texture_map_.at(key).get();
	}
}
