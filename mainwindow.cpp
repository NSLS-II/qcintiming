#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timingwidget.h"
#include <QFileDialog>
#include "timingdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timing = new TimingWidget(this);
    timing->move(20,40);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Timing_File_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this, 
      tr("Open Timing File"), "", tr("Timing Files (*.txt)"));
 
  TimingData data;
  data.readFromFile(filename.toStdString());
  timing->setTimingData(data);
}



void MainWindow::on_actionSave_Timing_File_triggered()
{
  QString filename = QFileDialog::getSaveFileName(this, 
      tr("Save Timing File"), "", tr("Timing Files (*.txt)"));

  timing->getTimingData().writeToFile(filename.toStdString());
}
