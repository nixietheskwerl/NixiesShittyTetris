/**
 * @file engine.cpp
 */

#include "engine.h"
#include <QEvent>
#include <QDebug>
#include <Qt>  /* For key constants */

Engine::Engine(QWidget *parent)
    : QObject(parent)
{
    _game_widget = new GameWidget(parent);
    _game_widget->setGeometry(0, 0, parent->width(), parent->height());
    _game_widget->show();  /* Make sure widget is visible */
    _game_widget->installEventFilter(this);
}

Engine::~Engine()
{
    if (_drop_timer) {
        _drop_timer->stop();
        delete _drop_timer;
        _drop_timer = nullptr;
    }
    if (_playfield) {
        delete _playfield;
        _playfield = nullptr;
    }
}

void Engine::initialize()
{
    message_box = new QMessageBox();
    message_box->setMinimumSize(400, 300);
    message_box->setWindowTitle("Game Over");
    message_box->setText("Game Over!");
    message_box->hide();
    
    _playfield = new Playfield();
    _playfield->initialize();
    _playfield->place_tetromino();

    _game_widget->setPlayfield(_playfield);

    _drop_timer = new QTimer(this);
    _drop_timer->setInterval(1000); /* Set drop interval to 1 second */
    connect(_drop_timer, &QTimer::timeout, this, [this]() {
        if (drop_tetromino()) {
            _game_widget->update();
        }
    });

    _drop_timer->start();
    game_state = STATE_PLAYING;
}

bool Engine::drop_tetromino()
{
    if (!_playfield || !_playfield->is_initialized()) {
        return false;
    }

    Tetromino* active = _playfield->get_active_tetromino();
    if (!active) return false;

    /* Check for collisions with pieces below, or the floor */
    if (_playfield->check_collision(*active, Direction::DOWN)) {
        if (!_playfield->place_tetromino()) {
            /* Game over */
            if (_drop_timer) _drop_timer->stop();
            game_state = STATE_GAMEOVER;
            message_box->show();    
            qDebug() << "Game Over!";
        }
        return false;
    } else {
        /* No collision, move piece down */
        int current_y = *active->get_y();
        active->set_y(current_y + 1);
        return true;
    }
}

bool Engine::eventFilter(QObject* obj, QEvent* event)
{
    /* Only handle key events coming from the game widget */
    if (obj == _game_widget && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        qDebug() << "Key press event received:" << keyEvent->key();
        handleKeyPress(keyEvent);
        return true; /* event handled */
    }
    /* Event processing */
    return QObject::eventFilter(obj, event);
}

void Engine::handleKeyPress(QKeyEvent* event)
{
    if (game_state != STATE_PLAYING) {
        qDebug() << "Game not in playing state, ignoring key press";
        return;
    }

    qDebug() << "Handling key press in Engine:" << event->key();
    if (!_playfield) {
        qDebug() << "No playfield";
        return;
    }
    Tetromino* active = _playfield->get_active_tetromino();
    if (!active) {
        qDebug() << "No active tetromino";
        return;
    }

    int x = *active->get_x();
    int y = *active->get_y();
    bool moved = false;

    qDebug() << "Current tetromino position:" << x << "," << y;

    switch (event->key()) {
        case Qt::Key_Left:
            if (!_playfield->check_collision(*active, Direction::LEFT)) {
                active->set_x(x - 1);
                moved = true;
                qDebug() << "Moving left to" << (x - 1);
            }
            break;

        case Qt::Key_Right:
            if (!_playfield->check_collision(*active, Direction::RIGHT)) {
                active->set_x(x + 1);
                moved = true;
                qDebug() << "Moving right to" << (x + 1);
            }
            break;

        case Qt::Key_Down:
            if (!_playfield->check_collision(*active, Direction::DOWN)) {
                active->set_y(y + 1);
                moved = true;
                qDebug() << "Moving down to" << (y + 1);
            } else {
                /* if collision on down, lock piece */
                if (_playfield->place_tetromino()) {
                    moved = true;
                    qDebug() << "Piece locked, placing new piece";
                } else {
                    qDebug() << "Game over - can't place new piece";
                    _drop_timer->stop();
                    game_state = STATE_GAMEOVER;
                    message_box->show();
                }
            }
            break;

        case Qt::Key_Up:
            if (!_playfield->check_collision(*active, Direction::ROTATION_RIGHT)) {
                active->rotate_right();
                moved = true;
                qDebug() << "Rotating right";
            }
            break;

        case Qt::Key_Z:
            if (!_playfield->check_collision(*active, Direction::ROTATION_LEFT)) {
                active->rotate_left();
                moved = true;
                qDebug() << "Rotating left";
            }
            break;
        case Qt::Key_Space:
            initialize();
            moved = true;
            qDebug() << "Game initialized";
        default:
            qDebug() << "Unhandled key:" << event->key();
            break;
    }
    
    if (moved) {
        qDebug() << "Tetromino moved, updating display";
        _game_widget->update();
    }
}

