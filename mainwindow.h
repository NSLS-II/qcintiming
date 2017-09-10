#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <timingwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_Timing_File_triggered();

    void on_actionSave_Timing_File_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    TimingWidget *timing;
};

#endif // MAINWINDOW_H
