#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/fixed.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>
#include <thread>
#include <iostream>

enum tipo{
    JUGADOR,
    OBSTACULO,
    OBJETIVO,
    VACIO
};

class Game: public Gtk::Window {
    public:
        Game();
        virtual ~Game();
    private:
        bool running = false;
        tipo matrix[20][20] = {VACIO};
        int min_div = 10;
    
        Gtk::Fixed plane;
        Gtk::Image cat;

        void move();
        void startThread();
};

Game::Game() {

    Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_file("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/cat.png", 20, 20);
    cat = Gtk::Image(pix);

    plane.put(cat, 250, 150);

    add(plane);

    set_size_request(500, 500);
    set_title("Pathfinding Game");
    show_all_children();
    startThread();
}
Game::~Game() {

}
void Game::startThread() {
    // std::thread my_thread(&Game::move, this);
    std::thread my_thread(foo);
    my_thread.detach();
    // my_thread.join();
}

void foo() {

}

void Game::move() {
    std::cout << "Moving\n";
    int x = 0;
    int y = 0;
    while (true) {
        plane.move(cat, x, y);
         x++;
        y++;
        std::cout << "Moved..\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.tec.pathfinding");
    Game game;
    return app->run(game);
}