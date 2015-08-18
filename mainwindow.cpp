#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::readFile()
{
    bool bRetVal = false;

    QFile file("/proc/cpuinfo");
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            int linesRead = 0;
            while (!file.atEnd())
            {
                QString strOneLine(file.readLine());
                ui->listWidget->addItem(strOneLine.trimmed());

                linesRead++;
                bRetVal = true;
            }

            QString strStatus;
            strStatus.sprintf("File load complete;  %d lines read", linesRead);
            ui->statusBar->showMessage(strStatus);
            file.close();
        }
        else
        {
            QMessageBox errorMsg;
            errorMsg.setText("Could not open file /proc/cpuinfo.");
            errorMsg.exec();
        }
    }
    else
    {
        QMessageBox errorMsg;
        errorMsg.setText("File /proc/cpuinfo does not exist.");
        errorMsg.exec();
    }

    return bRetVal;
}
