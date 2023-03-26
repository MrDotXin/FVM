#include "include/Ui/FVMGameMap.h"
#include "QtCore/QDebug"

const QPoint scene_core::FVMPlainGameMap::MapPosToStandardBlockPos(QPointF pos) {

    pos.rx() -= _m_absPos.x();
    pos.ry() -= _m_absPos.y();
    if (pos.rx() < 0 || pos.ry() < 0) return QPoint(-1, -1);
    if (!_m_block.empty() && !_m_block[0].empty()) {
        int __x = 0;
        int __y = 0;
        int __W = _m_block[__y][__x].relativePosX;
        int __H = _m_block[__y][__x].relativePosY;

        while (__W < pos.x() && __x < _m_block[0].size())     __W = _m_block[0][++__x].relativePosX;
        while (__H < pos.y() && __y < _m_block.size() - 1)    __H = _m_block[++__y][0].relativePosY;

        if (!(__x == _m_block[0].size()  
            || __y == _m_block.size()))
               return QPoint(__x, __y);
    }
    return QPoint(-1, -1);
}

const QPointF scene_core::FVMPlainGameMap::MapStandardBlockPosToStandardMapPos(const QPoint& pt)
{
    return QPointF(_m_block[pt.y()][pt.x()].relativePosX, 
                    _m_block[pt.y()][pt.x()].relativePosY); 
}

bool scene_core::FVMPlainGameMap::addObjectToMap(const int sx, const int sy, QGraphicsItem * food_obj)
{
    _m_block[sy][sx].Obj_list.push_front(food_obj);
    return true;
}

QGraphicsItem * scene_core::FVMPlainGameMap::removeFromMap(const int sx, const int sy)
{
    QGraphicsItem * item = _m_block[sy][sx].Obj_list.front();
    _m_block[sy][sx].Obj_list.pop_front();
    return item;
}

bool scene_core::FVMPlainGameMap::CurrentPositionOptional(QPoint pos)
{
    return pos.rx() >= 0 && pos.ry() >= 0 && _m_block[pos.y()][pos.x()].Obj_list.empty();
}