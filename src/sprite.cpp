#include <gtkmm-3.0/gtkmm/image.h>

class Sprite {
    public:
        Sprite();
        void set_matrix_coords(int x, int y);
        void set_gui_coords(int div);
        Gtk::Image img;
        int matrix_x;
        int matrix_y;
        int gui_x;
        int gui_y;
        void move(int new_x, int new_y);
    private:
        int div;
};

Sprite::Sprite() {

}

void Sprite::set_matrix_coords(int x, int y) {
    matrix_x = x;
    matrix_y = y;
}

void Sprite::set_gui_coords(int div) {
    this->div = div;
    gui_x = matrix_x * div;
    gui_y = matrix_y * div;
}

void Sprite::move(int new_x, int new_y) {
    matrix_x = new_x;
    matrix_y = new_y;
    gui_x = matrix_x * div;
    gui_y = matrix_y * div;
}