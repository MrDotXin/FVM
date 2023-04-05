#if ! defined(FVMDAINTYLAND_H_)
#define FVMDAIMTYLAND_H_
#include "FVMScenceCore.h"

namespace scene_core {

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




#endif // dinaty land