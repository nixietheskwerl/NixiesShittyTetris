/**
 * @file engine.h
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <cstdint>
#include "playfield.h"
#include "tetromino.h"
#include "enums.h"
#include "gamewidget.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QWidget *window = nullptr);
    ~Engine();
    void initialize();
    GameWidget* gameWidget() const { return _game_widget; }

public slots:
    void handleKeyPress(QKeyEvent* event);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Playfield *_playfield = nullptr;
    QTimer *_drop_timer = nullptr;
    QMessageBox* message_box = nullptr;
    GameWidget *_game_widget = nullptr;
    bool drop_tetromino();
    int game_state = STATE_INIT;
};
#endif /* ENGINE_H */