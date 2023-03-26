#if ! defined(_FVMKNAPACK_H_)
#define _FVMKNAPACK_H_
#include <QtWidgets/QDialog>

namespace FVMctrl_core {

    class PackageDialog : public QDialog
    {
        public:
            PackageDialog(QWidget * mainwin);
            ~PackageDialog() noexcept = default;
            
            virtual void paintEvent(QPaintEvent *);
        private:

    };
}


#endif