#include "pch.h"
#include "renderer_implementation.hpp"

#include "../sdl-util/sdl_conversion.hpp"

namespace kobold_layer::nucleus::render
{
    renderer_implementation::renderer_implementation(
        std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> p_sdl_renderer,
        std::shared_ptr<sdl_util::sdl_dispatcher> p_sdl_dispatcher) :
        p_sdl_renderer_(std::move(p_sdl_renderer)),
        p_sdl_dispatcher_(std::move(p_sdl_dispatcher)) { }


    void renderer_implementation::render_copy(
        SDL_Texture* p_texture,
        rectangle const& texture_clip,
        rectangle const& destination,
        float const angle,
        bool const flip_horizontally,
        bool const flip_vertically) const
    {
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        if (flip_horizontally) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
        if (flip_vertically)   flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);

        SDL_Rect texture_clip_sdl = sdl_util::to_sdl_rect(texture_clip);
        SDL_Rect destination_sdl = sdl_util::to_sdl_rect(destination);

        this->p_sdl_dispatcher_->render_copy_ex(
            this->p_sdl_renderer_->get_resource(),
            p_texture,
            &texture_clip_sdl,
            &destination_sdl,
            angle,
            nullptr,
            flip);
    }

    void renderer_implementation::render_clear() const
    {
        this->p_sdl_dispatcher_->render_clear(this->p_sdl_renderer_->get_resource());
    }


    void renderer_implementation::render_present() const
    {
        this->p_sdl_dispatcher_->render_present(this->p_sdl_renderer_->get_resource());
    }
}
