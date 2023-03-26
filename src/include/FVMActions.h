#if ! defined(_FVMACTION_H_)
#define _FVMACTION_H_
#include "core/Game/Object/FVMObjectType.h"
#include "Ui/Object/FVMBulletObject.h"


// 每个类的具体行为
namespace FVMcore {

    template<class _Object_View> 
    void EMIT(_Object_View* _obj_v)
    {
        static typename _Object_View::food_type type_info {};
        _EMIT(_obj_v, type_info); 
    }

    template<class _Object_View>
    const QRect Attack_range(_Object_View * _obj_v)
    {
        static typename _Object_View::food_type type_info {};
        return _Attack_range(_obj_v, type_info);
    }

    template<class _Object_View>
    void _EMIT(_Object_View * _obj_V, const FVMcore::_Sagittarius& info) {

        int __l {info.base_info.level} ;
        int __drct[3] {
            __l == 2 ? 2 : 1,
            __l == 0 ? 1 : 2,
            __l == 2 ? 2 : 1
        };
        for (int i = -1; i < 2; i++) {
          if (_obj_V->blockHeight() + i >= 0 &&  
              _obj_V->blockHeight() + i <= _obj_V->_max_VBlockCounts) {
                int __LengthOfForeBullets {0};

                while (__drct[i + 1]-- > 0) {
                    auto * _bullet = new scene_core::ShooterBullet(_obj_V->blockHeight() + i, _obj_V->_m_obj->getBulletPicAddress(), _obj_V->_m_obj->getBulletPicCounts());
                    _obj_V->scene()->addItem(_bullet);
                    _bullet->moveBy(
                        _obj_V->pos().x() + 40 + _obj_V->boundingRect().width() + __LengthOfForeBullets,
                        _obj_V->pos().y() + 60 + i * _obj_V->_block_size
                    );
                    __LengthOfForeBullets += _bullet->boundingRect().width() - 30;
                    _bullet->setZValue(_obj_V->_max_VBlockCounts * _obj_V->_max_HBlockCounts + 1);
                    _bullet->setDefaultEndPos(QPoint(_obj_V->scene()->width(), _bullet->pos().y()));
                    _bullet->setIsStopped(false);
                }
            }
        }
    }

    //  可以用模板方法优化
    template<class _Object_View>
    QRect _Attack_range(_Object_View * _obj_v, const FVMcore::_Sagittarius& info) { 

        auto& map = _obj_v->manager->getGameMap();
        // last : 
        int __y  = (_obj_v->block_y <= 1) ? 0 : (map[_obj_v->block_y - 2][_obj_v->block_x].relativePosY);
        int __ey = map[_obj_v->block_y + 1 < _obj_v->_max_VBlockCounts ? 
            _obj_v->block_y + 1 : _obj_v->block_y][_obj_v->block_x].relativePosY;

        int __x  =  map[_obj_v->block_y][_obj_v->block_x].relativePosX;

        return QRect(__x + map.getAbsPos().x(), __y + map.getAbsPos().y() + 40, 3000, __ey - __y - 80);
    }

    template<class _Object_View>
    QRect _Attack_range(_Object_View * _obj_v, const FVMcore::_cactus& info) { 

        auto& map = _obj_v->manager->getGameMap();
        int __y  = (_obj_v->block_y == 0) ? 0 : (map[_obj_v->block_y - 1][_obj_v->block_x].relativePosY);
        int __x  =  map[_obj_v->block_y][_obj_v->block_x].relativePosX;
        return QRect(__x + map.getAbsPos().x(), __y + map.getAbsPos().y() + 30, 3000, 5);
    }

    template<class _Object_View>
    QRect _Attack_range(_Object_View * _obj_v, const FVMcore::_hunter_doge& info) { 

        return QRect(_obj_v->block_x, _obj_v->block_y - 1, 0, 2);
    }

    template<class _Object_View>
    QRect _Attack_range(_Object_View * _obj_v, const FVMcore::_libra& info) { 

        return QRect(_obj_v->block_x, _obj_v->block_y - 1, 0, 2);
    }

    template<class _Object_View>
    void _EMIT(_Object_View * _obj_V, const FVMcore::_cactus& ) {

        int __l = 3;
        int __bullet_counts {
            __l == 1 ? 1 : (__l == 2 ? 2 : 4)
        };
        int _LengthOfForeBullets = 0;
        while (__bullet_counts -- > 0)  {
                auto _bullets = new scene_core::ShooterBullet(
                        _obj_V->blockHeight(),
                        _obj_V->_m_obj->getBulletPicAddress(), 
                        _obj_V->_m_obj->getBulletPicCounts()
                    );
                _obj_V->scene()->addItem(_bullets);
                _bullets->moveBy(
                    _obj_V->pos().x() + 150 + _LengthOfForeBullets,
                    _obj_V->pos().y() + _obj_V->boundingRect().height() / 2  
                );
                _bullets->setZValue(_obj_V->_max_VBlockCounts * _obj_V->_max_HBlockCounts + 1);
                _bullets->setDefaultEndPos(QPoint(_obj_V->scene()->width(), _obj_V->pos().y()));
                _bullets->setIsStopped(false);
                _LengthOfForeBullets += _bullets->boundingRect().width() - 60; 
        } 
    }

    template<class _Object_View>
    void _EMIT(_Object_View * _obj_V, const FVMcore::_libra&)
    {

    }

    template<class _Object_View>
    void _EMIT(_Object_View * _obj_V, const FVMcore::_hunter_doge&)
    {
        
    }

}

#endif