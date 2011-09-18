#include <QObject>

class myclass: public QObject
{
    Q_OBJECT

public:
    myclass();
    void set_value(int newValue);
    int get_value();

signals:
    void mysignal(); 
    void int_mysignal(int value);

public slots:
    void do_print(); 
    void do_mysignal();
    void int_myslot(int value);

private:
    int m_value;
    int m_cnt;
};
