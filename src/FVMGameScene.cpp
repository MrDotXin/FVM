#include "include/Ui/FVMGameScene.h"
#include "include/Ui/FVMGameMap.h"
#include "MainWidget.h"
#include <QtWidgets/QFrame>
#include <QtGui/QMouseEvent>

scene_core::Temple::Temple(MainWidget * parent)
    : m_mainwin(parent), m_scene(new QGraphicsScene)
{
    this->setObjectName("Temple_Scene");

    this->setScene(m_scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setOptimizationFlag(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    setMouseTracking(true);
    this->resize(m_mainwin->width(), m_mainwin->height());
    this->_m_update_rect = QRect(scene_begin_x, 0, scene_action.width(), scene_action.height() + scene_begin_y);
    m_scene->setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);
    m_scene->setSceneRect(QRect(0, 0, this->width(), this->height()));
    
}

void scene_core::Temple::mousePressEvent(QMouseEvent * ev)
{
    qDebug() << "Temple scene : mousePressEvent" << ev->pos();

    m_mainwin->mousePressEvent(ev);
    QGraphicsView::mousePressEvent(ev);
}   

void scene_core::Temple::drawScene(QPainter * painter)
{
    painter->setPen(QPen(Qt::red, 2));
    painter->drawText(QPoint(0, 50), QString("当前实体数 %1").arg(scene()->items().count()));
}

void scene_core::Temple::mouseMoveEvent(QMouseEvent * ev) 
{
    m_mainwin->mouseMoveEvent(ev);
    QGraphicsView::mouseMoveEvent(ev);
}

void scene_core::Temple::createScene()
{
    this->setViewport(m_mainwin);   //  let MainWidget destroy the scene object;
    this->show(); 
}

void scene_core::Temple::paintEvent(QPaintEvent * ev)
{
    QPainter painter(m_mainwin);

    painter.drawPixmap(QRect(-111, 0, scene_prospect.width(), scene_prospect.height()), scene_prospect);
    painter.drawPixmap(QRect(182, 100, scene_action.width(), scene_action.height()), scene_action);
    painter.end();

    m_mainwin->paintEvent(ev);
    QGraphicsView::paintEvent(ev);
}

void scene_core::Temple::createGameMap(scene_core::FVMPlainGameMap * gm)
{
    // 第一行和第四行高度60 * 60 其余 60 * 65
    auto& _block = gm->getBlockArray();
    gm->setAbsPos(this->scene_begin_x + this->scene_card_begin_x, this->scene_begin_y);
    gm->setBoundary(QRect(this->scene_begin_x, this->scene_begin_y, this->getSceneWidth(), this->getSceneHeight()));
    int __h, __w, _height, _width;
    _FVMBlock __b {};
    _height = _width = 0;
    for (__h = 0; __h < 7; __h ++) {
        _block.emplace_back(std::vector<scene_core::_FVMBlock>());  
        _width = 0; 
        _height += (__h == 0 || __h == 3) ? 60 : 65; 
        for (__w = 0; __w < 9; __w ++) {
            _width += 60;
            __b.relativePosX = _width;
            __b.relativePosY = _height;
            _block[__h].push_back(__b);
        
        }
    }
}

void scene_core::Temple::deleteScene()
{

}

void scene_core::Temple::pauseScene()
{
    isPaused = true; 
}

void scene_core::Temple::updateScene()
{
    if (!isPaused) {
        
        m_scene->advance();      
        m_mainwin->repaint();

    }
}
