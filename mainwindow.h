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

/**
 * @brief Главное окно приложения для учета компаний.
 *
 * Содержит основную функциональность приложения: таблицу данных,
 * меню, обработку файлов и фильтрацию данных.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор главного окна.
     * @param parent Родительский виджет.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор главного окна.
     */
    ~MainWindow();

private slots:
    /// @name Слоты обработки действий меню
    /// @{
    void on_actionOpen_triggered();  ///< Открыть файл
    void on_actionSave_triggered();  ///< Сохранить файл
    void switchLanguage(QAction *action);  ///< Переключить язык интерфейса
    void on_actionEdit_triggered(bool checked);  ///< Режим редактирования
    void on_actionAdd_line_triggered();  ///< Добавить строку
    void on_actionRemove_triggered();  ///< Удалить строку
    void on_actionClose_triggered();  ///< Закрыть файл
    void on_actionSearch_triggered();  ///< Поиск данных
    void on_actionClear_triggered();  ///< Сбросить фильтр
    /// @}

private:
    Ui::MainWindow *ui; ///< Указатель на UI главного окна.

    /// @name Модели данных
    /// @{
    MyTableModel *tableModel; ///< Основная модель данных.
    MyTableModel *model; ///< Дополнительная модель данных.
    QSortFilterProxyModel *proxyModel; ///< Прокси-модель для фильтрации.
    /// @}

    /// @name Система перевода
    /// @{
    QTranslator appTranslator; ///< Переводчик для строк приложения.
    QTranslator qtTranslator; ///< Переводчик для строк Qt.
    /// @}

    QActionGroup *languageActionGroup; ///< Группа действий для переключения языка.
    QString qmPath; ///< Путь к файлам перевода.

    /// @name Вспомогательные методы
    /// @{
    void dialogAbout(); ///< Показать диалог "О программе".
    void saveFile(const QString &fileName); ///< Сохранить данные в файл.
    void loadFile(const QString &fileName); ///< Загрузить данные из файла.
    void createLanguageMenu(); ///< Создать меню выбора языка.
    void handleNewCompany(const MyTableModel::company &cp); ///< Обработать новую компанию.
    /// @}
};
#endif
