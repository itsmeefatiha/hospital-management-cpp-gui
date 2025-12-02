#include "pagepatientsearch.h"
#include "ui_pagepatientsearch.h"
#include <QSqlQuery>

PagePatientSearch::PagePatientSearch(QWidget *parent) :
    QWidget(parent), ui(new Ui::PagePatientSearch)
{
    ui->setupUi(this);
}

PagePatientSearch::~PagePatientSearch() { delete ui; }

void PagePatientSearch::on_btn_search_clicked()
{
    ui->listWidget_results->clear();
    QString search = "%" + ui->lineEdit_search->text() + "%";

    QSqlQuery query;
    query.prepare("SELECT id_user, nom || ' ' || prenom FROM utilisateurs WHERE role='PATIENT' AND (nom ILIKE :s OR prenom ILIKE :s)");
    query.bindValue(":s", search);

    if(query.exec()) {
        while(query.next()) {
            QString label = query.value(1).toString();
            int id = query.value(0).toInt();

            // On stocke l'ID dans l'item (invisible pour l'utilisateur)
            QListWidgetItem *item = new QListWidgetItem(label);
            item->setData(Qt::UserRole, id);
            ui->listWidget_results->addItem(item);
        }
    }
}

void PagePatientSearch::on_listWidget_results_itemClicked(QListWidgetItem *item)
{
    // Quand on clique, on récupère l'ID stocké et on envoie le signal
    int id = item->data(Qt::UserRole).toInt();
    emit patientSelected(id);
}
