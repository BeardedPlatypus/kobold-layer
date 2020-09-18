#pragma once
#include <memory>

#include "kobold-layer.nucleus/render/rectangle.hpp"
#include "kobold-layer.nucleus/render/renderer.h"

namespace kobold_layer::nucleus::texture {
	/// <summary>
	/// <see cref="texture"/> defines the interface of a single texture loaded
	/// from a single image.
	/// </summary>
	class texture
	{
	public:
		texture(const texture&) = delete;
		texture& operator=(const texture&) = delete;

		texture(texture&&) noexcept = delete;
		texture& operator=(texture&&) noexcept = delete;

		virtual ~texture() = default;

		/// <summary>
		/// Renders this <see cref="texture"/> with <paramref name="renderer"/>.
		/// </summary>
		/// <param name="p_renderer">The renderer.</param>
		/// <param name="clip">The clipping rectangle.</param>
		/// <param name="dst">The destination rectangle.</param>
		/// <param name="angle">The angle.</param>
		/// <param name="flip_horizontally">if set to <c>true</c> [flip horizontally].</param>
		/// <param name="flip_vertically">if set to <c>true</c> [flip vertically].</param>
		virtual void render(std::shared_ptr<render::renderer> p_renderer,
			render::rectangle const& clip,
			render::rectangle const& dst,
			float angle,
			bool flip_horizontally,
			bool flip_vertically) const = 0;

		/// <summary>
		/// Gets the dimensions of this <see cref="texture"/>.
		/// </summary>
		/// <returns>
		/// The dimensions of this texture.
		/// </returns>
		[[nodiscard]] virtual render::rectangle get_dimensions() const = 0;
	protected:
		texture() = default;
	};
}

