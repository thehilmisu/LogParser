#include "definitions.h"
#include "xmlparser.h"

xmlparser::xmlparser(QString path)
{
    xmlPath = path;
    counts.clear();
}
xmlparser::~xmlparser()
{
    args.clear();
}

QStringList xmlparser::extractSearchTerms( QString path, QVector< QPair<int, int> > &argumentListType )
{
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
    }

    QStringList temp;
    temp.clear();
    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "AnalyseDoc"){
            while(reader.readNextStartElement()){
                if(reader.name() == "SearchText"){
                    foreach(const QXmlStreamAttribute &attr, reader.attributes()) {
                        if (attr.name().toString() == QLatin1String("doSearch")) {
                            if(attr.value().toString() == "true"){
                                temp << reader.readElementText();
                                qDebug() << temp;

                                argumentListType.append( qMakePair(SEARCH_TYPE_NORMAL, 0) );
                            }
                        }
                        else if(attr.name().toString() == QLatin1String("occuranceCount")){
                            qDebug() << "occ count" << attr.value();
                            counts << attr.value().toString();
                        }
                        else if (attr.name().toString() == QLatin1String("searchType")) {
                            if(attr.value().toString() == "regex")
                                argumentListType.last().first = SEARCH_TYPE_REGEX;
                            else if(attr.value().toString() == "rgx_multiline") {
                                int cnt0, cnt1; cnt0 = cnt1 = 0;

                                argumentListType.last().first = SEARCH_TYPE_REGEXM;
                                cnt0 = temp.count("\\r?\\n");
                                cnt1 = temp.count("\\r\\n");

                                if(cnt0 > cnt1) cnt1 = cnt0;
                                argumentListType.last().second = cnt1;
                            }
                        }
                    }
                }
                else
                    reader.skipCurrentElement();
            }
        }
        else
            qDebug() << "Wrong Type of File";
    }

    return temp;
}
QStringList xmlparser::getOccuranceCount()
{
    return counts;
}
