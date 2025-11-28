/********************************************************************************
** Form generated from reading UI file 'receptiondashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEPTIONDASHBOARD_H
#define UI_RECEPTIONDASHBOARD_H

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

class Ui_ReceptionDashboard
{
public:
    QHBoxLayout *mainLayout;
    QFrame *sideBar;
    QVBoxLayout *sideBarLayout;
    QPushButton *btnPatients;
    QPushButton *btnRdvs;
    QPushButton *btnAdmissions;
    QSpacerItem *sidebarSpacerTop;
    QWidget *centralArea;
    QVBoxLayout *centralLayout;
    QLabel *lblAgendaTitle;
    QTableWidget *tableAgenda;

    void setupUi(QWidget *ReceptionDashboard)
    {
        if (ReceptionDashboard->objectName().isEmpty())
            ReceptionDashboard->setObjectName("ReceptionDashboard");
        ReceptionDashboard->resize(1050, 650);
        ReceptionDashboard->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background: #f6f7fb; font-family:'Segoe UI', Arial, sans-serif; color:#1a202c; }\n"
"QFrame#sideBar { background:#2062d8; border-radius:17px; }\n"
"QPushButton.sidebarBtn { background:transparent; border:none; color:#e3eafc; font-size:15px; font-weight:600; text-align:left; padding:13px 15px; border-radius:6px; margin-top:2px; margin-bottom:2px; }\n"
"QPushButton.sidebarBtn:hover { background:#1853c4; color:#fff; }\n"
"QLabel.agendaTitle {font-size:17px;color:#2062d8;font-weight:600;margin-bottom:6px;margin-top:8px;}\n"
"QHeaderView::section { background-color:#2062d8;color:white; border:none; font-weight:500;padding:7px;border-radius:0;}\n"
"QTableWidget { background:white; border-radius:6px; font-size:14px; gridline-color:#e3eafc; }\n"
"QTableWidget::item:selected { background:#eaf1fe; color:#1a202c;}\n"
"QTableCornerButton::section { background: #2062d8; }\n"
"   "));
        mainLayout = new QHBoxLayout(ReceptionDashboard);
        mainLayout->setObjectName("mainLayout");
        sideBar = new QFrame(ReceptionDashboard);
        sideBar->setObjectName("sideBar");
        sideBar->setMinimumWidth(75);
        sideBar->setMaximumWidth(100);
        sideBar->setFrameShape(QFrame::StyledPanel);
        sideBarLayout = new QVBoxLayout(sideBar);
        sideBarLayout->setObjectName("sideBarLayout");
        btnPatients = new QPushButton(sideBar);
        btnPatients->setObjectName("btnPatients");
        btnPatients->setObjectName("sidebarBtn");
        btnPatients->setMinimumHeight(32);

        sideBarLayout->addWidget(btnPatients);

        btnRdvs = new QPushButton(sideBar);
        btnRdvs->setObjectName("btnRdvs");
        btnRdvs->setObjectName("sidebarBtn");
        btnRdvs->setMinimumHeight(32);

        sideBarLayout->addWidget(btnRdvs);

        btnAdmissions = new QPushButton(sideBar);
        btnAdmissions->setObjectName("btnAdmissions");
        btnAdmissions->setObjectName("sidebarBtn");
        btnAdmissions->setMinimumHeight(32);

        sideBarLayout->addWidget(btnAdmissions);

        sidebarSpacerTop = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        sideBarLayout->addItem(sidebarSpacerTop);


        mainLayout->addWidget(sideBar);

        centralArea = new QWidget(ReceptionDashboard);
        centralArea->setObjectName("centralArea");
        centralLayout = new QVBoxLayout(centralArea);
        centralLayout->setObjectName("centralLayout");
        centralLayout->setContentsMargins(0, 0, 0, 0);
        lblAgendaTitle = new QLabel(centralArea);
        lblAgendaTitle->setObjectName("lblAgendaTitle");
        lblAgendaTitle->setObjectName("agendaTitle");

        centralLayout->addWidget(lblAgendaTitle);

        tableAgenda = new QTableWidget(centralArea);
        if (tableAgenda->columnCount() < 5)
            tableAgenda->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableAgenda->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableAgenda->setObjectName("tableAgenda");
        tableAgenda->setColumnCount(5);
        tableAgenda->setRowCount(0);

        centralLayout->addWidget(tableAgenda);


        mainLayout->addWidget(centralArea);

        mainLayout->setStretch(1, 1);

        retranslateUi(ReceptionDashboard);

        QMetaObject::connectSlotsByName(ReceptionDashboard);
    } // setupUi

    void retranslateUi(QWidget *ReceptionDashboard)
    {
        ReceptionDashboard->setWindowTitle(QCoreApplication::translate("ReceptionDashboard", "Espace R\303\251ception", nullptr));
        btnPatients->setText(QCoreApplication::translate("ReceptionDashboard", "\360\237\221\244", nullptr));
#if QT_CONFIG(tooltip)
        btnPatients->setToolTip(QCoreApplication::translate("ReceptionDashboard", "Patients", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRdvs->setText(QCoreApplication::translate("ReceptionDashboard", "\360\237\223\205", nullptr));
#if QT_CONFIG(tooltip)
        btnRdvs->setToolTip(QCoreApplication::translate("ReceptionDashboard", "Rendez-vous", nullptr));
#endif // QT_CONFIG(tooltip)
        btnAdmissions->setText(QCoreApplication::translate("ReceptionDashboard", "\360\237\217\245", nullptr));
#if QT_CONFIG(tooltip)
        btnAdmissions->setToolTip(QCoreApplication::translate("ReceptionDashboard", "Admissions (Hospitalisation)", nullptr));
#endif // QT_CONFIG(tooltip)
        lblAgendaTitle->setText(QCoreApplication::translate("ReceptionDashboard", "Agenda du jour", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableAgenda->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ReceptionDashboard", "Heure", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableAgenda->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ReceptionDashboard", "Patient", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableAgenda->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ReceptionDashboard", "Service", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableAgenda->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ReceptionDashboard", "M\303\251decin", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableAgenda->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ReceptionDashboard", "Statut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReceptionDashboard: public Ui_ReceptionDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEPTIONDASHBOARD_H
