#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <vector>
#include <cstdlib>
#include <ctime>

int rand_num(int min, int max);

QPoint rand_point(int max_x, int max_y);

typedef std::vector<std::vector<Cell *>> Matrix;

class Grid {
private:
    size_t mines_amount {};
    size_t mines_marked {};
    size_t closed_cells {};
    QSize size;

    void deletePointers();

public:
    static const uint8_t padding = 2;
    Matrix matrix;

    Grid();

    Grid(const QSize &_size, const size_t mines);

    void reset();

    void unset();

    void clearMines();

    Cell *getCell(const QPoint &pos) const;

    size_t getMines() const;

    int getWidth() const;

    int getHeight() const;

    void openCell(const QPoint &pos);

    void changeMarker(const QPoint &pos);

    bool isWinningSituation() const;

    void appointButton(Cell *btn_p, const QPoint &pos);

    std::vector<QPoint> getNeighbours(const QPoint &pos) const;

    std::vector<QPoint> getPossiblePositions(const std::vector<QPoint> &exceptions) const;

    size_t countNeighboursMines(const QPoint &pos) const;

    void seed(const QPoint &pos) const;

    void openAllMines() const;

    void closeAllCells() const;

    ~Grid();
};

#endif // GRID_H
