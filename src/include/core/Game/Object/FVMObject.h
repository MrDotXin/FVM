#pragma once 
// #include "QtCore/QDebug"
#include <list>
#include <array>
#include <stdarg.h>
#include <QtWidgets/QGraphicsItem>
#include "../Actions/FVMFoodPolicy.h"
// 
class QGraphicsItem;
class QGraphicsScene;

namespace FVMctrl_core {class FVMFoodCard; }
namespace FVMcore::system {class FVMAbstructCardManager; }
namespace FVMcore::battle {class FVMBattleSceneManager; }
namespace FVMcore {

    class __FVMAbstructObject 
    {
        public:
            using _hash_value = int;
            __FVMAbstructObject(_hash_value id) : id(id) {};
            ~__FVMAbstructObject() = default; 

            [[nodiscard]] inline const _hash_value& getId() const {return id; }
        private:
            _hash_value id;
    }; // class __FVMAbstructObject

    /// @brief FoodObject store resource for the food
    //! 
    /*!

    */
    class FoodObject : public __FVMAbstructObject
    { 

        public:    
        private: 
            const int pic_anchor_x; 
            public:  
                [[nodiscard]] const int getAnchorX() const; 
                // void setAnchorX(const int);
        private: 
            const int pic_anchor_y; 
            public:  
                [[nodiscard]] const int getAnchorY() const; 
                // void setAnchorY(const int);
        private: 
            const int pic_res_counts;    
            public:  
                [[nodiscard]] const int getNormalPicCounts() const; 
                // void setNormalPicCounts(const int);
        private: 
            const int bullet_pic_counts;    
            public:  
                [[nodiscard]] const int getBulletPicCounts() const; 
                // void setBulletPicCounts(const int);
        private: 
            const int behavior_pic_start_pos;  
            public:  
                [[nodiscard]] const int getUniquePicStartPos() const; 
                // void setUniquePicStartPos(const int);
        private: 
            const char * bullet_pic_address; 
            public: 
                [[nodiscard]] const char *getBulletPicAddress()const; 
                // void setBulletPicAddress(const char *);
        private: 
            const char * food_pic_address; 
            public: 
                [[nodiscard]] const char *getNormalBehaviourAddress()const; 
                // void setNormalBehavioursAddress(const char *);
        private: 
            const char * food_card_pic_address; 
            public: 
                [[nodiscard]] const char *getCardAddress() const; 
                // void setCardAddress(const char *);
        private: 
            const int bullet_hit_start_pos;
            public: 
                [[nodiscard]] const int getBulletHitStartPos() const; 
                // void setBulletHitStartPos(const int);
        private: 
            policy::FoodAbstructPolicy * food_emit;
            public: 
                [[nodiscard]] policy::FoodAbstructPolicy *getEmitPolicy() const; 
                void setEmitPolicy(policy::FoodAbstructPolicy * p);
        public:
            FoodObject(policy::FoodAbstructPolicy * pcy, const int id, 
                        const int PicResCounts, const int BehavePicStartPos, const char * behavioursAddress,    
                        const char * bulletPicAddress, const int bulletPicCounts, const int bulletHitStartPos,   
                        const int foodOriginAnchorX, const int foodOriginAnchorY,       
                        const char * cardAddress
                    )
                :   __FVMAbstructObject(id), food_emit(pcy), 
                    pic_res_counts(PicResCounts), behavior_pic_start_pos(BehavePicStartPos), food_pic_address(behavioursAddress),                    
                    bullet_pic_address(bulletPicAddress), bullet_pic_counts(bulletPicCounts), bullet_hit_start_pos(bulletHitStartPos),
                    pic_anchor_x(foodOriginAnchorX), pic_anchor_y(foodOriginAnchorY),
                    food_card_pic_address(cardAddress)
            {};

            ~FoodObject() noexcept {if (food_emit != nullptr) delete food_emit; };     
        public :  
            [[nodiscard]] scene_core::FoodObjectView * createFoodObjectView(FVMctrl_core::FVMFoodCard * card, battle::FVMBattleSceneManager * scene, 
                        const int scene_x, const int scene_y, const int x, const int y, const int block_x, const int block_y
                ) {
                    return food_emit->createFoodObjectView(this, card, scene, food_emit, scene_x, scene_y, x, y, block_x, block_y);
            }

            [[nodiscard]] inline FVMctrl_core::FVMFoodCard * createCardObject(
                    FVMAbstructCardManager * manager ,const int& level, const int& stratum, const bool& tied = false)
                {return food_emit->createFoodCard(manager, level, stratum, tied, getCardAddress(), getId()); }
             
    };

inline const int FoodObject::getAnchorX() const {return this->pic_anchor_x; }

inline const int FoodObject::getAnchorY() const{return this->pic_anchor_y; }

inline const int FoodObject::getBulletPicCounts() const {return this->bullet_pic_counts; }

inline const int FoodObject::getNormalPicCounts() const {return this->pic_res_counts; }

inline const int FoodObject::getUniquePicStartPos() const {return this->behavior_pic_start_pos; }

inline const char * FoodObject::getNormalBehaviourAddress() const {return this->food_pic_address; }

inline const char * FoodObject::getBulletPicAddress() const {return this->bullet_pic_address; }

inline const char * FoodObject::getCardAddress() const {return this->food_card_pic_address; }

inline const int FoodObject::getBulletHitStartPos() const {return this->bullet_hit_start_pos; }

inline policy::FoodAbstructPolicy * FoodObject::getEmitPolicy() const {return this->food_emit; }

inline void FoodObject::setEmitPolicy(policy::FoodAbstructPolicy * p) {this->food_emit = p;}


}




