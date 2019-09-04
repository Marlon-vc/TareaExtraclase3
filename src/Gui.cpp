#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/fixed.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>
#include <thread>
#include <iostream>

typedef void *(*THREADFUNCPTR)(void *);

class Game: public Gtk::Window {
    public:
        Game();
        virtual ~Game();
    private:
        Gtk::Button button1;
        Gtk::Box container;
        Gtk::Fixed plane;
        Gtk::Image cat;

        void move();
        void startThread();
};

Game::Game(): button1("start"), container(Gtk::ORIENTATION_VERTICAL){

    // container.put();
    // container.move();

    Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_file("/home/marlon/TEC/II Semestre 2019/Datos II/TareaExtraclase3/res/cat.png", 20, 20);
    cat = Gtk::Image(pix);

    plane.put(cat, 250, 150);
    plane.show_all_children();

    button1.signal_clicked().connect(sigc::mem_fun(*this, &Game::startThread));

    container.add(plane);
    container.add(button1);
    add(container);

    set_size_request(500, 500);
    set_title("Pathfinding Game");
    show_all_children();
    
}

Game::~Game() {

}
void Game::startThread() {
    // pthread_t thread;
    // int rc;
    // rc = pthread_create(&thread, NULL, (THREADFUNCPTR) &Game::move, this);
    // if (rc) {
    //     std::cout << "Unable to start thread..\n";
    // }
    std::thread my_thread(move);
    
}

void Game::move() {
    std::cout << "Moving\n";
    int x = 0;
    int y = 0;
    while (true) {
        plane.move(cat, x, y);
        x++;
        y++;
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.tec.pathfinding");
    Game game;
    return app->run(game);
}