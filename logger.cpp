#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{
    logs.clear();
    totalFiles = 0;
    totalMatch = 0;
}

void Logger::addLogs(QString log, int id)
{
    QStringList temp;
    temp << log << "\n";
    logs[id].append(temp);

    if(log.contains("Found"))
        totalMatch++;
}

void Logger::setName(QString n)
{
    logName = n + "_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_HHmmss");
}
void Logger::setPath(QString p)
{
    logPath = p +"/";
}
QString Logger::getPath()
{
    return logPath+logName;
}
QString Logger::getRawPath()
{
    return logPath;
}
void Logger::initLogList(int count)
{
    QStringList temp;
    for(int i=0;i<count;i++)
    {
        logs.append(temp);
    }
    logs.append(temp); //(files.count()+1)for an additional log like total pc and tc
    totalFiles = count;
    totalMatch = 0;
}
void Logger::clearLogs()
{
    logs.clear();
}
void Logger::finalizeLogs(QStringList argumentList)
{
    QDir dir; // Initialize to the desired dir if 'path' is relative
              // By default the program's working directory "." is used.

    // We create the directory if needed
    if (!dir.exists(logPath))
        dir.mkpath(logPath);

    QFile file(logPath + logName + ".hkn");
    if(!file.open(QIODevice::ReadWrite)){
        qDebug() << "Can not open file";
    }

    QTextStream out(&file);
    out << "Total Files Processed: "+QString::number(totalFiles)+
           ", Date Time : "+QDateTime::currentDateTime().toString("yyyy-MM-dd_HHmmss")+
           ", Total Match Count : " +QString::number(totalMatch) + "\n";
    out << "Search Terms :\n";
    for(auto i : argumentList)
        out << " - " << i << "\n";
    out << "------------------------------------------------------------------------------------------------------------------\n";
    for(auto i: logs){
        for(auto j : i){
            out << j;
        }
        out << "------------------------------------------------------------------------------------------------------------------\n";
    }

    file.close();
}
