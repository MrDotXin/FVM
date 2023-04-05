#include "include/Ui/scene/FVMDaintyLand.h"
#include "include/Ui/ctrl/FVMCtrlCore.h"
#include "MainWidget.h"
#include "include/Ui/FVMGameScene.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>


scene_core::daintyLandScene::daintyLandScene(QWidget * mainwin)
    : m_mainwin(mainwin)
{

}


void scene_core::daintyLandScene::createScene()
{
    if (m_mainwin == nullptr) {
        return;
    }

    m_mainwin->setStyleSheet("#FVM{border-image:url(../resource/daintyLand/daintyLand.png)}");
    if (!cached) {
        auto * temple_icon = new FVMctrl_core::svgPolyButton(
            "../resource/daintyLand/level/temple/icon/", 14, 0,
            m_mainwin,
            "../resource/daintyLand/level/temple/icon/", 14, 13,
            "../resource/daintyLand/level/temple/icon/", 14, 0
        );
        temple_icon->triggled_func = [this](){
            dynamic_cast<MainWidget * >(this->m_mainwin)->switchScene
                (new scene_core::Temple(dynamic_cast<MainWidget * >(this->m_mainwin)));
        };

        
        m_ctrl.push_back(temple_icon);
        temple_icon->move(250, 340);

        cached = true;
    }
    for (auto& ctrl : m_ctrl)
        ctrl->show();
}

void scene_core::daintyLandScene::deleteScene()
{
    m_mainwin->setStyleSheet("");
    for (auto & ctrl : m_ctrl)
        ctrl->setHidden(true);
}

void scene_core::daintyLandScene::drawScene(QPainter *)
{

}

void scene_core::daintyLandScene::updateScene()
{

}

void scene_core::daintyLandScene::pauseScene()
{

}