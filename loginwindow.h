#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase> // Pour gérer la DB

// Inclure les en-têtes des différents tableaux de bord
#include "admindashboard.h"
#include "receptiondashboard.h"
#include "doctordashboard.h"
#include "patientdashboard.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_btn_login_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
