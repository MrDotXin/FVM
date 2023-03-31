#include "include/core/Game/Actions/FVMFoodPolicy.h"
#include "include/Ui/ctrl/FVMBattleCardDemo.h"
#include "include/Ui/FVMGameMap.h"
#include "include/Ui/Object/FVMGameObject.h"
#include "include/core/Game/Object/FVMObject.h"
#include "include/Ui/Object/FVMBulletObject.h"

const QRegion FVMcore::policy::PaiPaiRooster::AttackRange(scene_core::FVMPlainGameMap& map, const int& x, const int& y) {

    int __y  = (y == 0) ? 0 : ((map[y - 1][x]).relativePosY);
    int __x  =  (map[y][x]).relativePosX;
    return QRect(__x + map.getAbsPos().x(), __y + map.getAbsPos().y() + 30, 3000, 5);
}

void FVMcore::policy::PaiPaiRooster::Emit(scene_core::FoodObjectView * Obj_V) {
    // TODO create bullet for PaiPaiRooster    
}

FVMctrl_core::FVMFoodCard * FVMcore::policy::FoodAbstructPolicy::createFoodCard(FVMAbstructCardManager * manager, const int & level, const int& stratum, const bool & tied, const char * cardResAddr, const int& id) {
    return new FVMctrl_core::FVMFoodCard(manager, id, level, stratum, energy(), cardResAddr);  
}

//! @brief use policy to create a food object 
/*!

    @param obj      Provide food resource
    @param card     Provide level     
    @param policy   Provide diversified data and "attacking functions" for each food 
    @return An object, may taken charge of by object pool, which is compatible with Q-Style Object  
*/ 
scene_core::FoodObjectView* FVMcore::policy::FoodAbstructPolicy::createFoodObjectView(FVMcore::FoodObject * obj, FVMctrl_core::FVMFoodCard * card, battle::FVMBattleSceneManager * scene, FoodAbstructPolicy * policy,
                                        const int scene_x, const int scene_y, const int x, const int y, const int block_x, const int block_y, 
                                        privacy::FVMUser *
            ) {
    return new scene_core::FoodObjectView(card, obj, scene, policy, scene_x, scene_y, x, y, block_x, block_y);
}


///////////////////////////////////////////////////////////////////////////////
// UncleCorn
const QRegion FVMcore::policy::UncleCorn::AttackRange(scene_core::FVMPlainGameMap & map, const int& x, const int& y) {
    int __y  = (y == 0) ? 0 : ((map[y - 1][x]).relativePosY);
    int __x  =  (map[y][x]).relativePosX;
    return QRect(__x + map.getAbsPos().x(), __y + map.getAbsPos().y() + 30, 3000, 5);   
}

void FVMcore::policy::UncleCorn::Emit(scene_core::FoodObjectView * Obj_V) {
    
}