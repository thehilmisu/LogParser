#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Log Analyzer v1.2.0");

    dirOps = new DirectoryOps();
    log = new Logger();

    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    qDebug() << name;

    log->setPath("C:\\Users\\"+name+"\\Desktop\\"); //default path. check if it is OK for everyone

    isFirstTime = true;

    readCounter = 0;

    ui->lblLoading->setVisible(false);

    connect(ui->btnOpenLog,SIGNAL(released()),this,SLOT(openLog()));

    threadList.clear();

    timer = new QTimer();
    timer->setInterval(250);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTimeout()));
    threadCounter = 0;

    xml = new xmlparser("");

    isXMLSelected = false;
    isDirectorySelected = false;

    ui->lblSelectedDirectory->setText("not selected");
    ui->lblOutputDirectory->setText("Current: Desktop");
    ui->lblXMLDirectory->setText("not selected");
    ui->btnStartProcess->setEnabled(false);
    ui->copyCheck->setEnabled(false);
    ui->occurTogetherCheck->setEnabled(false);
    connect(ui->btnStartProcess,SIGNAL(released()),this,SLOT(startProcess()));

    connect(ui->btnSelectOutput,SIGNAL(released()),this,SLOT(selectOutputDir()));

    connect(ui->btnSelectXML,SIGNAL(released()),this,SLOT(selectXML()));

    connect(ui->copyCheck,SIGNAL(toggled(bool)),this,SLOT(copyToggle(bool)));

    connect(ui->occurTogetherCheck,SIGNAL(toggled(bool)),this,SLOT(togetherToggle(bool)));

    connect(ui->DeviceSpecificCheck,SIGNAL(toggled(bool)),this,SLOT(deviceSpecificToggle(bool)));

    files2copy.clear();

    isDeviceSpecific = false;


    QStringList regions;
    regions << "ROW" << "NAR" << "CHN";
    ui->comboRegion->addItems(regions);

}

MainWindow::~MainWindow()
{
    delete dirOps;
    delete logOps;
    delete log;
    delete xml;
    delete ui;
}

void MainWindow::folderComboChanged(QString folder){

    for(int i=0;i<threadList.count();i++){
        if(threadList.at(i)->isFinished())
            delete threadList.at(i);
    }

    threadCounter = 0;
    threadList.clear();

    dirOps->folderName = folder;
}

void MainWindow::dutComboChanged(QString dut){
    //ui->resultWidget->clear();
    logOps = NULL;
    threadCounter = 0;

    for(int i=0;i<threadList.count();i++){
        if(threadList.at(i)->isFinished())
            delete threadList.at(i);
    }

    threadList.clear();

    if(!isFirstTime){

        dirOps->dutName = dut;
        QStringList ls = dirOps->getLogFiles();

        readCount = ls.count();
        ui->lblLoading->setVisible(true);

        for(int i=0;i<ls.count();i++){
            threadList.append(new LogOperations(ls.at(i),argumentList,argumentListType,i));
            connect(threadList.at(i),SIGNAL(doneReadingLines()),this,SLOT(readingDone()));
            connect(threadList.at(i),SIGNAL(result(QString)),this,SLOT(addResultItem(QString)));
            connect(threadList.at(i),SIGNAL(finished()),this,SLOT(threadFinished()));
        }
    }else{
        isFirstTime = false;
    }
}

void MainWindow::startProcess()
{
    if((isXMLSelected) && (isDirectorySelected))
    {
        for(int i=0;i<threadList.count();i++){
            if(threadList.at(i)->isFinished())
                delete threadList.at(i);
        }

        log->clearLogs();

        threadList.clear();

        files2copy.clear();

        QStringList files;
        QStringList tempfiles = dirOps->getDirectoryLogFiles(globalDir);

        if(isDeviceSpecific){//get device sepecific log files only
            QString deviceNumber = ui->txtDevice->text();
            QString comboText = ui->comboRegion->currentText();
            QString deviceRegion;

            if(comboText == "ROW")
                deviceRegion = "92054";
            else if(comboText == "NAR")
                deviceRegion = "91954";
            else if(comboText == "CHN")
                deviceRegion = "92154";
            else
                deviceRegion = "92054";//default ROW (Rest of the World)

            QStringList tfiles = tempfiles.filter(QRegExp(deviceRegion));
            if(tfiles.count() > 0){
                files = tfiles.filter(QRegExp(deviceNumber));
            }
        }
        else//get all the log files
            files = tempfiles;


        QStringList occCounts = xml->getOccuranceCount();

        log->initLogList(files.count());

        for(int i=0;i<files.count();i++){
            threadList.append(new LogOperations(files.at(i),argumentList,argumentListType,i));
            //threadList.at(i)->moveToThread(new QThread());
            log->addLogs(files.at(i),i);
            connect(threadList.at(i),SIGNAL(doneReadingLines()),this,SLOT(readingDone()));
            connect(threadList.at(i),SIGNAL(result(QString,int)),this,SLOT(addResultItem(QString,int)));
            connect(threadList.at(i),SIGNAL(finished()),this,SLOT(threadFinished()));
            connect(threadList.at(i),SIGNAL(copyFile(QString,QString)),this,SLOT(getFilesForCopy(QString,QString)));
            threadList.at(i)->setFileCopy(ui->copyCheck->isChecked());
            threadList.at(i)->setOccurTogether(ui->occurTogetherCheck->isChecked());
            threadList.at(i)->setOccuranceCount(occCounts);
        }

        ui->lblLoading->setVisible(true);
        timer->start();
    }
}

