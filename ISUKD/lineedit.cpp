#include "lineedit.h"

LineEdit::LineEdit(QWidget* parent) : QLineEdit(parent)
{

}

void LineEdit::keyPressEvent(QKeyEvent* event) {
    // Do not trigger auto-repeating events
    if (event->isAutoRepeat()) {
        return;
    }
    QLineEdit::keyPressEvent(event);
    emit onKeyPressEvent(event);
}

void LineEdit::keyReleaseEvent(QKeyEvent* event) {
    // Do not trigger auto-repeating events
    if (event->isAutoRepeat()) {
        return;
    }
    QLineEdit::keyReleaseEvent(event);
    emit onKeyReleaseEvent(event);
}
