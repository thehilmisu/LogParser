#include "logoperations.h"
#include <QRegularExpression>

LogOperations::LogOperations(QString path, QStringList ar, QVector< QPair<int, int> > argumentListType, int threadID)
{
    setFileName(path);
    setArguments(ar, argumentListType);
    parsed = false;
    state = OPEN_FILE;
    firstTestCycleNumber = 0;
    lineNumberOnLog = 0;
    testCycleMapped = false;
    id = threadID;
    isfinished = false;
    TCIndex = 0;
    powerCycle = 0;
    pcTurn = false;
    copyEnabled = false;
    firstTimeCopy = true;
    occureTogether = false;
    occuranceCounts.clear();
}
LogOperations::~LogOperations()
{
    qDebug() << id << "thread deleted";
}
void LogOperations::setFileName(QString path){
    p = path;
}
void LogOperations::setFileCopy(bool val){
    copyEnabled = val;
}
void LogOperations::setOccurTogether(bool val){
    occureTogether = val;
}
void LogOperations::setCopyPath(QString path){
    copyPath = path;
}
void LogOperations::setOccuranceCount(QStringList counts){
    occuranceCounts = counts;
}
void LogOperations::setArguments(QStringList ar, QVector< QPair<int, int> > argumentListType){
    arguments.clear();
    for(int i=0;i<ar.count();i++){
        //temp.append("\\b"+ar.at(i)+"\\b");

        if(argumentListType[i].first == SEARCH_TYPE_NORMAL)
            arguments.append( qMakePair( QVariant(ar[i]), 0 ) );
        else
            arguments.append( qMakePair( QVariant( QRegularExpression(ar[i], QRegularExpression::CaseInsensitiveOption) ), argumentListType[i].first ) );
    }
}
void LogOperations::run(){
    forever
    {
        static int holder = 0;
        holder++;
        if(holder > 5){
            holder = 0;

            if(state == OPEN_FILE)
            {
                file.setFileName(p);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                    qDebug() << "File could not open!!" << p;
                    state = FILE_NOT_READ;
                }else{
                    state = PARSE_STATE;
                }
            }
            else if(state == PARSE_STATE)
            {
                if(!parsed){
                    QTextStream in (&file);
                    QString line;
                    while(!in.atEnd())
                    {
                        line = in.readLine();
                        if(line.length() > 0)
                        {
                            lines.append(line);

                            if(line.contains(TEST_CYCLE_END))
                            {
                                if(!testCycleMapped){
                                    const QRegExp rx(QLatin1Literal("[^0-9]+"));
                                    const auto&& testCycleNumbers = line.split(rx,
                                                                               QString::SkipEmptyParts);

                                    if(testCycleNumbers.count() > 0)
                                        firstTestCycleNumber = QString(testCycleNumbers.at(testCycleNumbers.count()-1)).toInt();

                                    testCycleMapped = true;
                                }
                            }
                        }
                    }
                    file.close();
                    parsed = true;
                    state = INITIALIZE_CYCLES;
                    emit doneReadingLines();
                }
            }
            else if(state == INITIALIZE_CYCLES)
            {
                QStringList temp = lines.filter(TEST_CYCLE_END);
                for(int i=0;i<temp.count();i++){
                    testCycles.append({""});
                }
                testCycles.append({""});
                state = EXTRACT_TEST_CYCLES;
            }
            else if(state == EXTRACT_TEST_CYCLES)
            {
                int cycleIndex = 0;
                for(int i=0;i<lines.count();i++){
                    if(!lines.at(i).contains(TEST_CYCLE_END)){
                        testCycles[cycleIndex].append(lines.at(i));
                    }else{
                        cycleIndex++;
                    }
                }
                qDebug() << p << id << "OK" << "Test Cycles : "
                         << cycleIndex << "Line Count : " << lines.count();

                state = SEARCH_STATE;
            }
            else if(state == SEARCH_STATE_WAIT)
            {
                TCIndex++;
                state = SEARCH_STATE;
            }
            else if(state == SEARCH_STATE)
            {
                QStringList tempList;
                int tempCount = 1;
                bool isFound = false;
                int counter = 0;

                isFound = false;
                if(occureTogether)//every search terms occurance in the same cycle together
                {
                    for(int j=0;j<arguments.count();j++)
                    {
                        if(arguments[j].second == 0)
                        {
                            if( arguments[j].first.typeName() == QString("QString") )
                                tempList = testCycles.at(TCIndex).filter( arguments[j].first.toString() );
                            else
                                tempList = testCycles.at(TCIndex).filter( arguments[j].first.toRegularExpression() );
                        }
                        else
                        {
                            QString mstr;
                            QStringList mstrList;
                            int count = testCycles.at(TCIndex).count();
                            for(int k = 0; k < count; k++)
                            {
                                mstr = testCycles.at(TCIndex)[k];
                                for(int l = 1; l <= arguments[j].second; l++)
                                {
                                    if(k + l < count)
                                    {
                                        mstr.append( QString("\r\n") );
                                        mstr.append( testCycles.at(TCIndex)[k + l] );
                                    }
                                    else
                                        break;
                                }

                                mstrList.append(mstr);
                                tempList = mstrList.filter( arguments[j].first.toRegularExpression() );
                                if(tempList.count() > 0)
                                {
                                    mstrList.clear();
                                    break;
                                }

                                mstrList.clear();
                            }
                        }

                        if(occuranceCounts.count() == arguments.count())
                            tempCount = occuranceCounts.at(j).toInt();
                        else
                            tempCount = 0;

                        if(tempList.count() > 0)
                        {
                            counter++;
                            if(counter > arguments.count()-1){
                                //if(tempCount >= tempList.count())//occurance count
                                {
                                    isFound = true;
                                    break;
                                }
                            }
                            else
                                isFound = false;
                        }
                    }

                    //power cycles
                    for(auto i : testCycles.at(TCIndex).filter("PS:set:"))
                    {
                        if(i.contains("true") && (!pcTurn))
                        {
                            powerCycle++;
                            pcTurn = true;
                        }
                        if(i.contains("false"))
                            pcTurn =  false;
                    }

                    if(isFound)
                    {
                        QString temp = "Found in Test Cycle ===> " +
                                QString::number(firstTestCycleNumber+TCIndex)+
                                " Power Cycle: " +QString::number(powerCycle);
                        qDebug() << temp;
                        if(copyEnabled && firstTimeCopy)
                            copyFileFromServer();

                        emit result(temp,id);
                    }
                    counter = 0;
                    tempList.clear();
                }
                else//every search terms occurance in the same cycle does not have to be together
                {
                    //qDebug() << arguments.count() << arguments.at(0);
                    for(int j=0;j<arguments.count();j++)
                    {
                        if(arguments[j].second == 0)
                        {
                            if( arguments[j].first.typeName() == QString("QString") )
                                tempList = testCycles.at(TCIndex).filter( arguments[j].first.toString() );
                            else
                                tempList = testCycles.at(TCIndex).filter( arguments[j].first.toRegularExpression() );
                        }
                        else
                        {
                            QString mstr;
                            QStringList mstrList;
                            int count = testCycles.at(TCIndex).count();
                            for(int k = 0; k < count; k++)
                            {
                                mstr = testCycles.at(TCIndex)[k];
                                for(int l = 1; l <= arguments[j].second; l++)
                                {
                                    if(k + l < count)
                                    {
                                        mstr.append( QString("\r\n") );
                                        mstr.append( testCycles.at(TCIndex)[k + l] );
                                    }
                                    else
                                        break;
                                }

                                mstrList.append(mstr);
                                tempList = mstrList.filter( arguments[j].first.toRegularExpression() );
                                if(tempList.count() > 0)
                                {
                                    mstrList.clear();
                                    break;
                                }

                                mstrList.clear();
                            }
                        }

                        if(occuranceCounts.count() == arguments.count())
                            tempCount = occuranceCounts.at(j).toInt();
                        else
                            tempCount = 0;

                        if(tempList.count() > 0)
                        {
                            //qDebug() << tempList.count() << tempCount;
                            //if(testCycles.at(TCIndex).filter(QRegExp(t)).count() <= 0)
                            {
                                //if(tempCount == tempList.count())
                                {
                                    isFound = true;
                                    break;
                                }
                            }
                        }
                    }

                    //power cycles
                    for(auto i : testCycles.at(TCIndex).filter("PS:set:"))
                    {
                        if(i.contains("true") && (!pcTurn))
                        {
                            powerCycle++;
                            pcTurn = true;
                        }
                        if(i.contains("false"))
                            pcTurn =  false;
                    }

                    if(isFound)
                    {
                        QString temp = "Found in Test Cycle ===> " +
                                QString::number(firstTestCycleNumber+TCIndex)+
                                " Power Cycle: " +QString::number(powerCycle);
                        qDebug() << temp;
                        if(copyEnabled && firstTimeCopy)
                            copyFileFromServer();

                        emit result(temp,id);
                    }
                    counter = 0;
                    tempList.clear();
                }

                if(TCIndex >= (testCycles.count() - 1))
                {
                    tempList.clear();
                    //add total test cycle and power cycle counts
                    QString temp = "-> Total Test Cycle: " +
                            QString::number(TCIndex)+
                            " - Total Power Cycle: " +QString::number(powerCycle);
                    emit result(temp,id);
                    TCIndex = 0;
                    powerCycle = 0;
                    state = IDLE_STATE;
                }
                else
                {
                    state = SEARCH_STATE_WAIT;
                }

            }
            else if(state == FILE_NOT_READ)
            {
                lines.clear();
                parsed = false;
                state = OPEN_FILE;
            }
            else if(state == IDLE_STATE)
            {
                lines.clear();
                testCycles.clear();
                arguments.clear();
                break;
            }

        }

    }
    qDebug() << "Thread #" << id << " gone!";
    isfinished = true;
    emit finished();
}
QString LogOperations::extractDUTName(QString path)
{
    return path.split('/').at(path.split('/').count()-1);
}
QString LogOperations::mapTestCycle(int index)
{
    return QString::number(firstTestCycleNumber + index);
}
int LogOperations::extractDateTime(QString line)
{
    qDebug() << line;
    return 0;
}
bool LogOperations::isFinished()
{
    return isfinished;
}
void LogOperations::copyFileFromServer()
{
    firstTimeCopy = false;
    emit copyFile(p,copyPath+extractDUTName(p));
}
