#if ! defined(_FVMABSTRUCTCARDMANAGER_H_)
#define _FVMABSTRUCTCARDMANAGER_H_

namespace FVMctrl_core {class FVMFoodCard;}
class QGraphicsScene;
namespace FVMcore {

    class FVMAbstructCardManager
    {
        public:
            FVMAbstructCardManager() = default;
            virtual ~FVMAbstructCardManager() noexcept = default;
            virtual void cardSelected(FVMctrl_core::FVMFoodCard *) = 0;
            virtual QGraphicsScene * scene() = 0;
    };
}



#endif