void MainWindow::selectOutputDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly);
    if((dir.length() > 2) && (dir != ""))
    {
        log->setPath(dir);
        ui->lblOutputDirectory->setText(dir);
    }
    else
    {
        QString name = qgetenv("USER");
        if (name.isEmpty())
            name = qgetenv("USERNAME");
        qDebug() << name;

        log->setPath("C:\\Users\\"+name+"\\Desktop\\");
        ui->lblOutputDirectory->setText("C:\\Users\\"+name+"\\Desktop\\");
    }

    if((isXMLSelected) && (isDirectorySelected))
    {
        ui->btnStartProcess->setEnabled(true);
        ui->copyCheck->setEnabled(true);
        ui->occurTogetherCheck->setEnabled(true);
    }
    else
    {
        ui->btnStartProcess->setEnabled(false);
        ui->copyCheck->setEnabled(false);
        ui->occurTogetherCheck->setEnabled(false);
    }

}

void MainWindow::selectXML()
{
    QString path = QFileDialog::getOpenFileName(this,"Open XML","","*.xml");

    if((path.length() > 2) && (path != ""))
    {
        ui->lblXMLDirectory->setText(path);
        QString folder = path.mid(0,path.lastIndexOf("/"));
        log->setPath(folder);//if XML selected, set the output path to this directory
        ui->lblOutputDirectory->setText(folder);
        getSearchTerms(path);
        isXMLSelected = true;
    }
    else
    {
        ui->lblXMLDirectory->setText("XML did not selected");
        isXMLSelected = false;
    }

    if((isXMLSelected) && (isDirectorySelected))
    {
        ui->btnStartProcess->setEnabled(true);
        ui->copyCheck->setEnabled(true);
        ui->occurTogetherCheck->setEnabled(true);
    }
    else
    {
        ui->btnStartProcess->setEnabled(false);
        ui->copyCheck->setEnabled(false);
        ui->occurTogetherCheck->setEnabled(false);
    }
}

void MainWindow::openLog(){

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly);

    if((dir.length() > 2) && (dir != ""))
    {
        ui->lblSelectedDirectory->setText(dir);

        globalDir = dir;

        isDirectorySelected = true;
    }
    else{
        isDirectorySelected = false;
    }

    if((isXMLSelected) && (isDirectorySelected))
    {
        ui->btnStartProcess->setEnabled(true);
        ui->copyCheck->setEnabled(true);
        ui->occurTogetherCheck->setEnabled(true);
    }
    else
    {
        ui->btnStartProcess->setEnabled(false);
        ui->copyCheck->setEnabled(false);
        ui->occurTogetherCheck->setEnabled(false);
    }
}

void MainWindow::timerTimeout(){
    threadList.at(threadCounter)->setCopyPath(log->getRawPath());
    threadList.at(threadCounter)->run();
    threadCounter++;
    if(threadCounter >= (threadList.count())){
        timer->stop();
        threadCounter = 0;
    }
    ui->lblLoading->setText("Processing ... \n" + QString::number(readCounter) + "/" +
                            QString::number(threadList.count()));
}

void MainWindow::readingDone(){
    //implemented later
}

void MainWindow::threadFinished(){
    readCounter++;
    ui->lblLoading->setText("Processing ... \n" + QString::number(readCounter) + "/" +
                            QString::number(threadList.count()));
    if(readCounter >= threadList.count()){
         ui->lblLoading->setVisible(false);
         log->setName("Report");
         log->finalizeLogs(argumentList);

         for(int i=0;i<files2copy.count();i=i+2){
            QFile::copy(files2copy.at(i),files2copy.at(i+1));
         }

         qDebug() << "Process done...";
         readCounter = 0;
         threadList.clear();

         int ret = QMessageBox::information(this, tr("Log Analyzer"),
                                        tr("Process done!\n"
                                           "Report created at: \n ") +log->getPath(),
                                        QMessageBox::Ok);
         qDebug() << ret;

     }
}
void MainWindow::deviceSpecificToggle(bool val)
{
    ui->comboRegion->setEnabled(val);
    ui->txtDevice->setEnabled(val);
    isDeviceSpecific = val;
}

void MainWindow::getSearchTerms(QString path)
{
    argumentList.clear();
    argumentListType.clear();
    argumentList = xml->extractSearchTerms(path, argumentListType);
    for(auto i : threadList)
        i->setArguments(argumentList, argumentListType);
}
void MainWindow::addResultItem(QString item, int id)
{
    log->addLogs(item,id);
}
void MainWindow::copyToggle(bool val)
{
    for(auto i : threadList)
        i->setFileCopy(val);
}
void MainWindow::togetherToggle(bool val)
{
    for(auto i : threadList)
        i->setOccurTogether(val);
}
void MainWindow::getFilesForCopy(QString from, QString to)
{
    files2copy << from <<to;
}
