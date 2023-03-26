#include "include/Ui/FVMUi.h"
#include "include/Ui/ctrl/FVMCtrlCore.h"
#include "include/Ui/FVMPackage.h"
#include "MainWidget.h"
#include <QtGui/QPainter>
#include <QtWidgets/QDialog>
#include <QtGui/QMouseEvent>


FVMctrl_core::FVMOptionGroup::FVMOptionGroup(MainWidget * parent)
    : QWidget(parent), option_group_background("../resource/GameUi/Tool/bk.png") 
{
    // base : x 75 / 50 y : 10
    this->resize(option_group_background.size());
    this->setObjectName("FVMOPTION");
    this->setStyleSheet("#FVMOPTION{border-image:url(../resource/GameUi/Tool/bk.png)}");

    ui_quit = new FVMctrl_core::polyButton(
            "../resource/GameUi/Tool/back.png",
            this,
            "../resource/GameUi/Tool/back.png",
            "../resource/GameUi/Tool/back(2).png",
            "../resource/GameUi/Tool/back.png"
    );

    ui_synthesisHouse = new FVMctrl_core::polyButton(
        "../resource/GameUi/Tool/composesite.png",
        this,
        "../resource/GameUi/Tool/composesite.png",
        "../resource/GameUi/Tool/composesite(2).png",
        "../resource/GameUi/Tool/composesite.png"
    );

    ui_knapsack = new FVMctrl_core::polyButton(
        "../resource/GameUi/Tool/knapsack.png",
        this,
        "../resource/GameUi/Tool/knapsack.png",
        "../resource/GameUi/Tool/knapsack(2).png",
        "../resource/GameUi/Tool/knapsack.png"
    );

    ui_quit->triggled_func = [this, parent]() {
        parent->switchScene(parent->currentScene()->getSceneId() - 1);
    };

    ui_knapsack->triggled_func = [this, parent]() {
        
        static auto dlg = new FVMctrl_core::PackageDialog(parent);
        dlg->exec();
    };

    ui_knapsack->move(125, 9);
    ui_synthesisHouse->move(212, 10);
    ui_quit->move(396, 10);
    this->move(510, 540);
}



void FVMctrl_core::FVMOptionGroup::mouseMoveEvent(QMouseEvent * ev)
{
    if (_is_draging) {
        this->move(ev->pos() - drag_pos);
        qDebug() << this->pos();
    }
}

void FVMctrl_core::FVMOptionGroup::mousePressEvent(QMouseEvent * ev)
{
    _is_draging = true;
    drag_pos = ev->pos() - this->pos();
}

void FVMctrl_core::FVMOptionGroup::mouseReleaseEvent(QMouseEvent *)
{
    _is_draging = false;
}

void FVMctrl_core::FVMOptionGroup::paintEvent(QPaintEvent *)
{
    static QPixmap base("../resource/GameUi/Tool/base.png");
    QPainter painter(this);
    painter.drawPixmap(QRect(74, 10, base.width(), base.height()), base);
    painter.drawPixmap(QRect(123, 10, base.width(), base.height()), base);
    // painter.drawPixmap(QRect(168, 10, base.width(), base.height()), base);
    painter.drawPixmap(QRect(214, 10, base.width(), base.height()), base);
    painter.drawPixmap(QRect(396, 10, base.width(), base.height()), base);
    painter.end();
}