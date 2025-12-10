#include "pagerooms.h"
#include "ui_pagerooms.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

PageRooms::PageRooms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageRooms)
{
    ui->setupUi(this);
    refresh();
}

PageRooms::~PageRooms()
{
    delete ui;
}

void PageRooms::refresh()
{
    ui->tableRooms->setRowCount(0);

    QSqlQuery query;
    if(query.exec("SELECT numero, type_chambre, etage, est_disponible FROM chambres ORDER BY numero")) {
        while(query.next()) {
            int row = ui->tableRooms->rowCount();
            ui->tableRooms->insertRow(row);

            ui->tableRooms->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableRooms->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableRooms->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));

            bool dispo = query.value(3).toBool();
            QTableWidgetItem *itemStatus = new QTableWidgetItem(dispo ? "Libre" : "Occupée");

            // Mettre en couleur (Vert = Libre, Rouge = Occupée)
            if(dispo) itemStatus->setForeground(QBrush(QColor("#28a745")));
            else itemStatus->setForeground(QBrush(QColor("#dc3545")));

            ui->tableRooms->setItem(row, 3, itemStatus);
        }
    }
}

void PageRooms::on_btn_add_room_clicked()
{
    QString num = ui->lineEdit_room_num->text();
    QString type = ui->combo_type->currentText();
    QString etage = ui->lineEdit_floor->text();

    if(num.isEmpty() || etage.isEmpty()) return;

    QSqlQuery query;
    query.prepare("INSERT INTO chambres (numero, type_chambre, etage, est_disponible) "
                  "VALUES (:num, :type, :etage, true)");
    query.bindValue(":num", num);
    query.bindValue(":type", type);
    query.bindValue(":etage", etage.toInt());

    if(query.exec()) {
        QMessageBox::information(this, "Succès", "Chambre ajoutée.");
        ui->lineEdit_room_num->clear();
        ui->lineEdit_floor->clear();
        refresh();
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}
