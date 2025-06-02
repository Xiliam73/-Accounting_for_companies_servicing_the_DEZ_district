#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePathAndName = QFileDialog::getOpenFileName(this);
    if(!filePathAndName.isEmpty())
        loadFile(filePathAndName);

}

void MainWindow::on_actionSave_triggered()
{
    QString filePathAndName = QFileDialog::getSaveFileName(this);
    if(!filePathAndName.isEmpty())
        saveFile(filePathAndName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Application", QString("Can't read file %1: \n%2").arg(fileName, file.errorString()));
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QTextStream in(&file);
    QApplication::restoreOverrideCursor();

    // in.readAll() - весь текст файла с которым можно работать



    file.close();
}

void MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Application", QString("Can't write file %1: \n%2").arg(fileName, file.errorString()));
        return;
    }
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QTextStream out(&file);
    QApplication::restoreOverrideCursor();
}

