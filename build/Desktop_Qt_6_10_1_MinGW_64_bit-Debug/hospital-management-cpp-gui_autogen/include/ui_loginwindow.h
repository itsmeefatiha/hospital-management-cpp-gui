/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *centralLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widgetCentre;
    QVBoxLayout *formLayout;
    QLabel *labelTitre;
    QLineEdit *editIdentifiant;
    QLineEdit *editPassword;
    QPushButton *btnLogin;
    QSpacerItem *verticalSpacer2;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(380, 300);
        LoginWindow->setStyleSheet(QString::fromUtf8("background:#f4f6fa;font-family:'Segoe UI',Arial,sans-serif;font-size:15px;"));
        centralLayout = new QVBoxLayout(LoginWindow);
        centralLayout->setObjectName("centralLayout");
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        centralLayout->addItem(verticalSpacer);

        widgetCentre = new QWidget(LoginWindow);
        widgetCentre->setObjectName("widgetCentre");
        formLayout = new QVBoxLayout(widgetCentre);
        formLayout->setObjectName("formLayout");
        labelTitre = new QLabel(widgetCentre);
        labelTitre->setObjectName("labelTitre");
        labelTitre->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        labelTitre->setFont(font);
        labelTitre->setStyleSheet(QString::fromUtf8("color:#222;"));

        formLayout->addWidget(labelTitre);

        editIdentifiant = new QLineEdit(widgetCentre);
        editIdentifiant->setObjectName("editIdentifiant");
        editIdentifiant->setMaximumWidth(300);
        editIdentifiant->setStyleSheet(QString::fromUtf8("background:white;color:#222;padding:6px;font-size:14px;border:1px solid #cccccc;border-radius:4px;"));

        formLayout->addWidget(editIdentifiant);

        editPassword = new QLineEdit(widgetCentre);
        editPassword->setObjectName("editPassword");
        editPassword->setEchoMode(QLineEdit::Password);
        editPassword->setMaximumWidth(300);
        editPassword->setStyleSheet(QString::fromUtf8("background:white;color:#222;padding:6px;font-size:14px;border:1px solid #cccccc;border-radius:4px;"));

        formLayout->addWidget(editPassword);

        btnLogin = new QPushButton(widgetCentre);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setMaximumWidth(300);
        btnLogin->setMinimumHeight(36);
        btnLogin->setStyleSheet(QString::fromUtf8("background:#2077ec;color:white;font-weight:bold;font-size:16px;border-radius:4px;"));

        formLayout->addWidget(btnLogin);


        centralLayout->addWidget(widgetCentre);

        verticalSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        centralLayout->addItem(verticalSpacer2);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Connexion - H\303\264pital", nullptr));
        labelTitre->setText(QCoreApplication::translate("LoginWindow", "Connexion hospitali\303\250re", nullptr));
        editIdentifiant->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Identifiant", nullptr));
        editPassword->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Mot de passe", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginWindow", "Se connecter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
