#include "pch.h"
#include "sdl_conversion.hpp"

namespace kobold_layer::nucleus::sdl_util
{
    render::rectangle to_rectangle(SDL_Rect const* p_rect)
    {
        return render::rectangle(p_rect->x, p_rect->y, p_rect->w, p_rect->h);
    }

    SDL_Rect to_sdl_rect(render::rectangle const& rectangle)
    {
        SDL_Rect result;
        result.x = rectangle.x;
        result.y = rectangle.y;
        result.w = rectangle.width;
        result.h = rectangle.height;

        return result;
    }
}
