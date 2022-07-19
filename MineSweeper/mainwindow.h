#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <QDebug>
#include "grid.h"

int getCenteredWidgetXPos(const QWidget &widget);

class MainWindow : public QMainWindow {
    Q_OBJECT

enum GameState {
    INACTIVE,
    ACTIVE,
    OVER
};

private:
    Grid grid;
    GameState game_state = INACTIVE;
    static constexpr auto default_window_size = QSize(400, 400);
    static constexpr auto default_button_size = QSize(300, 32);
    static constexpr auto half_button_size = QSize(150, 32);
    static constexpr auto custom_size = QSize(200, 24);
    static constexpr auto custom_num_size = QSize(40, 24);

    static constexpr uint8_t minimum_mines_percentage = 20;
    static constexpr uint8_t maximum_mines_percentage = 60;
    static constexpr uint8_t minimum_side_length = 8;
    static constexpr uint8_t maximum_side_length = 22;

    QLabel *select_difficulty_l = nullptr;
    QLabel *game_caption = nullptr;
    QLabel *custom_width_label = nullptr;
    QLabel *custom_height_label = nullptr;
    QLabel *custom_mines_amount_label = nullptr;

    QSlider *custom_width = nullptr;
    QSlider *custom_height = nullptr;
    QSlider *custom_mines_amount = nullptr;

    QLineEdit *custom_width_num = nullptr;
    QLineEdit *custom_height_num = nullptr;
    QLineEdit *custom_mines_amount_num = nullptr;

    QPushButton *custom_level_create_btn = nullptr;
    QPushButton *easy_level_btn = nullptr;
    QPushButton *medium_level_btn = nullptr;
    QPushButton *hard_level_btn = nullptr;
    QPushButton *custom_level_btn = nullptr;
    QPushButton *restart_btn = nullptr;
    QPushButton *back_btn = nullptr;

    void openCell(const QPoint &pos, const bool recursively);

    void openNeighbours(const QPoint &pos);

    void createGameGrid(const QSize &the_grid_size, const size_t mines_am, const QSize &window_size);

    void displayMenuButtons() const;

    void displayActionButtons() const;

    void displayCustomSettings() const;

    void displayCaption(const QString &text) const;

    void hideMenuButtons(const bool display_action_btns) const;

    void hideActionButtons() const;

    void hideCustomSettings() const;

    void hideCaption() const;

    void updateNumericSliderVal(const QSlider &slider, QLineEdit &edit) const;

    void updateNumericHeightVal() const;

    void updateNumericWidthVal() const;

    void updateNumericMinesVal() const;

    void init(const QSize &size, const size_t mines_am);

    void goToMainMenu();

    void restart();

    void checkForWinning();

    void initCustom();

    void handleLeftClick(const QPoint &pos);

    void handleRightClick(const QPoint &pos);

    void handleDoubleClick(const QPoint &pos);

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
};
#endif // MAINWINDOW_H
