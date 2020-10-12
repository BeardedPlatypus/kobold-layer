#include "pch.h"
#include "kobold-layer.clr/view.hpp"


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

	bool view::has_texture(std::string const& key)
	{
		return this->p_view_->has_texture(key);
	}

	void view::load_texture(std::string const& key, std::string const& texture_path)
	{
		this->p_view_->load_texture(key, texture_path);
	}
}