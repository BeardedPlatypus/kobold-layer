#pragma once

#include "kobold-layer.nucleus/render/world.hpp"

#include <memory>

namespace kobold_layer::nucleus::render
{	
	/// <summary>
	/// <see cref="world" /> defines the world boundaries in which textures
	/// and sprites can be rendered.
	/// </summary>
	class world_implementation final : public world
	{
	public:
		explicit world_implementation(rectangle<float> const& boundaries);

		/// <summary>
		/// Get the boundaries of this <see cref="world"/>
		/// </summary>
		/// <returns>
		/// A <see cref="rectangle"/> defining the boundaries of this world.
		/// </returns>
		[[nodiscard]] rectangle<float> get_boundaries() const override;
		
		/// <summary>
		/// Sets boundaries of this <see cref="world"/> to the specified
		/// <paramref name="new_boundaries"/>.
		/// </summary>
		/// <param name="new_boundaries">The new boundaries.</param>
		void set_boundaries(rectangle<float> const& new_boundaries) override;

	private:
		std::unique_ptr<rectangle<float>> p_boundaries_;
	};
}