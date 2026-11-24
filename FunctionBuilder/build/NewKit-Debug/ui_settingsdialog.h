/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *dialogLayout;
    QLabel *heading;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *closeButton;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->setMinimumSize(QSize(340, 0));
        SettingsDialog->setStyleSheet(QString::fromUtf8("\n"
"QDialog { background: #1E2530; }\n"
"QLabel { color: #F1F5F9; font-size: 16px; font-weight: bold; }\n"
"QPushButton { background: #303A49; color: #F1F5F9; border: 1px solid #465367; border-radius: 6px; padding: 8px 14px; }\n"
"QPushButton:hover, QPushButton:focus { border-color: #5491F8; background: #354358; }\n"
"  "));
        dialogLayout = new QVBoxLayout(SettingsDialog);
        dialogLayout->setSpacing(10);
        dialogLayout->setObjectName("dialogLayout");
        dialogLayout->setContentsMargins(18, 18, 18, 18);
        heading = new QLabel(SettingsDialog);
        heading->setObjectName("heading");

        dialogLayout->addWidget(heading);

        saveButton = new QPushButton(SettingsDialog);
        saveButton->setObjectName("saveButton");

        dialogLayout->addWidget(saveButton);

        loadButton = new QPushButton(SettingsDialog);
        loadButton->setObjectName("loadButton");

        dialogLayout->addWidget(loadButton);

        closeButton = new QPushButton(SettingsDialog);
        closeButton->setObjectName("closeButton");

        dialogLayout->addWidget(closeButton);


        retranslateUi(SettingsDialog);
        QObject::connect(closeButton, &QPushButton::clicked, SettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        heading->setText(QCoreApplication::translate("SettingsDialog", "\320\244\320\260\320\271\320\273 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262", nullptr));
        saveButton->setText(QCoreApplication::translate("SettingsDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 JSON\342\200\246", nullptr));
        loadButton->setText(QCoreApplication::translate("SettingsDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 JSON\342\200\246", nullptr));
        closeButton->setText(QCoreApplication::translate("SettingsDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
