#if ! defined(FVMDAINTYTOWN_H_)
#define FVMDAINTYTOWN_H_
#include "FVMScenceCore.h"

namespace scene_core {
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
}


#endif