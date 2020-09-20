#pragma once

#include <filesystem>
#include <unordered_map>

#include "kobold-layer.nucleus/texture/texture.hpp"

#include "texture_factory.hpp"
#include "texture_manager.hpp"

namespace kobold_layer::nucleus::texture
{
	/// <summary>
	/// <see cref="texture_manager_implementation"/> implements the
	/// interface to create and store <see cref="texture"/> objects.
	/// </summary>
	class texture_manager_implementation final : public texture_manager
	{
	public:
		/// <summary>
		/// Creates a new <see cref="texture_manager_implementation"/>.
		/// </summary>
		/// <param name="p_texture_factory">
		/// A pointer to the <see cref="texture_factory"/> to create the textures with.
		/// </param>
		explicit texture_manager_implementation(std::unique_ptr<texture_factory> p_texture_factory);

		void load_texture(std::string const& key,
			              std::filesystem::path const& texture_path) override;

		[[nodiscard]] bool has_texture(std::string const& key) const override;
		[[nodiscard]] const texture* get_texture(std::string const& key) const override;

	private:
		using texture_map = std::unordered_map<std::string, std::unique_ptr<texture>>;
		texture_map texture_map_ = texture_map();

		std::unique_ptr<texture_factory> p_texture_factory_;
	};
}