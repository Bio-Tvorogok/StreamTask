#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString mPath = "C:/";
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(mPath);
    ui->treeView->setModel(dirModel);
    //ui->treeView->setRootIndex(dirModel->index(mPath));

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot |
                            QDir::Files);
    fileModel->setRootPath(mPath);
    ui->listView->setModel(fileModel);
    ui->listView->setRootIndex(fileModel->index(mPath));

    for (int i = 1; i < dirModel->columnCount(); ++i)
        ui->treeView->hideColumn(i);

    text_stream.setCodec(QTextCodec::codecForName("CP1251"));
    text_stream.setAutoDetectUnicode(false);
    ui->RadioCP1251->click();

    ui->textEdit->setEnabled(false);
    ui->pushButtonSave->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    //last_file_name = nullptr;

    QString mPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fileModel->setRootPath(mPath));
    ui->textEdit->clear();
    ui->textEdit->setEnabled(false);
    ui->pushButtonSave->setEnabled(false);
    ui->listView->clearSelection();
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->pushButtonSave->setEnabled(false);
    if (index.isValid()){
        ui->textEdit->setEnabled(true);
        QString mPath = fileModel->fileInfo(index).absoluteFilePath();
        read_file(mPath);
    } else {
        ui->textEdit->setEnabled(false);
    }
}


void MainWindow::on_RadioCP1251_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251"));
    read_file(last_file_name);
}

void MainWindow::on_RadioUTF8_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    read_file(last_file_name);
}

void MainWindow::read_file(QString path){

    QFile file(path);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        last_file_name = path;

        text_stream.setDevice(&file);
        ui->textEdit->clear();
        ui->textEdit->append(text_stream.readAll());
        last_file_data = ui->textEdit->toPlainText();
        file.close();
    }
}

void MainWindow::on_checkBoxBoldFront_clicked(bool checked)
{
    if (checked){
        ui->textEdit->setFontWeight(QFont::Bold);
    } else {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
    if (last_file_data != nullptr) {
        read_file(last_file_name);
    }
}

void MainWindow::on_checkBoItalics_clicked(bool checked)
{
    if (checked){
        ui->textEdit->setFontItalic(true);
    } else {
        ui->textEdit->setFontItalic(false);
    }
    if (last_file_data != nullptr) {
        read_file(last_file_name);
    }
}

void MainWindow::on_checkBoxUnderlined_clicked(bool checked)
{
    if (checked){
        ui->textEdit->setFontUnderline(true);
    } else {
        ui->textEdit->setFontUnderline(false);
    }
    if (last_file_data != nullptr) {
        read_file(last_file_name);
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    switch (index) {
    case 0:
        ui->textEdit->setTextColor(QColor(Qt::GlobalColor::black));
        break;
    case 1:
        ui->textEdit->setTextColor(QColor(Qt::GlobalColor::white));
        break;
    case 2:
        ui->textEdit->setTextColor(QColor(Qt::GlobalColor::red));
        break;
    case 3:
        ui->textEdit->setTextColor(QColor(Qt::GlobalColor::blue));
        break;
    }
    if (last_file_data != nullptr) {
        read_file(last_file_name);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    ui->pushButtonSave->setEnabled(true);
}


void MainWindow::on_pushButtonSave_clicked()
{
    auto path = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), "txt file (*.txt)");
    QFile file(path);
    if (file.open(QFile::WriteOnly)) {
        text_stream.setDevice(&file);
        QString text = ui->textEdit->toPlainText();
        text.replace("\n", "\r\n");
        text_stream << text;
       // file << ui->textEdit->toPlainText();
    } else {
        QMessageBox::warning(this, "File Error", "file not open", QMessageBox::Ok);
    }

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "designed by bio-tvorogok");
}

void MainWindow::on_pushButtonClose_clicked()
{
    QApplication::quit();
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSave_triggered()
{
    if (ui->textEdit->isEnabled())
        on_pushButtonSave_clicked();
}
