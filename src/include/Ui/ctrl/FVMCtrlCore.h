#pragma once 
#include <QtWidgets/QWidget>
#include <functional>
#include <QtGui/QMovie>
#include <QtWidgets/QLabel>
#include <QtSvg/QSvgRenderer>
#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <memory>
#include <vector>


// possibly turn these ctrl class into a template
namespace FVMctrl_core {

    enum class animation_type {
                circle,
                line 
            };  


    inline namespace _Image {

        class svgSplicer
        {
            using image_type = QSvgRenderer;
            public:
                svgSplicer(int count, const std::string& firstFrameint, int startCount = 1);
                svgSplicer(const std::string& firstFrame);
                ~svgSplicer() noexcept;

                void render(QPainter *, const QRect& rect);

                [[nodiscard]] inline const int & count()        const { return _frameCount; } 
                [[nodiscard]] inline const int & currentFrame() const { return _currentFrame; }  
                [[nodiscard]] inline bool isValid()             const{ return _Valid;}  
                [[nodiscard]] inline const std::shared_ptr<QSvgRenderer> currentImage() const { return _m_splicer[_currentFrame]; } 
                [[nodiscard]] inline const QRect currentImageRect()      const 
                    {return QRect(0, 0, 
                        currentImage()->defaultSize().width(),
                        currentImage()->defaultSize().height()); }

                [[nodiscard]] inline const std::shared_ptr<QSvgRenderer> MaxRenderer() const {return maxRenderer; }
                [[nodiscard]] inline const std::shared_ptr<QSvgRenderer> MinRenderer() const {return mininRenderer; }

            private:
                std::vector<std::shared_ptr<QSvgRenderer> > _m_splicer;

                std::shared_ptr<QSvgRenderer> maxRenderer;
                std::shared_ptr<QSvgRenderer> mininRenderer; 
                bool _Valid;
                int _frameCount;
                int _currentFrame;
        }; // class svgSplicer

        class imageSplicer
        {
            using image_type = QPixmap;
            public:
                imageSplicer() : _Valid(false) {};
                imageSplicer(int count, const std::string& firstFrame, const std::string & picType = "png");
                ~imageSplicer() noexcept = default;

                bool reset(const int& count, const std::string& firstFrame, const std::string& picType = "png");

                void render(QPainter *, const QRect& rect = QRect(), bool st = true);
                void render(QPainter *, const int& framePos, const QRect& rect = QRect()); ///< For optimalize 
                [[nodiscard]] inline const int & count() {return _frameCount; }
                [[nodiscard]] inline const int & currentFrame() {return _currentFrame;}
                [[nodiscard]] inline const bool & isValid() {return _Valid; }
                [[nodiscard]] inline const QPixmap * currentImage() { return &_m_splicer[_currentFrame]; }
                [[nodiscard]] inline const QRect currentImageRect() const 
                    { return QRect(0, 0, _m_splicer[_currentFrame].width(), _m_splicer[_currentFrame].height());}

                inline void setStartFrame(const int startFrame) {_start_frame = startFrame; _currentFrame = _start_frame; }
                inline void setEndFrame(const int endFrame) {_end_frame = endFrame; } 
                [[nodiscard]] inline const int& StartFrame() {return _start_frame; }
                [[nodiscard]] inline const int& EndFrame() {return _end_frame; }
                [[nodiscard]] inline const int currentCounts() const {return _end_frame - _start_frame + 1; }

                inline void setStay(bool s = true) { _move = !s; }
                inline bool advance() {
                        ++_currentFrame;
                        if (_currentFrame == _end_frame) {
                            _currentFrame = _start_frame;
                            return true;
                        }
                        return false;
                } 

            private:
                std::vector<QPixmap> _m_splicer;

                bool _Valid;
                bool _move;
                int _frameCount;
                int _currentFrame;
                int _start_frame = 0;
                int _end_frame;
        }; // class imageSplicer

        template<class _Splicer_Type>
        class SplicerPlayer : public QWidget
        {

            public:
                template<class...Args>
                    SplicerPlayer(QWidget * parent, Args&&...args) 
                        : QWidget(parent), _m_splicer(std::forward<Args>(args)...)
                    {
                        startTimer(100);
                    }
                ~SplicerPlayer() noexcept = default;

                virtual void paintEvent(QPaintEvent *) {
                    QPainter painter(this);
                    _m_splicer.render(&painter, _m_splicer.currentImageRect());
                    painter.end();
                }
                virtual void timerEvent(QTimerEvent *) {
                    this->resize(
                            _m_splicer.currentImageRect().width(),
                            _m_splicer.currentImageRect().height()
                        );
                    repaint();
                }
            private:
                _Splicer_Type _m_splicer;
        };

    } // namespace _Image 

        enum class button_status {
                origin,
                pressed,
                hover,
                released = 3
            };

        // class polyButton
        class polyButton : public QWidget
        {    
            public :
                // for further 
                polyButton(QWidget * parent = nullptr);
            public :
                using QWidget::setMask;


