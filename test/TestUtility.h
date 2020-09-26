#ifndef TESTUTILITY_H
#define TESTUTILITY_H

#include <QtTest>
#define QINRANGE(value, rangeMin, rangeMax) \
    QVERIFY(value >= rangeMin); \
    QVERIFY(value <= rangeMax)

#endif // TESTUTILITY_H
