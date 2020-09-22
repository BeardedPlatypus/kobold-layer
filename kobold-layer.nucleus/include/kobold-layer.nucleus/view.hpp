#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "../src/sdl-util/sdl_dispatcher_implementation.hpp"

#include "kobold-layer.nucleus/render/renderer.hpp"
#include "../src/texture/texture_manager_implementation.hpp"

namespace kobold_layer::nucleus {

	class view {
	public:
		view() = default;

		void initialise();
		void initialise(void const* p_native_window);

		void update();
		[[nodiscard]] bool should_quit() const;
	private:
		std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher_ =
			std::make_shared<sdl_util::sdl_dispatcher_implementation>();

		std::shared_ptr<render::renderer> p_renderer_;
		std::unique_ptr<texture::texture_manager> p_tex_manager;

		std::unique_ptr<sdl_util::resource_wrapper<SDL_Window>> p_window_;

		bool should_quit_ = false;
	};
}