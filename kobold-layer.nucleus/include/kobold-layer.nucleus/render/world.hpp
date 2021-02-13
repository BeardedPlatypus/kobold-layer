#pragma once

#include "kobold-layer.nucleus/render/rectangle.hpp"

namespace kobold_layer::nucleus::render
{	
	/// <summary>
	/// <see cref="world" /> defines the world boundaries in which textures
	/// and sprites can be rendered.
	/// </summary>
	class world
	{
	public:
		world(const world&) = delete;
		world& operator=(const world&) = delete;

		world(world&&) noexcept = delete;
		world& operator=(world&&) noexcept = delete;

		virtual ~world() = delete;

		/// <summary>
		/// Get the boundaries of this <see cref="world"/>
		/// </summary>
		/// <returns>
		/// A <see cref="rectangle"/> defining the boundaries of this world.
		/// </returns>
		[[nodiscard]] virtual rectangle get_boundaries() const = 0;
		
		/// <summary>
		/// Sets boundaries of this <see cref="world"/> to the specified
		/// <paramref name="new_boundaries"/>.
		/// </summary>
		/// <param name="new_boundaries">The new boundaries.</param>
		virtual void set_boundaries(rectangle const& new_boundaries) = 0;
	};
	
}
