#pragma once
#include <filesystem>
#include "kobold-layer.nucleus/texture/texture.hpp"

namespace kobold_layer::nucleus::texture
{
	/// <summary>
	/// <see cref="texture_factory_implementation"/> implements the interface to
	/// construct <see cref="texture"/> objects.
	/// </summary>
	class texture_factory
	{
	public:
		texture_factory(const texture_factory&) = delete;
		texture_factory& operator=(const texture_factory&) = delete;

		texture_factory(texture_factory&&) noexcept = delete;
		texture_factory& operator=(texture_factory&&) noexcept = delete;

		virtual ~texture_factory() = default;

		/// <summary>
		/// Constructs the texture from the given <paramref name="texture_path"/>.
		/// </summary>
		/// <param name="texture_path">The path to the texture.</param>
		/// <returns>
		/// A new <see cref="std::unique_ptr<{texture}"/>.
		/// </returns>
		[[nodiscard]] virtual std::unique_ptr<texture> construct_texture(const std::filesystem::path& texture_path) const = 0;

	protected:
		texture_factory() = default;
	};
}
