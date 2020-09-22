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

    private:
        nucleus::view* p_view_;
    };
}