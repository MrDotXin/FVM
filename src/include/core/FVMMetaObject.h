#pragma once
#include <unordered_map>

namespace FVMcore {class FoodObject; class MouseObject; class __FVMAbstructObject; }

namespace FVMcore::_meta {
    

    class FVMMetaPool final { 
        // Object cache pool, to load object as prompt as possible 
        public:
            static int objRefCount;
            static FVMMetaPool * m_metaObject;
        private:
            std::unordered_map<unsigned int, FoodObject  *> m_resUnit; 
            std::unordered_map<unsigned int, MouseObject *> m_mresUnit;
        public:
            FVMMetaPool();
            ~FVMMetaPool();    
            static FVMMetaPool * Instance();
            __FVMAbstructObject * LoadFromId(unsigned int id); 
        private: 
            bool registerFVMObjectInfo(); 
            bool LoadGlobalFVMFoodObject();
            bool LoadGlobalFVMMouseObject();
    };
}