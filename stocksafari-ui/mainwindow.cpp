#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <cpr/cpr.h>
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_tabWidget_currentChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        // Aktien Tab aufgerufen
        QGroupBox* box;
        QVBoxLayout* layoutScrollArea;
        QHBoxLayout* layoutAktienBox;

        //layoutScrollArea->addWidget(box);
        //box->setLayout(layoutAktienBox);

        // ui->vlAktien->addItem(box);

    }
    else {
        // Portfolio aufgerufen
    }
}


void MainWindow::on_btnLogin_clicked()
{
    LoginDialog loginDialog;
    loginDialog.exec();
}

