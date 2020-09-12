#pragma once
#include <SDL2/SDL.h>

#include "kobold-layer.nucleus/render/rectangle.hpp"

namespace kobold_layer::nucleus::sdl_util
{
	/// <summary>
	/// Convert <paramref name="p_rect"/>  to  <see cref="render::rectangle"/>.
	/// </summary>
	/// <param name="p_rect">A pointer to the <see cref="SDL_Rect"/> to convert.</param>
	/// <returns>
	/// The corresponding <see cref="render::rectangle"/>.
	/// </returns>
	render::rectangle to_rectangle(const SDL_Rect* p_rect);

	/// <summary>
	/// Convert <paramref name="rectangle"/>  to a <see cref="SDL_Rect"/>.
	/// </summary>
	/// <param name="rectangle">Rectangle to convert.</param>
	/// <returns>
	/// The corresponding <see cref="SDL_Rect"/>.
	/// </returns>
	SDL_Rect to_sdl_rect(const render::rectangle& rectangle);
}

