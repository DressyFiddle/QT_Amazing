#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "form.h"
#include <QToolTip>
#include <QTabBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set widget background
    ui->widgetReal->setStyleSheet("background-color:black;");
    ui->widgetComplimentary->setStyleSheet("background-color:white;");
    // Set defaults
    ui->textRED->setText(QString("%1").arg(m_RED));
    ui->textGREEN->setText(QString("%1").arg(m_GREEN));
    ui->textBLUE->setText(QString("%1").arg(m_BLUE));
    // Bit of hardcoding, always hurts everyone :D
    ui->textSelected->setText(QString("255,255,255"));
    ui->textComplimentary->setText(QString("0,0,0"));

    tabBar = ui->tabWidget->tabBar();
    tabBar->setTabText(0,"Last actions");
    tabBar->setTabText(1,"One Lone Tab");
    tabBar->tabToolTip(1).append("I'll do something some day...");
    tabBar->tabWhatsThis(1).append("I'll do something some day...");
    // FUN...
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::receive_from_gui);
    // RGB Connection
    connect(ui->RED, &QSlider::valueChanged, this, &MainWindow::updateRedTextValue);
    connect(ui->RED, &QSlider::valueChanged, this, &MainWindow::logThis);
    connect(ui->textRED, &QTextEdit::textChanged, this, &MainWindow::updateRedSliderValue);

    connect(ui->GREEN, &QSlider::valueChanged, this, &MainWindow::updateGreenTextValue);
    connect(ui->GREEN, &QSlider::valueChanged, this, &MainWindow::logThis);
    connect(ui->textGREEN, &QTextEdit::textChanged, this, &MainWindow::updateGreenSliderValue);

    connect(ui->BLUE, &QSlider::valueChanged, this, &MainWindow::updateBlueTextValue);
    connect(ui->BLUE, &QSlider::valueChanged, this, &MainWindow::logThis);
    connect(ui->textBLUE, &QTextEdit::textChanged, this, &MainWindow::updateBlueSliderValue);

    //Add export
    connect(ui->actionExport_Log, &QAction::toggled, this, &MainWindow::openSaveWindow);

    //Add about
    connect(ui->actionAbout,&QAction::toggled,this, &MainWindow::showAbout);

    //Randomizer
    connect(ui->btn_Randomizer, &QPushButton::clicked, this, &MainWindow::randomize);

    //Freakin
    connect(ui->frekin, &QPushButton::clicked, this, &MainWindow::frekingButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receive_from_gui()
{
    counter ++;
    qDebug() << "Number of clicks" << counter;
}

void MainWindow::logThis()
{
    QTime currentTime = QTime::currentTime();
    QString formatedString = currentTime.toString("HH:mm:ss");

    QString real =  QString("%1,%2,%3").arg(m_RED).arg(m_GREEN).arg(m_BLUE);
    QString comp =  QString("%1,%2,%3").arg(255-m_RED).arg(255-m_GREEN).arg(255-m_BLUE);
    QString full = QString("LOG # time - %1 values: rgb(%2), complimentary rgb(%3)").arg(formatedString).arg(real).arg(comp);

    this->log.push_back(full);
    ui->tab_one_textBrowser->append(full);
}

void MainWindow::openSaveWindow()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save File",
                                                    QDir::homePath(),
                                                    "Text Files (*.txt);");


    if(fileName.isEmpty())
    {
        QMessageBox::warning(nullptr, "Warning", "This shouldn't be visible at all!");
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    for(QString s : log) {
        out << s << "\n";
    }

    file.close();

    QMessageBox::information(nullptr,"Non-Informational","Well now, you did your thing... HOPE YOU ARE HAPPY!");
}

void MainWindow::showAbout()
{
    Form *about = new Form();
    about->show();
}

void MainWindow::randomize()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    int m_RED = distrib(gen);
    updateRedTextValue(m_RED);
    int m_BLUE = distrib(gen);
    updateBlueTextValue(m_BLUE);
    int m_GREEN = distrib(gen);
    updateGreenTextValue(m_GREEN);
}

