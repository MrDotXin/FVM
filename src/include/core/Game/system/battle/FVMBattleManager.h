#if ! defined(_FVMBATTLEMANAGER_H_)
#define _FVMBATTLEMANAGER_H_
#include "../../../../Ui/FVMScenceCore.h"
#include "../../../../Ui/ctrl/FVMBattleCardDemo.h"
#include "../../../../Ui/FVMGameMap.h"
#include "../FVMAbstructCardManager.h"
#include "../../../../core/FVMQuadTree.h"

class MainWidget;
namespace FVMctrl_core  {class FVMFoodCard; } 
namespace scene_core    {class _FVMAbstructGameScene; class MouseObjectView;}
namespace FVMcore       {class __FVMMouse; }
namespace FVMcore::privacy {class FVMUser; }
namespace FVMcore::battle {

    //! @class FVMcore::battle::FVMBattleSceneManager
    //! @brief 
    /*!

    */ 
    class FVMBattleSceneManager : public scene_core::scene_base
    {
        public:
            using MouseUnit = FVMcore::algo::QuadTree<scene_core::MouseObjectView, QRectF>; 
        public:
            FVMBattleSceneManager() = default;         
            ~FVMBattleSceneManager() noexcept = default;

            void setScene(scene_core::_FVMAbstructGameScene * scene);
            void setParent(MainWidget * w) {m_mainwin = w; }

// From Basic scene Object
            void updateScene();
            void pauseScene();
            void deleteScene();    
            void drawScene(QPainter *);          
            void createScene();
            const QRect updateRect();
            void mousePressEvent(QMouseEvent * me);   
            void mouseMoveEvent(QMouseEvent * me);         
            QGraphicsScene * scene();
            virtual int getSceneId() { return 3;}
// Ui Base
            void setUpGameUi();
            void progressChanged() {};

// Card Place && Create
            void cardPlaced() {};  
            void cardPlaceHint();   ///< Picture the the OBjectView with lower alpha to show the where it would be placed 

            void cardSelected(FVMctrl_core::FVMFoodCard * card);
// Mouse actions
            void generateMouse(QGraphicsItem * new_mouse);
            scene_core::FVMPlainGameMap& getGameMap() {return m_map; }
            MouseUnit& getMousePosManager() {return mousePosManager; }
// Global Behaviour
        private:
            scene_core::_FVMAbstructGameScene * m_scene = nullptr;
            scene_core::FVMPlainGameMap m_map;

            MouseUnit mousePosManager;
            QGraphicsPixmapItem * m_current_selection = nullptr;
            FVMctrl_core::FVMBattleCardDemo m_card_demo {nullptr};
            bool _isSelected {false};
            bool _isCurrentPosOptional {false};
            FVMctrl_core::FVMFoodCard * current_food_info {nullptr};
            QPointF current_mouse_point;
            QPoint predicted_optimal_pos; 
        private:
            
            MainWidget * m_mainwin;
    };

}

#endif