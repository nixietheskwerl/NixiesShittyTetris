/**
 * @file gamewidget.cpp
 */

#include "gamewidget.h"
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>
#include "enums.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    /* Resize events */
    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);
    
    /* Keyboard focus */
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    
    blocksize_x = BLOCK_SIZE_X;
    blocksize_y = BLOCK_SIZE_Y;
    game_offset_x = GAME_OFFSET_X;
    game_offset_y = GAME_OFFSET_Y;
    
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    updateBlockSize();
    
    qDebug() << "GameWidget created with size:" << width() << "x" << height();
}

void GameWidget::updateBlockSize()
{
    /* Calculate block sizes maintaining aspect ratio */
    int total_grid_width = GRID_WIDTH + 1 + 4;  /* 15 units total */
    blocksize_x = width() / total_grid_width;
    blocksize_y = height() / GRID_HEIGHT;
    
    /* Use the smaller size to maintain square blocks */
    size_t block_size = std::min(blocksize_x, blocksize_y);
    blocksize_x = block_size;
    blocksize_y = block_size;
    
    /* Left padding to center the game+preview area */
    int total_pixel_width = total_grid_width * block_size;
    game_offset_x = (width() - total_pixel_width) / 2;
    game_offset_y = (height() - (GRID_HEIGHT * block_size)) / 2;
}

void GameWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBlockSize();
    qDebug() << "Resize event:" << width() << "x" << height();
    update();
}

void GameWidget::onResize()
{
    updateBlockSize();
    update(); /* Repaint */
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    qDebug() << "Paint event called, playfield:" << (_playfield ? "exists" : "null");
    qDebug() << "Widget size:" << width() << "x" << height();
    qDebug() << "Block size:" << blocksize_x << "x" << blocksize_y;
    qDebug() << "Game offset:" << game_offset_x << "," << game_offset_y;
    
    if (!_playfield) return;

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::black);
    
    /* Draw checkerboard pattern */
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if ((x + y) % 2 == 0) {
                painter.fillRect(
                    game_offset_x + x * blocksize_x,
                    game_offset_y + y * blocksize_y,
                    blocksize_x - 1,
                    blocksize_y - 1,
                    QColor(40, 40, 40)
                );
            }
        }
    }
    
    /* Draw the playfield grid and placed blocks */
    painter.setPen(Qt::darkGray);
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            
            painter.drawRect(
                game_offset_x + x * blocksize_x,
                game_offset_y + y * blocksize_y,
                blocksize_x - 1,
                blocksize_y - 1
            );
            
            /* Draw placed blocks */
            if (_playfield->get_cell(x, y)) {
                painter.fillRect(
                    game_offset_x + x * blocksize_x,
                    game_offset_y + y * blocksize_y,
                    blocksize_x - 1,
                    blocksize_y - 1,
                    Qt::blue  /* blue for placed blocks */
                );
            }
        }
    }

    /* Draw the active tetromino */
    Tetromino* active = _playfield->get_active_tetromino();
    if (active) {
        auto shape = active->get_shape(active->get_rotation());
        int tetromino_x = *active->get_x();
        int tetromino_y = *active->get_y();

        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);

        for (int row = 0; row < 4; ++row) {
            int row_data = shape[row];
            for (int col = 0; col < 4; ++col) {
                if ((row_data & (0b1000 >> col)) != 0) {
                    int draw_x = game_offset_x + (tetromino_x + col) * blocksize_x;
                    int draw_y = game_offset_y + (tetromino_y + row) * blocksize_y;
                    if (draw_x < 0) {
                        continue; /* Out of bounds */
                    }
                    painter.fillRect(
                        draw_x, 
                        draw_y,
                        blocksize_x - 1,
                        blocksize_y - 1, 
                        Qt::red
                    );
                }
            }
        }
    }
    
    /* Draw "Next" preview panel on right */
    int preview_panel_x = game_offset_x + GRID_WIDTH * blocksize_x + blocksize_x;  /* 1 block gap */
    int preview_panel_y = game_offset_y;
    int preview_size = blocksize_x * 5;  /* Show a 4x4 preview area */
    
    /* Panel background */
    painter.fillRect(preview_panel_x, preview_panel_y, preview_size, preview_size, QColor(30, 30, 30));
    
    /* Panel border */
    painter.setPen(Qt::gray);
    painter.drawRect(preview_panel_x, preview_panel_y, preview_size, preview_size);
    
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(preview_panel_x, preview_panel_y + preview_size + 10, preview_size, 20, Qt::AlignCenter, "Next");
    
    /* Draw future tetromino in the preview panel */
    Tetromino* future = _playfield->get_future_tetromino();
    if (future) {
        auto shape = future->get_shape(future->get_rotation());
        
        painter.setBrush(Qt::green);
        painter.setPen(Qt::NoPen);
        
        int preview_offset_x = preview_panel_x + blocksize_x / 2;
        int preview_offset_y = preview_panel_y + blocksize_x / 2;
        
        for (int row = 0; row < 4; ++row) {
            int row_data = shape[row];
            for (int col = 0; col < 4; ++col) {
                if ((row_data & (0b1000 >> col)) != 0) {
                    painter.fillRect(
                        preview_offset_x + col * blocksize_x,
                        preview_offset_y + row * blocksize_x,
                        blocksize_x - 1,
                        blocksize_x - 1,
                        Qt::green
                    );
                }
            }
        }
    }
}