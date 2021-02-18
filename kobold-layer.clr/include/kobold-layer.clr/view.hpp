#pragma once
#include <kobold-layer.nucleus/view.hpp>
#include <kobold-layer.clr/rectangle.hpp>

namespace kobold_layer::clr {
    public ref class view sealed {
    public:
        view();
        ~view();

        void initialise(void* p_native_window);

        void update();

		void initialise_frame();
		void render_texture(System::String^ texture_label);
		void finalise_frame();
    	
        bool should_exit();

		bool has_texture(System::String^ key);
		void load_texture(System::String^ key, System::String^ texture_path);
        void unload_texture(System::String^ key);

		rectangle^ get_world_area();
		void set_world_area(rectangle^ new_area);
    	
		rectangle^ get_viewport_area();
		void set_viewport_area(rectangle^ new_area);
    private:
        nucleus::view* p_view_;
    };
}