#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/fixed.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>
#include <thread>
#include <iostream>
#include <random>

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
        const int WIDTH = 500;
        const int HEIGHT = 500;
        const static int resolution = 100;
        bool running = false;
        tipo matrix[resolution][resolution] = {VACIO};
        int min_div;

        int player_x;
        int player_y;
    
        Gtk::Fixed plane;
        Gtk::Image player;
        
        void init();
        void move();
        void startThread();
        void placePlayer();
        Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};
 
Game::Game() {
    player = Gtk::Image(load_image("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/cat.png", 20, 20));
    add(plane);
    set_size_request(WIDTH, HEIGHT);
    set_title("Pathfinding Game");
    show_all_children();
    init();
    placePlayer();
    startThread();
    show_all_children();
}

Game::~Game() {
}

void Game::init() {
    min_div = WIDTH / resolution;
    std::cout << "min div: " << min_div << "\n";
}

void Game::startThread() {
    running = true;
    std::thread my_thread(&Game::move, this);    
    my_thread.detach();
}

void Game::placePlayer() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> dist(0, resolution);

    //Índices del jugador en la matriz
    player_x = dist(eng);
    player_y = dist(eng);
    int x = player_x * min_div;
    int y = player_y * min_div;
    std::cout << "Player indexes: \nX: " << player_x << "\tY: " << player_y << "\n";
    std::cout << "Player coordinates:\nX: " << x << "\tY: " << y << "\n";
    plane.put(player, x, y);
}

void Game::move() {
    std::cout << "Starting movement..\n";
    while (running) {
        plane.move(player, player_x * min_div, player_y * min_div);
        player_x++;
        player_y++; 
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
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