﻿#pragma once
#include "kobold-layer.nucleus/render/viewport.hpp"

#include <memory>
#include <tuple>

#include "kobold-layer.nucleus/render/world.hpp"

namespace kobold_layer::nucleus::render
{
	/// <summary>
	/// <see cref="viewport_implementation" /> implements the <see cref="viewport" /> interface.
	/// </summary>
	/// <seealso cref="viewport" />
	class viewport_implementation final : public viewport
	{
	public:		
        /// <summary>
        /// Creates a new <see cref="viewport_implementation"/>.
        /// </summary>
        /// <param name="p_world">A pointer to the world.</param>
        /// <param name="render_width">Width of the render.</param>
        /// <param name="render_height">Height of the render.</param>
        /// <param name="viewport_coordinates">The viewport coordinates.</param>
		viewport_implementation(
			std::shared_ptr<world const> p_world,
			unsigned int render_width,
			unsigned int render_height,
			rectangle<float> const& viewport_coordinates);
		
		[[nodiscard]] unsigned int get_render_width() const override;
		void set_render_width(unsigned int new_render_width) override;

		[[nodiscard]] unsigned int get_render_height() const override;
		void set_render_height(unsigned int new_render_height) override;

		[[nodiscard]] rectangle<float> get_viewport_coordinates() const override;
		void set_viewport_coordinates(rectangle<float> const& new_coordinates) override;

		[[nodiscard]] std::optional<viewport::clipped_rects> clip_to_viewport(
			rectangle<int> const& tex_source,
			rectangle<float> const& world_destination) const override;

	private:
		std::shared_ptr<world const> p_world_;

		std::unique_ptr<rectangle<float>> p_viewport_coordinates_;

		unsigned int render_width_;
		unsigned int render_height_;

        [[nodiscard]] bool has_fully_enclosed(rectangle<float> const& rect) const;
        [[nodiscard]] bool has_intersection_with(rectangle<float> const& rect) const;

		[[nodiscard]] std::tuple<rectangle<float>, rectangle<int>> clip_viewport_coordinates(rectangle<float> const&, rectangle<int> const&) const;
		[[nodiscard]] rectangle<int> translate_to_render_coordinates(rectangle<float> const& world_dest) const;
	};
}
