#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	fileName = "untitled.txt";
	setWindowTitle(fileName);

#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
	ui->actionPrint->setEnabled(false);
#endif
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
	filePath = QFileDialog::getOpenFileName(this);
	fileName = filePath.split("/").last();
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "error", file.errorString());
	}
	ui->plainTextEdit->setPlainText(file.readAll());
	setWindowTitle(fileName);
	isChangedText = false;
	file.close();
}

void MainWindow::on_actionSave_triggered()
{
	if (filePath.isEmpty())
	{
		filePath = QFileDialog::getSaveFileName(this);
		fileName = filePath.split("/").last();
	}
	save();
}


void MainWindow::on_actionSave_As_triggered()
{
	filePath = QFileDialog::getSaveFileName(this);
	fileName = filePath.split("/").last();
	save();
}

void MainWindow::on_plainTextEdit_textChanged()
{
	if(isFirstChanged){
		isFirstChanged = false;
	} else {
		isChangedText = true;
		setWindowTitle(fileName + "(*)");
	}
}


void MainWindow::save()
{
	QFile file(filePath);
	if(!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(0, "error", file.errorString());
	} else {
		QTextStream stream(&file);
		qDebug() << ui->plainTextEdit->toPlainText();
		stream << ui->plainTextEdit->toPlainText()<< endl;
	}
	setWindowTitle(fileName);
	isChangedText = false;
	file.close();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
	if(isChangedText){
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, fileName, "Dosyada değişiklik yaptınız kaydetmek ister misiniz?", QMessageBox::Yes|QMessageBox::No);

		if (reply == QMessageBox::Yes) {
			if (filePath.isEmpty())
			{
				filePath = QFileDialog::getSaveFileName(this);
				fileName = filePath.split("/").last();
			}
			save();
		} else {
			QApplication::quit();
		}
	}
}


void MainWindow::on_actionCut_triggered()
{
	ui->plainTextEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
	ui->plainTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
	ui->plainTextEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
	ui->plainTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
	ui->plainTextEdit->redo();
}


void MainWindow::on_actionPrint_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
	QPrinter printDev;
#if QT_CONFIG(printdialog)
	QPrintDialog dialog(&printDev, this);
	if (dialog.exec() == QDialog::Rejected)
		return;
#endif // QT_CONFIG(printdialog)
	ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}

