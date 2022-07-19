#include "cell.h"

void Cell::setState(const ButtonState &state, const QString &val = "") {
    if (val.length() > 1) {
        qDebug() << "Error: The text is too long for this kind of button";
        return;
    }

    QString textVal = "";
    if (val != "0") textVal = val;

    if (state == OPENED) {
        marker = NO_FLAG;
        opened = true;
        setColor(hasMine ? RED : LIGHT_GRAY);
        setText(hasMine ? "💣" : textVal);
    }
    else {
        opened = false;
        setColor(DARK_GRAY);
        setText(textVal);
    }
}

void Cell::open() {
    setState(OPENED, "0");
}

void Cell::open(const QString &val) {
    setState(OPENED, val);
}

void Cell::close() {
    marker = NO_FLAG;
    setState(CLOSED, "0");
}

Cell::Flagged Cell::setNextClosedState() {
    if (text() == "⚑") {
        marker = POSSIBLE_MINE;
        setState(CLOSED, "?");
    }
    else if (text() == "?") {
        marker = NO_FLAG;
        setState(CLOSED, "0");
    }
    else {
        marker = POTENTIAL_MINE;
        setState(CLOSED, "⚑");
    }
    return marker;
}

Cell::Cell(const QString &text, QWidget *parent = nullptr) : QPushButton(text, parent) {
    close();
    resize(size);
}

Cell::Cell(QWidget *parent) : QPushButton(parent) { }

void Cell::setColor(const QColor &color) {
    setStyleSheet(QString("background-color: ") + color.name() + QString(";") + QString(" color: black;"));
    palette.setColor(QPalette::Button, color);
    setAutoFillBackground(true);
    setPalette(palette);
    update();
}

void Cell::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        left_clicked = true;
        emit clicked();
    }
    else if (e->button() == Qt::RightButton) {
        right_clicked = true;
        emit rightClicked();
    }
    if (left_clicked && right_clicked) {
        emit bothClicked();
    }
}

void Cell::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        left_clicked = false;
    }
    else if (e->button() == Qt::RightButton) {
        right_clicked = false;
    }
}

void Cell::mouseDoubleClickEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton)
        emit doubleClicked();
}
