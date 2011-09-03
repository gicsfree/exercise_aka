/********************************************************************************
** Form generated from reading ui file 'form.ui'
**
** Created: Fri Sep 2 15:33:08 2011
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *btn_send;
    QLineEdit *ledt_ip;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *btn_connect;
    QLineEdit *ledt_file;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        btn_send = new QPushButton(Form);
        btn_send->setObjectName(QString::fromUtf8("btn_send"));
        btn_send->setGeometry(QRect(30, 220, 85, 28));
        ledt_ip = new QLineEdit(Form);
        ledt_ip->setObjectName(QString::fromUtf8("ledt_ip"));
        ledt_ip->setGeometry(QRect(60, 50, 131, 31));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 57, 18));
        progressBar = new QProgressBar(Form);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 140, 251, 23));
        progressBar->setValue(24);
        btn_connect = new QPushButton(Form);
        btn_connect->setObjectName(QString::fromUtf8("btn_connect"));
        btn_connect->setGeometry(QRect(214, 50, 61, 28));
        ledt_file = new QLineEdit(Form);
        ledt_file->setObjectName(QString::fromUtf8("ledt_file"));
        ledt_file->setGeometry(QRect(130, 220, 113, 26));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        btn_send->setText(QApplication::translate("Form", "\345\217\221\351\200\201\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form", "IP:", 0, QApplication::UnicodeUTF8));
        btn_connect->setText(QApplication::translate("Form", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
