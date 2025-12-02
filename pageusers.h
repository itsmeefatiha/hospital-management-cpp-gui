#ifndef PAGEUSERS_H
#define PAGEUSERS_H

#include <QWidget>

namespace Ui {
class PageUsers;
}

class PageUsers : public QWidget
{
    Q_OBJECT

public:
    explicit PageUsers(QWidget *parent = nullptr);
    ~PageUsers();

    // Fonction accessible depuis l'AdminDashboard
    void refresh(); // <--- AJOUTÉ

private slots:
    void on_btn_save_user_clicked();

private:
    Ui::PageUsers *ui;
};

#endif // PAGEUSERS_H