                polyButton(
                    QString originSheet,  
                    QWidget * parent = nullptr, 
                    QString pressedSheet = "",
                    QString hoverSheet ="", 
                    QString releasedSheet = ""
                    );
                
                polyButton(
                    std::string picType,
                    int originsheetCounts,      std::string originSheet,                   
                    QWidget * parent,
                    int pressedSheetCounts = 1, std::string pressedSheet = "",
                    int hoverSheetCount    = 1, std::string hoverSheet = "",
                    int releasedSheetCount = 1, std::string releasedSheet = ""
                );
                
                virtual ~polyButton() noexcept;

                inline void enableMask(bool flag = true) { mask_enable = flag; }
                inline const button_status & currentStatus() {return status;}
                void updateStatus(button_status default_status = button_status::origin);    
                void setMask();
                void advance();

                virtual void paintEvent(QPaintEvent *) override;
                virtual void mousePressEvent(QMouseEvent *) override;
                virtual void mouseReleaseEvent(QMouseEvent *) override;
                virtual bool eventFilter(QObject *, QEvent *) override;
                virtual void timerEvent(QTimerEvent *) override;
                

                virtual void mouseMoveEvent(QMouseEvent * ) override;
                QPointF vecP;
                bool mv = false;

                void modifyStatusSheet(button_status st, QPixmap * pix);  
            private:
                std::vector<QPixmap> originSheet;
                std::vector<QPixmap> pressedSheet;
                std::vector<QPixmap> hoverSheet;
                std::vector<QPixmap> releasedSheet;

                button_status status = button_status::origin;
                std::vector<QPixmap>::iterator curImage;
                std::vector<QPixmap>::iterator beginImage;
                std::vector<QPixmap>::iterator endImage;
                bool mask_enable = false; 
            public:
                std::function<void()> triggled_func = 
                    [this](){qDebug() << QString("不是哥们你TM拿ak当烧火棍用啊"); };
        }; // class polyButton


        // class dynamicPolyButton
        class dynamicPolyButton : public QWidget
        {
            protected :
                // for further code
                dynamicPolyButton() = default;
            public:
                dynamicPolyButton(                    
                    QString origin,                    
                    QWidget * parent = nullptr,
                    QString hover = "",
                    QString press = "",
                    QString release = ""
                );
                ~dynamicPolyButton() noexcept = default;

                void setMask(QPixmap * pix);
                void updateStatus(button_status default_status = button_status::origin);

                inline const button_status & currentStatus() { return status; }
                inline void enableMask() { mask_enable = true; }
                inline QRect currentMask() {return QWidget::mask().boundingRect(); }

                virtual void paintEvent(QPaintEvent *) override;
                virtual void mousePressEvent(QMouseEvent *) override;
                virtual void mouseReleaseEvent(QMouseEvent *) override;
                virtual bool eventFilter(QObject *, QEvent *) override;

            private:
                QMovie originMv;
                QMovie hoverMv;
                QMovie pressedMv;
                QMovie releasedMv;
                QLabel * m_Mvdisplayer; 
                QMovie * m_currentMv;
                button_status status;

                bool mask_enable = false;
        }; // class dynamicPolyButton


        // class svgPolyButton
        class svgPolyButton : public QWidget
        {
            public: 
                using QWidget::setMask;

                svgPolyButton(
                    std::string originSheet,
                    QWidget * parent = nullptr,
                    std::string pressedSheet = "",
                    std::string hoverSheet = "",
                    std::string releasedSheet = ""
                );

                svgPolyButton(
                    std::string originSheet, int originCount, int originStartCount = 1,
                    QWidget * parent = nullptr,                    
                    std::string hoverSheet = "", int hoverCount = 1, int hoverStartCount = 1,
                    std::string pressedSheet = "", int pressedCount = 1, int pressedStartCount = 1,
                    std::string releasedSheet = "", int releasedCount = 1, int releasedStartCount = 1
                );

                ~svgPolyButton() noexcept = default;

                void makeMask();                        // 要改这里
                void updateStatus(button_status status = button_status::origin);
                virtual void paintEvent(QPaintEvent *) override;
                virtual void mousePressEvent(QMouseEvent *) override;
                virtual void mouseReleaseEvent(QMouseEvent *) override;
                virtual bool eventFilter(QObject *, QEvent *) override;
                virtual void timerEvent(QTimerEvent *) override;

                virtual void mouseMoveEvent(QMouseEvent * ) override;
                QPointF vecP;
                bool mv = false; 

            private:
                svgSplicer originSheet;
                svgSplicer pressedSheet;
                svgSplicer releasedSheet;
                svgSplicer hoverSheet;
                svgSplicer * m_currentSheet;
                button_status status;
                bool isValid = false;      
                bool masked = false;    

                QPixmap invalid_pixmap; 
            public:
                std::function<void()> triggled_func = 
                    [this](){qDebug() << QString("不是哥们你TM拿ak当烧火棍用啊"); };
        };

} // namespace FVMctrl_core