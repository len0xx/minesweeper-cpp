#include "mainwindow.h"

int getCenteredWidgetXPos(const QWidget &widget) {
    return (widget.parentWidget()->size().width() - widget.size().width()) / 2;
}

void MainWindow::displayMenuButtons() const {
    select_difficulty_l->show();
    easy_level_btn->show();
    medium_level_btn->show();
    hard_level_btn->show();
    custom_level_btn->show();
    hideActionButtons();
    hideCaption();
}

void MainWindow::displayActionButtons() const {
    restart_btn->show();
    back_btn->show();
}

void MainWindow::displayCustomSettings() const {
    hideMenuButtons(false);
    custom_width->show();
    custom_height->show();
    custom_mines_amount->show();
    custom_width_label->show();
    custom_height_label->show();
    custom_mines_amount_label->show();
    custom_width_num->show();
    custom_height_num->show();
    custom_mines_amount_num->show();
    custom_level_create_btn->show();
    back_btn->show();
    back_btn->resize(default_button_size);
    back_btn->move(getCenteredWidgetXPos(*custom_level_create_btn), 280);
}

void MainWindow::displayCaption(const QString &text) const {
    game_caption->move(getCenteredWidgetXPos(*game_caption), 10);
    game_caption->setText(text);
    game_caption->show();
}

void MainWindow::hideMenuButtons(const bool display_action_btns = true) const {
    select_difficulty_l->hide();
    easy_level_btn->hide();
    medium_level_btn->hide();
    hard_level_btn->hide();
    custom_level_btn->hide();
    if (display_action_btns) displayActionButtons();
}

void MainWindow::hideActionButtons() const {
    restart_btn->hide();
    back_btn->hide();
}

void MainWindow::hideCustomSettings() const {
    custom_width->hide();
    custom_height->hide();
    custom_mines_amount->hide();
    custom_width_label->hide();
    custom_height_label->hide();
    custom_mines_amount_label->hide();
    custom_width_num->hide();
    custom_height_num->hide();
    custom_mines_amount_num->hide();
    custom_level_create_btn->hide();
    back_btn->hide();
    back_btn->resize(half_button_size);
}

