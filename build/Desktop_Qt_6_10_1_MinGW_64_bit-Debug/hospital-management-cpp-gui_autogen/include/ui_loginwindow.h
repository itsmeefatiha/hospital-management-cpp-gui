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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_image;
    QFrame *frame_login;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_1;
    QLabel *label_title;
    QLabel *label_subtitle;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *lineEdit_email;
    QLineEdit *lineEdit_password;
    QPushButton *btn_login;
    QLabel *label_forgot;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(900, 550);
        LoginWindow->setStyleSheet(QString::fromUtf8("background-color: #f0f2f5;"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_image = new QLabel(centralwidget);
        label_image->setObjectName("label_image");
        label_image->setMaximumSize(QSize(350, 350));
        label_image->setStyleSheet(QString::fromUtf8("color: white;"));
        label_image->setPixmap(QPixmap(QString::fromUtf8("resources/hospital_bg.png")));
        label_image->setScaledContents(true);
        label_image->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label_image);

        frame_login = new QFrame(centralwidget);
        frame_login->setObjectName("frame_login");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_login->sizePolicy().hasHeightForWidth());
        frame_login->setSizePolicy(sizePolicy);
        frame_login->setMinimumSize(QSize(400, 0));
        frame_login->setMaximumSize(QSize(450, 16777215));
        frame_login->setStyleSheet(QString::fromUtf8("QFrame#frame_login {\n"
"    background-color: white;\n"
"}\n"
"QLabel {\n"
"    color: #333;\n"
"    font-family: \"Segoe UI\", sans-serif;\n"
"}\n"
"QLineEdit {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    background-color: #f9f9f9;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #2d7aed;\n"
"}\n"
"QPushButton {\n"
"    background-color: #2d7aed;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 12px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1a5fc7;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #154ba1;\n"
"}"));
        verticalLayout = new QVBoxLayout(frame_login);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(40, 40, 40, 40);
        verticalSpacer_1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        label_title = new QLabel(frame_login);
        label_title->setObjectName("label_title");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(24);
        font.setBold(true);
        label_title->setFont(font);
        label_title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_title);

        label_subtitle = new QLabel(frame_login);
        label_subtitle->setObjectName("label_subtitle");
        label_subtitle->setStyleSheet(QString::fromUtf8("color: #777; font-size: 14px;"));
        label_subtitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_subtitle);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        lineEdit_email = new QLineEdit(frame_login);
        lineEdit_email->setObjectName("lineEdit_email");

        verticalLayout->addWidget(lineEdit_email);

        lineEdit_password = new QLineEdit(frame_login);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(lineEdit_password);

        btn_login = new QPushButton(frame_login);
        btn_login->setObjectName("btn_login");
        btn_login->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btn_login);

        label_forgot = new QLabel(frame_login);
        label_forgot->setObjectName("label_forgot");
        label_forgot->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        label_forgot->setStyleSheet(QString::fromUtf8("color: #2d7aed; text-decoration: underline;"));
        label_forgot->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_forgot);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout->addWidget(frame_login);

        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Connexion H\303\264pital", nullptr));
        label_image->setText(QString());
        label_title->setText(QCoreApplication::translate("LoginWindow", "Bienvenue", nullptr));
        label_subtitle->setText(QCoreApplication::translate("LoginWindow", "Gestion Hospitali\303\250re", nullptr));
        lineEdit_email->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Adresse Email", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Mot de passe", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginWindow", "Se connecter", nullptr));
        label_forgot->setText(QCoreApplication::translate("LoginWindow", "Mot de passe oubli\303\251 ?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
