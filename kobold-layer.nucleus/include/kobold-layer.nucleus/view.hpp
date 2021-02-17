#pragma once
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include "../src/sdl-util/sdl_dispatcher_implementation.hpp"

#include "kobold-layer.nucleus/render/canvas.hpp"
#include "kobold-layer.nucleus/render/viewport.hpp"
#include "kobold-layer.nucleus/render/world.hpp"
#include "../src/texture/texture_manager_implementation.hpp"

namespace kobold_layer::nucleus {	
	/// <summary>
	/// <see cref="view"/> defines the main entry point for rendering sprites.
	/// </summary>
	class view {
	public:
		view() = default;

		/// <summary>
		/// Initialise a new window to render to.
		/// </summary>
		void initialise();
		
		/// <summary>
		/// Initialise a new window to render to on the provided native window.
		/// </summary>
		/// <param name="p_native_window">The native window used to initialise the view.</param>
		void initialise(void const* p_native_window);
		
		/// <summary>
		/// Initialise a new frame to render.
		/// </summary>
		/// <remarks>
		/// This call should be followed by a call to <see cref="finalise_frame"/>.
		/// </remarks>
		void initialise_frame();

		void render_texture(const std::string& texture_label) const;
		
		/// <summary>
		/// Finalise the frame currently being rendered.
		/// </summary>
		/// <remarks>
		/// This call should be preceded by a call to <see cref="initialise_frame"/>.
		/// </remarks>
		void finalise_frame() const;

		void update();
	
		[[nodiscard]] bool should_quit() const;
		
		/// <summary>
		/// Determines whether the view has a texture with the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>
		///   <c>true</c> if the specified key has texture; otherwise, <c>false</c>.
		/// </returns>
		[[nodiscard]] bool has_texture(std::string const& key) const;

        /// <summary>
        /// Loads the texture and associate it with the provided key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="texture_path">The texture path.</param>
		void load_texture(std::string const& key, std::filesystem::path const& texture_path);
		
        /// <summary>
        /// Unloads the texture associated with the specified <paramref name="key"/>.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <remarks>
        /// If no texture is associated with <paramref name="key"/> then
        /// nothing will happen.
        /// </remarks>
		void unload_texture(std::string const& key);

		/// <summary>
		/// Get the world coordinates of this <see cref="view"/>.
		/// </summary>
		/// <returns>
		/// The world coordinates of this <see cref="view"/>.
		/// </returns>
		render::rectangle<float> get_world_area() const;

		/// <summary>
		/// Set the world area of this <see cref="view"/> to
		/// <paramref name="new_area"/>.
		/// </summary>
		/// <param name="new_area">The new world coordinates.</param>
		void set_world_area(render::rectangle<float> const& new_area);

		/// <summary>
	    /// Get the viewport coordinates of this <see cref="view"/>.
	    /// </summary>
	    /// <returns>
	    /// The world coordinates of this <see cref="view"/>.
	    /// </returns>
		render::rectangle<float> get_viewport_area() const;

		/// <summary>
		/// Set the viewport area of this <see cref="view"/> to
		/// <paramref name="new_area"/>.
		/// </summary>
		/// <param name="new_area">The new viewport coordinates.</param>
		void set_viewport_area(render::rectangle<float> const& new_area);

	private:
		std::shared_ptr<sdl_util::sdl_dispatcher> p_dispatcher_ =
			std::make_shared<sdl_util::sdl_dispatcher_implementation>();

		std::shared_ptr<render::world> p_world_;
		std::shared_ptr<render::viewport> p_viewport_;
		std::shared_ptr<render::canvas> p_canvas_;
		std::unique_ptr<texture::texture_manager> p_tex_manager;

		std::unique_ptr<sdl_util::resource_wrapper<SDL_Window>> p_window_;

		bool should_quit_ = false;
	};
}