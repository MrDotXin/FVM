#include "include/Ui/ctrl/FVMCtrlCore.h"
#include <QtGui/QPainter>
#include <QtCore/QEvent>
#include <QtCore/QDebug>
#include <QtGui/QMouseEvent>


FVMctrl_core::polyButton::polyButton(QWidget * parent)
    : QWidget(parent), 
    pressedSheet {QString(" ")},
    hoverSheet {QString(" ")},
    releasedSheet {QString(" ")}
{
    this->setMouseTracking(true);
    installEventFilter(this);
    QPixmap pi(parent->size());
    pi.fill(Qt::transparent);
    originSheet.emplace_back(pi);
    updateStatus();
}


FVMctrl_core::polyButton::polyButton(
                    QString originSheet,  
                    QWidget * parent, 
                    QString pressedSheet,
                    QString hoverSheet, 
                    QString releasedSheet
    )
    : QWidget(parent),
    originSheet({originSheet}), pressedSheet({pressedSheet}), 
    hoverSheet({hoverSheet}), releasedSheet({releasedSheet}),
    status(button_status::origin) 
{
    this->setMouseTracking(true);
    installEventFilter(this);
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->updateStatus();
}


/// @brief dynamic Button 
/// @param originSheet          : Appearence when the button was not triggled
/// @param originsheetCounts    : count of the pic which compose of an animation 
/// @param pressedSheet         : Appearence when the button was pressed
/// @param pressedSheetCounts   : count of the pic which compose of an animation while pressed
/// @param parent               : window that displays the button
/// @param hoverSheetCount      : count of the pic which compose of a animation while hovered
/// @param hoverSheet           : Apperaence when the cursor hover on the button
/// @param releasedSheetCount   : count of the pic which compose of a animation while mouse release  
/// @param releasedSheet        : Appearence when the button was released
// note : the string parameter should be like this : "../resource/daintyTown/{statusName}{counts}.{picType}"
FVMctrl_core::polyButton::polyButton(
                    std::string picType,
                    int originSheetCounts,   std::string originSheet,
                    QWidget * parent,
                    int pressedSheetCounts,  std::string pressedSheet,
                    int hoverSheetCounts,    std::string hoverSheet,
                    int releasedSheetCounts, std::string releasedSheet
                ) : QWidget(parent) 
{
    this->setMouseTracking(true);
    installEventFilter(this);
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    int i = 1;
    do {this->originSheet.emplace_back(QPixmap((originSheet + std::to_string(i) + '.' + picType).c_str()));     }  while (i++ < originSheetCounts); i = 1;
    do {this->pressedSheet.emplace_back(QPixmap((pressedSheet + std::to_string(i) + '.' + picType).c_str()));   }  while (i++ < pressedSheetCounts);i = 1;
    do {this->hoverSheet.emplace_back(QPixmap((hoverSheet + std::to_string(i) + '.' + picType).c_str()));       }  while (i++ < hoverSheetCounts);  i = 1;
    do {this->releasedSheet.emplace_back(QPixmap((releasedSheet + std::to_string(i) + '.' + picType).c_str())); }  while (i++ < releasedSheetCounts);
    updateStatus();
    startTimer(100);


    triggled_func = [this](){qDebug() << "不是哥们你拿ak当烧火棍用啊"; };
}

FVMctrl_core::polyButton::~polyButton()
{

}

