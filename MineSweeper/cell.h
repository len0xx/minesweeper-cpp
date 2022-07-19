#include <QtWidgets>

#ifndef CELL_HPP
#define CELL_HPP

const QColor LIGHT_GRAY = QColor(216, 216, 216, 1);
const QColor DARK_GRAY = QColor(160, 160, 160, 1);
const QColor RED = Qt::red;

class Cell : public QPushButton {
    Q_OBJECT
public:
    enum Flagged {
        NO_FLAG,
        POSSIBLE_MINE,
        POTENTIAL_MINE
    };

    Flagged marker = NO_FLAG;
    bool hasMine = false;
    bool opened = false;
    QPalette palette;

    static constexpr auto size = QSize(30, 30);

    void setColor(const QColor &color);

    explicit Cell(const QString &text, QWidget *parent);

    explicit Cell(QWidget *parent);

    void open();

    void open(const QString &val);

    void close();

    Flagged setNextClosedState();

    virtual ~Cell() {}

private:
    bool left_clicked = false;
    bool right_clicked = false;

    enum ButtonState {
        OPENED,
        CLOSED
    };

    void setState(const ButtonState &state, const QString &val);

private slots:
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void mouseDoubleClickEvent(QMouseEvent *e);

signals:
    void rightClicked();

    void doubleClicked();

    void bothClicked();
};

#endif // CELL_HPP
