/********************************************************************************
** Form generated from reading UI file 'doctordashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCTORDASHBOARD_H
#define UI_DOCTORDASHBOARD_H

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

class Ui_DoctorDashboard
{
public:
    QHBoxLayout *mainLayout;
    QFrame *sideBar;
    QVBoxLayout *sideBarLayout;
    QPushButton *btnAgenda;
    QPushButton *btnPatients;
    QPushButton *btnDossier;
    QPushButton *btnOrdonnances;
    QSpacerItem *sidebarSpacerTop;
    QWidget *centralArea;
    QVBoxLayout *centralLayout;
    QLabel *lblAgendaTitle;
    QTableWidget *tableAgenda;

    void setupUi(QWidget *DoctorDashboard)
    {
        if (DoctorDashboard->objectName().isEmpty())
            DoctorDashboard->setObjectName("DoctorDashboard");
        DoctorDashboard->resize(1050, 650);
        DoctorDashboard->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background: #f7f8fc; font-family:'Segoe UI', Arial, sans-serif; color:#1a202c; }\n"
"QFrame#sideBar { background:#1550c8; border-radius:18px; }\n"
"QPushButton.sidebarBtn { background:transparent; border:none; color:#e3eafc; font-size:15px; font-weight:600; text-align:left; padding:13px 15px; border-radius:6px; margin-top:2px; margin-bottom:2px; }\n"
"QPushButton.sidebarBtn:hover { background:#113fa2; color:#fff; }\n"
"QLabel.agendaTitle {font-size:17px;color:#1550c8;font-weight:600;margin-bottom:6px;margin-top:8px;}\n"
"QHeaderView::section { background-color:#1550c8;color:white; border:none; font-weight:500;padding:7px;border-radius:0;}\n"
"QTableWidget { background:white; border-radius:6px; font-size:14px; gridline-color:#e3eafc; }\n"
"QTableWidget::item:selected { background:#eaf1fe; color:#1a202c;}\n"
"QTableCornerButton::section { background: #1550c8; }\n"
"   "));
        mainLayout = new QHBoxLayout(DoctorDashboard);
        mainLayout->setObjectName("mainLayout");
        sideBar = new QFrame(DoctorDashboard);
        sideBar->setObjectName("sideBar");
        sideBar->setMinimumWidth(75);
        sideBar->setMaximumWidth(100);
        sideBar->setFrameShape(QFrame::StyledPanel);
        sideBarLayout = new QVBoxLayout(sideBar);
        sideBarLayout->setObjectName("sideBarLayout");
        btnAgenda = new QPushButton(sideBar);
        btnAgenda->setObjectName("btnAgenda");
        btnAgenda->setObjectName("sidebarBtn");
        btnAgenda->setMinimumHeight(32);

        sideBarLayout->addWidget(btnAgenda);

        btnPatients = new QPushButton(sideBar);
        btnPatients->setObjectName("btnPatients");
        btnPatients->setObjectName("sidebarBtn");
        btnPatients->setMinimumHeight(32);

        sideBarLayout->addWidget(btnPatients);

        btnDossier = new QPushButton(sideBar);
        btnDossier->setObjectName("btnDossier");
        btnDossier->setObjectName("sidebarBtn");
        btnDossier->setMinimumHeight(32);

        sideBarLayout->addWidget(btnDossier);

        btnOrdonnances = new QPushButton(sideBar);
        btnOrdonnances->setObjectName("btnOrdonnances");
        btnOrdonnances->setObjectName("sidebarBtn");
        btnOrdonnances->setMinimumHeight(32);

        sideBarLayout->addWidget(btnOrdonnances);

        sidebarSpacerTop = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        sideBarLayout->addItem(sidebarSpacerTop);


        mainLayout->addWidget(sideBar);

        centralArea = new QWidget(DoctorDashboard);
        centralArea->setObjectName("centralArea");
        centralLayout = new QVBoxLayout(centralArea);
        centralLayout->setObjectName("centralLayout");
        centralLayout->setContentsMargins(0, 0, 0, 0);
        lblAgendaTitle = new QLabel(centralArea);
        lblAgendaTitle->setObjectName("lblAgendaTitle");
        lblAgendaTitle->setObjectName("agendaTitle");

        centralLayout->addWidget(lblAgendaTitle);

        tableAgenda = new QTableWidget(centralArea);
        if (tableAgenda->columnCount() < 4)
            tableAgenda->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableAgenda->setObjectName("tableAgenda");
        tableAgenda->setColumnCount(4);
        tableAgenda->setRowCount(0);

        centralLayout->addWidget(tableAgenda);


        mainLayout->addWidget(centralArea);

        mainLayout->setStretch(1, 1);

        retranslateUi(DoctorDashboard);

        QMetaObject::connectSlotsByName(DoctorDashboard);
    } // setupUi

    void retranslateUi(QWidget *DoctorDashboard)
    {
        DoctorDashboard->setWindowTitle(QCoreApplication::translate("DoctorDashboard", "Espace M\303\251decin", nullptr));
        btnAgenda->setText(QCoreApplication::translate("DoctorDashboard", "\360\237\223\206", nullptr));
#if QT_CONFIG(tooltip)
        btnAgenda->setToolTip(QCoreApplication::translate("DoctorDashboard", "Mon agenda", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPatients->setText(QCoreApplication::translate("DoctorDashboard", "\360\237\221\244", nullptr));
#if QT_CONFIG(tooltip)
        btnPatients->setToolTip(QCoreApplication::translate("DoctorDashboard", "Patients", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDossier->setText(QCoreApplication::translate("DoctorDashboard", "\360\237\223\204", nullptr));
#if QT_CONFIG(tooltip)
        btnDossier->setToolTip(QCoreApplication::translate("DoctorDashboard", "Dossier m\303\251dical", nullptr));
#endif // QT_CONFIG(tooltip)
        btnOrdonnances->setText(QCoreApplication::translate("DoctorDashboard", "\360\237\222\212", nullptr));
#if QT_CONFIG(tooltip)
        btnOrdonnances->setToolTip(QCoreApplication::translate("DoctorDashboard", "Ordonnances", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAgendaTitle->setText(QCoreApplication::translate("DoctorDashboard", "Mon Agenda - Jour", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableAgenda->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DoctorDashboard", "Heure", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableAgenda->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DoctorDashboard", "Patient", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableAgenda->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DoctorDashboard", "Motif", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableAgenda->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DoctorDashboard", "Statut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DoctorDashboard: public Ui_DoctorDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCTORDASHBOARD_H
