#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QTimer>
#include <QMessageBox>
#include <directoryops.h>
#include <logoperations.h>
#include <xmlparser.h>
#include <logger.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void folderComboChanged(QString folder);
    void dutComboChanged(QString dut);
    void readingDone();
    void addResultItem(QString item, int id);
    void selectOutputDir();
    void selectXML();
    void startProcess();
    void openLog();
    void threadFinished();
    void timerTimeout();
    void copyToggle(bool val);
    void togetherToggle(bool val);
    void deviceSpecificToggle(bool val);
    void getFilesForCopy(QString from,QString to);

private:
    Ui::MainWindow *ui;
    DirectoryOps *dirOps;
    LogOperations *logOps;
    xmlparser *xml;
    Logger *log;
    QTimer *timer;
    QList<LogOperations *> threadList;
    QList<Arguments> args;
    QList<QString> files2copy;
    QStringList argumentList;
    QVector< QPair<int, int> > argumentListType;
    QString globalDir;
    void getSearchTerms(QString path);
    bool isFirstTime;
    bool isXMLSelected;
    bool isDirectorySelected;
    bool isDeviceSpecific;
    int readCount;
    int readCounter;
    int threadCounter;

};

#endif // MAINWINDOW_H
