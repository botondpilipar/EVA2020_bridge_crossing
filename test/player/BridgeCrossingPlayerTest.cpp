// Qt Library Includes
#include <QtTest>
#include <QSignalSpy>
#include <cstring>

// Local library includes
#include <UnimplementedException.h>
#include <BridgeCrossingPlayer.h>
#include <SingletonFactory.hpp>


using namespace kd417d::eva;
using namespace kd417d::eva::logic;
using namespace kd417d::eva::access;

class BridgeCrossingPlayerTest : public QObject
{
    Q_OBJECT
    static constexpr int testIdentifier = 1;

public:
    BridgeCrossingPlayerTest()
    {
        qRegisterMetaType<BridgeCrossingTypes::PlayerActionSet>("BridgeCrossingTypes::PlayerActionSet");
    }
    ~BridgeCrossingPlayerTest() = default;

private slots:
    void initTestCase();
    void init();
    void cleanupTestCase();

    void testPlayerId();

    void testPerformAction();
    void testPerformInvalidAction();
    void testPerformMoveToBridgeMultipletimes();

    void testThrowOnMove();
    void testThrowOnBoardPosition();

    void testDataInitialization();
    void testDataSave();

private:
    std::unique_ptr<BridgeCrossingPlayer> playerWithId;
};

void
BridgeCrossingPlayerTest::initTestCase()
{

}

void
BridgeCrossingPlayerTest::init()
{
    SingletonFactory<BridgeCrossingSettings>::setFactory(new BridgeCrossingSettings());

    playerWithId = std::unique_ptr<BridgeCrossingPlayer>(new BridgeCrossingPlayer(testIdentifier,
                                                                                  BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                                  BridgeCrossingTypes::PlayerType::SLOW));
}
void BridgeCrossingPlayerTest::cleanupTestCase()
{
    if(SingletonFactory<BridgeCrossingSettings>::isFactorySet())
        SingletonFactory<BridgeCrossingSettings>::deleteFactory();
}

void BridgeCrossingPlayerTest::testPlayerId()
{
    QCOMPARE(testIdentifier, playerWithId->getUniqueId());
}

void BridgeCrossingPlayerTest::testPerformAction()
{
    QSignalSpy crossSpy(playerWithId.get(), SIGNAL(actionPerformedSignal(BridgeCrossingTypes::PlayerActionSet)));
    QVERIFY(crossSpy.isValid());

    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::CROSS);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::RETURN);

    QCOMPARE(crossSpy.count(), 4);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::CROSS);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);
    QCOMPARE(qvariant_cast<BridgeCrossingTypes::PlayerActionSet>(crossSpy.takeFirst().at(0))
             , BridgeCrossingTypes::PlayerActionSet::RETURN);
}

void BridgeCrossingPlayerTest::testPerformInvalidAction()
{
    QSignalSpy crossSpy(playerWithId.get(), SIGNAL(actionPerformedSignal(BridgeCrossingTypes::PlayerActionSet)));
    QVERIFY(crossSpy.isValid());

    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::CROSS);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::RETURN);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE); // valid transition

    QCOMPARE(crossSpy.count(), 1);
}

void BridgeCrossingPlayerTest::testPerformMoveToBridgeMultipletimes()
{
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);
    playerWithId->performAction(BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);

    BridgeCrossingTypes::PlayerState state = playerWithId->getPlayerState();
    QCOMPARE(state, BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
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
