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
#include "sprite.cpp"

class Game: public Gtk::Window {
    public:
        Game();
        virtual ~Game();
    private:
        int min_div;
        bool running = false;
        const int WIDTH = 500;
        const int HEIGHT = 500;
        const int obstacle_count = 100;
        const static int resolution = 100;
        Sprite *matrix[resolution][resolution];

        std::random_device rd;
        std::mt19937 eng;
        std::uniform_int_distribution<> dist;
    
        Gtk::Fixed plane;

        Sprite player;
        Sprite target;
        
        void init();
        void move();
        void startThread();
        void placePlayer();
        void generateObstacles();
        Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};
 
Game::Game(): eng(rd()), dist(0, resolution) {
    player.img = Gtk::Image(load_image("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/cat.png", 20, 20));
    target.img = Gtk::Image(load_image("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/target.png", 20, 20));
    add(plane);
    set_size_request(WIDTH, HEIGHT);
    set_title("Pathfinding Game");
    show_all_children();
    init();
    placePlayer();
    generateObstacles();
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
    //Índices del jugador en la matriz
    player.set_matrix_coords(dist(eng), dist(eng));
    player.set_gui_coords(min_div);

    std::cout << "Player coordinates:\nX: " << player.matrix_x << "\tY: " << player.matrix_y << "\n";
    plane.put(player.img, player.gui_x, player.gui_y);

    target.set_matrix_coords(dist(eng), dist(eng));
    target.set_gui_coords(min_div);
    plane.put(target.img, target.gui_x, target.gui_y);
    std::cout << "Target coordinates:\nX: " << target.matrix_x << "\tY: " << target.matrix_y << "\n";
}

void Game::move() {
    std::cout << "Starting movement..\n";

    bool up;
    bool left;

    if (target.matrix_x < player.matrix_x) {
        left = true;
    } else {
        left = false;
    }

    if (target.matrix_y < player.matrix_y) {
        up = false;
    } else {
        up = true;
    }

    while (running) {

        plane.move(player.img, player.gui_x, player.gui_y);
        player.move(player.matrix_x + 1, player.matrix_y + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
}

void Game::generateObstacles() {
    std::cout << "Generating Sprites..\n";
    for (int i=0; i < obstacle_count; i++) {
        std::cout << "Sprite " << i << "\n";
        Sprite *obs = new Sprite();
        obs->img = Gtk::Image(load_image("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/obstacle.png", 20, 20));
        obs->set_matrix_coords(dist(eng), dist(eng));
        obs->set_gui_coords(min_div);
        plane.put(obs->img, obs->gui_x, obs->gui_y);
        matrix[obs->matrix_x][obs->matrix_y] = obs;
    }
    plane.show_all_children();
}

Glib::RefPtr<Gdk::Pixbuf> Game::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.tec.pathfinding");
    Game game;
    return app->run(game);
}