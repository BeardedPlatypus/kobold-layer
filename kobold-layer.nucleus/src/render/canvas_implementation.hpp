#pragma once

#include <memory>

#include "kobold-layer.nucleus/render/canvas.hpp"
#include "kobold-layer.nucleus/render/renderer.hpp"
#include "kobold-layer.nucleus/render/viewport.hpp"

namespace kobold_layer::nucleus::render
{
    /// <summary>
    /// <see cref="canvas_implementation"/> implements the interface with which to render
    /// a <see cref="SDL_Texture"/> to world space coordinates.
    /// </summary>
	class canvas_implementation final : public canvas
	{
	public:
		/// <summary>
		/// Construct a new <see cref="canvas_implementation"/> with the given
		/// pointer to the <see cref="renderer"/> and <see cref="viewport"/>.
		/// </summary>
		/// <param name="p_renderer">Pointer to the renderer to use.</param>
		/// <param name="p_viewport">Pointer to the viewport to use.</param>
		canvas_implementation(std::shared_ptr<renderer> p_renderer,
		                      std::unique_ptr<viewport> p_viewport);

		void render_copy(SDL_Texture* p_texture, 
			             rectangle<int> const& texture_clip,
			             rectangle<float> const& destination, 
			             float angle, 
			             bool flip_horizontally,
			             bool flip_vertically) const override;
		void present() const override;
		void clear() const override;
	
	private:
		std::shared_ptr<renderer> const p_renderer_;
		std::unique_ptr<viewport> const p_viewport_;
	};
	
}
