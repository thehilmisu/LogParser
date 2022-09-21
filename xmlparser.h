#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QStringList>
#include <QXmlStreamReader>
#include <QDebug>
#include <QColor>
#include <QFile>

struct Arguments
{
    QColor color;
    QString argument;
};


class xmlparser
{
public:
    xmlparser(QString path);
    ~xmlparser();
    QStringList extractSearchTerms( QString path, QVector< QPair<int, int> > &argumentListType );
    QStringList getOccuranceCount();

private:
    QString xmlPath;
    QList<Arguments> args;
    QStringList counts;
};

#endif // XMLPARSER_H
