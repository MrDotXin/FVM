#if ! defined(_FVMBATTLECARDDEMO_H_)
#define _FVMBATTLECARDDEMO_H_
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include "../../core/Game/Object/FVMObject.h"
#include "../../core/Game/system/FVMAbstructCardManager.h"
#include <QtGui/QCursor>
#include <unordered_map>

class MainWidget;
namespace FVMcore::battle {class FVMBattleSceneManager;}

namespace FVMctrl_core {


    class FVMFoodCard : public QGraphicsItem
    {
        public:
        // Three states in card item, while in fight manager, it can be selected, and has caching time
        // while in common ui, it can be selected and add to the group 
        // while in compose site, it can be selected and consumed  

            FVMFoodCard(FVMcore::FVMAbstructCardManager * manager, const int id, 
                const int level, const int stratum, const int energy, const char * cardAddr); 
            ~FVMFoodCard() noexcept = default;

        // Paint Event : card level, card pixmap, card selected, card caching period
            virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * );

            virtual QRectF boundingRect() const override{ return QRect(0, 0, qreal(60) * scale, qreal(77) * scale );} 
            inline const QPixmap & getShape() {return m_card;}
            inline void setSelected(bool s = false) { _isSelected = s;}

            void addedToScene(QGraphicsScene *);
            void drawStatus(int status, QPainter * painter);

            virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
            virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
            virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) ;
            virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) ;

            void setScaleSize(qreal d) {scale = d; setScale(d); }
            void setLevel(const int level);
            inline const int& getLevel()   { return m_level; }
            inline const int& getStratum() { return m_stratum; }
            inline const int& getFoodId()  { return food_id; }
            inline const int getEnergy()  { return std::abs(food_energy); }
        private:
            bool _isSelected;
            bool _isLeaved;
            int state;
            int m_level, m_stratum, food_id, food_energy;
            qreal scale = 1;

            QPixmap m_card;
            QPixmap m_card_level;
            QPixmap tied_img;
        // 0, at battle field  
        // 1, in package
        // 2, before battle scene
        // 3, in compose site     
            FVMcore::FVMAbstructCardManager * manager;
    };

    class FVMCard : public QGraphicsItem
    {
        private:  
            QPixmap m_static_items_pic;
        public:
            FVMCard(const char * m_pic);
            ~FVMCard() noexcept = default;

            virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * );
            virtual QRectF boundingRect() const override{ return 
                QRect(0, 0, 
                    m_static_items_pic.width(), 
                    m_static_items_pic.height()); } 

            const QPixmap & getShap() { return m_static_items_pic; }
    };


    class FVMBattleCardDemo : public FVMcore::FVMAbstructCardManager {
        public:
            FVMBattleCardDemo(FVMcore::battle::FVMBattleSceneManager * scene = nullptr, MainWidget * widget = nullptr) : manager(scene), m_mainwin(widget) {} ;
            ~FVMBattleCardDemo() noexcept = default;
            void setScene(FVMcore::battle::FVMBattleSceneManager * scene) 
            {
                 manager = scene;
            }
            
            void setWidget(MainWidget * widget) { m_mainwin = widget;}
            void addCard(FVMcore::FoodObject * food_obj, const int level);
            virtual void cardSelected(FVMFoodCard * card);
            void setUpUiInScene();
            void deleteInscene();
            FVMFoodCard * operator[] (int id);
            virtual QGraphicsScene * scene();
        private:
            std::vector<FVMFoodCard *> _m_card_group;
            FVMCard *flame;
            FVMCard *shovel;
            FVMcore::battle::FVMBattleSceneManager * manager;
            MainWidget * m_mainwin;
    };
}





#endif