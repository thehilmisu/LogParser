#include "directoryops.h"

DirectoryOps::DirectoryOps(QObject *parent) : QObject(parent)
{
    //getLogFiles();
}
DirectoryOps::~DirectoryOps()
{
    qDebug() << "dir ops deleted";
}

QList<QString> DirectoryOps::getLogFiles(){
    QList<QString> temp;
    ////bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/
    QDirIterator it("//bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/"+folderName+"/"+dutName+"/",
                    QDir::AllEntries,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString t = it.next();
        if(t.contains(".Log")){
            if(!t.contains(".csv")){
                temp.append(t);
                //qDebug() << t;
            }
        }
    }

    return temp;
}

QList<QString> DirectoryOps::getDirectoryLogFiles(QString dir){
    QList<QString> temp;
    ////bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/
    QDirIterator it(dir,
                    QDir::AllEntries,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString t = it.next();
        if(t.contains(".Log")){
            if(!t.contains(".csv")){
                temp.append(t);
                //qDebug() << t;
            }
        }
    }

    return temp;
}

QList<QString> DirectoryOps::getDUTNames(QString fname){
    QList<QString> temp;
    ////bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/
    QDirIterator it("//bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/"+fname+"/", QDir::Dirs);
    while (it.hasNext()) {
        QString t = it.next();
        QStringList str = t.split("/");
        if(!str.at(str.count()-1).startsWith(".")){
            temp.append(str.at(str.count()-1));
        }
    }

    return temp;
}

QList<QString> DirectoryOps::getFolderNames(){
    QList<QString> temp;
    ////bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/
    QDirIterator it("//bosch.com/CloudDrive/CM/202112_GM_VCU_DV_log/", QDir::Dirs);
    while (it.hasNext()) {
        QString t = it.next();

        QStringList str = t.split("/");
        if(!str.at(str.count()-1).contains(".")){
            temp.append(str.at(str.count()-1));
        }
    }

    return temp;
}
