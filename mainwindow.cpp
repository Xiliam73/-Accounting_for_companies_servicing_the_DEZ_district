#include "mainwindow.h"
#include "searchdialog.h"
#include "spinboxdelegate.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QActionGroup>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QLibraryInfo>
#include "mytablemodel.h"
#include "maskdelegate.h"
#include "dialogaddline.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tableModel(new MyTableModel(this))
    , model(new MyTableModel(this))
    , proxyModel(new QSortFilterProxyModel(this))
    , languageActionGroup(nullptr)
{
    ui->setupUi(this);

    // ui->tableView->setModel(tableModel);
    // ui->tableView->verticalHeader()->setVisible(false);
    // ui->tableView->setItemDelegateForColumn(0, new SpinBoxDelegate(ui->tableView));
    // ui->tableView->setItemDelegateForColumn(2, new SpinBoxDelegate(ui->tableView));
    // ui->tableView->setItemDelegateForColumn(5, new MaskDelegate("+7(000)000-00-00", this));

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    QAction* aboutAction = new QAction(tr("About"), this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::dialogAbout);

    qApp->installTranslator(&appTranslator);
    qmPath = qApp->applicationDirPath() + "/translations";
    createLanguageMenu();














    proxyModel->setSourceModel(tableModel);

    // Устанавливаем прокси-модель как основную
    ui->tableView->setModel(proxyModel);

    // Настройки таблицы
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(true);

    // Устанавливаем делегаты (уже после установки модели)
    ui->tableView->setItemDelegateForColumn(0, new SpinBoxDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(2, new SpinBoxDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(5, new MaskDelegate("+7(000)000-00-00", this));



}

MainWindow::~MainWindow()
{
    // delete proxyModel;
    // delete sourceModel;

    if(languageActionGroup!=nullptr)
        delete languageActionGroup;

    delete tableModel;

    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    if( ui->tableView->model() == nullptr) ui->tableView->setModel(tableModel);
    QString filePathAndName = QFileDialog::getOpenFileName(this);
    if(!filePathAndName.isEmpty())
        loadFile(filePathAndName);

}

void MainWindow::on_actionSave_triggered()
{
    QString filePathAndName = QFileDialog::getSaveFileName(this);
    if(!filePathAndName.isEmpty())
        tableModel->WriteDataInFile(filePathAndName);
}

void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();

    appTranslator.load("Accounting_for_companies_servicing_the_DEZ_district_" + locale, qmPath);
    locale.chop(3);

    auto isOpen = qtTranslator.load("qt_" + locale, + ".qm", QLibraryInfo::path(QLibraryInfo::TranslationsPath));

    qDebug() << "Translation: " << isOpen;
    ui->retranslateUi(this);
}

void MainWindow::loadFile(const QString &fileName)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // Просто загружаем данные в существующую модель
    if (!tableModel->LoadDataFromFile(fileName)) {
        qWarning() << "Failed to load file:" << fileName;
    }

    QApplication::restoreOverrideCursor();


}

void MainWindow::createLanguageMenu()
{
    languageActionGroup = new QActionGroup(this);
    connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);

    QDir dir(qmPath);

    QStringList fileNames = dir.entryList(QStringList("Accounting_for_companies_servicing_the_DEZ_district_*.qm"));
    for (int i = 0; i < fileNames.size(); ++i) {
        QString locale = fileNames[i];
        locale.remove(0,locale.indexOf("_") + 1);
        locale.remove(0,locale.indexOf("_") + 1);
        locale.remove(0,locale.indexOf("_") + 1);
        locale.remove(0,locale.indexOf("_") + 1);
        locale.remove(0,locale.indexOf("_") + 1);
        locale.remove(0,locale.indexOf("_") + 1);
        locale.remove(0,locale.indexOf("_") + 1);

        locale.truncate(locale.lastIndexOf("."));

        QTranslator translator;
        translator.load(fileNames[i], qmPath);

        QString language = translator.translate("Mainwindow", "English");

        QAction *action = new QAction(tr("&%1 %2").arg(i+1).arg(language));
        action->setCheckable(true);
        action->setData(locale);

        ui->menuLanguage->addAction(action);
        languageActionGroup->addAction(action);
        if(language == "English")
            action->setChecked(true);
    }
}

void MainWindow::saveFile(const QString &fileName)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);


    tableModel->WriteDataInFile(fileName);






    QApplication::restoreOverrideCursor();
}

void MainWindow::dialogAbout()
{
    QMessageBox::information(this,tr("Разработка ПО учёта компаний, обслуживающих район ДЭЗ"),tr("Developed by student ICTMS2-5\n Klimov Ivan Ilich"));
}

void MainWindow::on_actionEdit_triggered(bool checked)
{
    tableModel->changeFlag(checked);

}

void MainWindow::handleNewCompany(const MyTableModel::company &cp)
{
    tableModel->addLine(cp);
}

void MainWindow::on_actionAdd_line_triggered()
{
    if(tableModel != nullptr){
        DialogAddLine dialog(this);
        connect(&dialog, &DialogAddLine::companyAdded, this, &MainWindow::handleNewCompany);
        dialog.exec();
    }
    else
        QMessageBox::information(this, tr("Crash Report"),tr("TableModel doesn't exist"));
}

void MainWindow::on_actionRemove_triggered()
{
    if(tableModel != nullptr){
        int row = ui->tableView->currentIndex().row();
        if(!tableModel->removeRow(row))
            QMessageBox::information(this, tr("Deletion Error"), tr("The table is empty"));

    }
}


void MainWindow::on_actionClose_triggered()
{
    // 1. Получаем модель
    QAbstractItemModel* model = ui->tableView->model();

    // 2. Отсоединяем от TableView
    ui->tableView->setModel(nullptr);

    // 3. Безопасно удаляем
    if (model && model->parent() == nullptr) {  // Если нет родителя
        delete model;
    }

    ui->statusbar->showMessage(tr("Таблица закрыта"), 2000);
}


void MainWindow::on_actionSearch_triggered()
{
    if(tableModel->getFileName().isEmpty())
        return;


    model->LoadDataFromFile(tableModel->getFileName());

    SearchDialog dialog(this);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted) {
        int column = dialog.selectedColumn();
        QString value = dialog.searchValue();

        proxyModel->setFilterKeyColumn(dialog.selectedColumn());
        proxyModel->setFilterFixedString(dialog.searchValue());
    }
    dialog.close();
}


void MainWindow::on_actionClear_triggered()
{
    proxyModel->setFilterFixedString("");
}

