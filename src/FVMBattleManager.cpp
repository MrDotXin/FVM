#include <QtGui/QMouseEvent>
#include "include/core/Game/system/battle/FVMBattleManager.h"
#include "include/Ui/FVMGameScene.h"
#include "include/core/Game/Object/FVMObject.h"
#include "include/Ui/Object/FVMGameObject.h"
#include "include/core/FVMMetaObject.h"
#include "include/Ui/Object/FVMBulletObject.h"

void FVMcore::battle::FVMBattleSceneManager::setScene(scene_core::_FVMAbstructGameScene * scene) {
    m_scene = scene;
    m_card_demo.setScene(this);
    mousePosManager.buildTree(
        QRect(scene->getBeginPoint_x(), 0, 
            scene->getSceneWidth() + 100, scene->getSceneHeight() + 100), 2);
}


void FVMcore::battle::FVMBattleSceneManager::createScene()
{
        qDebug() << "Manager : Create Scene ";
        if (m_scene != nullptr) {
            
            setUpGameUi();
            m_scene->createScene();
            m_scene->createGameMap(&m_map);
        }
        qDebug() << "Manager : Done Create Scene ";
}

void FVMcore::battle::FVMBattleSceneManager::setUpGameUi()
{
    // stimulate user info scanning
    qDebug() << "set card select ui";
    do {
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 16);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 15);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 14);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 13);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 12);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 11);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 10);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 9);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 8);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(9)), 7);
        m_card_demo.addCard(dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(0)), 11);
    } while(false); 
    m_card_demo.setUpUiInScene();
    // 
}

void FVMcore::battle::FVMBattleSceneManager::cardSelected(FVMctrl_core::FVMFoodCard * obj)
{
    FoodObject * food_obj = dynamic_cast<FoodObject *>(_meta::FVMMetaPool::Instance()->LoadFromId(obj->getFoodId()));
    if (m_current_selection == nullptr) {
        QPixmap pixmap(QString(food_obj->getNormalBehaviourAddress()) + "1.png");
        m_current_selection = new QGraphicsPixmapItem(pixmap);
        scene()->addItem(m_current_selection);
        current_food_info = obj;
        m_current_selection->setZValue(qreal(23));

        m_current_selection->moveBy(
                current_mouse_point.x() - m_current_selection->pos().x() - m_current_selection->pixmap().width() / 2, 
                current_mouse_point.y() - m_current_selection->pos().y() - m_current_selection->pixmap().height() / 2
           );    
        _isSelected = true;

    } else {
        /*
        if (current_food_info->getFoodId() == food_obj->getId()) {
            if (m_current_selection->isVisible()) {
                m_current_selection->hide();
                _isSelected = false;
            } else {
                m_current_selection->show();
                _isSelected = true;
            }
        } else */{
            if (current_food_info != nullptr) current_food_info->setSelected(false);
            QPixmap pixmap(QString(food_obj->getNormalBehaviourAddress()) + "1.png");
            m_current_selection->setPixmap(pixmap);
            current_food_info = obj;
            m_current_selection->show();
            _isSelected = true;
        }
    }

}

void FVMcore::battle::FVMBattleSceneManager::mousePressEvent(QMouseEvent *)
{
    if (_isSelected && m_map.CurrentPositionOptional(predicted_optimal_pos)) {
    // Place our card;  
    QPointF pos = m_map.MapStandardBlockPosToStandardMapPos(predicted_optimal_pos);
        QGraphicsItem * new_food = 
            dynamic_cast<FoodObject *>(
                _meta::FVMMetaPool::Instance()->
                    LoadFromId(current_food_info->getFoodId()))->createFoodObjectView(
                        current_food_info, this,
                        m_map.getAbsPos().x(), m_map.getAbsPos().y(), pos.x(), pos.y(),
                        predicted_optimal_pos.x(), predicted_optimal_pos.y()
            );
        m_current_selection->hide();
        current_food_info->setSelected(false);
        _isCurrentPosOptional = false;
        _isSelected = false;
        m_map.addObjectToMap(predicted_optimal_pos.rx(), predicted_optimal_pos.ry(), new_food);
    }
}

void FVMcore::battle::FVMBattleSceneManager::mouseMoveEvent(QMouseEvent * me)
{   
    current_mouse_point = me->position();
    if (m_current_selection != nullptr) {
        m_current_selection->moveBy(
            current_mouse_point.x() - m_current_selection->pos().x() - m_current_selection->pixmap().width() / 2, 
            current_mouse_point.y() - m_current_selection->pos().y() - m_current_selection->pixmap().height() / 2
        );
        // Draw previsted position for the selected card
        if (_isSelected) {
            predicted_optimal_pos = m_map.MapPosToStandardBlockPos(current_mouse_point);
            if (predicted_optimal_pos.x() >= 0) {
                _isCurrentPosOptional = true;
            }
        }
    }
}
inline void FVMcore::battle::FVMBattleSceneManager::deleteScene() 
{m_scene->deleteScene(); scene_core::_BasicBulletObject::enemy_list = nullptr;}
void FVMcore::battle::FVMBattleSceneManager::drawScene(QPainter * painter){m_scene->drawScene(painter);}
inline void FVMcore::battle::FVMBattleSceneManager::updateScene() 
{
    static int tick = 0;
    if (tick++ % 3 == 0) {
        // mousePosManager.update();
        tick = 0;
    } 
    m_scene->updateScene(); 
}
inline void FVMcore::battle::FVMBattleSceneManager::pauseScene()  {m_scene->pauseScene();  }
QGraphicsScene * FVMcore::battle::FVMBattleSceneManager::scene() {return m_scene->scene(); }
inline const QRect FVMcore::battle::FVMBattleSceneManager::updateRect() {return m_scene->updateRect(); }
