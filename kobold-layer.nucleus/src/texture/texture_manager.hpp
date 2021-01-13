#pragma once

#include <filesystem>
#include "kobold-layer.nucleus/texture/texture.hpp"

namespace kobold_layer::nucleus::texture
{
	/// <summary>
	/// <see cref="texture_manager"/> defines the interface to create and
	/// store <see cref="texture"/> objects.
	/// </summary>
	class texture_manager
	{
	public:
		texture_manager(texture_manager const&) = delete;
		texture_manager& operator=(texture_manager const&) = delete;

		texture_manager(texture_manager&&) noexcept = delete;
		texture_manager& operator=(texture_manager&&) noexcept = delete;

		virtual ~texture_manager() = default;

		/// <summary>
		/// Loads the texture specified at <paramref name="texture_path"/> with
		/// the given <paramref name="key"/>.
		/// </summary>
		/// <param name="key">The key with which the texture will be stored.</param>
		/// <param name="texture_path">The path to the texture.</param>
		virtual void load_texture(
			std::string const& key,
			std::filesystem::path const& texture_path) = 0;

		virtual void unload_texture(
			std::string const& key) = 0;

		/// <summary>
		/// Determines whether <see cref="texture"/> is associated with the specified
		/// <paramref name="key"/>.
		/// </summary>
		/// <param name="key">The key of the texture.</param>
		/// <returns>
		/// <c>true</c> if a texture exists with the specified <paramref name="key"/>
		/// otherwise <c>false</c>.
		/// </returns>
		[[nodiscard]] virtual bool has_texture(std::string const& key) const = 0;

		/// <summary>
		/// Gets the texture associated with <paramref name="key"/>.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>
		/// The texture associated with <paramref name="key"/>.
		/// </returns>
		[[nodiscard]] virtual const texture* get_texture(std::string const& key) const = 0;

	protected:
		texture_manager() = default;
	};
}