void MainWindow::hideCaption() const {
    game_caption->hide();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      select_difficulty_l(new QLabel("Select the difficulty:", this)),
      game_caption(new QLabel("The game is over", this)),
      custom_width_label(new QLabel("Width:", this)),
      custom_height_label(new QLabel("Height:", this)),
      custom_mines_amount_label(new QLabel("Mines percentage:", this)),
      custom_width(new QSlider(Qt::Horizontal, this)),
      custom_height(new QSlider(Qt::Horizontal, this)),
      custom_mines_amount(new QSlider(Qt::Horizontal, this)),
      custom_width_num(new QLineEdit(QString::number(minimum_side_length), this)),
      custom_height_num(new QLineEdit(QString::number(minimum_side_length), this)),
      custom_mines_amount_num(new QLineEdit(QString::number(minimum_mines_percentage), this)),
      custom_level_create_btn(new QPushButton("Create custom level", this)),
      easy_level_btn(new QPushButton("Easy (9x9, 10 mines)", this)),
      medium_level_btn(new QPushButton("Medium (16x16, 40 mines)", this)),
      hard_level_btn(new QPushButton("Hard (16x30, 99 mines)", this)),
      custom_level_btn(new QPushButton("Custom settings", this)),
      restart_btn(new QPushButton("Restart", this)),
      back_btn(new QPushButton("Back to the menu", this))
{
    std::srand(std::time(nullptr));

    setWindowTitle("Minesweeper");
    setFixedSize(default_window_size);

    game_caption->resize(default_button_size);
    game_caption->setAlignment(Qt::AlignCenter);
    hideCaption();

    custom_height->resize(custom_size);
    custom_height->setMinimum(minimum_side_length);
    custom_height->setMaximum(maximum_side_length);
    custom_height_num->resize(custom_num_size);
    custom_width->resize(custom_size);
    custom_width->setMinimum(minimum_side_length);
    custom_width->setMaximum(maximum_side_length);
    custom_width_num->resize(custom_num_size);
    custom_mines_amount->resize(custom_size);
    custom_mines_amount->setMinimum(minimum_mines_percentage);
    custom_mines_amount->setMaximum(maximum_mines_percentage);
    custom_height_label->resize(custom_size);
    custom_width_label->resize(custom_size);
    custom_mines_amount_label->resize(custom_size);
    custom_mines_amount_num->resize(custom_num_size);
    custom_height_label->move(70, 70);
    custom_height->move(70, 95);
    custom_height_num->move(280, 95);
    custom_height_num->setEnabled(false);
    custom_width_label->move(70, 120);
    custom_width->move(70, 145);
    custom_width_num->move(280, 145);
    custom_width_num->setEnabled(false);
    custom_mines_amount_label->move(70, 170);
    custom_mines_amount->move(70, 195);
    custom_mines_amount_num->move(280, 195);
    custom_mines_amount_num->setEnabled(false);
    custom_level_create_btn->resize(default_button_size);
    custom_level_create_btn->move(getCenteredWidgetXPos(*custom_level_create_btn), 240);
    hideCustomSettings();

    select_difficulty_l->resize(default_button_size);
    select_difficulty_l->move(getCenteredWidgetXPos(*select_difficulty_l), 70);

    easy_level_btn->resize(default_button_size);
    easy_level_btn->move(getCenteredWidgetXPos(*easy_level_btn), 120);

    medium_level_btn->resize(default_button_size);
    medium_level_btn->move(getCenteredWidgetXPos(*medium_level_btn), 170);

    hard_level_btn->resize(default_button_size);
    hard_level_btn->move(getCenteredWidgetXPos(*hard_level_btn), 220);

    custom_level_btn->resize(default_button_size);
    custom_level_btn->move(getCenteredWidgetXPos(*custom_level_btn), 270);

    restart_btn->resize(half_button_size);

    back_btn->resize(half_button_size);

    hideActionButtons();

    QObject::connect(custom_height, &QSlider::valueChanged, this, &MainWindow::updateNumericHeightVal);

    QObject::connect(custom_width, &QSlider::valueChanged, this, &MainWindow::updateNumericWidthVal);

    QObject::connect(custom_mines_amount, &QSlider::valueChanged, this, &MainWindow::updateNumericMinesVal);

    QObject::connect(easy_level_btn, &QPushButton::clicked, this, [this](){
        hideMenuButtons();

        createGameGrid(QSize(9, 9), 10, QSize(400, 460));
    });

    QObject::connect(medium_level_btn, &QPushButton::clicked, this, [this](){
        hideMenuButtons();

        createGameGrid(QSize(16, 16), 40, QSize(600, 670));
    });

    QObject::connect(hard_level_btn, &QPushButton::clicked, this, [this](){
        hideMenuButtons();

        createGameGrid(QSize(30, 16), 99, QSize(1100, 670));
    });

    QObject::connect(restart_btn, &QPushButton::clicked, this, &MainWindow::restart);

    QObject::connect(back_btn, &QPushButton::clicked, this, &MainWindow::goToMainMenu);

    QObject::connect(custom_level_btn, &QPushButton::clicked, this, &MainWindow::displayCustomSettings);

    QObject::connect(custom_level_create_btn, &QPushButton::clicked, this, [this](){
        hideMenuButtons();
        hideCustomSettings();

        initCustom();
    });
}

void MainWindow::updateNumericSliderVal(const QSlider &slider, QLineEdit &edit) const {
    edit.setText(QString::number(slider.value()));
}

void MainWindow::updateNumericHeightVal() const {
    updateNumericSliderVal(*custom_height, *custom_height_num);
}

void MainWindow::updateNumericWidthVal() const {
    updateNumericSliderVal(*custom_width, *custom_width_num);
}

void MainWindow::updateNumericMinesVal() const {
    updateNumericSliderVal(*custom_mines_amount, *custom_mines_amount_num);
}

void MainWindow::openNeighbours(const QPoint &pos) {
    for (auto n: grid.getNeighbours(pos)) {
        if (!(grid.getCell(n)->hasMine) && (grid.getCell(n)->marker == Cell::Flagged::NO_FLAG))
            openCell(n, grid.countNeighboursMines(n) == 0);
    }
}

void MainWindow::openCell(const QPoint &pos, const bool recursively = true) {
    if (!grid.getCell(pos)->opened) {
        size_t mines_around = grid.countNeighboursMines(pos);

        if (grid.getCell(pos)->hasMine) {
            game_state = OVER;
            displayCaption("Game is over!");
            grid.getCell(pos)->open();
            grid.openAllMines();
        }
        else {
            grid.getCell(pos)->open(QString::number(mines_around));
            if (recursively) openNeighbours(pos);
        }
        checkForWinning();
    }
}

void MainWindow::createGameGrid(const QSize &the_grid_size, const size_t mines_am, const QSize &window_size) {
    game_state = INACTIVE;
    init(the_grid_size, mines_am);
    setFixedSize(window_size);

    const size_t top_edge = 60;
    const size_t left_edge = (size().width() - (Cell::size.width() * grid.getWidth() + Grid::padding * (grid.getHeight() - 1))) / 2;

    for (int i = 0; i < grid.getWidth(); i++) {
        for (int j = 0; j < grid.getHeight(); j++) {
            QPoint btn_pos(i, j);
            Cell *current_cell = new Cell("", this);
            current_cell->move(left_edge + i * (Cell::size.width() + Grid::padding), top_edge + j * (Cell::size.height() + Grid::padding));
            current_cell->show();
            grid.appointButton(current_cell, btn_pos);
            QObject::connect(current_cell, &Cell::clicked, this, [this, btn_pos](){
                handleLeftClick(btn_pos);
            });
            QObject::connect(current_cell, &Cell::rightClicked, this, [this, btn_pos](){
                handleRightClick(btn_pos);
            });
            QObject::connect(current_cell, &Cell::doubleClicked, this, [this, btn_pos](){
                handleDoubleClick(btn_pos);
            });
            QObject::connect(current_cell, &Cell::bothClicked, this, [this, btn_pos](){
                handleDoubleClick(btn_pos);
            });
        }
    }

    displayActionButtons();
    restart_btn->move(getCenteredWidgetXPos(*restart_btn) - 80, window_size.height() - 70);
    back_btn->move(getCenteredWidgetXPos(*back_btn) + 80, window_size.height() - 70);
}

void MainWindow::goToMainMenu() {
    setFixedSize(default_window_size);
    hideCustomSettings();
    displayMenuButtons();
    grid.unset();
}

void MainWindow::restart() {
    grid.clearMines();
    grid.reset();
    grid.closeAllCells();
    game_state = INACTIVE;
    hideCaption();
    restart_btn->setEnabled(false);
}

void MainWindow::init(const QSize &size, const size_t mines_am) {
    grid = Grid(size, mines_am);
    restart_btn->setEnabled(false);
}

void MainWindow::initCustom() {
    qDebug() << "Custom width: " << custom_width->value();
    qDebug() << "Custom height: " << custom_height->value();
    qDebug() << "Custom mines percentage: " << static_cast<double>(custom_mines_amount->value()) / 100;
    size_t custom_mines_amount_n = static_cast<double>(custom_mines_amount->value()) / 100 * custom_width->value() * custom_height->value();
    qDebug() << "Custom mines amount: " << custom_mines_amount_n;
    auto window_size = QSize(custom_width->value() * (Cell::size.width() + Grid::padding) + 100, custom_height->value() * (Cell::size.height() + Grid::padding) + 140);
    createGameGrid(QSize(custom_width->value(), custom_height->value()), custom_mines_amount_n, window_size);
}

void MainWindow::handleLeftClick(const QPoint &pos) {
    if (game_state != OVER) {
        if (game_state == INACTIVE) {
            game_state = ACTIVE;
            grid.seed(pos);
            openCell(pos);
            restart_btn->setEnabled(true);
        }
        else {
            openCell(pos, grid.countNeighboursMines(pos) == 0);
        }
    }
}

void MainWindow::handleRightClick(const QPoint &pos) {
    if (game_state == INACTIVE) {
        return;
    }
    if (game_state == OVER) {
        return handleLeftClick(pos);
    }
    if (!grid.getCell(pos)->opened) {
        grid.changeMarker(pos);
        checkForWinning();
    }
}

void MainWindow::checkForWinning() {
    if (grid.isWinningSituation()) {
        game_state = OVER;
        displayCaption("You won!");
    }
}

void MainWindow::handleDoubleClick(const QPoint &pos) {
    uint8_t mines_around = grid.countNeighboursMines(pos);
    if (mines_around > 0) {
        uint8_t marked_cells = 0;
        uint8_t marked_question_cells = 0;
        auto neighbours = grid.getNeighbours(pos);
        for (auto n: neighbours) {
            if (grid.getCell(n)->marker == Cell::Flagged::POTENTIAL_MINE) {
                marked_cells++;
            }
            else if (grid.getCell(n)->marker == Cell::Flagged::POSSIBLE_MINE) {
                marked_question_cells++;
            }
        }
        if (mines_around == marked_cells && marked_question_cells == 0) {
            for (auto n: neighbours) {
                if (grid.getCell(n)->marker == Cell::Flagged::NO_FLAG) {
                    openCell(n, grid.countNeighboursMines(n) == 0);
                }
            }
        }
    }
}

MainWindow::~MainWindow() { }
