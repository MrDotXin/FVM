#include "include/Ui/FVMScenceCore.h"
#include "include/Ui/ctrl/FVMCtrlCore.h"
#include "MainWidget.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>


scene_core::daintyTownScene::daintyTownScene(QWidget * parent)
    : m_mainwin(parent), cached(false)
{   
    
}

scene_core::daintyTownScene::~daintyTownScene()
{

}

void scene_core::daintyTownScene::createScene()
{    
    if (m_mainwin == nullptr)
            return;
    m_mainwin->setStyleSheet("#FVM{border-image:url(../resource/daintyTown/daintyTown.png)}");
    if (cached == false) {
    /////////////////////////////////////////// basic scene built      
        auto * ceremonyCake = new FVMctrl_core::SplicerPlayer<FVMctrl_core::imageSplicer>(
            m_mainwin,
            31,
            "../resource/daintyTown/cake/",
            "png"
        );
        m_ctrl.push_back(ceremonyCake);
        auto * catAnim = new FVMctrl_core::SplicerPlayer<FVMctrl_core::svgSplicer>(
            m_mainwin,
            23,
            "../resource/daintyTown/catHead/", 0
        );
        m_ctrl.push_back(catAnim);
        auto * cakeContour = new FVMctrl_core::svgPolyButton(
            "../resource/daintyTown/cake/0.svg",
            m_mainwin
        );
        m_ctrl.push_back(cakeContour);
        auto * game = new FVMctrl_core::svgPolyButton(
            "../resource/daintyTown/gameStartButton/", 22, 0,
            m_mainwin,
            "../resource/daintyTown/gameStartButton/", 22, 0,
            "../resource/daintyTown/gameStartButton/", 22, 13
        );

        m_ctrl.push_back(game);
        auto * shipContour = new FVMctrl_core::svgPolyButton(
            "../resource/daintyTown/shipContour.svg",
            m_mainwin
        );
        m_ctrl.push_back(shipContour);

        auto * flan1 = new FVMctrl_core::SplicerPlayer<FVMctrl_core::imageSplicer>(
            m_mainwin,
            4, "../resource/daintyTown/flan1/" 
        );

        m_ctrl.push_back(flan1);

        game->triggled_func = [this]() {
            dynamic_cast<MainWidget *>(this->m_mainwin)->switchScene(1);
        };
        shipContour->triggled_func = game->triggled_func;


        cakeContour->raise();
        flan1->raise();
        flan1->move(536, 276);
        ceremonyCake->move(388, 0);
        catAnim->move(834, 238);
        game->move(655, 401);
        cakeContour->move(413, 105);
        shipContour->move(406, 278);

        cached = true;
    }
    for (auto & ctrl : m_ctrl)
        ctrl->show();
    /////////////////////////////////////////////////////////
}

void scene_core::daintyTownScene::deleteScene()
{
    m_mainwin->setStyleSheet("");
    for (auto& ctrl : m_ctrl)
        ctrl->setHidden(true);
}

void scene_core::daintyTownScene::updateScene()
{
    
}

void scene_core::daintyTownScene::pauseScene()
{
    
}

void scene_core::daintyTownScene::drawScene(QPainter * painter )
{
    static QPixmap ship("../resource/daintyTown/ship.png");
    painter->drawPixmap(QRect(495, 262, ship.width(), ship.height()), ship);

}