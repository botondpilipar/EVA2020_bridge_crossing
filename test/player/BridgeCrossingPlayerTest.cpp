// Qt Library Includes
#include <QtTest>
#include <QSignalSpy>
#include <cstring>

// Local library includes
#include <UnimplementedException.h>
#include <BridgeCrossingPlayer.h>


using namespace kd417d::eva;
using namespace kd417d::eva::logic;
using namespace kd417d::eva::access;

class BridgeCrossingPlayerTest : public QObject
{
    Q_OBJECT
    static constexpr int testIdentifier = 1;

public:
    BridgeCrossingPlayerTest() : identifier(testIdentifier),
        playerWithId(nullptr)
    {
        qRegisterMetaType<BridgeCrossingTypes::PlayerActionSet>("BridgeCrossingTypes::PlayerActionSet");
    }
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


    QSignalSpy crossSpy(playerWithId.get(), SIGNAL(actionPerformedSignal(BridgeCrossingTypes::PlayerActionSet)));
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

    QVERIFY_EXCEPTION_THROWN(playerWithId->move(QPair(0, 0)), UnimplementedException);
}
void BridgeCrossingPlayerTest::testThrowOnBoardPosition()
{
    QVERIFY_EXCEPTION_THROWN(playerWithId->getPositionOnBoard(), UnimplementedException);
}
void BridgeCrossingPlayerTest::testDataInitialization()
{
    PlayerData data(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                    testIdentifier,
                    BridgeCrossingTypes::PlayerType::SLOW,
                    10);
    playerWithId->initialize(data);

    QCOMPARE(playerWithId->getPlayerState(), BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
    QCOMPARE(playerWithId->getUniqueId(), 1);
    QCOMPARE(playerWithId->getPlayerType(), BridgeCrossingTypes::PlayerType::SLOW);
    QCOMPARE(playerWithId->getCrossSpeed(), 10);

}
void BridgeCrossingPlayerTest::testDataSave()
{
    std::unique_ptr<PlayerData> data(new PlayerData(BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE,
                    testIdentifier,
                    BridgeCrossingTypes::PlayerType::FAST,
                    112));

    playerWithId->initialize(*data);
    std::unique_ptr<PlayerData> saved(playerWithId->save());

    QVERIFY(*data == *saved);
}

QTEST_APPLESS_MAIN(BridgeCrossingPlayerTest);

#include "BridgeCrossingPlayerTest.moc"
