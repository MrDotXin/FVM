#if ! defined(FVMBULLETOBJECT_H_)
#define FVMBULLETOBJECT_H_
#include <QtWidgets/QGraphicsItem>
#include "../Object/FVMGameObject.h"
#include "../../core/FVMDataStruct.h"
#include "../anim/FVMAnimation.h"


namespace scene_core {

        //! @brief
        /*!
            
        */ 
        class _BasicBulletObject
        {  
        public:
            static FVMcore::algo::QuadTree<scene_core::MouseObjectView, QRectF> * enemy_list; ///< Global mouse set enable each bullet to detect the enemy
        public:
            _BasicBulletObject() = delete;
            _BasicBulletObject(const int counts, const char * bulletAddr, const int uniqueStartPos);
           bool advance(); 
           void drawBullet(QPainter *);
           inline QRectF Rect() const { return m_animation.visibleRect(); };
        private:
            scene_core::BulletAnimation m_animation;
        };

        /// @brief ShooterBullet provide most strightforward way to attack a foe object 
        /*! 
            @attention Behaviours from shooter bullet can be consideriably optimalized 
        */ 
        class ShooterBullet : public QGraphicsItem, public _BasicBulletObject
        {
            public:
                ShooterBullet() = delete;
                ShooterBullet(const int counts, const char * bulletAddr, const int uniqueStartPos, 
                    const int height, const int effect);
                ~ShooterBullet() noexcept = default;
            public:
                virtual void advance(int phase) override;
                virtual QRectF boundingRect() const override { return _BasicBulletObject::Rect(); }
                virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *) override;
                void hit(scene_core::MouseObjectView * mouse);
                ShooterBullet * clone() const {return nullptr; }
            private:
                int bulletHarm;
                int bulletEffect;
                int bulletHeight;
        };
}

#endif