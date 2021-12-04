#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // slider max and min
    ui->horizontalSliderRed->setMinimum(0);
    ui->horizontalSliderRed->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderGreen->setMinimum(0);
    ui->horizontalSliderGreen->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderBlue->setMinimum(0);
    ui->horizontalSliderBlue->setMaximum(RGB_VALUE_MAX);

    // spinBox max and min values
    ui->spinBoxRed->setMinimum(0);
    ui->spinBoxRed->setMaximum(RGB_VALUE_MAX);

    ui->spinBoxGreen->setMinimum(0);
    ui->spinBoxGreen->setMaximum(RGB_VALUE_MAX);

    ui->spinBoxBlue->setMinimum(0);
    ui->spinBoxBlue->setMaximum(RGB_VALUE_MAX);

    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this, &MainWindow::onColorChanged);

    connect(ui->horizontalSliderRed, &QSlider::valueChanged, ui->spinBoxRed, &QSpinBox::setValue);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, ui->spinBoxGreen, &QSpinBox::setValue);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, ui->spinBoxBlue, &QSpinBox::setValue);

    onColorChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorChanged()
{
    //qDebug() << "onColorChanged";
    QColor selectedColor(ui->horizontalSliderRed->value(),
                         ui->horizontalSliderGreen->value(),
                         ui->horizontalSliderBlue->value());

    QPixmap colorMap(64, 64);
    colorMap.fill(selectedColor);
    ui->colorLabel->setPixmap(colorMap);
}