void FVMctrl_core::polyButton::updateStatus(button_status s)
{
    auto old = status;
    switch(status = s; status) 
    {
        case button_status::origin :
            if (beginImage != originSheet.begin()) {
                curImage   = originSheet.begin(); 
                beginImage = curImage; 
                endImage   = originSheet.end(); 
            }
            break;

        case button_status::hover  : {
            if (hoverSheet[0].isNull()) {
                if (old == button_status::origin)
                        break;
                //curImage   = originSheet.begin();
                //beginImage = curImage;
                //endImage   = originSheet.end();
            }
            else {
                curImage   = hoverSheet.begin();
                beginImage = curImage;
                endImage   = hoverSheet.end();
            }
        }
        break;

        case button_status::pressed : {
            if (pressedSheet[0].isNull()) {
                //curImage   =  originSheet.begin();
                //beginImage = curImage;
                //endImage   = originSheet.end();
            }
            else {
                curImage   = pressedSheet.begin();
                beginImage = curImage;
                endImage   = pressedSheet.end();
            }
        }
        break;

        case button_status::released : {
            if (releasedSheet[0].isNull()) {
                if (hoverSheet[0].isNull()) {
                    //curImage   = originSheet.begin();
                    //beginImage = curImage;
                    //endImage   = originSheet.end();
                }
                else {
                      //curImage   = hoverSheet.begin();
                      //beginImage = curImage;
                      //endImage   = hoverSheet.end();
                }
                break;
            }
            else {
                curImage   = releasedSheet.begin();
                beginImage = curImage;
                endImage   = releasedSheet.end();
            }
        }
    } 
    
    this->resize(curImage->size());
    setMask();
    repaint();    
}

void FVMctrl_core::polyButton::advance()
{
    static bool flag = true;
    if (flag) {
        if (++curImage == endImage) {
            --curImage, flag = false;
        }
    }
    else {
        if (--curImage == beginImage) {
            flag = true;
        }
    }
    
    this->setMask();
    this->resize(curImage->size());
    repaint();
}

void FVMctrl_core::polyButton::timerEvent(QTimerEvent *)
{
    this->advance();
}

void FVMctrl_core::polyButton::setMask()
{
    if (mask_enable)
        QWidget::setMask(curImage->mask());
}

void FVMctrl_core::polyButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!curImage->isNull()) {
        painter.drawPixmap(QRect(0, 0, curImage->width(), curImage->height()), *curImage);
    } else 
        qDebug() << "Invalid picture address !";
    painter.end();
}

bool FVMctrl_core::polyButton::eventFilter(QObject * obj, QEvent * event)
{
    if (obj == this) {
        if (event->type() == QEvent::Enter) {
            setCursor(Qt::PointingHandCursor);
            updateStatus(button_status::hover);
        }
        else if (event->type() == QEvent::Leave) {
            setCursor(Qt::ArrowCursor);
            updateStatus(button_status::origin);
        }
    }
    return QWidget::eventFilter(obj, event);
}

void FVMctrl_core::polyButton::mousePressEvent(QMouseEvent * event) {
    updateStatus(button_status::pressed);
    vecP = event->globalPosition() - this->pos();
    mv = true;
}

void FVMctrl_core::polyButton::mouseReleaseEvent(QMouseEvent *) {
    setCursor(Qt::PointingHandCursor);
    updateStatus(button_status::hover);
    mv = false;

    triggled_func();
}

void FVMctrl_core::polyButton::mouseMoveEvent(QMouseEvent * event) {
    if (mv == true) {
        QPointF pt = event->globalPosition() - vecP; 
        this->move(pt.x(), pt.y());
        qDebug() << pt;
    }
}
// class polyButton

/////////////////////////////////////////////////////////////////////////////////


void FVMctrl_core::dynamicPolyButton::paintEvent(QPaintEvent * p)
{
}

void FVMctrl_core::dynamicPolyButton::updateStatus(button_status st)
{
    status = st;
    switch(status) {
        case button_status::origin :
                    m_currentMv->setPaused(true);
                    m_currentMv = &originMv;
                    m_Mvdisplayer->setMovie(m_currentMv);
                    m_currentMv->start();
                    break;
        case button_status::hover :
                    if (hoverMv.isValid()) {
                       m_currentMv->stop();
                       m_currentMv = &hoverMv;
                       m_Mvdisplayer->setMovie(m_currentMv);
                        m_currentMv->start();
                    }
                    break;
        case button_status::pressed :
                    if (pressedMv.isValid()) {
                       m_currentMv->stop();
                       m_currentMv = &pressedMv;
                       m_Mvdisplayer->setMovie(m_currentMv);
                        m_currentMv->start();
                    }
                    break;
        case button_status::released :
                    if (releasedMv.isValid()) {
                        m_currentMv->stop();
                        m_currentMv = &releasedMv;
                        m_Mvdisplayer->setMovie(m_currentMv);
                        m_currentMv->start();
                    }
    }
    if (status != button_status::origin)
        this->clearMask();
    repaint();
}

