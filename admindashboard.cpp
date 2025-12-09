#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "loginwindow.h"

#include <QtCharts>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QHeaderView>

AdminDashboard::AdminDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
    ui->tableWidget_appointments->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // --- DIAGNOSTIC DE CHEMIN D'IMAGE ---
    QString imagePath = ":/resources/medicine.png";
    qDebug() << "--- DIAGNOSTIC IMAGE ---";
    qDebug() << "Dossier d'exécution de l'app :" << QDir::currentPath();
    qDebug() << "Chemin complet attendu :" << QDir::current().absoluteFilePath(imagePath);

    if (!QFile::exists(imagePath)) {
        qDebug() << "ERREUR CRITIQUE : Le fichier n'existe pas à cet emplacement !";
        qDebug() << "SOLUTION : Copiez le dossier 'resources' dans le dossier 'build-...'";
    }

    // --- 2. AJOUT DU LOGO DANS LA SIDEBAR ---
    QPixmap logo(imagePath);

    if (!logo.isNull()) {
        ui->label_app_name->setPixmap(logo.scaledToWidth(50, Qt::SmoothTransformation));
        ui->label_app_name->setAlignment(Qt::AlignCenter);
    } else {
        // Fallback
        qDebug() << "Erreur : Chargement de l'image échoué.";
        ui->label_app_name->setText("Hôpital Manager");
    }
    // ----------------------------------------

    // Initialisation des pages
    pageUsers = new PageUsers();
    pageServices = new PageServices();
    pageRooms = new PageRooms();

    ui->stackedWidget->addWidget(pageUsers);
    ui->stackedWidget->addWidget(pageServices);
    ui->stackedWidget->addWidget(pageRooms);

    ui->stackedWidget->setCurrentIndex(0);

    // Charger les données du Dashboard au démarrage
    refreshStats();
    loadRecentActivity();
    setupChart();
    setupDoughnutChart();
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::refreshStats()
{
    QSqlQuery query;

    // 1. Total Utilisateurs
    if(query.exec("SELECT COUNT(*) FROM utilisateurs")) {
        if(query.next()) {
            ui->label_s1_v->setText(query.value(0).toString());
        }
    }

    // 2. Taux d'Occupation ((Chambres occupées / Total) * 100)
    int totalRooms = 0;
    int occupiedRooms = 0;

    // Compter total
    if(query.exec("SELECT COUNT(*) FROM chambres")) {
        if(query.next()) totalRooms = query.value(0).toInt();
    }
    // Compter occupées (est_disponible = false)
    if(query.exec("SELECT COUNT(*) FROM chambres WHERE est_disponible = false")) {
        if(query.next()) occupiedRooms = query.value(0).toInt();
    }

    if(totalRooms > 0) {
        int rate = (occupiedRooms * 100) / totalRooms;
        ui->label_s2_v->setText(QString::number(rate) + "%");
    } else {
        ui->label_s2_v->setText("0%");
    }

    // 3. Médecins Actifs
    if(query.exec("SELECT COUNT(*) FROM medecins")) {
        if(query.next()) {
            ui->label_s3_v->setText(query.value(0).toString());
        }
    }
}

void AdminDashboard::loadRecentActivity()
{
    // Affiche les 5 derniers RDV planifiés
    ui->tableWidget_appointments->setRowCount(0);

    QSqlQuery query;
    // Jointure pour avoir les noms
    QString sql = "SELECT p.nom || ' ' || p.prenom, "
                  "m.nom || ' ' || m.prenom, "
                  "s.nom_service, "
                  "r.date_heure "
                  "FROM rendez_vous r "
                  "JOIN utilisateurs p ON r.id_patient = p.id_user "
                  "JOIN utilisateurs m ON r.id_medecin = m.id_user "
                  "JOIN medecins med ON m.id_user = med.id_medecin "
                  "JOIN services s ON med.id_service = s.id_service "
                  "ORDER BY r.date_heure DESC LIMIT 5";

    if(query.exec(sql)) {
        while(query.next()) {
            int row = ui->tableWidget_appointments->rowCount();
            ui->tableWidget_appointments->insertRow(row);

            ui->tableWidget_appointments->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // Patient
            ui->tableWidget_appointments->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Médecin
            ui->tableWidget_appointments->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Service
            ui->tableWidget_appointments->setItem(row, 3, new QTableWidgetItem(query.value(3).toDateTime().toString("dd/MM/yyyy HH:mm"))); // Date
        }
    }
}

// --- Navigation ---
void AdminDashboard::on_btn_menu_dashboard_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    refreshStats();
    ui->btn_menu_dashboard->setChecked(true); ui->btn_menu_users->setChecked(false);
    ui->btn_menu_services->setChecked(false); ui->btn_menu_rooms->setChecked(false);
}

void AdminDashboard::on_btn_menu_users_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    pageUsers->refresh();
    ui->btn_menu_dashboard->setChecked(false); ui->btn_menu_users->setChecked(true);
    ui->btn_menu_services->setChecked(false); ui->btn_menu_rooms->setChecked(false);
}

void AdminDashboard::on_btn_menu_services_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
    pageServices->refresh();
    ui->btn_menu_dashboard->setChecked(false); ui->btn_menu_users->setChecked(false);
    ui->btn_menu_services->setChecked(true); ui->btn_menu_rooms->setChecked(false);
}

