#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    void setPath(QString p);
    QString getPath();
    QString getRawPath();
    void setName(QString n);
    void addLogs(QString log, int id);
    void clearLogs();
    void initLogList(int count);
    void finalizeLogs(QStringList argumentList);

private:
    QString logPath;
    QString logName;
    QList<QStringList> logs;
    int totalFiles;
    int totalMatch;

signals:

public slots:
};

#endif // LOGGER_H
