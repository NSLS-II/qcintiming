#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timingwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "timingdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(925,800);

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

  if(!filename.isNull())
  {
    TimingData data;
    if(data.readFromFile(filename.toStdString()) == false)
    {
      // Error reading file
      QMessageBox msgBox(this);
      msgBox.setText(tr("Unable to read timing file due to error in format"));
      msgBox.setDetailedText(QString::fromStdString(data.getErrorMessage()));
      msgBox.setWindowTitle(this->windowTitle());
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
    timing->setTimingData(data);
  }
}



void MainWindow::on_actionSave_Timing_File_triggered()
{
  QString filename = QFileDialog::getSaveFileName(this, 
      tr("Save Timing File"), "", tr("Timing Files (*.txt)"));

  if(!filename.isNull()){
    timing->getTimingData().writeToFile(filename.toStdString());
  }
}

void MainWindow::on_actionAbout_triggered()
{
  QMessageBox::about(this, this->windowTitle(),
      tr("Written by Stuart B. Wilkins"));
}
