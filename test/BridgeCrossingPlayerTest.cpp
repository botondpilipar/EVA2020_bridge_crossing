#include <QtTest>
#include <BridgeCrossingPlayer.h>
// add necessary includes here

using namespace kd417d::eva::logic;

class BridgeCrossingPlayerTest : public QObject
{
    Q_OBJECT

public:
    BridgeCrossingPlayerTest() : player() {}
    ~BridgeCrossingPlayerTest() = default;

private slots:
    void testContruction();
    void testPlayerId();
    void testPerformAction();
    void testThrowOnMove();
    void testThrowOnBoardPosition();
    void testDataInitialization();
    void testDataSave();
    void testSettingsChangedInteraction();

private:
    BridgeCrossingPlayer player;
};

void BridgeCrossingPlayerTest::testContruction()
{

}
void BridgeCrossingPlayerTest::testPlayerId()
{

}
void BridgeCrossingPlayerTest::testPerformAction()
{

}
void BridgeCrossingPlayerTest::testThrowOnMove()
{

}
void BridgeCrossingPlayerTest::testThrowOnBoardPosition()
{

}
void BridgeCrossingPlayerTest::testDataInitialization()
{

}
void BridgeCrossingPlayerTest::testDataSave()
{

}
void BridgeCrossingPlayerTest::testSettingsChangedInteraction()
{

}


QTEST_APPLESS_MAIN(BridgeCrossingPlayerTest)

#include "BridgeCrossingPlayerTest.moc"
