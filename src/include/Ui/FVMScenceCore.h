#if ! defined(_FVMSCENECORE_H_)
#define _FVMSCENECORE_H_
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
// The main scene of the pragmme 

//////////////////////////////
class QWidget;

namespace scene_core {

        class scene_base
            {
                public:
                    scene_base()  = default;
                    virtual ~scene_base() = default;
                    virtual int getSceneId() = 0;
                    virtual void createScene() = 0;             // Initial scene object
                    virtual void deleteScene() = 0;             // Clear the scene 
                    virtual void updateScene() = 0;             // Update some basic info of the scene as the time by
                    virtual void drawScene(QPainter *) = 0;     // Draw updated object in scene 
                    virtual void pauseScene() = 0;              // Suspend the game progress
                    virtual const QRect updateRect() {return QRect(); }      // Return a region that need redraw


                public: // user event
                    virtual void mousePressEvent(QMouseEvent *) {};
                    virtual void mouseMoveEvent(QMouseEvent *) {};
            };

            class daintyTownScene : public scene_base
            {
                public:
                    daintyTownScene(QWidget * mainwin = nullptr);
                    ~daintyTownScene();

                    virtual int getSceneId() { return 0;}
                    virtual void createScene() override;
                    virtual void deleteScene() override;
                    virtual void updateScene() override;
                    virtual void drawScene(QPainter *) override;
                    virtual void pauseScene() override;
                private:
                    QWidget * m_mainwin;
                    std::vector<QWidget *> m_ctrl;
                    bool cached;
            };

            class daintyLandScene : public scene_base
            {
                public:
                    daintyLandScene(QWidget * mainwin = nullptr);
                    ~daintyLandScene() noexcept = default;

                    virtual int getSceneId() { return 1;}
                    virtual void createScene() override;
                    virtual void deleteScene() override;
                    virtual void updateScene() override;
                    virtual void drawScene(QPainter *) override;
                    virtual void pauseScene() override ;

                private:
                    QWidget * m_mainwin;
                    std::vector<QWidget * > m_ctrl;
                    bool cached;
            };

}

#endif