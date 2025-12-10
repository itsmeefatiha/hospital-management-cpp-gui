#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
public:
    static QSqlDatabase connect();
};

#endif // DATABASE_H
