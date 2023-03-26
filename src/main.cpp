#include <QtWidgets/QApplication>
#include "MainWidget.h"


/*
    * @brief 关于代码 ；
    *   我会尽量用相同规则下的命名方式和书写方式
    *   以便以后重构的时候整理代码和简化代码
    *   "__" 开头的变量说明是内部的,没事别乱改!
    * 
    * 
*/
int main(int argc, char* argv[])
{
    QApplication FVM_app(argc, argv);
    MainWidget mw;
    qDebug() << "show";
    mw.show();
    return FVM_app.exec();
}