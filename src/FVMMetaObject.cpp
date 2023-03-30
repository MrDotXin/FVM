#include "include/core/FVMMetaObject.h"
#include "include/Ui/Object/FVMGameObject.h"
#include "include/core/Game/Object/FVMObject.h"

/*! @brief MAS define different states for mouse 
    Those states are :
    
*/
#define MAS(...) FVMcore::__FVMAbstructMouseObject::Animation_State {__VA_ARGS__}
#define FOOD_ADDRESS(FoodName, statrum) "../resource/Food"#FoodName"/"#statrum"/"
#define FOOD_CARD_ADDRESS 
#define FVM_META_FOOD_OBJECT(name, resCount, behaveStartPos, bulletCount, hitStartPos) 

int FVMcore::_meta::FVMMetaPool::objRefCount = 0;
FVMcore::_meta::FVMMetaPool * FVMcore::_meta::FVMMetaPool::m_metaObject = nullptr;

FVMcore::_meta::FVMMetaPool::FVMMetaPool()
{
    LoadGlobalFVMFoodObject();
    LoadGlobalFVMMouseObject();
}

FVMcore::_meta::FVMMetaPool::~FVMMetaPool()
{
    if (m_metaObject != nullptr) {
        
        for (auto& [id, singleton_object] : m_resUnit) {
            qDebug() << "ID : " << id << " deleted.";
            delete singleton_object;
        }
        FVMcore::_meta::FVMMetaPool * tmp = m_metaObject;
        m_metaObject = nullptr;
        delete tmp;
    }
}

FVMcore::_meta::FVMMetaPool * FVMcore::_meta::FVMMetaPool::Instance() {
    if (m_metaObject == nullptr) {
        m_metaObject = new FVMcore::_meta::FVMMetaPool;
    }
    return m_metaObject;
}

FVMcore::__FVMAbstructObject * FVMcore::_meta::FVMMetaPool::LoadFromId(unsigned int id )
{
    return m_resUnit[id];
}

bool FVMcore::_meta::FVMMetaPool::registerFVMObjectInfo()
{
    return true;
}

bool FVMcore::_meta::FVMMetaPool::LoadGlobalFVMFoodObject()
{
    // Load all Object from file once a 6
    qDebug() << "Load game card resource...";
    m_resUnit[9] = new FVMcore::FoodObject(new FVMcore::policy::PaiPaiRooster, 9, 27, 14, "../resource/Food/paipaiRooster/0/", 4, "../resource/Food/paipaiRooster/0/bullet", -70, -90, "../resource/Food/paipaiRooster/0/card.png", 2);
    m_resUnit[0] = new FVMcore::FoodObject(new FVMcore::policy::uncleCorn, 0, 23, 13, "../resource/Food/corn/0/", 4, "../resource/Food/corn/0/bullet/", -60, -90, "../resource/Food/corn/0/card.png", 2);
    qDebug() << "load game card done";
    return true;
}

bool FVMcore::_meta::FVMMetaPool::LoadGlobalFVMMouseObject()
{
    // meta data fill
    /*m_mresUnit[700 + 0] = new MouseObject<_IronPotPlain, int>(700 +0, 77, "../resource/Mouse/IronPotPlainMouse/", 0, -124);
    m_mresUnit[700 + 0]->build_state(6, MAS(1,  8,  41, 44, 0, 1, 1.70, 0, 1, 0.4), 
                                        MAS(9,  17, 45, 49, 0, 1, 1.70, 0, 1, 0.6),
                                        MAS(18, 24, 50, 56, 1, 1, 1.80, 0, 1, 0.8),
                                        MAS(25, 32, 57, 64, 0, 1, 1.70, 0, 1, 0.85),
                                        MAS(33, 40, 57, 64, 0, 1, 1.70, 0, 1, 0.94),
                                        MAS(65, 77, 65, 77, 0, 0.0, 2.5, 0, 1, 1.2)
                                );
    m_mresUnit[700 + 0]->setCollideRect(QRect(30, 42, 40, 80));
    */
    return true;
}

