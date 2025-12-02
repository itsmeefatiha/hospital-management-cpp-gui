#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

QSqlDatabase Database::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");       // adresse serveur
    db.setPort(5432);                  // port PostgreSQL
    db.setDatabaseName("db_hospital");
    db.setUserName("postgres");
    db.setPassword("fatiha");

    if (!db.open()) {
        qDebug() << "Erreur connexion DB:" << db.lastError().text();
    } else {
        qDebug() << "Connexion PostgreSQL réussie.";
    }

    return db;
}
