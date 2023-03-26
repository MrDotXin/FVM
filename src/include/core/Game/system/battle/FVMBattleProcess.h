#if ! defined(_FVMPROCESS_H_)
#define _FVMPROCESS_H_

namespace FVMctrl_core {class _FVMMouse; }
namespace FVMcore {class FVMObjectCollector; }
class QRect;
class QGraphicsItem;
namespace FVMcore::battle {

    class FVMBattleSceneManager;

    class FVMBattleProcess 
    {
        public:
            FVMBattleProcess();
            ~FVMBattleProcess();
           
            void advance(); 
            void pause();
        public:
        /// @brief  Push mouses into output queue 
        /// @return 
            QGraphicsItem * push_mouse();
            QGraphicsItem * pop_mouse(); 
        private:
            FVMBattleSceneManager * manager;
        public:
            FVMctrl_core::_FVMMouse * mouseAt(const QRect& range);
        
    };
}

#endif