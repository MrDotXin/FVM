#include "include/Ui/Object/FVMBulletObject.h"

/// enemy_list is from FVMBattleSceneManager, to detect if the bullet could hit the enemy object  
FVMcore::algo::QuadTree<scene_core::MouseObjectView, QRectF> * scene_core::_BasicBulletObject::enemy_list = nullptr;
///////////////////////////////////////////////////////////////////////////////
// _BasicBulletObejct  
scene_core::_BasicBulletObject::_BasicBulletObject(const int counts, const char * bulletAddr, const int hitCounts) :
    m_animation(bulletAddr, counts, hitCounts)
{
    
}

// flash the state of the bullet animation by ticks
bool scene_core::_BasicBulletObject::advance() {
    return m_animation.advance();
}
 
void scene_core::_BasicBulletObject::drawBullet(QPainter * painter) {
    m_animation.render(painter);
}

///////////////////////////////////////////////////////////////////////////////
// ShooterBullet 

//! @brief main constructor(called in most cases) 
/*! Shooter bullet provide most strightforward way to attack a foe object 

    @warning parameter should be fulled provided but once 

    @param counts For animation resource, total number of the resource : provided by FoodObject          
    @param bulletAddr For animation resource, where to find the resource group : provided by FoodObject
    @param hitcounts For animation resource, the animation start pos while the bullet hit the enemy : provide by FoodObject 
    @param row Block Y of the bullet object, an emeny can be hited only when the bullet hold the same row with it  
    @param effect Some appeded enchantment while the bullet hit the enemy.   
*/
scene_core::ShooterBullet::ShooterBullet(const int counts, const char * bulletAddr, const int uniqueStartPos, const int row, const int effect) : 
    _BasicBulletObject(counts, bulletAddr, uniqueStartPos)
{
    
}

//! @brief advance() take charge of the animiation && the detect 
void scene_core::ShooterBullet::advance(int) {

}

void scene_core::ShooterBullet::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *) {
    _BasicBulletObject::drawBullet(painter);
}

//! @brief Call by mouseUnit type pred
/*! ShooterBullet::hit would do follow jobs with FVMBattleSceneManager::mouse_list:
        [1]. Detect : 
            @if Mouse is hitable, which means the mouse is in the same hight, same row, alive, or the
                status of bullet matches what is required to reach the mouse.
        [2]. Attack :
            @if The harm the bullet caused has killed the mouse, there is no need to execute step 3, the mouse 
                become unreachable thereby.
        [3]. Adding effect
            @if The bullet is appended with certain enchantment(AOE, freeze, fire, poison .etc), then if mouse 
                is reachable, mouse can be appended with certain debuffs. 
*/  
void scene_core::ShooterBullet::hit(scene_core::MouseObjectView * mouse) {

}






