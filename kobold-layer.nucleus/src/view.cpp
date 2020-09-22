﻿#include "pch.h"
#include "kobold-layer.nucleus/view.hpp"

#include "render/renderer_implementation.hpp"
#include "texture/texture_factory_implementation.hpp"

#include <string>


namespace kobold_layer::nucleus {
    void view::initialise()
    {
        this->p_dispatcher_->init_sdl(SDL_INIT_VIDEO);
        atexit(SDL_Quit);

        const std::string title = "SDL Native App";

        this->p_window_ =
            this->p_dispatcher_->create_window(
                title.c_str(),
                100, 100,
                1200, 600,
                SDL_WINDOW_SHOWN);

        std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> renderer =
            this->p_dispatcher_->create_renderer(
                this->p_window_->get_resource(),
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_SetRenderDrawColor(renderer->get_resource(), 128, 216, 235, 255);

        this->p_renderer_ = std::make_unique<render::renderer_implementation>(std::move(renderer), p_dispatcher_);

        auto texture_factory = std::make_unique<texture::texture_factory_implementation>(renderer, this->p_dispatcher_);
        this->p_tex_manager = std::make_unique<texture::texture_manager_implementation>(std::move(texture_factory));
    }

    void view::initialise(void const * p_native_window)
    {
	    int const init_result = this->p_dispatcher_->init_sdl(SDL_INIT_VIDEO);

    	if (init_result != 0)
    	{
            return;
    	}
    	
        atexit(SDL_Quit);

        this->p_window_ =
            this->p_dispatcher_->create_window(p_native_window);

        std::shared_ptr<sdl_util::resource_wrapper<SDL_Renderer>> renderer =
            this->p_dispatcher_->create_renderer(
                this->p_window_->get_resource(),
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        this->p_renderer_ = std::make_unique<render::renderer_implementation>(renderer, p_dispatcher_);

        auto texture_factory = std::make_unique<texture::texture_factory_implementation>(renderer, this->p_dispatcher_);
        this->p_tex_manager = std::make_unique<texture::texture_manager_implementation>(std::move(texture_factory));

        // Load image.
        this->p_tex_manager->load_texture("sample", std::filesystem::path("sample.png"));
    }

    void view::update()
    {
        SDL_Delay(10);

        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event))
        {
            if (sdl_event.type != SDL_QUIT) continue;
            this->should_quit_ = true;
            break;
        }

        this->p_renderer_->render_clear();

        // Texture
        const auto texture = p_tex_manager->get_texture("sample");

        int width, height;
        this->p_dispatcher_->get_window_size(this->p_window_->get_resource(), &width, &height);
        const auto window_rect = render::rectangle(0, 0, width, height);

        const render::rectangle tex_rect = texture->get_dimensions();

        texture->render(this->p_renderer_, tex_rect, window_rect, 0.F, false, false);

        this->p_renderer_->render_present();
    }

    bool view::should_quit() const
    {
        return this->should_quit_;
    }
}