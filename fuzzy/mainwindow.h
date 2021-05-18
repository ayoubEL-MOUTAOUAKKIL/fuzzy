#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./domain/Car.h"
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
    void setImage(domain::Car&);
private slots:
    void on_RunButton_clicked();

private:
    Ui::MainWindow *ui;
    QLineEdit* powerField;
    QLineEdit* consumptionField;
    QLineEdit* seatsField;
    QLineEdit* priceField;
};
#endif // MAINWINDOW_H
