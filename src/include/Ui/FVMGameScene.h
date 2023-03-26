#if ! defined(_FVMGAMESCENE_H_)
#define _FVMGAMESCENE_H_
#include "FVMScenceCore.h"
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>


class MainWidget; 

namespace scene_core {
            class FVMPlainGameMap;
            class _FVMAbstructGameScene : public scene_base
            {
                public: 
                    _FVMAbstructGameScene() = default;
                    virtual ~_FVMAbstructGameScene() noexcept = default;
                public:     
                public :
                // from scene_base
                    virtual void createScene() override {};
                    virtual void deleteScene() override {};
                    virtual void updateScene() override {};
                    virtual void pauseScene() override  {};
                    virtual void drawScene(QPainter *) {};

                // unique for game scene 
                    virtual QGraphicsScene * scene()         = 0;
                    virtual void createGameMap(FVMPlainGameMap *) = 0;
                    virtual int getBeginPoint_x()            = 0;
                    virtual int getBeginPoint_y()            = 0; 
                    virtual int getSceneWidth()              = 0;
                    virtual int getSceneHeight()             = 0;
                    
            };

            class Temple : public _FVMAbstructGameScene, public QGraphicsView
            {

                const QPixmap scene_action     = QPixmap("../resource/daintyLand/level/temple/temple.png");
                const QPixmap scene_prospect   = QPixmap("../resource/daintyLand/level/temple/temple_prospect.png");
                const int scene_begin_x    = 192;
                const int scene_begin_y    = 110;
                const int scene_card_begin_x = 81;

                public :
                    Temple(MainWidget *);
                    virtual ~Temple() noexcept = default;

                    virtual void createScene() override;
                    virtual void deleteScene() override;
                    virtual void updateScene() override;
                    virtual void drawScene(QPainter *);
                    virtual void pauseScene() override;
                    virtual void paintEvent(QPaintEvent *) override;
                    virtual void createGameMap(FVMPlainGameMap *) override;
                    virtual int getSceneId() override {return 108; }
                    virtual void mousePressEvent(QMouseEvent *) override;
                    virtual void mouseMoveEvent(QMouseEvent *) override;
                    virtual QGraphicsScene * scene() {return QGraphicsView::scene(); }

                    virtual int getBeginPoint_x() {return scene_begin_x; };
                    virtual int getBeginPoint_y() {return scene_begin_y; };
                    virtual int getSceneWidth()   {return scene_action.width(); }
                    virtual int getSceneHeight()  {return scene_action.height(); }

                    
                private : 
                    QGraphicsScene * m_scene;
                    MainWidget * m_mainwin;
                    QRect _m_update_rect;
                    bool isPaused = false;
                public :
                    inline const QRect updateRect() {return _m_update_rect; }
            };  

}


#endif