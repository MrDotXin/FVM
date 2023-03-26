#pragma once
#include <array>
#include <list>
#include <queue>
#include <chrono>

namespace FVMcore::algo {
        // class QuadTreeNode
    namespace __Impl {
    	template<class bound_type>
    	constexpr bool checkInteracted(const bound_type& rect, const bound_type& box)
    	{return !(rect.x() + rect.width() < box.x() || rect.x() > box.x() + box.width() || rect.y() + rect.height() < box.y() || box.y() + box.height() < rect.y()); } 

    	template<class bound_type>
    	constexpr bool contain(const int& x, const int& y, const bound_type& box)
    	{return !(x <  box.x() || x > box.x() + box.width() || y < box.y() || y > box.y() + box.height()); }

    	template<class bound_type>
    	constexpr bool contain(const bound_type& box, const bound_type& space) 
    	{return (space.x() >= box.x() && space.x() + space.width() <= box.x() + box.width() && space.y() >= box.y() && space.y() + space.height() <= box.y() + box.height());}

    	//////// class QuadTreeNode version 1.0, suit based on c++17 
		/// @brief first edition of the implementation of quadTree
    	/// @param __vt :  value_type (heap-allocated)
        /// @brief : require {value_type::boundingRect()}
        /// @param __bt :  boundary_type 
        /// @brief require  {boundary_type::x(); boundary::y(); boundary_type::width(); boundary_type::height();}
            template<class __vt, class __bt>
            struct QuadTreeNode {
                std::array<QuadTreeNode<__vt, __bt> *, 4> children;
                std::list<__vt *> valist;               
                __bt boundary_rect;
                QuadTreeNode * root;
                bool is_leaf;
                int floor;

                QuadTreeNode() : children {nullptr, nullptr, nullptr, nullptr}, root{this}, floor{0}, is_leaf{true} {}
                QuadTreeNode(const __bt& boundary, 
                    int fixed_depth, QuadTreeNode * r = nullptr)
                    : children {nullptr, nullptr, nullptr, nullptr}, boundary_rect(boundary), root(r), floor(fixed_depth), is_leaf(true)
                {
                	
                    if (floor > 0) {
                        is_leaf = false;
                        auto __half_X = boundary.width() / 2;
                        auto __half_Y = boundary.height() / 2;
                        children[0] = new QuadTreeNode<__vt, __bt>(__bt{boundary_rect.x(), boundary_rect.y(), __half_X, __half_Y}, floor - 1, this);
                        children[1] = new QuadTreeNode<__vt, __bt>(__bt{boundary_rect.x() + __half_X, boundary_rect.y(), __half_X, __half_Y}, floor - 1, this);
                        children[2] = new QuadTreeNode<__vt, __bt>(__bt{boundary_rect.x(), boundary_rect.y() + __half_Y, __half_X, --__half_Y}, floor - 1, this);
                        children[3] = new QuadTreeNode<__vt, __bt>(__bt{boundary_rect.x() + __half_X, boundary_rect.y() + __half_Y, __half_X, __half_Y}, floor - 1, this);  
                    }
                }

                bool insert(__vt * value) {
                    if (checkInteracted(value->Rect(), boundary_rect)) {
                        __insertWithoutCheck(value);
                        return true;
                    }

                    return false;
                }

                void __insertWithoutCheck(__vt * value) {

                    if (is_leaf) {
                        valist.emplace_back(value);
                        return;
                    } else {
                        for (auto& __subNode : children) {
                            if (contain(__subNode->boundary_rect, value->Rect())) {
                                __subNode->__insertWithoutCheck(value);
                                return;
                            }
                        }
                    }
                    valist.emplace_back(value);
                }

                void remove(__vt * value) {
                    if (is_leaf) {
                        valist.remove(value);
                    }
                    else {
                        for (auto& __subNode : children) {
                            if (contain(__subNode->boundary_rect, value->Rect())) {
                                __subNode->remove(value);
                                return;
                            }    
                        }
                    } 
                    valist.remove(value);    
                }

            	/**/inline __vt * getItemAt(const __bt& search_rect) {
                    if (checkInteracted(search_rect, boundary_rect)) {
                        for (auto& mid_obj : valist) {
                            if (checkInteracted(mid_obj->Rect(), search_rect)) {
                                return mid_obj;
                            }
                        }

                        if (!is_leaf) {
                            for (auto& subNode : children) {
                                __vt * __pt = subNode->getItemAt(search_rect);
                                if (__pt != nullptr) {
                                    return __pt;
                                }
                            }
                        }
                    } 
                    return nullptr;
                }

