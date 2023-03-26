#include "include/Ui/FVMPackage.h"
#include "MainWidget.h"
#include "include/Ui/FVMUi.h"
#include "include/Ui/ctrl/FVMCtrlCore.h"

FVMctrl_core::PackageDialog::PackageDialog(QWidget * parent)
    : QDialog(parent, Qt::FramelessWindowHint)
{
    this->resize(930, 500);
    this->move(parent->pos().x() + 10, parent->pos().y() + 70);
    this->setObjectName("FVMPackageDlg");
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setPalette(QPalette(qRgb(38, 106, 171)));
    auto * form = new FVMCardContainerView(this, QRect(450, 50, 445, 400));
    auto cardBtn = new polyButton(
        "../resource/GameUi/Package/1.png",
        this,
        "../resource/GameUi/Package/2.png"
    );
    
    auto closeBtn = new polyButton(
        "../resource/GameUi/Package/dialogBtn/78.png",
        this,
        "../resource/GameUi/Package/dialogBtn/80.png",
        "../resource/GameUi/Package/dialogBtn/82.png"
    );

    auto coinBtn = new polyButton(
        "../resource/GameUi/Package/366.png",
        this
    );
    auto man_display = new polyButton(
        "../resource/GameUi/Package/555.png",
        this
    );


    closeBtn->triggled_func = [this]() {this->close(); };
    coinBtn->move(450, 451);
    closeBtn->move(887, 7);
    man_display->move(15, 74);
    cardBtn->move(622, 19);
}


void FVMctrl_core::PackageDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap background("../resource/GameUi/Package/upFrame.png");
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), background);
    QPixmap leftPack("../resource/GameUi/Package/backage.png");
    painter.drawPixmap(QRect(443, 12, leftPack.width() + 50, leftPack.height()), leftPack);

}