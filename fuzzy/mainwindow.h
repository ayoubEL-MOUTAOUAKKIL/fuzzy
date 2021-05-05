#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include<string>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUi() const;
    void addComboBoxElements();
    void setValidators();
    void setImage(QString,QString,QString,QString,QString,QString,QString,QString);
private slots:
    void on_RunButton_clicked();

private:
    Ui::MainWindow *ui;
    QLineEdit* qP;
    QLineEdit* qC;
    QLineEdit* qS;
    QLineEdit* qPr;
};
#endif // MAINWINDOW_H
