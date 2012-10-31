#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include "defines.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myField = new Field;
    ui->setupUi(this);
    settingsDialog = new ConnectionInfoDialog(this);
    client = new net(settingsDialog, myField, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settingsDialog;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    const int deltaY = this->centralWidget()->y();
    QPainter painter(this);
    painter.drawImage(0,deltaY,QImage(":/field.png"));
    painter.drawImage(0,deltaY,cellsImage());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (client->getState() == ST_MAKING_STEP)
        if (event->button() == Qt::LeftButton)
        {
            handleMouseCoord(event->pos());
            this->update();
        }
}

void MainWindow::handleMouseCoord(const QPoint &point)
{
    int x = point.x()/(FIELD_HEIGHT/FIELD_NUM_CELLS); //переводим координаты в €чейки пол€
    int y = (point.y()- this->centralWidget()->y())/(FIELD_WIDTH/FIELD_NUM_CELLS);
    if (myField->getField(x, y) == CL_CLEAR)
        if (client->getSymbol() == SM_X)
        {
            myField->setField(x, y, CL_X);
            QString step;
            step = QString("step:%1:%2").arg(x).arg(y);
            client->getSocket()->write(step.toLocal8Bit());
        }
        else
        {
            myField->setField(x, y, CL_O);
            QString step;
            step = QString("step:%1:%2").arg(x).arg(y);
            client->getSocket()->write(step.toLocal8Bit());
        }
}

QImage MainWindow::cellsImage()
{
    QImage image(FIELD_WIDTH, FIELD_HEIGHT, QImage::Format_ARGB32);
    QPainter imagePainter(&image);

    int cfx = FIELD_WIDTH/15;
    int cfy = FIELD_HEIGHT/15;
    for(int i=0; i<15; i++)
        for (int j=0; j<15; j++)
        {
            switch (myField->getField(i, j))
            {
            case CL_CLEAR:
                break;
            case CL_X:
                imagePainter.drawImage(i*cfx, j*cfy, QImage(":/X.png"));
                break;
            case CL_O:
                imagePainter.drawImage(i*cfx, j*cfy, QImage(":/O.png"));
                break;
            default:
                break;
            }
        }
    return image;
}

void MainWindow::on_action_triggered()
{
    client->newCon();
}


void MainWindow::on_action_3_triggered()
{
    close();
}

void MainWindow::on_action_2_activated()
{
   // settingsDialog->setModal( true );
    if( settingsDialog->exec() != QDialog::Accepted )
        return;
    this->update();
}

Field* MainWindow::getField()
{
    return myField;
}
