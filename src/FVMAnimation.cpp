#include "include/Ui/anim/FVMAnimation.h"

int scene_core::_animPlayParameters::Current_Game_Frames = 20;

scene_core::FoodAnimation::FoodAnimation(const int& frames,
                    const double& normalSpeed, const double& behaveSpeed, const double& animationNormalSpeed, const double& animayionBehaveSpeed,
                    const int& counts, const int& behave_begin, const char * resAddr,
                    const int& level, const QPoint stPt
                ) : 
    m_food_anim(counts, resAddr),
    food_play_param(behaveSpeed, counts - behave_begin + 1, frames, behave_begin, counts),
    food_normal_play_param(normalSpeed, behave_begin - 1, frames, 1, behave_begin), 
    level_play_param(2, 8, frames, 1, 8),
    behave(false)
{
    m_food_anim.setStay();
    if (level >= 7) {
        m_level_anim.reset(8, "../resource/Food/level/" + std::to_string(level) + '/');
        m_level_anim.setStay();
        level_rect = QRect(
            stPt.x(), stPt.y(),
            m_level_anim.currentImage()->width(),
            m_level_anim.currentImage()->height()
        );
    }

}
///////////////////////////////////////////////////////////////////////////////
// struct _animPlayParameters

inline void scene_core::_animPlayParameters::setParameters(const int& frames, const double& speed, const int& counts) {
    __average_ticks = (frames * (double)speed) / counts;
    if (__average_ticks == 0) __average_ticks = 1;
    // __total_counts = __average_counts * counts;
    __cur_ticks = 0; 
}

inline bool scene_core::_animPlayParameters::advance() {
    if (++__cur_ticks == __average_ticks) {
        __cur_ticks = 0;
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////////////////////////////
// class FoodAnimation
bool scene_core::FoodAnimation::advance() {
    if(level_play_param.advance()) {
        m_level_anim.advance();   
    }
    if (behave) {
        if (food_play_param.advance()) 
            return m_food_anim.advance(); 
    }
    else {
        if (food_normal_play_param.advance())
            m_food_anim.advance();
    }
    return false;                
}

void scene_core::FoodAnimation::switchTobehave(bool bh) {
    behave = bh;
    food_normal_play_param.reset();
    food_play_param.reset();
    if (bh) {
        m_food_anim.setEndFrame(food_play_param.end);
        m_food_anim.setStartFrame(food_play_param.begin);
    } else {
        m_food_anim.setEndFrame(food_normal_play_param.end);
        m_food_anim.setStartFrame(food_normal_play_param.begin);
    }
}

void scene_core::FoodAnimation::render(QPainter * painter) {
    m_food_anim.render(painter);
    m_level_anim.render(painter, level_rect);
}

///////////////////////////////////////////////////////////////////////////////
// BulletAniamtion
//
void scene_core::BulletAnimation::switchToBehave(bool bh) {
    behave = bh;
    if (bh) {
        m_bullet_anim.setStartFrame(bullet_hit_param.begin);
        m_bullet_anim.setEndFrame(bullet_hit_param.end); 
    } else {
        m_bullet_anim.setStartFrame(bullet_normal_param.begin);
        m_bullet_anim.setEndFrame(bullet_normal_param.end);
    }
}


scene_core::BulletAnimation::BulletAnimation(const char * bulletAddr, const int counts, const int hitCounts, const int frames) :
    bullet_hit_param(1.5, counts - hitCounts, frames, hitCounts, counts),
    bullet_normal_param(1.5, hitCounts, frames, 0, hitCounts),
    m_bullet_anim(counts, bulletAddr)
{
    switchToBehave(false);
}

void scene_core::BulletAnimation::render(QPainter * painter) {
    m_bullet_anim.render(painter);
}

bool scene_core::BulletAnimation::advance() {
    if (behave) {
        if (bullet_hit_param.advance()) {
            return m_bullet_anim.advance();
        }
    } else { 
        if (bullet_normal_param.advance()) {
            m_bullet_anim.advance();
        }
    }
    return false;  
}



