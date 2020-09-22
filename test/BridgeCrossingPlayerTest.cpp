#include <QtTest>
#include <BridgeCrossingPlayer.h>
#include <QSignalSpy>
// add necessary includes here

using namespace kd417d::eva::logic;

class BridgeCrossingPlayerTest : public QObject
{
    Q_OBJECT
    static constexpr int testIdentifier = 1;

public:
    BridgeCrossingPlayerTest() : identifier(testIdentifier),
        playerWithId(nullptr) {}
    ~BridgeCrossingPlayerTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPlayerId();
    void testPerformAction();
    void testThrowOnMove();
    void testThrowOnBoardPosition();
    void testDataInitialization();
    void testDataSave();
    void testSettingsChangedInteraction();

private:
    int identifier;
    std::unique_ptr<BridgeCrossingPlayer> playerWithId;
};

void BridgeCrossingPlayerTest::initTestCase()
{
    playerWithId = std::unique_ptr<BridgeCrossingPlayer>(new BridgeCrossingPlayer(identifier));

}
void BridgeCrossingPlayerTest::cleanupTestCase()
{

}

void BridgeCrossingPlayerTest::testPlayerId()
{
    QCOMPARE(testIdentifier, playerWithId->getUniqueId());
    QCOMPARE(0, BridgeCrossingPlayer().getUniqueId());
}
void BridgeCrossingPlayerTest::testPerformAction()
{
    qRegisterMetaType<BridgeCrossingTypes::PlayerActionSet>();
    QSignalSpy crossSpy(playerWithId.get(), SIGNAL(actionPerformedSignal(PlayerActionSet)));
    QVERIFY(crossSpy.isValid());

    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::CROSS);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::CROSS);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::RETURN);
    QCOMPARE(crossSpy.count(), 3);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::CROSS);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::CROSS);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::RETURN);
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
