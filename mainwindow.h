#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void randomize();
    void frekingButton();

signals:
    void transmit_to_object(bool);

private slots:
    void receive_from_gui();
    void logThis();
    void openSaveWindow();
    void showAbout();

    void updateRedTextValue(int value);
    void updateBlueTextValue(int value);
    void updateGreenTextValue(int value);
    void updateRedSliderValue();
    void updateBlueSliderValue();
    void updateGreenSliderValue();

private:
    Ui::MainWindow *ui;
    QTabBar *tabBar;
    std::vector<QString> log;
    int counter = 0;
    int m_RED = 0;
    int m_BLUE = 0;
    int m_GREEN = 0;
};
#endif // MAINWINDOW_H
