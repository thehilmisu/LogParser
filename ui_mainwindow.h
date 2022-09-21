/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblLoading;
    QPushButton *btnOpenLog;
    QPushButton *btnSelectXML;
    QPushButton *btnSelectOutput;
    QLabel *lblSelectedDirectory;
    QLabel *lblXMLDirectory;
    QLabel *lblOutputDirectory;
    QPushButton *btnStartProcess;
    QCheckBox *copyCheck;
    QCheckBox *occurTogetherCheck;
    QCheckBox *DeviceSpecificCheck;
    QComboBox *comboRegion;
    QLineEdit *txtDevice;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 350);
        MainWindow->setMinimumSize(QSize(500, 275));
        MainWindow->setMaximumSize(QSize(500, 350));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblLoading = new QLabel(centralWidget);
        lblLoading->setObjectName(QStringLiteral("lblLoading"));
        lblLoading->setGeometry(QRect(0, 0, 500, 350));
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        lblLoading->setFont(font);
        lblLoading->setStyleSheet(QStringLiteral("background:rgba(0,0,0,200);color:white;"));
        lblLoading->setScaledContents(true);
        lblLoading->setAlignment(Qt::AlignCenter);
        btnOpenLog = new QPushButton(centralWidget);
        btnOpenLog->setObjectName(QStringLiteral("btnOpenLog"));
        btnOpenLog->setGeometry(QRect(370, 30, 100, 30));
        btnSelectXML = new QPushButton(centralWidget);
        btnSelectXML->setObjectName(QStringLiteral("btnSelectXML"));
        btnSelectXML->setGeometry(QRect(370, 90, 100, 30));
        btnSelectOutput = new QPushButton(centralWidget);
        btnSelectOutput->setObjectName(QStringLiteral("btnSelectOutput"));
        btnSelectOutput->setGeometry(QRect(370, 160, 100, 30));
        lblSelectedDirectory = new QLabel(centralWidget);
        lblSelectedDirectory->setObjectName(QStringLiteral("lblSelectedDirectory"));
        lblSelectedDirectory->setGeometry(QRect(10, 10, 500, 25));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lblSelectedDirectory->setFont(font1);
        lblXMLDirectory = new QLabel(centralWidget);
        lblXMLDirectory->setObjectName(QStringLiteral("lblXMLDirectory"));
        lblXMLDirectory->setGeometry(QRect(10, 70, 500, 25));
        lblXMLDirectory->setFont(font1);
        lblOutputDirectory = new QLabel(centralWidget);
        lblOutputDirectory->setObjectName(QStringLiteral("lblOutputDirectory"));
        lblOutputDirectory->setGeometry(QRect(10, 130, 500, 25));
        lblOutputDirectory->setFont(font1);
        btnStartProcess = new QPushButton(centralWidget);
        btnStartProcess->setObjectName(QStringLiteral("btnStartProcess"));
        btnStartProcess->setGeometry(QRect(140, 300, 211, 41));
        copyCheck = new QCheckBox(centralWidget);
        copyCheck->setObjectName(QStringLiteral("copyCheck"));
        copyCheck->setGeometry(QRect(10, 270, 201, 19));
        copyCheck->setFont(font1);
        occurTogetherCheck = new QCheckBox(centralWidget);
        occurTogetherCheck->setObjectName(QStringLiteral("occurTogetherCheck"));
        occurTogetherCheck->setGeometry(QRect(280, 270, 201, 19));
        occurTogetherCheck->setFont(font1);
        DeviceSpecificCheck = new QCheckBox(centralWidget);
        DeviceSpecificCheck->setObjectName(QStringLiteral("DeviceSpecificCheck"));
        DeviceSpecificCheck->setGeometry(QRect(10, 210, 131, 19));
        DeviceSpecificCheck->setFont(font1);
        comboRegion = new QComboBox(centralWidget);
        comboRegion->setObjectName(QStringLiteral("comboRegion"));
        comboRegion->setEnabled(false);
        comboRegion->setGeometry(QRect(160, 210, 101, 22));
        txtDevice = new QLineEdit(centralWidget);
        txtDevice->setObjectName(QStringLiteral("txtDevice"));
        txtDevice->setEnabled(false);
        txtDevice->setGeometry(QRect(270, 210, 211, 21));
        txtDevice->setToolTipDuration(-1);
        txtDevice->setInputMethodHints(Qt::ImhDigitsOnly);
        MainWindow->setCentralWidget(centralWidget);
        btnOpenLog->raise();
        btnSelectXML->raise();
        btnSelectOutput->raise();
        lblSelectedDirectory->raise();
        lblXMLDirectory->raise();
        lblOutputDirectory->raise();
        btnStartProcess->raise();
        copyCheck->raise();
        occurTogetherCheck->raise();
        DeviceSpecificCheck->raise();
        comboRegion->raise();
        txtDevice->raise();
        lblLoading->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        lblLoading->setText(QApplication::translate("MainWindow", "Processing ...", Q_NULLPTR));
        btnOpenLog->setText(QApplication::translate("MainWindow", "Select  Directory", Q_NULLPTR));
        btnSelectXML->setText(QApplication::translate("MainWindow", "Select  XML", Q_NULLPTR));
        btnSelectOutput->setText(QApplication::translate("MainWindow", "Select Output Dir", Q_NULLPTR));
        lblSelectedDirectory->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        lblXMLDirectory->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        lblOutputDirectory->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        btnStartProcess->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        copyCheck->setText(QApplication::translate("MainWindow", "Copy founded files?", Q_NULLPTR));
        occurTogetherCheck->setText(QApplication::translate("MainWindow", "Check failures occur together?", Q_NULLPTR));
        DeviceSpecificCheck->setText(QApplication::translate("MainWindow", "Is device specific?", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        txtDevice->setToolTip(QApplication::translate("MainWindow", "Device Number", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        txtDevice->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        txtDevice->setPlaceholderText(QApplication::translate("MainWindow", "Device Number", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
