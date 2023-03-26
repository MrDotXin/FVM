#if ! defined (_FVMGAMEOBJECT_H_)
#define _FVMGAMEOBJECT_H_

#include <QtWidgets/QGraphicsItem>
#include "../anim/FVMAnimation.h"

namespace FVMcore::battle {class FVMBattleSceneManager; }
namespace FVMctrl_core    {class FVMFoodCard; }
namespace FVMcore::policy {class FoodAbstructPolicy; }
namespace FVMcore         {class FoodObject;}
namespace scene_core {

        class FoodObjectView : public QGraphicsItem
        { 
            using PFood_Launcher = FVMcore::policy::FoodAbstructPolicy *;
            using PFood_Info     = FVMctrl_core::FVMFoodCard *;
            public:
                FoodObjectView(
                    FVMctrl_core::FVMFoodCard * card_obj, 
                    FVMcore::FoodObject * food_obj,
                    FVMcore::battle::FVMBattleSceneManager * scene, 
                    FVMcore::policy::FoodAbstructPolicy * launcher,
                    const int scene_x,  
                    const int scene_y,     
                    const int x,             
                    const int y,
                    const int block_y,
                    const int block_x
                );
                ~FoodObjectView() noexcept = default;
                virtual void advance(int phase) override;
                virtual QRectF boundingRect() const override {return m_animation.visibleRect();}
                virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
                // specifying actions for each object
                inline void drawStatus(QPainter *);
                inline void drawPic(QPainter *);
                inline void drawEffect(QPainter *);
                inline const QRect& Rect() {return collideRect; };
                inline FVMcore::battle::FVMBattleSceneManager * getManager() {return manager; };

                FoodObjectView * clone();
            private:
                FoodAnimation  m_animation; 
                PFood_Launcher m_pLauncher;
                PFood_Info     m_pFood_info;
                FVMcore::battle::FVMBattleSceneManager * manager;
                QRegion        m_attackRange;
                QRect collideRect;
                qreal  m_hp;
                qreal  m_harm;                
        };

        class MouseObjectView : public QGraphicsItem {
            public:
                MouseObjectView(
                        FVMcore::battle::FVMBattleSceneManager * scene, 
                        const int scene_x,          // 动作区域
                        const int scene_y,     
                        const int x,                // 绝对位置
                        const int y,
                        const int block_y,
                        const int block_x
                );

                ~MouseObjectView() noexcept = default;
                inline void drawPic(QPainter *);
                inline void drawEffect(QPainter *);
                inline void drawStatus(QPainter *);
                virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *);
                virtual QRectF boundingRect() const override;
                virtual void  advance(int phase);
                virtual QRect Rect();
        };
}


#endif




