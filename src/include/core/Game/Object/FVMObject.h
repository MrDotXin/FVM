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
            
            virtual QGraphicsItem * createObject(battle::FVMBattleSceneManager * scene, 
                    const int scene_x,    
                    const int scene_y,     
                    const int x,           
                    const int y,
                    const int block_y,
                    const int block_x
                    )
                {return nullptr; }
        private:
            _hash_value id;
    };

    class FoodObject : public __FVMAbstructObject
    { 

        public:    
        private: const int pic_anchor_x; 
        public:  [[nodiscard]] const int getAnchorX()const; void setAnchorX(const int);
        private: const int pic_anchor_y; 
        public:  [[nodiscard]] const int getAnchorY()const; void setAnchorY(const int);
        private: const int pic_res_counts;    
        public:  [[nodiscard]] const int getNormalPicCounts()const; void setNormalPicCounts(const int);
        private: const int bullet_pic_counts;    
        public:  [[nodiscard]] const int getBulletPicCounts()const; void setBulletPicCounts(const int);
        private: const int behavior_pic_start_pos;  
        public:  [[nodiscard]] const int getUniquePicStartPos()const; void setUniquePicStartPos(const int);
        private: const char * bullet_pic_address; 
        public: [[nodiscard]] const char *getBulletPicAddress()const; void setBulletPicAddress(const char *);
        private: const char * food_pic_address; 
        public: [[nodiscard]] const char *getNormalBehaviourAddress()const; void setNormalBehavioursAddress(const char *);
        private: const char * food_card_pic_address; 
        public: [[nodiscard]] const char *getCardAddress() const; void setCardAddress(const char *);
        private: const int bullet_hit_start_pos;
        public: [[nodiscard]] const int getBulletHitStartPos() const; void setBulletHitStartPos(const int);
        private: policy::FoodAbstructPolicy * food_emit;
        public: [[nodiscard]] policy::FoodAbstructPolicy *getEmitPolicy() const; void setEmitPolicy(policy::FoodAbstructPolicy * p);
        public:
            FoodObject(int id, 
                                const int _normal_pic_counts,           // 素材总数
                                const int _unique_pic_startPos,         // 行动开始的图片位置
                                const char * _behaviours_address,       // 素材资源地址
                                const int _bullet_pic_counts,           // 子弹素材总数
                                const char * _bullet_pic_address,       // 子弹素材地址
                                const int _Food_origin_archor_x,        // 素材图片偏移x方向
                                const int _Food_origin_archor_y,        // 素材图片偏移y方向
                                const char * _card_address,
                                const int bulletHitStartPos
                                
                    )
                :   __FVMAbstructObject(id),
                    pic_res_counts(_normal_pic_counts), 
                    behavior_pic_start_pos(_unique_pic_startPos),
                    food_pic_address(_behaviours_address),
                    pic_anchor_x(_Food_origin_archor_x),
                    pic_anchor_y(_Food_origin_archor_y),
                    bullet_pic_address(_bullet_pic_address),
                    bullet_pic_counts(_bullet_pic_counts),
                    food_card_pic_address(_card_address),
                    bullet_hit_start_pos(bulletHitStartPos)
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

    class MouseObject : public __FVMAbstructObject {
        public:
            
            struct Animation_State {
                int norm_begin, norm_end, behave_begin, behave_end;
                bool once;
                double velocity;  
                double frequency;        
                int height;
                int reachable;
                double range;
            };
        public:

            using FVMMouseState = std::list<Animation_State>; 
            using pAnimStNode   = std::list<Animation_State>::iterator;            
            using state_node    = pAnimStNode;

        private:
            mutable FVMMouseState m_state_group;
            QRect collideRect;
        private:
            const int _mouse_origin_anchor_x;
            const int _mouse_origin_anchor_y;
            const char *  _mouse_pic_address;
            const char * _mouse_tool_address;
            const int _mouse_pic_counts;
            const int _mouse_tool_pic_counts;

        public:

            MouseObject(int id,
                                const int mousePicCounts,
                                const char * mousePicAddr,
                                const int mouseAnchorX,
                                const int mouseAnchorY,
                                const int mouseToolPicCounts = 0,
                                const char * mouseToolPicAddr = nullptr
                        )
            :  __FVMAbstructObject(id),
                _mouse_origin_anchor_x(mouseAnchorX),
                _mouse_origin_anchor_y(mouseAnchorY),
                _mouse_pic_address(mousePicAddr),
                _mouse_tool_address(mouseToolPicAddr), 
                _mouse_pic_counts(mousePicCounts),
                _mouse_tool_pic_counts(mouseToolPicCounts)
            {}

            ~MouseObject() noexcept = default;

        public:
            virtual QGraphicsItem * createObject(
                        battle::FVMBattleSceneManager * scene, 
                        const int scene_x,     // 动作区域
                        const int scene_y,     
                        const int x,           // 相对位置
                        const int y,
                        const int block_y,
                        const int block_x
                ); 
        public:
            const FVMMouseState * getMouseStateGroups() const {return &m_state_group; }
            inline pAnimStNode state_begin() const {return m_state_group.begin(); }
            inline pAnimStNode state_end()   const {return m_state_group.end();   } 
            inline const char * getNormalBehaviourAddress() const {return _mouse_pic_address; }
            inline const int getNormalBehaviourPicCounts() const {return _mouse_pic_counts; }  
            inline const int getAnchorX() const {return _mouse_origin_anchor_x; }
            inline const int getAnchorY() const {return _mouse_origin_anchor_y; }
            inline void setCollideRect(QRect rect) { collideRect = rect; }
            inline const QRect& getCollideRetc() const {return collideRect; }
        public:
            void build_state(int phase, Animation_State state_groups, ...) {
                va_list ap;
                va_start(ap, state_groups);
                m_state_group.emplace_back(state_groups);
                while(--phase > 0) {
                    state_groups = va_arg(ap, Animation_State);
                    m_state_group.emplace_back(state_groups);
                }
                va_end(ap);
            } 
    };
}




