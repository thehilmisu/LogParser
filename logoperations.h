#ifndef LOGOPERATIONS_H
#define LOGOPERATIONS_H

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <definitions.h>

class LogOperations : public QObject
{
    Q_OBJECT
public:
    LogOperations(QString path, QStringList ar, QVector< QPair<int, int> > argumentListType, int threadID);
    ~LogOperations();
    void setFileName(QString path);
    void setArguments(QStringList ar, QVector< QPair<int, int> > argumentListType);
    void setFileCopy(bool val);
    void setOccurTogether(bool val);
    void setCopyPath(QString path);
    void setOccuranceCount(QStringList counts);
    void run();
    bool isFinished();

private:
    QStringList lines;
    QList<QStringList> testCycles;
    QFile file;
    QString p;
    QString copyPath;
    int powerCycle;
    bool pcTurn;
    bool copyEnabled;
    QList< QPair<QVariant, int> > arguments;
    QString extractDUTName(QString path);
    QString mapTestCycle(int index);
    void copyFileFromServer();
    int firstTestCycleNumber;
    int lineNumberOnLog;
    int id;
    int TCIndex;
    int extractDateTime(QString line);
    bool parsed;
    int state;
    bool testCycleMapped;
    bool isfinished;
    bool firstTimeCopy;
    bool occureTogether;
    QStringList occuranceCounts;

signals:
    void doneReadingLines();
    void result(QString item, int id);
    void finished();
    void copyFile(QString from, QString to);

public slots:
};

#endif // LOGOPERATIONS_H
