#include <QApplication>
#include <QWindow>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QDebug>
#include "engine.h"

QApplication* app_instance = nullptr;
QWidget* main_window = nullptr;
Engine* game_engine = nullptr;

int main(int argc, char *argv[]) {
    app_instance = new QApplication(argc, argv);
    main_window = new QWidget();
    main_window->setWindowTitle("Nixie's Shitty Tetris");
    main_window->resize(GRID_WIDTH * 30 + 140, GRID_HEIGHT * 30);

    /* Main window */
    QVBoxLayout* layout = new QVBoxLayout(main_window);
    layout->setContentsMargins(0, 0, 0, 0);
    main_window->setLayout(layout);

    game_engine = new Engine(main_window);
    game_engine->initialize();
    
    if (game_engine->gameWidget()) {
        layout->addWidget(game_engine->gameWidget());
        qDebug() << "Added game widget to layout";
    }

    main_window->show();

    return app_instance->exec();

}

