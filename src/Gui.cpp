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
        const static int resolution = 20;
        bool running = false;
        tipo matrix[resolution][resolution] = {VACIO};
        int min_div;

        int player_x;
        int player_y;
    
        Gtk::Fixed plane;
        Gtk::Image player;

        void move();
        void startThread();
        void placePlayer();
        Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};
 
Game::Game() {
    player = Gtk::Image(load_image("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/cat.png", 20, 20));

    add(plane);

    set_size_request(500, 500);
    set_title("Pathfinding Game");
    show_all_children();
    startThread();
}
Game::~Game() {

}
void Game::startThread() {
    running = true;
    std::thread my_thread(&Game::move, this);    
    my_thread.detach();
}
void Game::placePlayer() {
    srand(500);
    player_x = rand();
    player_y = rand();
    plane.put(player, player_x, player_y);
    std::cout << "Player coordinates:\nX: " << player_x << "\tY: " << player_y << "\n";
}
void Game::move() {
    std::cout << "Starting movement..\n";
    while (running) {
        plane.move(player, player_x, player_y);
        player_x++;
        player_y++;
        std::cout << "Moved\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}
Glib::RefPtr<Gdk::Pixbuf> Game::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.tec.pathfinding");
    Game game;
    return app->run(game);
}