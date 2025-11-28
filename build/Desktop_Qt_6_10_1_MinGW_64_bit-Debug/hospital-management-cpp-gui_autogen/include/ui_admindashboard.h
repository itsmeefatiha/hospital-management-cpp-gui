/********************************************************************************
** Form generated from reading UI file 'admindashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINDASHBOARD_H
#define UI_ADMINDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminDashboard
{
public:
    QHBoxLayout *mainLayout;
    QFrame *sideBar;
    QVBoxLayout *sideBarLayout;
    QPushButton *btnDashboard;
    QPushButton *btnUsers;
    QPushButton *btnServices;
    QPushButton *btnRooms;
    QSpacerItem *sidebarSpacerTop;
    QPushButton *btnLogout;
    QWidget *centralArea;
    QVBoxLayout *centralLayout;
    QHBoxLayout *dashboardStats;
    QFrame *cardMedecins;
    QVBoxLayout *cardLayout1;
    QLabel *lblMedecinsTitle;
    QLabel *lblMedecinsVal;
    QLabel *lblMedecinsMini;
    QFrame *cardOccupation;
    QVBoxLayout *cardLayout2;
    QLabel *lblOccupationTitle;
    QLabel *lblOccupationVal;
    QLabel *lblOccupationMini;
    QFrame *cardUsers;
    QVBoxLayout *cardLayout3;
    QLabel *lblUsersTitle;
    QLabel *lblUsersVal;
    QLabel *lblUsersMini;
    QLabel *lblRdvTitle;
    QTableWidget *tableRdv;

    void setupUi(QWidget *AdminDashboard)
    {
        if (AdminDashboard->objectName().isEmpty())
            AdminDashboard->setObjectName("AdminDashboard");
        AdminDashboard->resize(1100, 700);
        AdminDashboard->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background: #f6f7fb; font-family:'Segoe UI', Arial, sans-serif; color:#1a202c; }\n"
"QFrame#sideBar { background:#2563eb; border-radius:18px; }\n"
"QPushButton.sidebarBtn { background:transparent; border:none; color:#e3eafc; font-size:15px; font-weight:600; text-align:left; padding:12px 15px; border-radius:6px; margin-top:2px; margin-bottom:2px; }\n"
"QPushButton.sidebarBtn:hover { background: #345afa; color:#fff; }\n"
"QLabel.cardTitle { font-size:12px; color:#7b8794; font-weight:400; margin-bottom:4px; }\n"
"QLabel.cardVal { font-size:21px; color:#2150b9; font-weight:500; }\n"
"QFrame[modernCard=\"true\"] { background:white; border-radius:11px; box-shadow:0 0 9px #a1a6b711; padding:14px 18px; }\n"
"QLabel.cardMini { font-size:10px; color:#bac3d0; margin-top:3px; }\n"
"QHeaderView::section { background-color:#2563eb;color:white; border:none; font-weight:500;padding:7px;border-radius:0; }\n"
"QTableWidget { background:white; border-radius:6px; font-size:14px; gridline-color:#e3eafc; }\n"
"QTable"
                        "Widget::item:selected { background:#eaf1fe; color:#1a202c; }\n"
"QTableCornerButton::section { background: #2563eb; }\n"
"   "));
        mainLayout = new QHBoxLayout(AdminDashboard);
        mainLayout->setObjectName("mainLayout");
        sideBar = new QFrame(AdminDashboard);
        sideBar->setObjectName("sideBar");
        sideBar->setMinimumWidth(68);
        sideBar->setMaximumWidth(96);
        sideBar->setFrameShape(QFrame::StyledPanel);
        sideBarLayout = new QVBoxLayout(sideBar);
        sideBarLayout->setObjectName("sideBarLayout");
        btnDashboard = new QPushButton(sideBar);
        btnDashboard->setObjectName("btnDashboard");
        btnDashboard->setObjectName("sidebarBtn");
        btnDashboard->setMinimumHeight(32);

        sideBarLayout->addWidget(btnDashboard);

        btnUsers = new QPushButton(sideBar);
        btnUsers->setObjectName("btnUsers");
        btnUsers->setObjectName("sidebarBtn");
        btnUsers->setMinimumHeight(32);

        sideBarLayout->addWidget(btnUsers);

        btnServices = new QPushButton(sideBar);
        btnServices->setObjectName("btnServices");
        btnServices->setObjectName("sidebarBtn");
        btnServices->setMinimumHeight(32);

        sideBarLayout->addWidget(btnServices);

        btnRooms = new QPushButton(sideBar);
        btnRooms->setObjectName("btnRooms");
        btnRooms->setObjectName("sidebarBtn");
        btnRooms->setMinimumHeight(32);

        sideBarLayout->addWidget(btnRooms);

        sidebarSpacerTop = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        sideBarLayout->addItem(sidebarSpacerTop);

        btnLogout = new QPushButton(sideBar);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setObjectName("sidebarBtn");
        btnLogout->setMinimumHeight(32);

        sideBarLayout->addWidget(btnLogout);


        mainLayout->addWidget(sideBar);

        centralArea = new QWidget(AdminDashboard);
        centralArea->setObjectName("centralArea");
        centralLayout = new QVBoxLayout(centralArea);
        centralLayout->setObjectName("centralLayout");
        centralLayout->setContentsMargins(0, 0, 0, 0);
        dashboardStats = new QHBoxLayout();
        dashboardStats->setObjectName("dashboardStats");
        cardMedecins = new QFrame(centralArea);
        cardMedecins->setObjectName("cardMedecins");
        cardLayout1 = new QVBoxLayout(cardMedecins);
        cardLayout1->setObjectName("cardLayout1");
        lblMedecinsTitle = new QLabel(cardMedecins);
        lblMedecinsTitle->setObjectName("lblMedecinsTitle");
        lblMedecinsTitle->setObjectName("cardTitle");

        cardLayout1->addWidget(lblMedecinsTitle);

        lblMedecinsVal = new QLabel(cardMedecins);
        lblMedecinsVal->setObjectName("lblMedecinsVal");
        lblMedecinsVal->setObjectName("cardVal");

        cardLayout1->addWidget(lblMedecinsVal);

        lblMedecinsMini = new QLabel(cardMedecins);
        lblMedecinsMini->setObjectName("lblMedecinsMini");
        lblMedecinsMini->setObjectName("cardMini");

        cardLayout1->addWidget(lblMedecinsMini);


        dashboardStats->addWidget(cardMedecins);

        cardOccupation = new QFrame(centralArea);
        cardOccupation->setObjectName("cardOccupation");
        cardLayout2 = new QVBoxLayout(cardOccupation);
        cardLayout2->setObjectName("cardLayout2");
        lblOccupationTitle = new QLabel(cardOccupation);
        lblOccupationTitle->setObjectName("lblOccupationTitle");
        lblOccupationTitle->setObjectName("cardTitle");

        cardLayout2->addWidget(lblOccupationTitle);

        lblOccupationVal = new QLabel(cardOccupation);
        lblOccupationVal->setObjectName("lblOccupationVal");
        lblOccupationVal->setObjectName("cardVal");

        cardLayout2->addWidget(lblOccupationVal);

        lblOccupationMini = new QLabel(cardOccupation);
        lblOccupationMini->setObjectName("lblOccupationMini");
        lblOccupationMini->setObjectName("cardMini");

        cardLayout2->addWidget(lblOccupationMini);


        dashboardStats->addWidget(cardOccupation);

        cardUsers = new QFrame(centralArea);
        cardUsers->setObjectName("cardUsers");
        cardLayout3 = new QVBoxLayout(cardUsers);
        cardLayout3->setObjectName("cardLayout3");
        lblUsersTitle = new QLabel(cardUsers);
        lblUsersTitle->setObjectName("lblUsersTitle");
        lblUsersTitle->setObjectName("cardTitle");

        cardLayout3->addWidget(lblUsersTitle);

        lblUsersVal = new QLabel(cardUsers);
        lblUsersVal->setObjectName("lblUsersVal");
        lblUsersVal->setObjectName("cardVal");

        cardLayout3->addWidget(lblUsersVal);

        lblUsersMini = new QLabel(cardUsers);
        lblUsersMini->setObjectName("lblUsersMini");
        lblUsersMini->setObjectName("cardMini");

        cardLayout3->addWidget(lblUsersMini);


        dashboardStats->addWidget(cardUsers);

        dashboardStats->setStretch(0, 1);
        dashboardStats->setStretch(1, 1);
        dashboardStats->setStretch(2, 1);

        centralLayout->addLayout(dashboardStats);

        lblRdvTitle = new QLabel(centralArea);
        lblRdvTitle->setObjectName("lblRdvTitle");
        lblRdvTitle->setStyleSheet(QString::fromUtf8("font-size:15px;margin:18px 0 8px 0;font-weight:500;color:#2563eb;"));

        centralLayout->addWidget(lblRdvTitle);

        tableRdv = new QTableWidget(centralArea);
        if (tableRdv->columnCount() < 5)
            tableRdv->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableRdv->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableRdv->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableRdv->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableRdv->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableRdv->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableRdv->setObjectName("tableRdv");
        tableRdv->setColumnCount(5);
        tableRdv->setRowCount(0);

        centralLayout->addWidget(tableRdv);

        centralLayout->setStretch(3, 1);

        mainLayout->addWidget(centralArea);

        mainLayout->setStretch(1, 1);

        retranslateUi(AdminDashboard);

        QMetaObject::connectSlotsByName(AdminDashboard);
    } // setupUi

    void retranslateUi(QWidget *AdminDashboard)
    {
        AdminDashboard->setWindowTitle(QCoreApplication::translate("AdminDashboard", "Espace Administrateur", nullptr));
        btnDashboard->setText(QCoreApplication::translate("AdminDashboard", "\360\237\217\240", nullptr));
#if QT_CONFIG(tooltip)
        btnDashboard->setToolTip(QCoreApplication::translate("AdminDashboard", "Tableau de bord", nullptr));
#endif // QT_CONFIG(tooltip)
        btnUsers->setText(QCoreApplication::translate("AdminDashboard", "\360\237\221\244", nullptr));
#if QT_CONFIG(tooltip)
        btnUsers->setToolTip(QCoreApplication::translate("AdminDashboard", "Utilisateurs", nullptr));
#endif // QT_CONFIG(tooltip)
        btnServices->setText(QCoreApplication::translate("AdminDashboard", "\360\237\217\245", nullptr));
#if QT_CONFIG(tooltip)
        btnServices->setToolTip(QCoreApplication::translate("AdminDashboard", "Services", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRooms->setText(QCoreApplication::translate("AdminDashboard", "\360\237\233\217\357\270\217", nullptr));
#if QT_CONFIG(tooltip)
        btnRooms->setToolTip(QCoreApplication::translate("AdminDashboard", "Chambres", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLogout->setText(QCoreApplication::translate("AdminDashboard", "\342\216\213", nullptr));
#if QT_CONFIG(tooltip)
        btnLogout->setToolTip(QCoreApplication::translate("AdminDashboard", "D\303\251connexion", nullptr));
#endif // QT_CONFIG(tooltip)
        lblMedecinsTitle->setText(QCoreApplication::translate("AdminDashboard", "M\303\251decins", nullptr));
        lblMedecinsVal->setText(QCoreApplication::translate("AdminDashboard", "24", nullptr));
        lblMedecinsMini->setText(QCoreApplication::translate("AdminDashboard", "Actifs ce mois", nullptr));
        lblOccupationTitle->setText(QCoreApplication::translate("AdminDashboard", "Taux d'occupation", nullptr));
        lblOccupationVal->setText(QCoreApplication::translate("AdminDashboard", "42%", nullptr));
        lblOccupationMini->setText(QCoreApplication::translate("AdminDashboard", "Chambres", nullptr));
        lblUsersTitle->setText(QCoreApplication::translate("AdminDashboard", "Utilisateurs", nullptr));
        lblUsersVal->setText(QCoreApplication::translate("AdminDashboard", "112", nullptr));
        lblUsersMini->setText(QCoreApplication::translate("AdminDashboard", "Comptes actifs", nullptr));
        lblRdvTitle->setText(QCoreApplication::translate("AdminDashboard", "Rendez-vous du jour", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableRdv->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AdminDashboard", "Patient", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableRdv->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AdminDashboard", "Service", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableRdv->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AdminDashboard", "M\303\251decin", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableRdv->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AdminDashboard", "Heure", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableRdv->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AdminDashboard", "Statut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminDashboard: public Ui_AdminDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINDASHBOARD_H
