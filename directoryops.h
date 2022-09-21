#ifndef DIRECTORYOPS_H
#define DIRECTORYOPS_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <QDir>
#include <QUrl>
#include <QFileDialog>
#include <QDirIterator>

class DirectoryOps : public QObject
{
    Q_OBJECT
public:
    explicit DirectoryOps(QObject *parent = nullptr);
    ~DirectoryOps();
    QList<QString> getLogFiles();
    QList<QString> getDirectoryLogFiles(QString dir);
    QList<QString> getDUTNames(QString fname);
    QList<QString> getFolderNames();
    QList<QString> logFiles;
    QString folderName;
    QString dutName;

signals:

public slots:
};

#endif // DIRECTORYOPS_H
