#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "set.h"
#include <QPushButton>
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <string>
#include <QTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(9);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setFont(QFont("wenquanyi",16));
    ui->pushbutton_3->setEnabled(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setStretchLastSection(true);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(this->width(),this->height());
    ui->pushbutton_2->setEnabled(false);

    count=0;
    second=0;
    minute=0;
    hour=0;
    Timer= new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(Time()));

    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->lineEdit_3->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->horizontalHeader()->setHidden(true);
}
void MainWindow::Time()
{
    count+=1;
    if(count==100)
    {
        count=0;
        second+=1;
        if(second==60)
        {
            second=0;
            minute+=1;
            if(minute==60)
            {
                minute=0;
                hour+=1;
                if(hour==24)
                {
                    hour=0;
                }
            }
        }
    }
    QString hourstr = QString::number(hour);
    QString minutestr = QString::number(minute);
    QString secondstr = QString::number(second);
    SetLength(&hourstr);
    SetLength(&minutestr);
    SetLength(&secondstr);
    Display(hourstr,minutestr,secondstr);
}

void MainWindow::Display(QString hour, QString minute, QString second)
{
    ui->lineEdit->setText(hour);
    ui->lineEdit_2->setText(minute);
    ui->lineEdit_3->setText(second);
}

void MainWindow::Starttimer()
{
    Timer->start(10);
}

void MainWindow::Resettimer()
{
        ui->lineEdit->setText("00");
        ui->lineEdit_2->setText("00");
        ui->lineEdit_3->setText("00");
        count=0;
        second=0;
        minute=0;
        hour=0;
}

void MainWindow::Stoptimer()
{
    Timer->stop();
}

void MainWindow::SetLength(QString *str)
{
    if(str->length()<2)
    {
        str->insert(0,"0");
    }
}

void MainWindow::on_pushbutton_1_clicked()
{
    int i,j;
    for(i=0;i<9;i++)
    {    for(j=0;j<9;j++)
        {
                board[i][j]=0;
                trial[i][j]=0;
                table[i][j]=0;
        }
    }
    for(i=0;i<9;i++)
    {    for(j=0;j<9;j++)
        {

                QTableWidgetItem *blank=new QTableWidgetItem();
                blank->setText("");
                ui->tableWidget->setItem(i,j,blank);
                //ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled);

        }
    }

    cnt=0;
    sudokugenerate();

    for(i=0;i<9;i++)
    {    for(j=0;j<9;j++)
        {
            if(board[i][j]!=0)
            {
                QTableWidgetItem *name=new QTableWidgetItem();
                name->setText(QString::number(board[i][j]));
                ui->tableWidget->setItem(i,j,name);
                QFont font=ui->tableWidget->item(i,j)->font();
                font.setBold(true);
                ui->tableWidget->item(i,j)->setFont(font);
                ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled);
            }
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
        }
    }
    ui->pushbutton_1->setText(tr("RESET"));
    ui->pushbutton_3->setEnabled(true);
    ui->pushbutton_2->setEnabled(true);


    Resettimer();
    Starttimer();

}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushbutton_2_clicked()
{

    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            board[i][j]=trial[i][j];
            if(board[i][j]!=0)
            {
                ui->tableWidget->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
                QTableWidgetItem *name=new QTableWidgetItem();
                name->setText(QString::number(board[i][j]));
                ui->tableWidget->setItem(i,j,name);
                QFont font=ui->tableWidget->item(i,j)->font();
                font.setBold(true);
                ui->tableWidget->item(i,j)->setFont(font);
                ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled);

            }
            else
            {
                QTableWidgetItem *blank=new QTableWidgetItem();
                blank->setText("");
                ui->tableWidget->setItem(i,j,blank);
            }
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
        }
    }
    ui->pushbutton_3->setEnabled(true);
    Resettimer();
    Starttimer();
}


void MainWindow::on_tableWidget_cellChanged(int row, int column)
{ 


    //qDebug()<<n<<table[row][column]<<board[row][column]<<endl;

    //if(n<0||n>9)
    std::string a;
    a=ui->tableWidget->item(row,column)->text().toStdString();
    int n;
    n=ui->tableWidget->item(row,column)->text().toInt();

     if(a==""||(n<=9&&n>=1))
     {

         int m,k;
         int i=row,j=column;
         bool t=true;
         for(m=0;m<9;m++)
         {
             if(board[i][m]==n&&m!=j)
             {
                 t=false;
                 break;
             }
         }
         for(m=0;m<9;m++)
         {
             if(board[m][j]==n&&m!=i)
             {
                 t=false;
                 break;
             }
         }
         for(m=i-i%3;m<=i-i%3+2;m++)
         {
             for(k=j-j%3;k<=j-j%3+2;k++)
             {
                  if(m==i&&k==j)
                      continue;
                  if(board[m][k]==n)
                  {
                      t=false;
                      break;
                  }
              }
         }

         if(!t)
         {
             ui->tableWidget->item(row,column)->setForeground(QBrush(QColor(255,0,0)));
         }
         else {
             board[row][column]=n;
             ui->tableWidget->item(row,column)->setForeground(QBrush(QColor(0,0,0)));
         }
         if(a=="")
             board[row][column]=0;
     }

     else{
         QMessageBox::warning(this,tr("Warning!"),tr("Invalid Input!"));
         ui->tableWidget->item(row,column)->setText("");
     }
}
void MainWindow::on_pushbutton_3_clicked()
{
    int i,j;
    bool t=true;
    ui->pushbutton_3->setEnabled(true);
    for(i=1;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(board[i][j]==0)
                t=false;
        }
    }

    if(t)
    {
        bool p=true;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if(board[i][j]!=table[i][j])
                {
                    p=false;
                    break;
                }
            }
        }
        if(p)
        {
             QMessageBox::information(this,tr("Congratulations!"),tr("You have completed the map!"));
             Stoptimer();
        }
    }
    else {
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                ui->tableWidget->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
                if(ui->tableWidget->item(i,j)->text().toInt()!=table[i][j])
                {
                    QTableWidgetItem *name=new QTableWidgetItem();
                    name->setText(QString::number(table[i][j]));
                    ui->tableWidget->setItem(i,j,name);
                    ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
                    Stoptimer();
                    Resettimer();
                }
            }
        }
    }


}

