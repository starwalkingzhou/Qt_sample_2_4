#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    initSingalSlots();
    setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    fLabCurFile = new QLabel();
    fLabCurFile->setMidLineWidth(150);
    fLabCurFile->setText("当前文件：");
    ui->statusbar->addWidget(fLabCurFile);

    progressBar = new QProgressBar();
    progressBar->setMinimum(5);
    progressBar->setMaximum(50);
    //设置当前进度的值
    progressBar->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progressBar);

    spinFontSize = new QSpinBox();
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    ui->toolBar->addWidget(new QLabel("字体大小"));
    ui->toolBar->addWidget(spinFontSize);


    comboFont= new QFontComboBox();
    ui->toolBar->addWidget(new QLabel("字体"));
    ui->toolBar->addWidget(comboFont);
}

void MainWindow::initSingalSlots()
{
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,SLOT(on_spinBoxFontSize_valueChange(int)));
    // connect(comboFont,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_comboFont_currentIndexChanged(const QString&)));
    connect(comboFont,SIGNAL(currentFontChanged(QFont)),this,SLOT(fontComboBoxFontChanged(QFont)));
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    QTextCharFormat fmt;

    // fmt = ui->textEdit->currentCharFormat();
    if(checked)
    {
        fmt.setFontWeight(QFont::Bold);
    }
    else
    {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}


void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    ui->actFontItalic->setChecked(fmt.fontItalic());
    ui->actFontBold->setChecked(fmt.font().bold());
    ui->actFontUnder->setChecked(fmt.fontUnderline());
}

void MainWindow::on_spinBoxFontSize_valueChange(int FontSize)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(FontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar->setValue(FontSize);
}

// void MainWindow::on_comboFont_currentIndexChanged(const QString &arg1)
// {
//     QTextCharFormat fmt;
//     fmt();
//     ui->textEdit->setCurrentFont(arg1);
// }

void MainWindow::fontComboBoxFontChanged(QFont f)
{
    ui->textEdit->setFont(f);	//设置当前字体

}


void MainWindow::on_actAbout_triggered()
{
    // MainWindow2 *w2 = new MainWindow2(this);
    // w2->setAttribute(Qt::WA_DeleteOnClose);
    // w2->setWindowOpacity(0.7);
    // w2->show();
    QMessageBox::information(this,
                             tr("关于我的"),
                             tr("姓名：周志刚\n学号：2022414040243"),
                             QMessageBox::Ok,
                             QMessageBox::Ok);
}

