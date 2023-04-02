#include "include/Ui/ctrl/FVMCtrlCore.h"
#include <QtGui/QPainter>

FVMctrl_core::svgSplicer::svgSplicer(int count, const std::string& firstFrame, int startCount)
    : _frameCount(count - startCount), _currentFrame(0), _Valid(true)
{
    if (firstFrame == "") return;
    int i = startCount;
    do {
        _m_splicer.emplace_back(
                new QSvgRenderer (
                        QString(
                            (firstFrame + std::to_string(i) + ".svg").c_str()
                        )
                    )
        ); 
        if (!((*_m_splicer.rbegin())->isValid())) {
            _Valid = false;
            break;
        }
        if (maxRenderer == nullptr || 
            (*_m_splicer.rbegin())->defaultSize().height() > maxRenderer->defaultSize().height() ||
            (*_m_splicer.rbegin())->defaultSize().width() > maxRenderer->defaultSize().width()
            ) {
                maxRenderer = (*_m_splicer.rbegin());
        }
    } while(i++ < count);

    if (_frameCount <= 0) _frameCount = 1;
}

FVMctrl_core::svgSplicer::svgSplicer(const std::string& firstFrame)
    : _frameCount(1), _currentFrame(0), _Valid(false)
{
    if (firstFrame == "") return;
    _m_splicer.emplace_back(new QSvgRenderer(QString(firstFrame.c_str())));
    if (!(*(_m_splicer.rbegin()))->isValid()) { 
        _m_splicer.clear();
        return ;
    }
    _Valid = true;
    maxRenderer = currentImage();
}

FVMctrl_core::svgSplicer::~svgSplicer() {};

void FVMctrl_core::svgSplicer::render(QPainter * painter, const QRect & rect)
{
    if (_Valid)
        _m_splicer[_currentFrame]->render(painter, rect);
    ++_currentFrame;
    if (_currentFrame == _frameCount)
        _currentFrame = 0;
}

///////////////////////////////////////////////////////////////////////////////////

bool FVMctrl_core::imageSplicer::reset(const int& count, const std::string& firstFrame, const std::string& profix)
{
    if (firstFrame == "") { _Valid = false; return _Valid;}
    _frameCount = count;
    _currentFrame = 0;
    _end_frame = _frameCount;
    _start_frame = _currentFrame;
    _m_splicer.clear();
    _Valid = true;
    _move = true;
    int i = 1;
    do {
        _m_splicer.emplace_back(                                                                                                                                
                QString(
                    (firstFrame + std::to_string(i) + '.' + profix).c_str()
                )
        ); 
        if (_m_splicer.back().isNull()) _Valid = false;
    } while(i++ < count);
    
    return _Valid;
}

FVMctrl_core::imageSplicer::imageSplicer(int count, const std::string& firstFrame, const std::string& profix) 
{
    if (!reset(count, firstFrame, profix)) _m_splicer.clear(); 
}

void FVMctrl_core::imageSplicer::render(QPainter * painter, const QRect & rect, bool status)
{
    if (_Valid) {
        
        painter->drawPixmap((rect == QRect() ? 
            QRect(0, 0, _m_splicer[_currentFrame].width(), 
                        _m_splicer[_currentFrame].height()) : rect), 
            _m_splicer[_currentFrame]);
        if (_move) ++_currentFrame;
        if (_currentFrame == _end_frame)
            _currentFrame = _start_frame;
    }
}