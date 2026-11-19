#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1376, 768);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setFrameShape(QFrame::NoFrame);

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    this->setFixedSize(1376, 768);

    primerNivel = new Nivel1(scene);
    primerNivel->iniciarNivel();
}

MainWindow::~MainWindow()
{
    delete primerNivel;
    delete ui;
}
