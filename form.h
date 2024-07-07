#ifndef FORM_H
#define FORM_H

#include <QDialog>

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QDialog *parent = nullptr);
    ~Form();

private slots:
    void wishIhadAnAngel();

private:
};

#endif // FORM_H