void MainWindow::frekingButton()
{
    QFont font = ui->frekin->font();
    font.setPointSize(font.pointSize() + 10);
    QToolTip::setFont(font);

    QPoint center = mapToGlobal(rect().center());

    QToolTip::showText(center,"TO FIGHT !",nullptr,QRect(),3000);
}

void MainWindow::updateRedTextValue(int value)
{
    ui->textRED->setText(QString("%1").arg(value));
    m_RED = value;

    QTextCursor  cursor = ui->textRED->textCursor();
    cursor.setPosition(ui->textRED->toPlainText().length(), QTextCursor::MoveAnchor);
    ui->textRED->setTextCursor(cursor);

    QString real =  QString("%1,%2,%3").arg(m_RED).arg(m_GREEN).arg(m_BLUE);
    QString comp =  QString("%1,%2,%3").arg(255-m_RED).arg(255-m_GREEN).arg(255-m_BLUE);

    QString rgb = "background-color: rgb(" + QString("%1,%2,%3").arg(m_RED).arg(m_GREEN).arg(m_BLUE) + ");";
    QString rgb_complimentary = "background-color: rgb(" + QString("%1,%2,%3").arg(255-m_RED).arg(255-m_GREEN).arg(255-m_BLUE) + ");";

    ui->widgetReal->setStyleSheet(rgb);
    ui->widgetComplimentary->setStyleSheet(rgb_complimentary);
    ui->textSelected->setText(real);
    ui->textComplimentary->setText(comp);
}

void MainWindow::updateBlueTextValue(int value)
{
    ui->textBLUE->setText(QString("%1").arg(value));
    m_BLUE = value;

    QTextCursor  cursor = ui->textBLUE->textCursor();
    cursor.setPosition(ui->textBLUE->toPlainText().length(), QTextCursor::MoveAnchor);
    ui->textBLUE->setTextCursor(cursor);

    QString real =  QString("%1,%2,%3").arg(m_RED).arg(m_GREEN).arg(m_BLUE);
    QString comp =  QString("%1,%2,%3").arg(255-m_RED).arg(255-m_GREEN).arg(255-m_BLUE);

    QString rgb = "background-color: rgb(" + real + ");";
    QString rgb_complimentary = "background-color: rgb(" + comp + ");";

    ui->widgetReal->setStyleSheet(rgb);
    ui->widgetComplimentary->setStyleSheet(rgb_complimentary);
    ui->textSelected->setText(real);
    ui->textComplimentary->setText(comp);
}

void MainWindow::updateGreenTextValue(int value)
{
    ui->textGREEN->setText(QString("%1").arg(value));
    m_GREEN = value;

    QTextCursor  cursor = ui->textGREEN->textCursor();
    cursor.setPosition(ui->textGREEN->toPlainText().length(), QTextCursor::MoveAnchor);
    ui->textGREEN->setTextCursor(cursor);

    QString real =  QString("%1,%2,%3").arg(m_RED).arg(m_GREEN).arg(m_BLUE);
    QString comp =  QString("%1,%2,%3").arg(255-m_RED).arg(255-m_GREEN).arg(255-m_BLUE);

    QString rgb = "background-color: rgb(" + real + ");";
    QString rgb_complimentary = "background-color: rgb(" + comp + ");";

    ui->widgetReal->setStyleSheet(rgb);
    ui->widgetComplimentary->setStyleSheet(rgb_complimentary);
    ui->textSelected->setText(real);
    ui->textComplimentary->setText(comp);
}

void MainWindow::updateRedSliderValue()
{
    QString str = ui->textRED->toPlainText();
    ui->RED->setValue(str.toInt());
}

void MainWindow::updateBlueSliderValue()
{
    QString str = ui->textBLUE->toPlainText();
    ui->BLUE->setValue(str.toInt());
}

void MainWindow::updateGreenSliderValue()
{
    QString str = ui->textGREEN->toPlainText();
    ui->GREEN->setValue(str.toInt());
}

