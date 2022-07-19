#include "grid.h"

int rand_num(int min, int max) {
    return arc4random() % (max - min) + min;
}

QPoint rand_point(int max_x, int max_y) {
    int x = rand_num(0, max_x);
    int y = rand_num(0, max_y);
    return QPoint(x, y);
}

Grid::Grid() {}

Grid::Grid(const QSize &_size, const size_t mines)
    : mines_amount(mines), size(_size)
{
    matrix.clear();
    matrix.resize(size.width());
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].resize(size.height());
    }
    reset();
}

void Grid::reset() {
    mines_marked = 0;
    closed_cells = size.width() * size.height();
}

void Grid::unset() {
    reset();
    size = QSize(0, 0);
    mines_amount = 0;
    deletePointers();
    matrix.clear();
}

Cell *Grid::getCell(const QPoint &pos) const {
    return matrix[pos.x()][pos.y()];
}

size_t Grid::getMines() const {
    return mines_amount;
}

void Grid::changeMarker(const QPoint &pos) {
    auto prev_state = matrix[pos.x()][pos.y()]->marker;
    auto new_state = matrix[pos.x()][pos.y()]->setNextClosedState();

    if (new_state == Cell::Flagged::POTENTIAL_MINE) {
        mines_marked++;
    } else if (prev_state == Cell::Flagged::POTENTIAL_MINE) {
        mines_marked--;
    }
}

bool Grid::isWinningSituation() const {
    return (mines_marked == mines_amount && closed_cells == mines_amount);
}

void Grid::appointButton(Cell *btn_p, const QPoint &pos) {
    matrix[pos.x()][pos.y()] = btn_p;
}

std::vector<QPoint> Grid::getNeighbours(const QPoint &pos) const {
    std::vector<QPoint> neighbours;

    if (pos.x() > 0) {
        neighbours.push_back(QPoint(pos.x() - 1, pos.y()));
        if (pos.y() > 0) neighbours.push_back(QPoint(pos.x() - 1, pos.y() - 1));
        if (pos.y() < (size.height() - 1))neighbours.push_back(QPoint(pos.x() - 1, pos.y() + 1));
    }

    if (pos.x() < (size.width() - 1)) {
        neighbours.push_back(QPoint(pos.x() + 1, pos.y()));
        if (pos.y() > 0) neighbours.push_back(QPoint(pos.x() + 1, pos.y() - 1));
        if (pos.y() < (size.height() - 1)) neighbours.push_back(QPoint(pos.x() + 1, pos.y() + 1));
    }

    if (pos.y() > 0) neighbours.push_back(QPoint(pos.x(), pos.y() - 1));
    if (pos.y() < (size.height() - 1))neighbours.push_back(QPoint(pos.x(), pos.y() + 1));

    return neighbours;
}

std::vector<QPoint> Grid::getPossiblePositions(const std::vector<QPoint> &exceptions) const {
    std::vector<QPoint> points;
    points.reserve(size.width() * size.height());

    for (int i = 0; i < size.width(); i++) {
        for (int j = 0; j < size.height(); j++) {
            bool flag = false;
            for (auto except: exceptions) {
                if ((QPoint(i, j) == except))
                    flag = true;
            }
            if (!flag)
                points.push_back(QPoint(i, j));
        }
    }

    return points;
}

size_t Grid::countNeighboursMines(const QPoint &pos) const {
    size_t counter = 0;
    for (auto n: getNeighbours(pos)) {
        if (matrix[n.x()][n.y()]->hasMine)
            counter++;
    }
    return counter;
}

int Grid::getWidth() const {
    return size.width();
}

int Grid::getHeight() const {
    return size.height();
}

void Grid::deletePointers() {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != nullptr)
                matrix[i][j]->deleteLater();
        }
    }
}

void Grid::clearMines() {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            matrix[i][j]->hasMine = false;
        }
    }
}

void Grid::seed(const QPoint &pos) const {
    std::vector exceptions{pos};
    auto neighbours = getNeighbours(pos);
    for (auto n: neighbours)
        exceptions.push_back(n);
    auto points = getPossiblePositions(exceptions);

    qDebug() << "Clicked at" << pos.x() << pos.y();
    for (size_t k = 0; k < mines_amount; k++) {
        int num = rand_num(0, points.size());

        QPoint p = points[num];
        qDebug() << p.x() << p.y();
        matrix[p.x()][p.y()]->hasMine = true;
        points.erase(points.begin() + num);
    }
}

void Grid::openCell(const QPoint &pos) {
    matrix[pos.x()][pos.y()]->open();
    closed_cells--;
    if (matrix[pos.x()][pos.y()]->marker == Cell::Flagged::POTENTIAL_MINE) {
        mines_marked--;
    }
    qDebug() << "Mines marked:" << mines_marked;
    qDebug() << "Closed cells:" << closed_cells;
}

void Grid::closeAllCells() const {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            matrix[i][j]->close();
        }
    }
}

void Grid::openAllMines() const {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j]->hasMine) matrix[i][j]->open();
        }
    }
}

Grid::~Grid() {
    deletePointers();
}
