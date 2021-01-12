#include "pch.h"
#include "kobold-layer.nucleus/view.hpp"

#include "render/renderer_implementation.hpp"
#include "texture/texture_factory_implementation.hpp"

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
    }

	void view::initialise_frame()
	{
    	// TODO: the eventing logic should be moved away from the view.
        SDL_Delay(10);

        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event))
        {
            if (sdl_event.type != SDL_QUIT) continue;
            this->should_quit_ = true;
            break;
        }

        this->p_renderer_->render_clear();
	}

	void view::render_texture(const std::string& texture_label) const
	{
        texture::texture const * const texture = p_tex_manager->get_texture(texture_label);

        int width;
    	int height;
    	
        this->p_dispatcher_->get_window_size(this->p_window_->get_resource(), &width, &height);
        const auto window_rect = render::rectangle(0, 0, width, height);

        render::rectangle const tex_rect = texture->get_dimensions();

        texture->render(this->p_renderer_, tex_rect, window_rect, 0.F, false, false);
	}

	void view::finalise_frame() const
	{
        this->p_renderer_->render_present();
	}

	void view::update()
	{
        this->initialise_frame();
        this->render_texture("sample");
        this->finalise_frame();
	}

    bool view::should_quit() const
    {
        return this->should_quit_;
    }

	bool view::has_texture(std::string const& key) const
	{
        return this->p_tex_manager->has_texture(key);
	}

	void view::load_texture(std::string const& key, std::filesystem::path const& texture_path)
	{
        this->p_tex_manager->load_texture(key, texture_path);
	}
}
