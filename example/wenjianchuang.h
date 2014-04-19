#ifndef WENJIANCHUANG_H
#define WENJIANCHUANG_H

#include <QDialog>

namespace Ui {
class wenjianchuang;
}

class wenjianchuang : public QDialog
{
    Q_OBJECT
    
public:
    explicit wenjianchuang(QWidget *parent = 0);
    ~wenjianchuang();
    
private:
    Ui::wenjianchuang *ui;
};

#endif // WENJIANCHUANG_H
