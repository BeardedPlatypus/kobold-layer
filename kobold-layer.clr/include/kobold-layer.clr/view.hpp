#pragma once
#include <kobold-layer.nucleus/view.hpp>

namespace kobold_layer::clr {
    public ref class view sealed {
    public:
        view();
        ~view();

        void initialise(void* p_native_window);
        void update();
        bool should_exit();

		bool has_texture(std::string const& key);
		void load_texture(std::string const& key, std::string const& texture_path);
    private:
        nucleus::view* p_view_;
    };
}