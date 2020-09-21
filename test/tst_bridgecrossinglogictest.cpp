#include <QtTest>
// add necessary includes here

class BridgeCrossingLogicTest : public QObject
{
    Q_OBJECT

public:
    BridgeCrossingLogicTest();
    ~BridgeCrossingLogicTest();

private slots:
    void test_case1();

};

BridgeCrossingLogicTest::BridgeCrossingLogicTest()
{

}

BridgeCrossingLogicTest::~BridgeCrossingLogicTest()
{

}

void BridgeCrossingLogicTest::test_case1()
{

}

QTEST_APPLESS_MAIN(BridgeCrossingLogicTest)

#include "tst_bridgecrossinglogictest.moc"
