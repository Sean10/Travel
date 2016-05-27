#ifndef RUNNING
#define RUNNING

#include <QObject>
#include <QDebug>

class Running: public QObject
{
    Q_OBJECT
public:
    Running();
    ~Running();
};

#endif // RUNNING

