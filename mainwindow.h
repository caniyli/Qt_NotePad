#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private slots:
	void on_actionOpen_triggered();

	void on_actionSave_triggered();

	void on_actionSave_As_triggered();

	void on_plainTextEdit_textChanged();

	void closeEvent (QCloseEvent *event);

	void on_actionCut_triggered();

	void on_actionCopy_triggered();

	void on_actionPaste_triggered();

	void on_actionUndo_triggered();

	void on_actionRedo_triggered();

	void on_actionPrint_triggered();

private:
	Ui::MainWindow *ui;
	void newFile();
	void open();
	void save();
	void saveAs();
	bool isChangedText = false;
	bool isFirstChanged = true;
	QMessageBox *messageBox;
	QString filePath;
	QString fileName;
};
#endif // MAINWINDOW_H
