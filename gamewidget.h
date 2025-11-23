#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "playfield.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void setPlayfield(Playfield* playfield) { _playfield = playfield; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Playfield* _playfield = nullptr;
    size_t blocksize_x;
    size_t blocksize_y;
    size_t game_offset_x;
    size_t game_offset_y;
    void updateBlockSize();

public slots:
    void onResize();
};

#endif /* GAMEWIDGET_H */