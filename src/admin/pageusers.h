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

    void refresh();

private slots:
    // Nos 4 actions
    void on_btn_add_clicked();      // Ajouter
    void on_btn_edit_clicked();     // Modifier
    void on_btn_delete_clicked();   // Supprimer
    void on_btn_clear_clicked();    // Annuler / Vider

    // Clic sur le tableau
    void on_tableUsers_cellClicked(int row, int column);

private:
    Ui::PageUsers *ui;

    void resetForm(); // Fonction pour remettre le formulaire à zéro
    int selectedUserId = -1; // Stocke l'ID de l'utilisateur en cours de modif (-1 = aucun)
    };

#endif // PAGEUSERS_H
