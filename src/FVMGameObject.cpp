#include "include/Ui/Object/FVMGameObject.h"
#include "QtWidgets/QGraphicsItemAnimation"
#include "QtWidgets/QGraphicsScene"
#include "include/core/Game/Object/FVMObject.h"
#include "include/Ui/ctrl/FVMBattleCardDemo.h"
#include "include/core/Game/system/battle/FVMBattleManager.h"


/// @brief initialize a object in battle field
/// @param card_obj provide level 
/// @param food_obj provide animation resource
/// @param scene    provide workplace
/// @param launcher provide behaviour
/// @param scene_x  provide absoluate positions for the object in scene  
/// @param scene_y 
/// @param x        provide relative positions for the object in scene
/// @param y 
/// @param block_x  provide graided(logical) positions for the object in scene
/// @param block_y 
scene_core::FoodObjectView::FoodObjectView(
                    FVMctrl_core::FVMFoodCard * card_obj, FVMcore::FoodObject * food_obj,FVMcore::battle::FVMBattleSceneManager * scene, FVMcore::policy::FoodAbstructPolicy * launcher, 
                    const int scene_x, const int scene_y, 
                    const int x, const int y, const int block_x, const int block_y
) : m_animation(
        scene_core::_animPlayParameters::Current_Game_Frames, 
        launcher->normal_speed(), 
        launcher->attack_speed(card_obj->getLevel()),
        launcher->animation_normal_speed(),
        launcher->animation_attack_speed(),
        food_obj->getNormalPicCounts(),
        food_obj->getUniquePicStartPos(),
        food_obj->getNormalBehaviourAddress(),
        card_obj->getLevel(),
        launcher->statePt()
        ),
    m_attackRange(launcher->AttackRange(scene->getGameMap(), block_x, block_y)),
    m_pFood_info(card_obj),
    m_pLauncher(launcher),
    m_hp(launcher->hp(card_obj->getLevel())),
    m_harm(launcher->harm(card_obj->getLevel())),
    collideRect(launcher->Rect())
{
    scene->scene()->addItem(this);
    this->moveBy(
        scene_x + x + food_obj->getAnchorX(),
        scene_y + y + food_obj->getAnchorY()
    );
    this->setZValue(block_x * block_y);
    m_animation.switchTobehave(false);
}

void scene_core::FoodObjectView::advance(int phase) {
    static int ticks = 0;
    if (m_animation.advance())
        m_pLauncher->Emit(this);
    if (++ticks == scene_core::_animPlayParameters::Current_Game_Frames) {
        ticks = 0;
    }      
}

void scene_core::FoodObjectView::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *) {
    this->drawPic(painter);
    this->drawStatus(painter);
    this->drawEffect(painter);
}

inline void scene_core::FoodObjectView::drawPic(QPainter * painter) {
    m_animation.render(painter);
}

inline void scene_core::FoodObjectView::drawStatus(QPainter * painter) {

}

inline void scene_core::FoodObjectView::drawEffect(QPainter * painter) {
    // painter->setPen(QPen(Qt::red));
    // painter->drawRect(this->boundingRect());
}




