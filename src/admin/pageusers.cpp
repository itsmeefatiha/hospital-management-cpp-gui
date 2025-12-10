#include "pageusers.h"
#include "ui_pageusers.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

PageUsers::PageUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageUsers)
{
    ui->setupUi(this);

    // Configuration du tableau : ID, Nom Complet, Login, Role
    ui->tableUsers->setColumnCount(4);
    ui->tableUsers->setHorizontalHeaderLabels({"ID", "Nom Prénom", "Login", "Rôle"});
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // On cache la colonne ID (0) car l'utilisateur n'a pas besoin de la voir
    ui->tableUsers->setColumnHidden(0, true);

    resetForm(); // État initial
    refresh();   // Charger les données
}

PageUsers::~PageUsers()
{
    delete ui;
}

void PageUsers::refresh()
{
    ui->tableUsers->setRowCount(0);
    QSqlQuery query;

    // On récupère l'ID, le Nom, le Prénom, etc.
    if(query.exec("SELECT id_user, nom, prenom, login, role FROM utilisateurs ORDER BY id_user DESC")) {
        while(query.next()) {
            int row = ui->tableUsers->rowCount();
            ui->tableUsers->insertRow(row);

            QString id = query.value(0).toString();
            QString nomComplet = query.value(1).toString() + " " + query.value(2).toString();
            QString login = query.value(3).toString();
            QString role = query.value(4).toString();

            ui->tableUsers->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableUsers->setItem(row, 1, new QTableWidgetItem(nomComplet));
            ui->tableUsers->setItem(row, 2, new QTableWidgetItem(login));
            ui->tableUsers->setItem(row, 3, new QTableWidgetItem(role));
        }
    }
}

// --- CLIC SUR LE TABLEAU : REMPLIR LE FORMULAIRE ---
void PageUsers::on_tableUsers_cellClicked(int row, int column)
{
    // 1. Récupérer l'ID (caché en colonne 0)
    selectedUserId = ui->tableUsers->item(row, 0)->text().toInt();

    // 2. Récupérer les infos visuelles
    QString fullName = ui->tableUsers->item(row, 1)->text();
    QString login = ui->tableUsers->item(row, 2)->text();
    QString role = ui->tableUsers->item(row, 3)->text();

    // 3. Remplir les champs
    ui->lineEdit_name->setText(fullName);
    ui->lineEdit_email->setText(login);

    // On gère la combo box pour sélectionner le bon rôle
    // (Attention à la casse : la base stocke "MEDECIN", la combo affiche "Médecin")
    int index = -1;
    if (role == "MEDECIN") index = ui->combo_role->findText("Médecin", Qt::MatchContains);
    else if (role == "RECEPTIONNISTE") index = ui->combo_role->findText("Réceptionniste", Qt::MatchContains);
    else if (role == "ADMIN") index = ui->combo_role->findText("Administrateur", Qt::MatchContains);

    if (index != -1) ui->combo_role->setCurrentIndex(index);

    // 4. Mot de passe : On vide et on met un placeholder
    ui->lineEdit_password->clear();
    ui->lineEdit_password->setPlaceholderText("Laisser vide pour ne pas changer");

    // 5. Activer les boutons de modification
    ui->btn_add->setEnabled(false);
    ui->btn_edit->setEnabled(true);
    ui->btn_delete->setEnabled(true);
}

// --- BOUTON AJOUTER ---
void PageUsers::on_btn_add_clicked()
{
    QString nameFull = ui->lineEdit_name->text();
    QString login = ui->lineEdit_email->text();
    QString pass = ui->lineEdit_password->text();
    QString roleText = ui->combo_role->currentText();

    if(nameFull.isEmpty() || login.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires.");
        return;
    }

    // Conversion Rôle
    QString dbRole = "PATIENT";
    if (roleText.contains("Médecin")) dbRole = "MEDECIN";
    else if (roleText.contains("Réceptionniste")) dbRole = "RECEPTIONNISTE";
    else if (roleText.contains("Admin")) dbRole = "ADMIN";

    // Séparation Nom/Prénom
    QString nom = nameFull.split(" ").first();
    QString prenom = nameFull.contains(" ") ? nameFull.section(" ", 1) : ".";

    QSqlQuery query;
    query.prepare("INSERT INTO utilisateurs (nom, prenom, login, mot_de_passe, role) VALUES (:n, :p, :l, :pw, :r)");
    query.bindValue(":n", nom);
    query.bindValue(":p", prenom);
    query.bindValue(":l", login);
    query.bindValue(":pw", pass);
    query.bindValue(":r", dbRole);

    if(query.exec()) {
        QMessageBox::information(this, "Succès", "Utilisateur ajouté.");
        resetForm();
        refresh();
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}

// --- BOUTON MODIFIER ---
void PageUsers::on_btn_edit_clicked()
{
    if (selectedUserId == -1) return;

    QString nameFull = ui->lineEdit_name->text();
    QString login = ui->lineEdit_email->text();
    QString pass = ui->lineEdit_password->text();
    QString roleText = ui->combo_role->currentText();

    // Conversion Rôle
    QString dbRole = "PATIENT";
    if (roleText.contains("Médecin")) dbRole = "MEDECIN";
    else if (roleText.contains("Réceptionniste")) dbRole = "RECEPTIONNISTE";
    else if (roleText.contains("Admin")) dbRole = "ADMIN";

    QString nom = nameFull.split(" ").first();
    QString prenom = nameFull.contains(" ") ? nameFull.section(" ", 1) : ".";

    QSqlQuery query;

    // Si le mot de passe est vide, on ne le change pas
    if (pass.isEmpty()) {
        query.prepare("UPDATE utilisateurs SET nom=:n, prenom=:p, login=:l, role=:r WHERE id_user=:id");
    } else {
        query.prepare("UPDATE utilisateurs SET nom=:n, prenom=:p, login=:l, role=:r, mot_de_passe=:pw WHERE id_user=:id");
        query.bindValue(":pw", pass);
    }

    query.bindValue(":n", nom);
    query.bindValue(":p", prenom);
    query.bindValue(":l", login);
    query.bindValue(":r", dbRole);
    query.bindValue(":id", selectedUserId);

    if(query.exec()) {
        QMessageBox::information(this, "Succès", "Utilisateur modifié.");
        resetForm();
        refresh();
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}

// --- BOUTON SUPPRIMER ---
void PageUsers::on_btn_delete_clicked()
{
    if (selectedUserId == -1) return;

    if(QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer cet utilisateur ?") == QMessageBox::Yes) {
        QSqlQuery q;
        q.prepare("DELETE FROM utilisateurs WHERE id_user = :id");
        q.bindValue(":id", selectedUserId);

        if(q.exec()) {
            resetForm();
            refresh();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer (peut-être lié à d'autres données).");
        }
    }
}

// --- BOUTON ANNULER ---
void PageUsers::on_btn_clear_clicked()
{
    resetForm();
}

void PageUsers::resetForm()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_password->setPlaceholderText("Mot de passe");
    ui->combo_role->setCurrentIndex(0);

    selectedUserId = -1;

    // Gestion de l'état des boutons
    ui->btn_add->setEnabled(true);     // On peut ajouter
    ui->btn_edit->setEnabled(false);   // On ne peut pas modifier (rien sélectionné)
    ui->btn_delete->setEnabled(false); // On ne peut pas supprimer

    ui->tableUsers->clearSelection();
}
