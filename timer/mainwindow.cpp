#include "mainwindow.hh"
#include "ui_mainwindow.h"

static const int TIMER_INTERVAL_ms = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked,
            this, &MainWindow::on_start_button_clicked);

    connect(ui->stopButton, &QPushButton::clicked,
            this, &MainWindow::on_stop_button_clicked);

    connect(ui->resetButton, &QPushButton::clicked,
            this, &MainWindow::on_reset_button_clicked);

    connect(ui->closeButton, &QPushButton::clicked,
            this, &MainWindow::on_close_button_clicked);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);

    // asetetaan taustaväri

    ui->lcdNumberMin->setStyleSheet("background: #000000;");

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(1,1,1));
    ui->lcdNumberSec->setPalette(palette);
    ui->lcdNumberMin->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_button_clicked()
{
    timer->start(TIMER_INTERVAL_ms);
}

void MainWindow::on_stop_button_clicked()
{
    timer->stop();
}

void MainWindow::on_reset_button_clicked()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::on_close_button_clicked()
{
    close();
}

void MainWindow::on_timer_timeout()
{
    int current_mins = ui->lcdNumberMin->intValue();
    int current_secs = ui->lcdNumberSec->intValue();

    if (current_secs == 59) {
        ui->lcdNumberMin->display(current_mins + 1);
        ui->lcdNumberSec->display(0);
    }
    else {
        ui->lcdNumberSec->display(current_secs + 1);
    }
}
