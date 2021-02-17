#include "pch.h"
#include "kobold-layer.clr/view.hpp"
#include "kobold-layer.nucleus/render/rectangle.hpp"

#include <msclr/marshal.h>

namespace kobold_layer::clr {
	view::view() : p_view_(new nucleus::view()) { }

	view::~view()
	{
		delete this->p_view_;
	}

	void view::initialise(void* p_native_window)
	{
		this->p_view_->initialise(p_native_window);
	}

	void view::update()
	{
		this->p_view_->update();
	}

	void view::initialise_frame()
	{
		p_view_->initialise_frame();
	}

	void view::render_texture(System::String^ texture_label)
	{
		msclr::interop::marshal_context marshal_context;
		std::string const native_label = marshal_context.marshal_as<const char*>(texture_label);

		this->p_view_->render_texture(native_label);
	}

	void view::finalise_frame()
	{
		this->p_view_->finalise_frame();
	}

	bool view::should_exit()
	{
		return this->p_view_->should_quit();
	}

	bool view::has_texture(System::String^ key)
	{
		msclr::interop::marshal_context marshal_context;
		std::string const native_key = marshal_context.marshal_as<const char*>(key);
		
		return this->p_view_->has_texture(native_key);
	}

	void view::load_texture(System::String^ key, System::String^ texture_path)
	{
		msclr::interop::marshal_context marshal_context;
		std::string const native_key = marshal_context.marshal_as<const char*>(key);
		std::filesystem::path const native_path = marshal_context.marshal_as<const char*>(texture_path);
		
		this->p_view_->load_texture(native_key, native_path);
	}

	void view::unload_texture(System::String^ key)
	{
		msclr::interop::marshal_context marshal_context;
		std::string const native_key = marshal_context.marshal_as<const char*>(key);
		
		this->p_view_->unload_texture(native_key);
	}

	template <typename T>
	rectangle<T>^ to_rectangle(nucleus::render::rectangle<T> const& rect)
	{
		return gcnew rectangle<T>(rect.x, rect.y, rect.width, rect.height);
	}

	template <typename T>
	nucleus::render::rectangle<T> from_rectangle(rectangle<T>^ rect)
	{
		return nucleus::render::rectangle<T>(rect->x, rect->y, rect->width, rect->height);
	}

	rectangle<float>^ view::get_world_area()
	{
		return to_rectangle<float>(this->p_view_->get_world_area());
	}

	void view::set_world_area(rectangle<float>^ new_area)
	{
		this->p_view_->set_world_area(from_rectangle(new_area));
	}

	rectangle<float>^ view::get_viewport_area()
	{
		return to_rectangle<float>(this->p_view_->get_viewport_area());
	}

	void view::set_viewport_area(rectangle<float>^ new_area)
	{
		this->p_view_->set_viewport_area(from_rectangle(new_area));
	}
}