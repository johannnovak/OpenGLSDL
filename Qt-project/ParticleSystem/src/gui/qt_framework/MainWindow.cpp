#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LogManager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    float proportion = 10;

//    m_ui->OpenGLLayout->setStretchFactor(m_ui->OpenGLLayout, 5);
    //proportion-1)*this->width()/proportion, this->height()));
  //  connect(m_ui->OpenGLLayout, SIGNAL(timeout()), this, SLOT(updated()));

//    m_ui->auxLayout->setGeometry(QRect((proportion-1)*this->width()/proportion, 0,this->width()/proportion, this->height()));
//    connect(m_ui->auxLayout, SIGNAL(timeout()), this, SLOT(updated()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::addOpenGlWidget(Game* _openGLWidget)
{
    m_game = _openGLWidget;
    //_openGLWidget->setFixedSize(QSize(4*this->width()/5, this->height()));

//    m_game->getScene().
  //      m_ui->particlesTab->

    m_ui->OpenGLLayout->addWidget(_openGLWidget,1);
}

void MainWindow::closeEvent (QCloseEvent* _event)
{
    LogManager::closeHandlers();

    _event->accept();
}

void MainWindow::resizeEvent(QResizeEvent* _event)
{
    m_game->setFixedSize(_event->size());
    m_ui->OpenGLLayout->setStretchFactor(m_game,5);
    updateGeometry();
}
