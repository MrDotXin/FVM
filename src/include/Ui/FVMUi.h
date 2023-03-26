#if ! defined(_FVMUI_H_)
#define _FVMUI_H_
#include "ctrl/FVMCtrlCore.h"
#include "../core/Game/system/FVMAbstructCardManager.h"
#include "ctrl/FVMBattleCardDemo.h"
#include <QtWidgets/QWidget>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>

// specified ctrl for project
// general group would compiler into plugins
class MainWidget;
class QGraphicsView;
class QGraphicsScene;

template<class T>
    using FVM2DArray = std::vector<std::vector<T> >;

namespace FVMctrl_core{
////////////////////////
// forward def 
    class FVMFoodCard;
    class FVMCardContainerView;
    class FVMGeneralScrollBar;
    FVMGeneralScrollBar * installFVMScrollBar(QGraphicsView *, const QRect, const QSize);    


    class FVMOptionGroup : public QWidget   
    {
        public: 
            FVMOptionGroup(MainWidget * parent);
            ~FVMOptionGroup() noexcept = default;

            QPoint drag_pos;
            bool _is_draging;
            virtual void mousePressEvent(QMouseEvent *);
            virtual void mouseMoveEvent(QMouseEvent *);
            virtual void mouseReleaseEvent(QMouseEvent *);
            virtual void paintEvent(QPaintEvent *);
        private:
            FVMctrl_core::polyButton * ui_knapsack;
            FVMctrl_core::polyButton * ui_shopMall;
            FVMctrl_core::polyButton * ui_synthesisHouse;
            FVMctrl_core::polyButton * ui_cuisineRecipe;
            FVMctrl_core::polyButton * ui_quit;
            FVMctrl_core::polyButton * ui_missionManager;

            QPixmap option_group_background;
    }; // class FVMOptionGroup

//////////////////////////
// with regard to card view
    class FVMCardPlatform : public QGraphicsItem
    {   
        public: // Build global single object with singleton
            static QGraphicsPixmapItem * m_selected_block;
            static const int mergain_w = -1;
            static const int mergain_h = -1;
        public:
            FVMCardPlatform();
            virtual ~FVMCardPlatform() noexcept = default;

            virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
            virtual QRectF boundingRect() const override {return QRectF(0, 0, m_platform.width(), m_platform.height()); };
            void addedToScene(QGraphicsScene *);
            virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
            virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

            inline void addCard(FVMFoodCard * card) {food_card = card; };
            inline FVMFoodCard * card() {return food_card; }
            inline bool empty() {return food_card == nullptr; }
            inline FVMFoodCard * removeCard() {FVMFoodCard * __tmp = food_card; food_card = nullptr; return __tmp; }

        private:
            const QPixmap m_platform {"../resource/GameUi/cardContainer/cardframe.png" };
            FVMFoodCard * food_card {nullptr};
    }; // class FVMCardPlarform

    class FVMCardContainerModel
    {
        public:
            using CardList = std::vector<FVMFoodCard *>;

            FVMCardContainerModel(FVMCardContainerView * view);
            ~FVMCardContainerModel() noexcept = default;
            CardList& getList() {return m_card_group; }

            void updateView();
        private:
            CardList m_card_group; 
            FVMCardContainerView * m_view {nullptr};
    }; // class FVMCardContainerModel

    // class FVMCardContainerView
    class FVMCardContainerView : public QFrame, public FVMcore::FVMAbstructCardManager
    {
        // Card Container View receive all kinds of QWidget object to create their own viewport
        enum {view_frame_mergain_W = 10 };
        enum {view_frame_mergain_H = 10 };
       public:
            struct _CardBlock {
                int releativeX;
                int releativeY;
                FVMCardPlatform * platform;

                _CardBlock() : platform {nullptr}, releativeX {}, releativeY {} {};

                inline void addCard(FVMFoodCard * new_card, QGraphicsScene * scene) {
                    if (platform != nullptr) {
                        if (auto * __tmp = removeCard(scene); 
                            __tmp != nullptr)
                                delete __tmp;
                        platform->addCard(new_card);
                        new_card->addedToScene(scene);
                        new_card->moveBy(qreal(releativeX) + 4, qreal(releativeY) + 1.5);
                        new_card->setScaleSize(qreal(0.75));
                    }  
                }
                [[nodiscard]] inline FVMFoodCard * removeCard(QGraphicsScene * scene) {
                    if (platform != nullptr && !platform->empty()) {
                        scene->removeItem(platform->card());
                        return platform->removeCard();
                    }
                    return nullptr;
                }
            };

       public:
            FVMCardContainerView(QWidget * parent = nullptr, const QRect view_area = QRect(0, 0, 400, 400));
            ~FVMCardContainerView() noexcept = default;

            void addCard(FVMFoodCard * card);
            void removeCard(int x, int y);
            void removeCard(FVMFoodCard *);

            void setCardState(const bool isSelectable, const int x, const int y);
            void setCardState(FVMFoodCard *);
            void setViewState(int state);

            void cardSelected(FVMFoodCard * card) {qDebug() << "card clicked "; };
            void setUpViewUi(QWidget * widget);

            inline void setModel(FVMCardContainerModel * model) {m_model = model;};
            void createCardScene(int mode, int width);
            void deleteCardScene();

            void InitFoodCardModelView();
            void InitView();
            virtual QGraphicsScene* scene() {return m_scene; }
        public :
            friend FVMGeneralScrollBar * installFVMScrollBar(QGraphicsView *, const QRect, const QSize);
        private:

            QGraphicsView * m_view   {nullptr};
            QGraphicsScene * m_scene {nullptr};

            FVMGeneralScrollBar * m_scrollBar_handle {nullptr};
            FVMCardContainerModel * m_model          {nullptr};
        private:

            FVM2DArray<_CardBlock> m_block;
         
            int blocknums {100};
            int block_col;
            int block_row;

    }; // class FVMCardContainerView
/////////////////////////////////
//
    // class scroll
    class FVMGeneralScrollBar  
    {
        public:
            friend FVMGeneralScrollBar * installFVMScrollBar(QGraphicsView *, const QRect, const QSize);
        public:
            FVMGeneralScrollBar(const QRect scroll_rect, const QSize scrollSize);
            ~FVMGeneralScrollBar();

            void InitCtrl();    
            void setView(QGraphicsView *);

            constexpr int MapToScrollDist(int handle_move_dist);
            constexpr int MapFromScrollDist(int scrolled_dist);

        private:
            // up scroll, down scroll, handle
            QGraphicsView * view;
            FVMGeneralScrollBar * m_scroll_bar;
            const qreal scroll_factor; 
        private:
    };
}


#endif