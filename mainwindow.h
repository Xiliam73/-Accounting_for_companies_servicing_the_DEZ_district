#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mytablemodel.h"
#include <QMainWindow>
#include <QTranslator>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class QActionGroup;
class MyTableModel;


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void switchLanguage(QAction *action);

    void on_actionEdit_triggered(bool checked);

    void on_actionAdd_line_triggered();

    void on_actionRemove_triggered();

    void on_actionClose_triggered();

    void on_actionSearch_triggered();

    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;


    MyTableModel *tableModel;


    MyTableModel *model;
    QSortFilterProxyModel *proxyModel;


    QTranslator appTranslator;
    QTranslator qtTranslator;


    QActionGroup *languageActionGroup;


    QString qmPath;


    void dialogAbout();
    void saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void createLanguageMenu();
    void handleNewCompany(const MyTableModel::company &cp);
};
#endif
