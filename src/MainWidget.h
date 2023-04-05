#pragma once
#include <QtWidgets/QWidget>
#include "include/core/Game/system/battle/FVMBattleManager.h"
#include "include/Ui/FVMGameScene.h"
#include "include/Ui/FVMUi.h"
#include <QtGui/QMouseEvent>
#include <list>
#include <unordered_map>
// display all the scene

class MainWidget : public QWidget
{

    public:
        MainWidget(QWidget * parent = nullptr);
        ~MainWidget();
    public:
        virtual void paintEvent(QPaintEvent *) override;
        virtual void mousePressEvent(QMouseEvent * ) override;
        virtual void mouseMoveEvent(QMouseEvent * ) override;
        virtual void timerEvent(QTimerEvent *) override;

    public:
        void switchScene(scene_core::scene_base *);
        bool switchScene(int id);

        scene_core::scene_base * currentScene() {return m_currentScene; }
    private:
        std::unordered_map<int, scene_core::scene_base *>  m_scene_cache; ///< stone scenes having been loaded 
        FVMcore::battle::FVMBattleSceneManager             m_battleManager;
        scene_core::scene_base *                           m_currentScene;
    private:        
        FVMctrl_core::FVMCardContainerView * m_view_frame;
        FVMctrl_core::FVMOptionGroup *       m_opg;
};