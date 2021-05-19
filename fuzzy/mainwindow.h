#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./domain/Car.h"
#include <QMainWindow>
#include <QLineEdit>
#include<string>
#include <vector>
#include "./domain/Car.h"
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
    void on_Car_Changed();

private:
    Ui::MainWindow *ui;
    QLineEdit* powerField;
    QLineEdit* consumptionField;
    QLineEdit* seatsField;
    QLineEdit* priceField;
    std::vector<domain::Car*> vCars;
};
#endif // MAINWINDOW_H
