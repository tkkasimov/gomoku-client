#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include <QPoint>
#include <QImage>
#include "ConnectionInfoDialog.h"
#include "net.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Field* getField();

private:
    void handleMouseCoord(const QPoint &point);
    QImage cellsImage();
    
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_action_triggered();

    void on_action_3_triggered();

    void on_action_2_activated();

    void on_updateState();

private:
    Ui::MainWindow *ui;
    ConnectionInfoDialog *settingsDialog;
    net *client;
    Field *myField;
};

#endif // MAINWINDOW_H
