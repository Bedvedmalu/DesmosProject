#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "functionrepository.h"

#include <QMainWindow>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void addFunctionRow();
    void createFunctionRow(int id);
    void removeFunctionRow(QWidget* row);
    void rebuildSliders(int id, QVBoxLayout* layout);
    void showSettings();

    Ui::MainWindow* ui;
    QPointer<QWidget> draggedRow;
    int nextFunctionId = 0;
    FunctionRepository repository;
};

#endif
