#include "include/Ui/FVMUi.h"
#include "include/core/Game/Object/FVMObject.h"
#include "include/core/FVMMetaObject.h"

FVMctrl_core::FVMCardContainerView::FVMCardContainerView(QWidget * parent, const QRect view_area)
    : QFrame(parent)
{
    this->move(view_area.x(), view_area.y());
    this->resize(view_area.width(), view_area.height());
    this->setObjectName("Container");
    this->setStyleSheet("#Container{border-image:url(../resource/GameUi/cardContainer/frame.png); border: no-repeat;}");
    InitView();
}

void FVMctrl_core::FVMCardContainerView::createCardScene(int mode, int width)
{
    static const QSize size = QPixmap("../resource/GameUi/cardContainer/cardframe.png").size();

    block_col = width / size.width();
    block_row = blocknums / block_col + (blocknums % block_col == 0 ? 0 : 1);
    int __height = 0;
    int __initWidth = (width % size.width()) / 2;
    int __width = __initWidth;

    for (int __r = 0; __r < block_row; __r++) {
        m_block.push_back({});
        __width = __initWidth;
        for (int __l = 0; __l < block_col; __l++) {
            _CardBlock __b;
            __b.releativeX = __width;
            __b.releativeY = __height;
            __b.platform = new FVMCardPlatform;
            m_block[__r].push_back(__b);
            __b.platform->addedToScene(m_scene);
            __b.platform->moveBy(__b.releativeX, __b.releativeY);
            __width += size.width();
        }
        __height += size.height();
    }

    m_scene->setSceneRect(QRect(0, 0, width, __height));
    InitFoodCardModelView();
}

void FVMctrl_core::FVMCardContainerView::InitFoodCardModelView()
{
    auto& __food_list = m_model->getList();
    auto __iter_list = m_block.begin();
    auto __block_iter = __iter_list->begin();  
    for (auto& __card : __food_list) {
        if (__block_iter == __iter_list->end()) {
            if (++__iter_list == m_block.end()) {
                break;
            }
            __block_iter = __iter_list->begin();
        }
        __block_iter++->addCard(__card, m_scene);
    }
    m_view->show();
}

void FVMctrl_core::FVMCardContainerView::deleteCardScene()
{
   auto card_list = m_model->getList();
}

void FVMctrl_core::FVMCardContainerView::InitView()
{
    QFrame * view = new QFrame(this);
    view->setFixedSize(this->width() - 10, this->height() - 30);

    view->move(10, 10);

    m_view = new QGraphicsView(this);
    m_scene = new QGraphicsScene;

    m_scene->setBackgroundBrush(QColor(qRgb(0, 44, 81)));

    m_view->setViewport(view);
    m_view->resize(view->size());
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setScene(m_scene);
    m_view->raise();

    m_model = new FVMCardContainerModel(this);

    createCardScene(0, m_view->width());
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// FVMCardContainerModel
FVMctrl_core::FVMCardContainerModel::FVMCardContainerModel(FVMCardContainerView * view)
{
    m_view = view;
    view->setModel(this);
    for (int i = 0; i < 1; i++) {
        auto food = FVMcore::_meta::FVMMetaPool::Instance()->LoadFoodFromId(9);
        m_card_group.emplace_back(
            new FVMFoodCard(m_view, 9, 10, 0, food->getEmitPolicy()->energy(), food->getCardAddress()));
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////
// class FVMCardPlantform
QGraphicsPixmapItem * FVMctrl_core::FVMCardPlatform::m_selected_block = nullptr;

void FVMctrl_core::FVMCardPlatform::paint(QPainter * painter , const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(QRect(0, 0, m_platform.width(), m_platform.height()), m_platform);
}

void FVMctrl_core::FVMCardPlatform::addedToScene(QGraphicsScene * scene)
{
    if (m_selected_block == nullptr) {
        m_selected_block = new QGraphicsPixmapItem;
        m_selected_block->setPixmap(QPixmap("../resource/GameUi/cardContainer/cardSelected.png"));
        scene->addItem(m_selected_block);
        m_selected_block->setZValue(1);
        m_selected_block->hide();
    }
    scene->addItem(this);
    this->setZValue(0);
    installSceneEventFilter(this);
}

FVMctrl_core::FVMCardPlatform::FVMCardPlatform()
{
    setAcceptHoverEvents(true);
}

void FVMctrl_core::FVMCardPlatform::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    qDebug() << "HoverEnter";
    if (empty()) {
        if (m_selected_block != nullptr) {
            m_selected_block->moveBy(qreal(this->pos().x() - m_selected_block->pos().x()) + mergain_w, 
                                        qreal(this->pos().y() - m_selected_block->pos().y()) + mergain_h);
            m_selected_block->show();
            qDebug() << m_selected_block->pos();
            qDebug() << this->pos();
        }
    }
}

void FVMctrl_core::FVMCardPlatform::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    qDebug() << "HoverLeave";
    if (m_selected_block != nullptr) {
        m_selected_block->hide();
    }
}
///////////////////////////////////////////////////
//
FVMctrl_core::FVMGeneralScrollBar * FVMctrl_core::installFVMScrollBar(QGraphicsView * view, const QRect rect, const QSize size)
{

    return nullptr;
} 






