#pragma once
#include <QtWidgets/QWidget>
#include "include/core/Game/system/battle/FVMBattleManager.h"
#include "include/Ui/FVMGameScene.h"
#include "include/Ui/FVMUi.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QScrollArea>
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
        void switchScene(int id);

        scene_core::scene_base * currentScene() {return m_currentScene; }
    private:
        std::list<QWidget *> m_general_widget_group; 
        std::unordered_map<int, scene_core::scene_base *>  m_scene_cache;

        scene_core::scene_base * m_currentScene = nullptr;
        FVMcore::battle::FVMBattleSceneManager   m_battleManager;
    private:
        FVMctrl_core::FVMOptionGroup * m_opg;

        FVMctrl_core::FVMCardContainerView * m_view_frame;
        QScrollArea * area;
};