void AdminDashboard::on_btn_menu_rooms_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
    pageRooms->refresh();
    ui->btn_menu_dashboard->setChecked(false); ui->btn_menu_users->setChecked(false);
    ui->btn_menu_services->setChecked(false); ui->btn_menu_rooms->setChecked(true);
}

void AdminDashboard::on_btn_logout_clicked() {
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}
void AdminDashboard::setupChart()
{
    // 1. Préparer les données (7 jours de la semaine initialisés à 0)
    QMap<int, int> rdvParJour;
    for(int i=1; i<=7; ++i) rdvParJour[i] = 0;

    // 2. Récupérer les données réelles depuis la BDD (PostgreSQL)
    QSqlQuery query;
    // EXTRACT(ISODOW) renvoie 1 pour Lundi, 7 pour Dimanche
    QString sql = "SELECT EXTRACT(ISODOW FROM date_heure) as jour, COUNT(*) "
                  "FROM rendez_vous "
                  "WHERE date_heure >= date_trunc('week', CURRENT_DATE) "
                  "GROUP BY jour";

    if(query.exec(sql)) {
        while(query.next()) {
            int jour = query.value(0).toInt();
            int count = query.value(1).toInt();
            rdvParJour[jour] = count;
        }
    }

    // 3. Créer le BarSet (Les barres verticales)
    QBarSet *set0 = new QBarSet("Rendez-vous");
    for(int i=1; i<=7; ++i) {
        *set0 << rdvParJour[i]; // Ajouter la valeur de chaque jour
    }
    set0->setColor(QColor(45, 122, 237)); // Bleu du thème (#2d7aed)

    // 4. Créer la Série
    QBarSeries *series = new QBarSeries();
    series->append(set0);

    // 5. Créer le Graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Rendez-vous cette semaine");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(false); // Pas besoin de légende pour une seule série
    chart->setBackgroundRoundness(0);
    chart->setMargins(QMargins(0,0,0,0)); // Maximiser l'espace

    // 6. Axe X (Jours)
    QStringList categories;
    categories << "Lun" << "Mar" << "Mer" << "Jeu" << "Ven" << "Sam" << "Dim";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 7. Axe Y (Nombre)
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d"); // Entiers uniquement
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 8. Affichage (ChartView)
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // --- INTÉGRATION DANS L'INTERFACE ---
    // On remplace le widget placeholder vide par notre graphique
    if (ui->verticalLayout_chart) {
        // Supprimer le placeholder existant
        if(ui->chart_placeholder) {
            ui->verticalLayout_chart->removeWidget(ui->chart_placeholder);
            delete ui->chart_placeholder;
            ui->chart_placeholder = nullptr;
        }
        // Ajouter le graphique
        ui->verticalLayout_chart->addWidget(chartView);
    }
}
void AdminDashboard::setupDoughnutChart()
{
    // 1. Récupération des données SQL
    int totalChambres = 0;
    int chambresOccupees = 0;
    QSqlQuery query;

    // Compter le total
    if(query.exec("SELECT COUNT(*) FROM chambres")) {
        if(query.next()) totalChambres = query.value(0).toInt();
    }

    // Compter les occupées (est_disponible = false)
    if(query.exec("SELECT COUNT(*) FROM chambres WHERE est_disponible = false")) {
        if(query.next()) chambresOccupees = query.value(0).toInt();
    }

    int chambresLibres = totalChambres - chambresOccupees;

    // 2. Création de la série (Camembert)
    QPieSeries *series = new QPieSeries();
    // C'est cette ligne qui transforme le Pie Chart en Doughnut Chart (Trou au milieu)
    series->setHoleSize(0.40);

    // Ajout des parts
    QPieSlice *sliceOcc = series->append("Occupées", chambresOccupees);
    QPieSlice *sliceFree = series->append("Libres", chambresLibres);

    // 3. Personnalisation des couleurs et labels
    // Occupées en BLEU (Couleur du thème)
    sliceOcc->setColor(QColor("#2d7aed"));
    sliceOcc->setLabelVisible(true);
    sliceOcc->setLabelColor(Qt::black);

    // Libres en GRIS CLAIR
    sliceFree->setColor(QColor("#e0e0e0"));
    sliceFree->setLabelVisible(true);

    // Si une part est trop petite, on cache le label pour éviter la superposition
    if (chambresOccupees == 0) sliceOcc->setLabelVisible(false);
    if (chambresLibres == 0) sliceFree->setLabelVisible(false);

    // 4. Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Disponibilité des Lits");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setAlignment(Qt::AlignRight); // Légende à droite
    chart->setBackgroundRoundness(0);
    chart->setMargins(QMargins(0,0,0,0));

    // 5. Création de la Vue (ChartView)
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 6. Intégration dans l'interface (Remplacement du Placeholder)
    // On vérifie que le layout existe (créé dans le XML précédent)
    if (ui->verticalLayout_doughnut) {
        // Si le placeholder existe encore, on le supprime
        if(ui->doughnut_placeholder) {
            ui->verticalLayout_doughnut->removeWidget(ui->doughnut_placeholder);
            delete ui->doughnut_placeholder;
            ui->doughnut_placeholder = nullptr;
        }
        // On ajoute le graphique
        ui->verticalLayout_doughnut->addWidget(chartView);
    }
}
