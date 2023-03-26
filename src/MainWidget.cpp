#include "MainWidget.h"
#include "include/Ui/FVMGameScene.h"
#include "include/Ui/FVMScenceCore.h"
#include <QtWidgets/QDialog>
#include <QtGui/QPainter>


MainWidget::MainWidget(QWidget * parent)
    : QWidget(parent), m_opg( new FVMctrl_core::FVMOptionGroup(this))
{
    setMouseTracking(true);
    setFixedSize(950, 600);
    setObjectName("FVM");
    // this->setWindowFlag(Qt::FramelessWindowHint);
    m_currentScene = new scene_core::daintyTownScene(this);
    m_currentScene->createScene();
    m_currentScene->updateScene();
    qDebug() << "Widget built";
}

MainWidget::~MainWidget()
{

}

void MainWidget::mousePressEvent(QMouseEvent * me) 
{
    m_currentScene->mousePressEvent(me);
}

void MainWidget::mouseMoveEvent(QMouseEvent * m)
{
    m_currentScene->mouseMoveEvent(m);
}

void MainWidget::paintEvent(QPaintEvent * p)
{  
    QPainter painter(this);
    m_currentScene->drawScene(&painter);
    painter.end();
    QWidget::paintEvent(p);
}

void MainWidget::timerEvent(QTimerEvent *)
{
   m_currentScene->updateScene();

}

void MainWidget::switchScene(scene_core::scene_base * scene)
{
    static int timer_id = 0;
    if (scene->getSceneId() > 100) {
        m_battleManager.setScene(dynamic_cast<scene_core::_FVMAbstructGameScene *>(scene));
        scene = &m_battleManager;
        m_opg->setHidden(true);
        timer_id = startTimer(50);
    } else {m_opg->setHidden(false); if (timer_id != 0) {killTimer(timer_id); timer_id = 0;}}

    m_currentScene->deleteScene();
    m_scene_cache[m_currentScene->getSceneId()] = m_currentScene;
    m_currentScene = scene;
    m_currentScene->createScene();
    //    m_currentScene->updateScene();
}

void MainWidget::switchScene(int id)
{
    auto scene_iter = m_scene_cache.find(id);
    if (id == 0) {
        switchScene(scene_iter == m_scene_cache.end() 
            ? new scene_core::daintyTownScene(this) : scene_iter->second);
    } else if (id == 1) {
        switchScene(scene_iter == m_scene_cache.end() 
            ? new scene_core::daintyLandScene(this) : scene_iter->second);
    }
}

