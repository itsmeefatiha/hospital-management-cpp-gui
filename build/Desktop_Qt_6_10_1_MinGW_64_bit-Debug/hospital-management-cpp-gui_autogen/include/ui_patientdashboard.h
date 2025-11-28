/********************************************************************************
** Form generated from reading UI file 'patientdashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTDASHBOARD_H
#define UI_PATIENTDASHBOARD_H

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

class Ui_PatientDashboard
{
public:
    QHBoxLayout *mainLayout;
    QFrame *sideBar;
    QVBoxLayout *sideBarLayout;
    QPushButton *btnHome;
    QPushButton *btnRdv;
    QPushButton *btnDossier;
    QPushButton *btnOrdonnances;
    QSpacerItem *sidebarSpacerTop;
    QWidget *centralArea;
    QVBoxLayout *centralLayout;
    QLabel *lblPtDashTitle;
    QHBoxLayout *cardLayoutRow;
    QFrame *cardNextRdv;
    QVBoxLayout *vboxCard1;
    QLabel *lblNextRdv;
    QLabel *valNextRdv;
    QFrame *cardNotif;
    QVBoxLayout *vboxCard2;
    QLabel *lblNotif;
    QLabel *valNotif;
    QTableWidget *tableSynthese;

    void setupUi(QWidget *PatientDashboard)
    {
        if (PatientDashboard->objectName().isEmpty())
            PatientDashboard->setObjectName("PatientDashboard");
        PatientDashboard->resize(1050, 650);
        PatientDashboard->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background: #f7fafd; font-family:'Segoe UI', Arial, sans-serif; color:#1a202c; }\n"
"QFrame#sideBar { background:#23b1e9; border-radius:18px; }\n"
"QPushButton.sidebarBtn { background:transparent; border:none; color:#e3eafc; font-size:15px; font-weight:600; text-align:left; padding:13px 15px; border-radius:6px; margin-top:2px; margin-bottom:2px; }\n"
"QPushButton.sidebarBtn:hover { background:#189dcf; color:#fff; }\n"
"QLabel.ptDashTitle {font-size:17px;color:#23b1e9;font-weight:600;margin-bottom:8px;margin-top:12px;}\n"
"QFrame[card=\"true\"] { background: white; border-radius:11px; box-shadow: 0 1px 8px #1aaad911; padding:14px 18px; }\n"
"QLabel.cardLabel {font-size:13px;color:#7b8994; font-weight:400;}\n"
"QLabel.cardValue {font-size:15px;color:#1884ab; font-weight:500;}\n"
"QHeaderView::section { background-color:#23b1e9;color:white; border:none; font-weight:500;padding:7px;border-radius:0;}\n"
"QTableWidget { background:white; border-radius:6px; font-size:14px; gridline-color:#e3eafc; }\n"
""
                        "QTableWidget::item:selected { background:#edfaff; color:#1a202c;}\n"
"QTableCornerButton::section { background: #23b1e9; }\n"
"   "));
        mainLayout = new QHBoxLayout(PatientDashboard);
        mainLayout->setObjectName("mainLayout");
        sideBar = new QFrame(PatientDashboard);
        sideBar->setObjectName("sideBar");
        sideBar->setMinimumWidth(75);
        sideBar->setMaximumWidth(100);
        sideBar->setFrameShape(QFrame::StyledPanel);
        sideBarLayout = new QVBoxLayout(sideBar);
        sideBarLayout->setObjectName("sideBarLayout");
        btnHome = new QPushButton(sideBar);
        btnHome->setObjectName("btnHome");
        btnHome->setObjectName("sidebarBtn");

        sideBarLayout->addWidget(btnHome);

        btnRdv = new QPushButton(sideBar);
        btnRdv->setObjectName("btnRdv");
        btnRdv->setObjectName("sidebarBtn");

        sideBarLayout->addWidget(btnRdv);

        btnDossier = new QPushButton(sideBar);
        btnDossier->setObjectName("btnDossier");
        btnDossier->setObjectName("sidebarBtn");

        sideBarLayout->addWidget(btnDossier);

        btnOrdonnances = new QPushButton(sideBar);
        btnOrdonnances->setObjectName("btnOrdonnances");
        btnOrdonnances->setObjectName("sidebarBtn");

        sideBarLayout->addWidget(btnOrdonnances);

        sidebarSpacerTop = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        sideBarLayout->addItem(sidebarSpacerTop);


        mainLayout->addWidget(sideBar);

        centralArea = new QWidget(PatientDashboard);
        centralArea->setObjectName("centralArea");
        centralLayout = new QVBoxLayout(centralArea);
        centralLayout->setObjectName("centralLayout");
        centralLayout->setContentsMargins(0, 0, 0, 0);
        lblPtDashTitle = new QLabel(centralArea);
        lblPtDashTitle->setObjectName("lblPtDashTitle");
        lblPtDashTitle->setObjectName("ptDashTitle");

        centralLayout->addWidget(lblPtDashTitle);

        cardLayoutRow = new QHBoxLayout();
        cardLayoutRow->setObjectName("cardLayoutRow");
        cardNextRdv = new QFrame(centralArea);
        cardNextRdv->setObjectName("cardNextRdv");
        vboxCard1 = new QVBoxLayout(cardNextRdv);
        vboxCard1->setObjectName("vboxCard1");
        lblNextRdv = new QLabel(cardNextRdv);
        lblNextRdv->setObjectName("lblNextRdv");
        lblNextRdv->setObjectName("cardLabel");

        vboxCard1->addWidget(lblNextRdv);

        valNextRdv = new QLabel(cardNextRdv);
        valNextRdv->setObjectName("valNextRdv");
        valNextRdv->setObjectName("cardValue");

        vboxCard1->addWidget(valNextRdv);


        cardLayoutRow->addWidget(cardNextRdv);

        cardNotif = new QFrame(centralArea);
        cardNotif->setObjectName("cardNotif");
        vboxCard2 = new QVBoxLayout(cardNotif);
        vboxCard2->setObjectName("vboxCard2");
        lblNotif = new QLabel(cardNotif);
        lblNotif->setObjectName("lblNotif");
        lblNotif->setObjectName("cardLabel");

        vboxCard2->addWidget(lblNotif);

        valNotif = new QLabel(cardNotif);
        valNotif->setObjectName("valNotif");
        valNotif->setObjectName("cardValue");

        vboxCard2->addWidget(valNotif);


        cardLayoutRow->addWidget(cardNotif);


        centralLayout->addLayout(cardLayoutRow);

        tableSynthese = new QTableWidget(centralArea);
        if (tableSynthese->columnCount() < 4)
            tableSynthese->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableSynthese->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableSynthese->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableSynthese->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableSynthese->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableSynthese->setObjectName("tableSynthese");
        tableSynthese->setColumnCount(4);
        tableSynthese->setRowCount(0);

        centralLayout->addWidget(tableSynthese);


        mainLayout->addWidget(centralArea);

        mainLayout->setStretch(1, 1);

        retranslateUi(PatientDashboard);

        QMetaObject::connectSlotsByName(PatientDashboard);
    } // setupUi

    void retranslateUi(QWidget *PatientDashboard)
    {
        PatientDashboard->setWindowTitle(QCoreApplication::translate("PatientDashboard", "Espace Patient", nullptr));
        btnHome->setText(QCoreApplication::translate("PatientDashboard", "\360\237\217\240", nullptr));
#if QT_CONFIG(tooltip)
        btnHome->setToolTip(QCoreApplication::translate("PatientDashboard", "Accueil", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRdv->setText(QCoreApplication::translate("PatientDashboard", "\360\237\223\206", nullptr));
#if QT_CONFIG(tooltip)
        btnRdv->setToolTip(QCoreApplication::translate("PatientDashboard", "Mes rendez-vous", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDossier->setText(QCoreApplication::translate("PatientDashboard", "\360\237\223\213", nullptr));
#if QT_CONFIG(tooltip)
        btnDossier->setToolTip(QCoreApplication::translate("PatientDashboard", "Mon dossier", nullptr));
#endif // QT_CONFIG(tooltip)
        btnOrdonnances->setText(QCoreApplication::translate("PatientDashboard", "\360\237\222\212", nullptr));
#if QT_CONFIG(tooltip)
        btnOrdonnances->setToolTip(QCoreApplication::translate("PatientDashboard", "Ordonnances", nullptr));
#endif // QT_CONFIG(tooltip)
        lblPtDashTitle->setText(QCoreApplication::translate("PatientDashboard", "Mon Portail Patient", nullptr));
        lblNextRdv->setText(QCoreApplication::translate("PatientDashboard", "Prochain rendez-vous", nullptr));
        valNextRdv->setText(QCoreApplication::translate("PatientDashboard", "15 juin, 10h30", nullptr));
        lblNotif->setText(QCoreApplication::translate("PatientDashboard", "Notifications", nullptr));
        valNotif->setText(QCoreApplication::translate("PatientDashboard", "Vous avez 2 nouveaux comptes-rendus", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableSynthese->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PatientDashboard", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableSynthese->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PatientDashboard", "Service", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableSynthese->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PatientDashboard", "M\303\251decin", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableSynthese->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PatientDashboard", "Statut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientDashboard: public Ui_PatientDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTDASHBOARD_H
