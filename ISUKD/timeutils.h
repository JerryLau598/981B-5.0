#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <QString>

class TimeUtils
{
public:
    typedef unsigned long long timestamp_t;

    static timestamp_t getCurrentNanoSinceEpoch();
    static QString getCurrentTimeFormatted();
private:
    explicit TimeUtils();
};

#endif // TIMEUTILS_H
