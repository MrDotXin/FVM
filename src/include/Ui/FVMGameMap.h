#if ! defined(_FVMGAMEMAP_H_)
#define _FVMGAMEMAP_H_
#include <QtCore/qpoint.h>
#include <QtCore/qrect.h>
#include <vector>
#include <list>

class QPainter;
class QGraphicsItem;


namespace FVMcore {
    template<class value_type, class boundary_type>
    class QuadTree;
}

namespace FVMctrl_core {class _FVMMouse; }

namespace scene_core {

        struct _FVMBlock {
            // 相对于可种植区域的开始位置, 统一在右下角
            int relativePosX;    
            int relativePosY;
            // 类型 -1 :  需要承载物 
            //      0  :  可种植,或存在可共存通用类卡片  
            //      1  :  存在普通卡片
            //      3  :  辅助卡与普通卡共存，返回普通卡对象      
            int type;
            std::list<QGraphicsItem *> Obj_list;

            _FVMBlock() 
                : relativePosX {0},
                  relativePosY {0},
                  type {0}
            {}
        };

        class FVMPlainGameMap { 
                enum class notify_info_type {
                };
            public:
                using MapData = std::vector<std::vector<_FVMBlock> >;

                FVMPlainGameMap() = default;
                ~FVMPlainGameMap() noexcept = default;

                void advance(QPainter *);
                bool CurrentPositionOptional(QPoint pos);
                const QPoint MapPosToStandardBlockPos(QPointF pos);             
                const QPointF MapStandardBlockPosToStandardMapPos(const QPoint& );
                std::vector<_FVMBlock>& operator [](int y) {return _m_block[y]; }
                
                [[nodiscard]] QGraphicsItem * removeFromMap(const int sx, const int sy);
                [[nodiscard]] QGraphicsItem * removeFromMap(QGraphicsItem * );
                [[nodiscard]]  MapData & getBlockArray() {return _m_block; }  
                void setAbsPos(const int x, const int y) {_m_absPos.rx() = x, _m_absPos.ry() = y;}
                const QPoint& getAbsPos() {return _m_absPos; }
                void setBoundary(const QRect rect) {_m_boundary = rect; }

                bool addObjectToMap(const int sx, const int sy, QGraphicsItem *);
                bool addObjectToMap(const QPointF pos, QGraphicsItem *);
                void Notify(const int sx, const int sy, const notify_info_type type);

                const QPoint _MapToStandardBlockPos(const QPointF&, int, int, int, int);
                
                [[nodiscard]] FVMcore::QuadTree<FVMctrl_core::_FVMMouse, QRect> * BuildMouseSpaceManager();

            private:
                MapData _m_block;
                QPoint _m_absPos;
                QRect _m_boundary;
                const int max_block_x {9};
                const int max_block_y {7};
        };
}
#endif