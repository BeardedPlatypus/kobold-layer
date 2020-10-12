#include "pch.h"
#include "kobold-layer.clr/view.hpp"

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
}