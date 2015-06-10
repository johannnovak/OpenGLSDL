#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Game.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QResizeEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addOpenGlWidget(Game *_openGLWidget);
    void closeEvent(QCloseEvent* _event);
    void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow *m_ui;
    Game* m_game;
};

#endif // MAINWINDOW_H
