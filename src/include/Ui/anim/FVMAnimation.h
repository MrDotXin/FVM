#if ! defined(FVMANIMATION_H_)
#define FVMANIMATION_H_
#include "../ctrl/FVMCtrlCore.h"

namespace scene_core {

    /// @brief Use frames && the counts of pictures to control the speed of the playing
    ///
    /*!
        Current_Game_Frames take charge of all the animation plyaing speed
        _animPlayParameters is responsible for all unnatural motions      
    */
    struct _animPlayParameters {
        static int Current_Game_Frames; 
        int __average_ticks {};
        int __cur_ticks;

        int begin;
        int end;

        _animPlayParameters() = default;
        _animPlayParameters(const double speed, const int pic_counts, const int frames, const int begin, const int end ) : begin(begin), end(end) 
        {setParameters(frames, speed, pic_counts); };
        inline void reset() {__cur_ticks = 0;}
        void setParameters(const int& frames, const double& speed, const int& counts);
        bool advance();
    };

    /// @brief FoodAnimation, together with BulletAnimation, MouseAnimation, is used as an adapter to ImageSplicer
    ///
    /*!
        FoodAnimation draws all the status && effect on the food object, it is majorly divided into two different states
       [behave] and [normal]. FoodAnimation manages to find most appropriate way to show the animation based on the speed in
       diversed states in which the food could possible be. Mostly it deals with the transition between [normal] and [behave].
    */
    class FoodAnimation {
        public:
            FoodAnimation& operator=(const FoodAnimation&) = delete;
        public:
            FoodAnimation() = delete; 
            FoodAnimation(const int& frames, 
                const double& normal_speed, const double& behave_speed,
                const double& animNormSpeed, const double& animBehaveSpeed, 
                const int& counts, const int& behave_begin, 
                const char * resAddr, const int& level = 0, const QPoint stPt = {});
                
            ~FoodAnimation() noexcept = default;
            bool advance();             
            void switchTobehave(bool bh = true);
            void render(QPainter * painter);

            inline bool isValid() {return m_food_anim.isValid();}
            inline bool isBehaving() { return behave; }
            inline QRectF visibleRect() const {return m_food_anim.currentImageRect(); }
        private:  
            FVMctrl_core::imageSplicer m_food_anim;   ///< display the food itself
            FVMctrl_core::imageSplicer m_level_anim;  ///< display the grade of the food
            _animPlayParameters food_play_param;
            _animPlayParameters food_normal_play_param;
            _animPlayParameters level_play_param;
            QRect level_rect;                        ///< different food may have diversed place to show their grade
            bool behave;           
    };

    //! @brief BulletAnimation
    /*!
    */ 
    class BulletAnimation {
        public:
            BulletAnimation() = delete;
            BulletAnimation(const char * bulletAddr, const int counts, const int hitCounts, const int frames = _animPlayParameters::Current_Game_Frames);
            ~BulletAnimation() noexcept = default;
            void switchToBehave(bool bh = true);
            void render(QPainter *);
            bool advance();
            inline QRectF visibleRect() const {return m_bullet_anim.currentImageRect(); }
        private:
            FVMctrl_core::imageSplicer m_bullet_anim;
            _animPlayParameters bullet_normal_param;
            _animPlayParameters bullet_hit_param;
            bool behave;
    };

    class MouseAnimation {

    };

}


#endif