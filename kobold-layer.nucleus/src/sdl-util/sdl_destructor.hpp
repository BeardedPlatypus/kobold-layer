#pragma once
#include <SDL2/SDL.h>

namespace kobold_layer::nucleus::sdl_util {
	/// <summary>
	/// <see cref="sdl_destructor{T}"/> defines the destruction behaviour of
	/// different SDL components.
	/// </summary>
	template <typename T>
	struct sdl_destructor
	{
		void operator()(T* p) const;
	};

	/// <summary>
	/// <see cref="sdl_destructor<SDL_Window>"/> destructs the
	/// <see cref="SDL_Window"/> by calling <see cref="SDL_DestroyWindow"/>.
	/// </summary>
	template <>
	struct sdl_destructor<SDL_Window>
	{
		void operator()(SDL_Window* p) const
		{
			SDL_DestroyWindow(p);
		}
	};

	/// <summary>
	/// <see cref="sdl_destructor<SDL_Renderer>"/> destructs the
	/// <see cref="SDL_Renderer"/> by calling <see cref="SDL_DestroyRenderer"/>.
	/// </summary>
	template <>
	struct sdl_destructor<SDL_Renderer>
	{
		void operator()(SDL_Renderer* p) const
		{
			SDL_DestroyRenderer(p);
		}
	};

	/// <summary>
	/// <see cref="sdl_destructor<SDL_Texture>"/> destructs the
	/// <see cref="SDL_Texture"/> by calling <see cref="SDL_DestroyTexture"/>.
	/// </summary>
	template <>
	struct sdl_destructor<SDL_Texture>
	{
		void operator()(SDL_Texture* p) const
		{
			SDL_DestroyTexture(p);
		}
	};
}
