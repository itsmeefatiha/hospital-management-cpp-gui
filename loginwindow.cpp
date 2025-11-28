#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QPixmap>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // 1. Charger l'image pour le côté gauche
    // Remplacez le chemin par le chemin réel de votre image
    QPixmap pixmap("C:/Users/pc/Documents/hospital-management-cpp-gui/resources/hospital_bg.png");

    // Si vous n'avez pas de fichier ressource, mettez le chemin absolu pour tester :
    // QPixmap pixmap("C:/Users/VotreNom/Projet/hospital.jpg");

    ui->label_image->setPixmap(pixmap);
    ui->label_image->setScaledContents(true); // L'image s'adapte à la taille

    // Optionnel : Retirer la barre de titre classique pour un look 100% custom
    // setWindowFlags(Qt::FramelessWindowHint);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
