#include "form.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QUrl>

Form::Form(QDialog *parent)
    : QDialog(parent)
{
    setWindowTitle("About This");

    QLabel *titleLabel = new QLabel("<h3>Well, hmm whatever I whis it to be...</h3>", this);
    QLabel *versionLabel = new QLabel("Version 0.IwishThisHadAversion", this);
    QLabel *qt_version = new QLabel(QString("Qt Version: %1").arg(QT_VERSION_STR), this);
    QLabel *qt_version_number = new QLabel(QString("Qt Version number: %1").arg(QT_VERSION), this);
    QLabel *qt_build_key = new QLabel(QString("Qt Build Key: %1").arg(qVersion()), this);
    QLabel *qt_platform = new QLabel(QString("OS: %1").arg(QSysInfo::prettyProductName()), this);
    QPushButton *websiteButton = new QPushButton("Visit Website", this);

    connect(websiteButton, &QPushButton::clicked, this, &Form::wishIhadAnAngel);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(versionLabel);
    layout->addWidget(qt_version);
    layout->addWidget(qt_version_number);
    layout->addWidget(qt_build_key);
    layout->addWidget(qt_platform);
    layout->addWidget(websiteButton);
    layout->addStretch();

    setLayout(layout);
}

void Form::wishIhadAnAngel()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=wEERFBI9eCg"));
}

Form::~Form()
{
}

