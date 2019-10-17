#ifndef INTERFACES_H
#define INTERFACES_H

#include <QString>

class iSerialTextReceiver
{
public:
    virtual void serialTextReady( QString str )=0;
    virtual void serialHEXReady( QString str )=0;
};

#endif // INTERFACES_H
