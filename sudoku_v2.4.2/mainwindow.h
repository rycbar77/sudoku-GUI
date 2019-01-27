#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Starttimer();

    void Resettimer();

    void Stoptimer();
private slots:
    void on_pushbutton_1_clicked();

    void on_pushbutton_2_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushbutton_3_clicked();

    void Time();
private:
    Ui::MainWindow *ui;
    int hour;           //Hour
    int minute;         //Minute
    int second;         //Second
    int count;
    QTimer *Timer;
    void Display(QString,QString,QString);
    void SetLength(QString *str);
};

#endif // MAINWINDOW_H