FVMctrl_core::dynamicPolyButton::dynamicPolyButton(
                                        QString origin,                                        
                                        QWidget * parent,
                                        QString hover,
                                        QString press,
                                        QString release
            ) : QWidget(parent),
            originMv(origin),
            hoverMv(hover),
            pressedMv(press),
            releasedMv(release),
            m_Mvdisplayer(new QLabel(this)),
            m_currentMv(nullptr),
            status(button_status::origin)
{
    this->setMouseTracking(true);
    installEventFilter(this);
    auto frameChange = [this](int) {
        QPixmap pix = this->m_currentMv->currentPixmap();
        this->resize(pix.size());
        this->m_Mvdisplayer->resize(pix.size());
        if (currentStatus() == button_status::origin) {
            this->setMask(&pix);
        }
    };
    QObject::connect(&originMv, QMovie::frameChanged, frameChange);
    QObject::connect(&hoverMv, QMovie::frameChanged, frameChange);
    QObject::connect(&pressedMv, QMovie::frameChanged, frameChange);
    QObject::connect(&releasedMv, QMovie::frameChanged, frameChange); 
    m_currentMv = &originMv;
    m_Mvdisplayer->move(0, 0);
    if (m_currentMv->isValid()) {
        this->resize(m_currentMv->currentPixmap().size());
        m_Mvdisplayer->resize(this->size());
        m_Mvdisplayer->setMovie(m_currentMv);
        m_currentMv->start();
    } else {
        qDebug() << "inValid resource";
    }
}

bool FVMctrl_core::dynamicPolyButton::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::Enter) {
        setCursor(Qt::PointingHandCursor);
        updateStatus(button_status::hover);
    } else if (event->type() == QEvent::Leave) {
        setCursor(Qt::ArrowCursor);
        updateStatus(button_status::origin);
    }

    return QWidget::eventFilter(obj, event);
}

void FVMctrl_core::dynamicPolyButton::setMask(QPixmap * pix)
{
    if (mask_enable)
        QWidget::setMask(pix->mask());
}

void FVMctrl_core::dynamicPolyButton::mousePressEvent(QMouseEvent *) 
{
    updateStatus(button_status::pressed);
}

void FVMctrl_core::dynamicPolyButton::mouseReleaseEvent(QMouseEvent *)
{
    updateStatus(button_status::hover);
}
//class dynamicPolyButton

///////////////////////////////////////////////////////////////////////

FVMctrl_core::svgPolyButton::svgPolyButton(
                                        std::string hoverSheet,
                                        QWidget * parent,
                                        std::string pressedSheet,
                                        std::string originSheet,
                                        std::string releasedSheet
                        ) : QWidget(parent),
                            originSheet(originSheet),
                            pressedSheet(pressedSheet),
                            hoverSheet(hoverSheet),
                            releasedSheet(releasedSheet) 
{
    this->setMouseTracking(true);
    installEventFilter(this);
    if (this->hoverSheet.isValid()) {
        invalid_pixmap = QPixmap(   
                                QSize(
                                    this->hoverSheet.currentImage()->defaultSize().width(),
                                    this->hoverSheet.currentImage()->defaultSize().height()
                            )   
                    ); 

    invalid_pixmap.fill(Qt::transparent);
    resize(QSize(
        this->hoverSheet.currentImage()->defaultSize().width(),
        this->hoverSheet.currentImage()->defaultSize().height()
        )
    );
    m_currentSheet = &this->originSheet;
    makeMask();
    }
    updateStatus();
}

