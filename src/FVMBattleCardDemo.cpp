#include "include/Ui/ctrl/FVMBattleCardDemo.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPainter>
#include "include/core/Game/system/battle/FVMBattleManager.h"
#include "include/core/Game/Object/FVMObject.h"
#include "MainWidget.h"


void FVMctrl_core::FVMBattleCardDemo::setUpUiInScene()
{
    qDebug() << "Demo : Create Selection UI";
    int _defaultMovePlace = 200;
    if (this->manager != nullptr) {
        QGraphicsItemGroup * group = new QGraphicsItemGroup;
        flame = new FVMCard("../resource/battle/flameCollector.png");
        int _LengthOfForeCard = flame->getShap().width();

        manager->scene()->addItem(group);
        group->setZValue(qreal(20));        
        group->addToGroup(flame);
        for (auto & items : this->_m_card_group) {
            manager->scene()->addItem(items);
            items->setZValue(qreal(21));
            items->installSceneEventFilter(items);
            items->moveBy(_defaultMovePlace + -5 + _LengthOfForeCard, 17);
            _LengthOfForeCard += items->getShape().width();
        }
        group->moveBy(_defaultMovePlace, 0);
    }   
}

FVMctrl_core::FVMFoodCard * FVMctrl_core::FVMBattleCardDemo::operator[] (int id) {
    auto iter = std::find_if(_m_card_group.begin(), _m_card_group.end(), 
            [id](FVMctrl_core::FVMFoodCard * item) {return (item->getFoodId() == id); }
        );
    return iter == _m_card_group.end() ?  nullptr : *iter;  
}


void FVMctrl_core::FVMBattleCardDemo::addCard(FVMcore::FoodObject * food_obj, const int level)
{
    _m_card_group.emplace_back(food_obj->createCardObject(this, level, food_obj->getId() % 3));
}

void FVMctrl_core::FVMBattleCardDemo::cardSelected(FVMctrl_core::FVMFoodCard * card) {
    manager->cardSelected(card);
}

QGraphicsScene * FVMctrl_core::FVMBattleCardDemo::scene() {
    return manager->scene();
}

//////////////////////////////////////////////////////////////////////////////////
// class FVMFoodcard

FVMctrl_core::FVMFoodCard::FVMFoodCard(FVMcore::FVMAbstructCardManager * manager, const int id, 
                const int level, const int stratum, int energy, const char * cardAddr) :
    m_card(cardAddr),
    m_level(level),
    m_stratum(stratum),
    food_id(id),
    food_energy(energy),
    manager(manager)
{
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    if (level >= 7)
        m_card_level = QPixmap(QString("E:/FVM/resource/Food/level/static/") + std::to_string(m_level).c_str() + ".png");
}

void FVMctrl_core::FVMFoodCard::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
    if (!m_card.isNull())
        painter->drawPixmap(QRect(0, 0, m_card.width(), m_card.height()), m_card);
    painter->drawText(QPoint(18, m_card.height() - 6), std::to_string(food_energy).c_str());
    drawStatus(0, painter);
    if (!m_card_level.isNull())
        painter->drawPixmap(QRect(2, 2, m_card_level.width(), m_card_level.height()), m_card_level);
}

void FVMctrl_core::FVMFoodCard::mousePressEvent(QGraphicsSceneMouseEvent *event) 
{   
    //qDebug() << "pressed !";
    _isSelected = !_isSelected;
}
void FVMctrl_core::FVMFoodCard::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) 
{
    if (_isLeaved == false) {
      manager->cardSelected(this);
    } 
}
void FVMctrl_core::FVMFoodCard::hoverEnterEvent(QGraphicsSceneHoverEvent *event) 
{
    //qDebug() << "enter";
    _isLeaved = false;
    setCursor(Qt::PointingHandCursor);
}
void FVMctrl_core::FVMFoodCard::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) 
{
    _isLeaved = true;
    setCursor(Qt::ArrowCursor);
}

void FVMctrl_core::FVMFoodCard::addedToScene(QGraphicsScene * scene)
{
    scene->addItem(this);
    installSceneEventFilter(this);
}

void FVMctrl_core::FVMFoodCard::drawStatus(int status, QPainter * painter)
{
    // 0 : in battle field 
    // 1 : in fore battle field 
    // 2 : in compose site
    // 3 : in package(check place)
    if (this->_isSelected == true) {
                painter->fillRect(
                        QRect(0, 0, m_card.width(), m_card.height()), 
                            QColor(0, 0, 0, 70));
                }
}

////////////////////////////////////////////////////////////////////////////////
// class FVMCard
void FVMctrl_core::FVMCard::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
    if (!m_static_items_pic.isNull()) {
        painter->drawPixmap(
            QRect(0, 0, m_static_items_pic.width(), 
                        m_static_items_pic.height()), 
                        m_static_items_pic
            );
            
    }
}

FVMctrl_core::FVMCard::FVMCard(const char * card) 
    : m_static_items_pic(card)
{
}




/////////////////////////////////////////////////////////////////////////////////////
// _BasicFoodObject
