#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/fixed.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>
#include <iostream>

class Game: public Gtk::Window {
    public:
        Game();
        virtual ~Game();
    private:
        Gtk::Button button1;
        Gtk::Fixed container;
        void pressed();
};

Game::Game(): button1("Hello") {

    add(container);

    set_size_request(500, 300);
    set_title("Pathfinding Game");
    show_all_children();
}

Game::~Game() {

}

void Game::pressed() {
    std::cout << "Pressed\n";
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.tec.pathfinding");
    Game game;
    return app->run(game);
}