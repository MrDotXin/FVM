#include "MainWidget.h"
#include "include/Ui/scene/FVMScenceCore.h"
#include "include/Ui/scene/FVMDaintyTown.h"
#include "include/Ui/scene/FVMDaintyLand.h"
#include <QtWidgets/QDialog>
#include <QtGui/QPainter>


MainWidget::MainWidget(QWidget * parent)
    : QWidget(parent), m_opg( new FVMctrl_core::FVMOptionGroup(this)), m_currentScene(nullptr)
{
    setMouseTracking(true);
    setFixedSize(950, 600);
    setObjectName("FVM");
    m_currentScene = new scene_core::daintyTownScene(this);
    m_currentScene->createScene();
    m_currentScene->updateScene();
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

/// @brief SwitchScene provide generalized callback to change the viewport of main widget. 
/*! Scene can be divided into two catagories.  
        1. Ctrl scene   : which provide normal interactions and is static. 
        2. Battle scene : which is dynamic and has global timer to manipulate the flash speed.      
*/ 
void MainWidget::switchScene(scene_core::scene_base * scene)
{
    static int timer_id = 0;
    if (scene->getSceneId() > 100) {
    // New FVMBattleSceneManager to take charge of the battle scene to idealize special interaction requirements. 
        m_battleManager.setScene(dynamic_cast<scene_core::_FVMAbstructGameScene *>(scene));
        scene = &m_battleManager;
        m_opg->setHidden(true);
        timer_id = startTimer(50);
    } else {m_opg->setHidden(false); if (timer_id != 0) {killTimer(timer_id); timer_id = 0;}}

    m_currentScene->deleteScene();
    m_scene_cache[m_currentScene->getSceneId()] = m_currentScene;
    m_currentScene = scene;
    m_currentScene->createScene();
}

bool MainWidget::switchScene(int id)
{
    // If scene has been loaded with certain state.
    if (m_scene_cache.count(id) > 0 ) {
        switchScene(m_scene_cache[id]);
        return true;
    }
    return false;
}
