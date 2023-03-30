#if ! defined(FVMFOODPOLICY_H_)
#define FVMFOODPOLICY_H_
#include <QtGui/QRegion>

namespace FVMctrl_core {class FVMFoodCard; }
namespace FVMcore::privacy {class FVMUser{}; }
namespace scene_core {
        class FVMPlainGameMap; 
        class FoodObjectView; 
}

namespace FVMcore { class FoodObject; }
namespace FVMcore {class FVMAbstructCardManager; }
namespace FVMcore::battle {class FVMBattleSceneManager; }
namespace FVMcore::policy {
    

    // TODO Emit() outght to create debuff groups for the bullet, which would be attached to the foe. 
    
    /// @brief  Template functions for all food object while in battle-field 
    ///
    /*!
        FoodAbstructPolicy requires 
            [1]. FVMUser to gain ampl-data for concrete food object 
            [2]. FVMFoodCard to provide same object at different grades or even stratums
            [3]. Some purified template members to provide including basic properties, ranges, behave speed, offset rect and energy.
        @attention : 
            Member : statePt() is used to provide the position where to draw the food's grade.
            @if a food can change it's place automatically, then member velocity provide it's move speed.
            @if a food can create a flying object, then member Emit(...) diversify their behvaiours, which is called by FoodObjectView  
        @note Derive your new class based on FoodAbstructPolicy to provide the basic info of the food object newly added.            
    */
    class FoodAbstructPolicy {
         
        public:
            FoodAbstructPolicy() = default;
            ~FoodAbstructPolicy() noexcept = default;

            virtual const QRegion AttackRange(scene_core::FVMPlainGameMap & mp, const int& x, const int& y) = 0; 
            virtual const QRect Rect() = 0;     
            virtual const qreal velocity(const int& level, qreal ampl = 1) = 0;
            virtual const qreal harm(const int& level, qreal ampl = 1)     = 0;
            virtual const qreal hp(const int& level, qreal ampl = 1)       = 0;
            virtual const qreal attack_speed(const int& level, qreal ampl = 1) = 0;
            virtual const qreal normal_speed() = 0;
            virtual const qreal animation_normal_speed() = 0;
            virtual const qreal animation_attack_speed() = 0;
        /// @brief energy() provide the required energy to create a FoodObjectView
        /// @if the return of energy is negative, then the energy would increase by 50 every time the object is created.
            virtual const int energy() = 0;     
            virtual const QPoint statePt() = 0;
            virtual void Emit(scene_core::FoodObjectView * ) = 0; 
            [[nodiscard]] FVMctrl_core::FVMFoodCard*  createFoodCard(FVMAbstructCardManager * manager, const int & level, const int& stratum, const bool & tied, const char * cardResAddr, const int& id);
            [[nodiscard]] scene_core::FoodObjectView* createFoodObjectView(FVMcore::FoodObject * obj, FVMctrl_core::FVMFoodCard * card, battle::FVMBattleSceneManager * scene, FoodAbstructPolicy * policy,
                                        const int scene_x, const int scene_y, const int x, const int y, const int block_y, const int block_x, 
                                        privacy::FVMUser * user = nullptr
            );
    };

   class PaiPaiRooster : public FoodAbstructPolicy {

        public:
            PaiPaiRooster() = default;
            ~PaiPaiRooster() noexcept = default;

            using FoodAbstructPolicy::createFoodCard;
            virtual const QRegion AttackRange(scene_core::FVMPlainGameMap & mp, const int& x, const int& y) override;
            virtual void Emit(scene_core::FoodObjectView * ) override;
            virtual const qreal velocity(const int& level, qreal ampl = 1) {
                return ampl * 2.5;
            }
            virtual const qreal harm(const int& level, qreal ampl = 1) {
                return 1 * ampl + 1 * level * 0.4;
            }
            virtual const qreal hp(const int& level, qreal ampl = 1) {
                return 5 * ampl;
            }
            virtual const qreal attack_speed(const int& level, qreal ampl = 1) {
                return ampl * 2.5;
            }
            virtual const qreal normal_speed() {
                return animation_normal_speed();
            }
            virtual const qreal animation_normal_speed() {
                return 1.5;
            };
            virtual const qreal animation_attack_speed() {
                return 1.30;
            }; 
            virtual const QRect Rect() {
                return QRect();
            }
            virtual const int energy() {
                return 145;
            }
            virtual const QPoint statePt() {
                return QPoint(11, 55);
            }
   };

   class uncleCorn : public FoodAbstructPolicy {

        public:
            uncleCorn() = default;
            ~uncleCorn() noexcept = default;

            using FoodAbstructPolicy::createFoodCard;

            virtual const QRegion AttackRange(scene_core::FVMPlainGameMap & mp, const int& x, const int& y) override;
            virtual void Emit(scene_core::FoodObjectView * ) override {}
            virtual const qreal velocity(const int& level, qreal ampl = 1) {
                return ampl * 2.5;
            }
            virtual const qreal harm(const int& level, qreal ampl = 1) {
                return 1 * ampl + 1 * level * 0.4;
            }
            virtual const qreal hp(const int& level, qreal ampl = 1) {
                return 5 * ampl;
            }
            virtual const qreal attack_speed(const int& level, qreal ampl = 1) {
                return ampl * 2.5;
            }
            virtual const qreal normal_speed() {
                return animation_normal_speed();
            }
            virtual const qreal animation_normal_speed() {
                return 1.5;
            };
            virtual const qreal animation_attack_speed() {
                return 1.30;
            }; 
            virtual const QRect Rect() {
                return QRect();
            }
            virtual const int energy() {
                return -250;
            }
            virtual const QPoint statePt() {
                return QPoint(13, 60);
            };
   };       
};


#endif