#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget* parent = nullptr);

protected:
    virtual void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    virtual void keyReleaseEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

signals:
    void onKeyPressEvent(QKeyEvent* event);
    void onKeyReleaseEvent(QKeyEvent* event);
};

#endif // LINEEDIT_H