FVMctrl_core::svgPolyButton::svgPolyButton(
                                std::string hoverSheet, int hoverCount, int hoverStartCount,
                                QWidget * parent,                                
                                std::string originSheet, int originCount, int originStartCount,
                                std::string pressedSheet, int pressedCount, int pressedStartCount,
                                std::string releasedSheet, int releasedCount, int releasedStartCount
                    ) : QWidget(parent),
                        originSheet(originCount ,originSheet, originStartCount),
                        pressedSheet(pressedCount, pressedSheet, pressedStartCount),
                        hoverSheet(hoverCount, hoverSheet, hoverStartCount),
                        releasedSheet(releasedCount, releasedSheet, releasedStartCount)
            {
    this->setMouseTracking(true);
    installEventFilter(this);
    if (this->hoverSheet.isValid()) {
        invalid_pixmap = QPixmap(   
                                QSize(
                                    this->hoverSheet.currentImage()->defaultSize().width(),
                                    this->hoverSheet.currentImage()->defaultSize().height()
                            )   
                    );
    }

    invalid_pixmap.fill(Qt::transparent);
    resize(QSize(
        this->hoverSheet.currentImage()->defaultSize().width(),
        this->hoverSheet.currentImage()->defaultSize().height()
        )
    );
    startTimer(100);
    m_currentSheet = &this->originSheet;
    updateStatus();
}

void FVMctrl_core::svgPolyButton::updateStatus(FVMctrl_core::button_status s)
{   
    if (m_currentSheet->isValid()) masked = false; else masked = true;
    switch(status = s; status) {
        case button_status::origin   : m_currentSheet = &originSheet;   break;
        case button_status::pressed  : m_currentSheet = &pressedSheet;  break;
        case button_status::released : m_currentSheet = &releasedSheet; break;
        case button_status::hover    : m_currentSheet = &hoverSheet;    break;
    }
    isValid = m_currentSheet->isValid();
    if (isValid) {
        resize(
            m_currentSheet->currentImage()->defaultSize().width(),
            m_currentSheet->currentImage()->defaultSize().height()
        );
    }
    repaint();
}

void FVMctrl_core::svgPolyButton::makeMask()
{
    QPixmap pic;        
            pic = QPixmap(   
                        QSize(
                                hoverSheet.MaxRenderer()->defaultSize().width(),
                                hoverSheet.MaxRenderer()->defaultSize().height()
                            )   
                        );
            pic.fill(Qt::transparent);
            QPainter painter(&pic);
            hoverSheet.render(&painter, 
                            QRect(
                                0, 0, 
                                hoverSheet.currentImage()->defaultSize().width(),
                                hoverSheet.currentImage()->defaultSize().height()
                            )
                    );
            this->clearMask();
            this->setMask(pic.createMaskFromColor(Qt::transparent));   
            masked = true;
            painter.end();  
}

void FVMctrl_core::svgPolyButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (m_currentSheet->isValid()) {
        m_currentSheet->render(&painter, m_currentSheet->currentImageRect());  
    } else {
        painter.drawPixmap(QRect(0, 0, invalid_pixmap.width(), invalid_pixmap.height()), invalid_pixmap);
    }
    painter.end();
}


bool FVMctrl_core::svgPolyButton::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::Enter) {
        setCursor(Qt::PointingHandCursor);
        updateStatus(button_status::hover);
    } else if (event->type() == QEvent::Leave) {
        setCursor(Qt::ArrowCursor);
        updateStatus(button_status::origin);
    }

    return QWidget::eventFilter(obj, event);
}

void FVMctrl_core::svgPolyButton::mousePressEvent(QMouseEvent * event) {
    updateStatus(button_status::pressed);
    vecP = event->globalPosition() - this->pos();
    mv = true;
}

void FVMctrl_core::svgPolyButton::mouseReleaseEvent(QMouseEvent *) {
    setCursor(Qt::PointingHandCursor);
    updateStatus(button_status::hover);
    mv = false;

    triggled_func();
}

void FVMctrl_core::svgPolyButton::mouseMoveEvent(QMouseEvent * event) {
    if (mv == true) {
        QPointF pt = event->globalPosition() - vecP; 
        this->move(pt.x(), pt.y());
        qDebug() << pt;
    }
}

void FVMctrl_core::svgPolyButton::timerEvent(QTimerEvent * ) {
    repaint();
}
