#pragma once

#include "kobold-layer.nucleus/render/rectangle.hpp"

namespace kobold_layer::nucleus::render
{	
	/// <summary>
	/// <see cref="viewport" /> defines the interface for the viewport, responsible
	/// for maintaining the current <see cref="world" /> coordinates being rendered
	/// on the screen, as well as determining which section of rectangles can be
	/// displayed.
	/// </summary>
	class viewport
	{
	public:
		viewport(const viewport&) = delete;
		viewport& operator=(const viewport&) = delete;

		viewport(viewport&&) noexcept = delete;
		viewport& operator=(viewport&&) noexcept = delete;

		virtual ~viewport() = delete;
		
	    /// <summary>
	    /// Get the render width of this <see cref="viewport"/>.
	    /// </summary>
	    /// <returns>
	    /// The render width of this <see cref="viewport"/>.
	    /// </returns>
		[[nodiscard]] virtual unsigned int get_render_width() const = 0;
		
	    /// <summary>
	    /// Set the render width of this <see cref="viewport"/> to the specified
	    /// <paramref name="new_render_width"/>.
	    /// </summary>
	    /// <param name="new_render_width">The new render width.</param>
		virtual void set_render_width(unsigned int new_render_width) = 0;

	    /// <summary>
	    /// Get the render height of this <see cref="viewport"/>.
	    /// </summary>
	    /// <returns>
	    /// The render height of this <see cref="viewport"/>.
	    /// </returns>
		[[nodiscard]] virtual unsigned int get_render_height() const = 0;
		
	    /// <summary>
	    /// Set the render height of this <see cref="viewport"/> to the specified
	    /// <paramref name="new_render_height"/>.
	    /// </summary>
	    /// <param name="new_render_height">The new render height.</param>
		virtual void set_render_height(int new_render_height) = 0;

		
	    /// <summary>
	    /// Get the world coordinates of this <see cref="viewport"/>.
	    /// </summary>
	    /// <returns>
	    /// The world coordinates of this <see cref="viewport"/>.
	    /// </returns>
		[[nodiscard]] virtual rectangle get_viewport_coordinates() const = 0;

	    /// <summary>
	    /// Set the world coordinates of this <see cref="viewport"/> to the
	    /// specified <paramref name="new_coordinates"/>.
	    /// </summary>
	    /// <param name="new_coordinates">The new coordinates.</param>
		virtual void set_viewport_coordinates(rectangle const& new_coordinates) = 0;
	};
}