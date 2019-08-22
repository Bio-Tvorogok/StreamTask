#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QTextCodec>
#include <QDebug>
#include <QFont>
#include <QTextDocument>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_RadioCP1251_clicked();

    void on_RadioUTF8_clicked();

    void on_checkBoxBoldFront_clicked(bool checked);

    void on_checkBoItalics_clicked(bool checked);

    void on_checkBoxUnderlined_clicked(bool checked);
    void on_comboBox_activated(int index);

    void on_textEdit_textChanged();

    void on_pushButtonSave_clicked();

    void on_actionAbout_triggered();

    void on_pushButtonClose_clicked();

    void on_actionClose_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QTextStream text_stream;
    QString last_file_name = nullptr;

    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;

    QString last_file_data = nullptr;

    void read_file(QString path);
};

#endif // MAINWINDOW_H
