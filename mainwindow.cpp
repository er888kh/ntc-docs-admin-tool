#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_saveBTN_clicked()
{
    QJsonDocument finalResult;
    QJsonObject result;
    result["deviceName"] = ui->deviceNameLE->text();
    result["deviceDesc"] = ui->deviceDescTE->toPlainText();

    result["guaranteeStart"] = ui->guaranteeStart->selectedDate().toString("yyyy-MM-dd");
    result["guaranteeEnd"] = ui->guaranteeEnd->selectedDate().toString("yyyy-MM-dd");

    result["lifetimeStart"] = ui->lifetimeStart->selectedDate().toString("yyyy-MM-dd");
    result["lifetimeEnd"] = ui->lifetimeEnd->selectedDate().toString("yyyy-MM-dd");

    finalResult.setObject(result);

    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save Device Info"),
                                                    "", //dir
                                                    tr("JSON file (*.json);;All Files (*)"));
    if(filename.isEmpty()){
        return;
    }
    if(!filename.endsWith(".json", Qt::CaseInsensitive)){
        filename += ".json";
    }
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    if(!file.write(finalResult.toJson())){
        QMessageBox::information(this, tr("Unable to write file"),
            file.errorString());
        return;
    }
    return;
}
