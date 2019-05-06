#pragma once

#include <QMainWindow>
#include <QLabel>

namespace Ui {
    class MainWindow;
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* m_ui;
};