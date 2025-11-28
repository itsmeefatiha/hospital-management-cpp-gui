#include "mainwindow.h"
#include "loginwindow.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database::connect();  // 🔗 Connexion PostgreSQL
    LoginWindow login;
    login.show();
    return a.exec();
}
