#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView_points->load(QUrl("http://www.google.com"));
    load_cmb();
    qDebug()<<ui->cmb_hora->itemText(ui->cmb_hora->currentIndex());
    auto i=0;
    i++;
    qDebug()<<i;
}
void MainWindow::load_cmb()
{
    ifstream input("tipo_crimen.csv");
    if(input.is_open())
        qDebug()<<"Tipo de Crimen is open"<<endl;
    else
        qDebug()<<"Tipo de Crimen doesn't exist"<<endl;
    string buff;
    while(!input.eof())
    {
        getline(input,buff);
        if(!buff.empty())
            ui->cmb_tc->addItem(QString::fromStdString(buff));
    }

    ifstream input2("hora.csv");
    if(input2.is_open())
        qDebug()<<"Hora is open"<<endl;
    else
        qDebug()<<"Hora doesn't exist"<<endl;
    buff.clear();
    while(!input2.eof())
    {
        getline(input2,buff);
        if(!buff.empty())
            ui->cmb_hora->addItem(QString::fromStdString(buff));
    }


    ifstream input3("pdistrict.csv");
    if(input3.is_open())
        qDebug()<<"Pdistrict is open"<<endl;
    else
        qDebug()<<"Pdistrict doesn't exist"<<endl;
    buff.clear();
    while(!input3.eof())
    {
        getline(input3,buff);
        if(!buff.empty())
            ui->cmb_pd->addItem(QString::fromStdString(buff));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
