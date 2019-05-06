#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    QObject::connect(m_ui->openGLWidget, &OpenGLWidget::loadedModel, m_ui->treeWidget, &TreeWidget::showSceneNode);

    QObject::connect(m_ui->treeWidget, &TreeWidget::nodeProperty, m_ui->label, &QLabel::setText);
}

MainWindow::~MainWindow()
{

}