            	/**/ inline std::queue<__vt *> getItemListAt(const __bt& search_rect) {
                        std::queue<__vt *> __q;
                        if (checkInteracted(boundary_rect, search_rect)) {
                            std::queue<QuadTreeNode<__vt, __bt>* > __sq;
                            __sq.push(this);
                            while (!__sq.empty()) {
                                auto* __node = __sq.front();
                                __sq.pop();
                                for (auto& mid_obj : __node->valist) {
                                    if (checkInteracted(mid_obj->Rect(), search_rect)) {
                                        __q.push(mid_obj);
                                    }    
                                }
                                if (!(__node->is_leaf)) {
                                    for (auto& subNode : __node->children) {
                                        if (checkInteracted(subNode->boundary_rect, search_rect)) {
                                            __sq.push(subNode);
                                        }
                                    }         
                                }
                            }     
                        }
                        return __q;
                }
            	
            	/*inplace with pred*/ 
				template<class uninary_oper>
            	inline bool itemAtWithPred(uninary_oper&& pred, const __bt& search_rect) {
                    if (checkInteracted(boundary_rect, search_rect)) {
                        for (auto& mid_obj : valist) {
                            if (checkInteracted(mid_obj->Rect(), search_rect)) {
                                if (pred(mid_obj)) {
                                    qDebug() << search_rect << " with : " << mid_obj->Rect() << '\n';  
                                    return true;
                                }
                            }
                        }

                        if (!is_leaf) {
                            for (auto& __subNode : children) {
                                if (__subNode->itemAtWithPred(pred, search_rect)) {
                                    return true;
                                }
                            }
                        }
                    }
                    return false;
                }

                template<class oper_type>
                inline bool itemListAtWithPred(oper_type&& pred, const __bt& search_region) {
                    if (checkInteracted(boundary_rect, search_region)) {
                        std::queue<QuadTreeNode<__vt, __bt>* > __sq;
                        __sq.push(this);
                        while (!__sq.empty()) {
                            auto * __node = __sq.front();
                            __sq.pop();
                            for (auto& mid_obj : valist) {
                                if (checkInteracted(mid_obj->boundary_rect, search_region)) {
                                    pred(mid_obj);
                                }
                            }

                            if (!(__node->is_leaf)) {
                                for (auto& __subNode : __node) {
                                    if (checkInteracted(__subNode->boundary_rect, search_region)) {
                                        __sq.push(__subNode);
                                    }
                                }
                            }
                        }
                        return true;
                    }
                    return false;
                }

                void clear() {
                    valist.clear();
                    if (!is_leaf) {
                        for (auto& __subNode : children) {
                            __subNode->clear();
                            delete __subNode;
                            __subNode = nullptr;
                            is_leaf = true;
                        }
                    }
                }

                void update() {
                    for (auto iter = valist.begin(); iter != valist.end(); iter++) {
                        if (!(contain(boundary_rect, (*iter)->Rect()))) {
                            __vt * tmp = *iter;
                            ++iter;
                            valist.remove(tmp);
                            root->insert(tmp);
                            if (iter == valist.end()) break;
                        }
                    }

                    if (!is_leaf) {
                        for (auto& __subNode : children) {
                            __subNode->update();
                        }
                    }
                }
                
              //   void deleteQuadTree(); /*use delete to delete all nodes, only if elements in valist are heap-allocated*/
            };  // class QuadTreeNode
    }
    template<class _value_type, class _bound_type>
    class QuadTree {
        /// @brief only receive heap-allocated object 
        public:
            using value_type = _value_type;
            using bound_type = _bound_type;
            using pointer    = _value_type *;
            using reference  = _value_type &; 

        private:
            __Impl::QuadTreeNode<value_type, bound_type> * __M_root {nullptr};
        public:
            QuadTree() = default;
            QuadTree(const bound_type& original_rect, int depth) {
                __M_root = new __Impl::QuadTreeNode<value_type, bound_type>(original_rect, depth);
            }
            ~QuadTree() noexcept { if (__M_root != nullptr) __M_root->clear(); };

            inline void buildTree(const bound_type& original_rect, int depth)
            {
                if (__M_root != nullptr) 
                    {__M_root->clear(); delete __M_root;} 
                __M_root = new __Impl::QuadTreeNode<value_type, bound_type>(original_rect, depth);
            }
            inline void insert(pointer val) {__M_root->insert(val); }
            inline void remove(pointer val) {__M_root->remove(val); }
            inline void clear() { __M_root->clear(); }
            inline void update() {__M_root->update(); } 

            inline pointer getItemAt(const bound_type& search_rect) 
            {return __M_root->getItemAt(search_rect); }
            inline std::queue<pointer> getItemListAt(const bound_type& search_ragion) 
            {return __M_root->getItemListAt(search_ragion); }  
            template<class uninary_oper>
            inline bool itemAtWithPred(uninary_oper&& pred, const bound_type& search_rect) 
            { return __M_root->itemAtWithPred(std::forward<uninary_oper>(pred), search_rect); }
            template<class uninary_oper>
            inline bool itemListAtWithPred(uninary_oper&& pred, const bound_type& search_ragion) 
            { return __M_root->itemListAtWithPred(std::forward<uninary_oper>(pred), search_ragion); }
          //  inline void deleteQuadTree();
    };  // class QuadTree


}

