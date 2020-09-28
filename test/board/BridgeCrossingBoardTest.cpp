// Qt Library
#include <QSignalSpy>
#include <QtTest>
#include <algorithm>
#include <memory>

// common library
#include <SingletonFactory.hpp>
#include <CachedRandomDevice.h>
#include <UnimplementedException.h>

// logic library
#include <BridgeCrossingBoard.h>
#include <BridgeCrossingTypes.h>
#include <BridgeCrossingPlayer.h>
#include <BridgeCrossingSettings.h>

#include <TestUtility.h>

using namespace kd417d::eva;
using namespace kd417d::eva::logic;
using namespace kd417d::eva::access;
using namespace kd417d::eva::logic::bridge;

class BridgeCrossingBoardTest : public QObject
{
    Q_OBJECT

public:
    BridgeCrossingBoardTest()
    {
        qRegisterMetaType<BridgeCrossingTypes::BoardActionSet>();
        qRegisterMetaType<BridgeCrossingTypes::GameState>();
        qRegisterMetaType<PlayerIdMap>();
        qRegisterMetaType<PlayerData>();
        qRegisterMetaType<ScoredPoint>();
    }

    virtual ~BridgeCrossingBoardTest() override = default;

    QVector<std::shared_ptr<PlayerData>>* getSamplePlayerData() const;
private slots:

    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testInitialization();

    void testPlayerNumberOnNewGameStarted();
    void testNewGameSignalsEmittedOnNewGameStarted();
    void testPlayerCrossTimeOnNewGameStarted();
    void testPlayerStateOnNewGameStarted();

    void testPauseGame();
    void testContinueGame();
    void testGameOver();

    void testSave();

    void testMoveValidPlayer();
    void testMoveInvalidPlayer();
    void testCross();
    void testReturn();
    void testBridgeBufferOverflow();

    void testThrowOnGetSetDimension();
private:
    std::unique_ptr<BridgeCrossingBoard> mBoard;
    std::unique_ptr<QSignalSpy> mBoardChangedSignalSpy;
    std::unique_ptr<QSignalSpy> mNewGameSignalSpy;
    std::unique_ptr<QSignalSpy> mGameOverSignalSpy;
    std::unique_ptr<QSignalSpy> mScoredPointChangedSignalSpy;

    BridgeCrossingSettings* mSettings;
    CachedRandomDevice* mRandomDevice;
};

QVector<std::shared_ptr<PlayerData>>*
BridgeCrossingBoardTest::getSamplePlayerData() const
{
    QVector<std::shared_ptr<PlayerData>>* data = new QVector<std::shared_ptr<PlayerData>>();

    for(int i = 0; i<5; ++i)
    {
        PlayerData* playerData = new PlayerData(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                        SingletonFactory<CachedRandomDevice>::instance().random(),
                        BridgeCrossingTypes::PlayerType::MEDIUM,
                        10);
        data->push_back(std::shared_ptr<PlayerData>(playerData));
    }
    return data;
}

void
BridgeCrossingBoardTest::initTestCase() {}

void
BridgeCrossingBoardTest::cleanupTestCase() {}

void
BridgeCrossingBoardTest::init()
{
    BridgeCrossingSettings* settings = new BridgeCrossingSettings();
    SingletonFactory<BridgeCrossingSettings>::setFactory(settings);
    mSettings = SingletonFactory<BridgeCrossingSettings>::ptrInstance();


    CachedRandomDevice* randomDevice = new CachedRandomDevice();
    SingletonFactory<CachedRandomDevice>::setFactory(randomDevice);
    mRandomDevice = randomDevice;

    mBoard = std::unique_ptr<BridgeCrossingBoard>(new BridgeCrossingBoard());

    mBoardChangedSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(boardChangedSignal(PlayerIdMap)));

    mNewGameSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(newGameSignal()));

    mGameOverSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(gameOverSignal(ScoredPoint)));

    mScoredPointChangedSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(scoredPointChangedSignal(ScoredPoint)));
}

void
BridgeCrossingBoardTest::cleanup()
{
    SingletonFactory<BridgeCrossingSettings>::deleteFactory();
    SingletonFactory<CachedRandomDevice>::deleteFactory();
}

void BridgeCrossingBoardTest::testNewGameSignalsEmittedOnNewGameStarted()
{
    mBoard->startNewGame();

    QCOMPARE(mNewGameSignalSpy->count(), 1);
    QCOMPARE(mBoardChangedSignalSpy->count(), 1);
}

void
BridgeCrossingBoardTest::testPlayerNumberOnNewGameStarted()
{
    mBoard->startNewGame();

    QCOMPARE(mBoardChangedSignalSpy->count(), 1);

    auto boardChange = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0));
    QList<std::shared_ptr<PlayerData>> values = boardChange.values();

    int slowPlayers =  std::count_if(values.begin(), values.end(),
                  [](auto playerPtr) { return playerPtr->type == BridgeCrossingTypes::PlayerType::SLOW; });

    int mediumPlayers = std::count_if(values.begin(), values.end(),
                                    [](auto playerPtr) { return playerPtr->type == BridgeCrossingTypes::PlayerType::MEDIUM; });
    int fastPlayers = std::count_if(values.begin(), values.end(),
                                      [](auto playerPtr) { return playerPtr->type == BridgeCrossingTypes::PlayerType::FAST; });

    QVERIFY(slowPlayers >= 1);
    QVERIFY(mediumPlayers >= 1);
    QVERIFY(fastPlayers >= 1);
    QCOMPARE(values.size(), mSettings->allPlayers());
    QCOMPARE(slowPlayers, mSettings->getSlowPlayerNumber());
    QCOMPARE(mediumPlayers, mSettings->getMediumPlayerNumber());
    QCOMPARE(fastPlayers, mSettings->getFastPlayerNumber());
}

void
BridgeCrossingBoardTest::testPlayerCrossTimeOnNewGameStarted()
{
    mBoard->startNewGame();

    QCOMPARE(mBoardChangedSignalSpy->count(), 1);

    auto boardChange = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0));
    QList<std::shared_ptr<PlayerData>> values = boardChange.values();

    auto aSlowPlayer = std::find_if(values.begin(),
                                           values.end(),
                                           [](auto player){ return player->type ==
                                            BridgeCrossingTypes::PlayerType::SLOW; });
    auto aMediumPlayer = std::find_if(values.begin(),
                                             values.end(),
                                             [](auto player){ return player->type ==
                                              BridgeCrossingTypes::PlayerType::MEDIUM; });
    auto aFastPlayer = std::find_if(values.begin(),
                                           values.end(),
                                           [](auto player){ return player->type ==
                                            BridgeCrossingTypes::PlayerType::FAST; });
    QVERIFY(aSlowPlayer != values.end());
    QVERIFY(aMediumPlayer != values.end());
    QVERIFY(aFastPlayer != values.end());

    PlayerData slowPlayer = **aSlowPlayer;
    PlayerData mediumPlayer = **aMediumPlayer;
    PlayerData fastPlayer = **aFastPlayer;

    QCOMPARE(slowPlayer.speed, mSettings->getSlowPlayerCrossTime());
    QCOMPARE(mediumPlayer.speed, mSettings->getMediumPlayerCrossTime());
    QCOMPARE(fastPlayer.speed, mSettings->getFastPlayerCrossTime());
}

void
BridgeCrossingBoardTest::testPlayerStateOnNewGameStarted()
{
    mBoard->startNewGame();
    QList<std::shared_ptr<PlayerData>> boardChangeValues = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).values();

    QVERIFY(std::all_of(boardChangeValues.begin(),
                        boardChangeValues.end(),
                        [](auto data) { return data->state == BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE; }));
}

void
BridgeCrossingBoardTest::testInitialization()
{    

    auto initializationData = std::unique_ptr<QVector<std::shared_ptr<PlayerData>>>(getSamplePlayerData());

    QVector<Identifier> initializationId(initializationData->size());
    std::transform(initializationData->begin(),
                   initializationData->end(),
                   initializationId.begin(),
                   [](auto data){return data->id;});

    BoardData boardData(*initializationData, 100, initializationData->size(),
                        BridgeCrossingTypes::GameState::CROSS_SELECTION);

    mBoard->initialize(boardData);
    QCOMPARE(mBoardChangedSignalSpy->count(), 1);
    QCOMPARE(mBoard->getTimeEllapsed(), 100);
    QCOMPARE(mBoard->getGameState(), BridgeCrossingTypes::GameState::CROSS_SELECTION);

    PlayerIdMap changed = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0));

    QVERIFY(std::all_of(changed.keyValueBegin(), changed.keyValueEnd(),
                        [](const auto& kwp){ return kwp.first ==
                                                    kwp.second->id; }));
    auto changedValues = changed.values();

    QList<PlayerData> initialPlayerData;
    QList<PlayerData> boardChangedPlayerData;
    std::transform(initializationData->begin(),
                   initializationData->end(),
                   std::back_inserter(initialPlayerData),
                   DereferenceFunctor<std::shared_ptr<PlayerData>>());

    std::transform(changedValues.begin(),
                   changedValues.end(),
                   std::back_inserter(boardChangedPlayerData),
                   DereferenceFunctor<std::shared_ptr<PlayerData>>());

    QVERIFY(std::is_permutation(initialPlayerData.begin(),
                                initialPlayerData.end(),
                                boardChangedPlayerData.begin()));}

void BridgeCrossingBoardTest::testSave()
{
    mBoard->startNewGame();
    QList<std::shared_ptr<PlayerData>> boardChangeValues = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).values();

    std::unique_ptr<BoardData> data(mBoard->save());

    QList<PlayerData> changedValues{};

    for(std::shared_ptr<PlayerData> data : boardChangeValues)
    {
        changedValues.push_back(*data);
    }


    QList<std::shared_ptr<PlayerData>> savedValuePtrs = data->playerData.toList();
    QList<PlayerData> savedValues{};
    for(std::shared_ptr<PlayerData> data : savedValuePtrs)
    {
        PlayerData currentData = *data;
        savedValues.push_back(currentData);
    }

    QCOMPARE(data->playerNumber, mSettings->allPlayers());
    QCOMPARE(data->state, BridgeCrossingTypes::GameState::CROSS_SELECTION);
    QCOMPARE(data->point, 0);

    QVERIFY(std::is_permutation(changedValues.begin(), changedValues.end(),
                                savedValues.begin()));
}

void BridgeCrossingBoardTest::testMoveValidPlayer()
{
    mBoard->startNewGame();
    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    mBoard->movePlayer(boardChangeKeys.front());

    QCOMPARE(mBoardChangedSignalSpy->count(), 1);
    PlayerIdMap playerMoved = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0));
    QCOMPARE(playerMoved.firstKey(), boardChangeKeys.front());
}

void BridgeCrossingBoardTest::testMoveInvalidPlayer()
{
    mBoard->startNewGame();
    Identifier newId = mRandomDevice->random();
    mBoard->movePlayer(newId);

    QCOMPARE(mBoardChangedSignalSpy->count(), 1);
}

void BridgeCrossingBoardTest::testThrowOnGetSetDimension()
{
    Dimension2D newDim(2, 3);
    QVERIFY_EXCEPTION_THROWN(mBoard->getDimensions(), UnimplementedException);
    QVERIFY_EXCEPTION_THROWN(mBoard->setDimensions(newDim), UnimplementedException);
}

void BridgeCrossingBoardTest::testPauseGame()
{
    mBoard->startNewGame();
    mBoard->pauseGame();

    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    mBoard->movePlayer(boardChangeKeys.front());

    QVERIFY(mBoardChangedSignalSpy->empty());
}

void BridgeCrossingBoardTest::testContinueGame()
{
    mBoard->startNewGame();
    mBoard->pauseGame();
    mBoard->continueGame();

    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    mBoard->movePlayer(boardChangeKeys.front());

    QCOMPARE(mBoardChangedSignalSpy->count(), 1);
}

void
BridgeCrossingBoardTest::testGameOver()
{
    const Identifier onePlayerId = 1;
    const unsigned int onePlayerCrossTime = 1;
    const unsigned int gameEllapsedTime = 133;
    const unsigned int gamePlayerNumber = 1;

    mBoard->startNewGame();

    BoardData data({ std::make_shared<PlayerData>(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                    onePlayerId,
                                                    BridgeCrossingTypes::PlayerType::FAST,
                                                    onePlayerCrossTime)
                   },
                  gameEllapsedTime,
                  gamePlayerNumber,
                  BridgeCrossingTypes::GameState::CROSS_SELECTION);

    mBoard->initialize(data);

    mBoard->movePlayer(onePlayerId);
    mBoard->cross();

    QCOMPARE(mGameOverSignalSpy->count(), 1);
    QCOMPARE(qvariant_cast<ScoredPoint>(mGameOverSignalSpy->takeFirst().at(0)),
             gameEllapsedTime + onePlayerCrossTime);
    QCOMPARE(mNewGameSignalSpy->count(), 2);
}

void
BridgeCrossingBoardTest::testCross()
{
    mBoard->startNewGame();

    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    std::for_each(boardChangeKeys.begin(), boardChangeKeys.begin() + 4,
                  [this](Identifier id) { mBoard->movePlayer(id); });
    mBoard->cross();

    // 3 move + 1 cross
    QCOMPARE(mBoardChangedSignalSpy->count(), 4);

    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(0).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS);
    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(1).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS);
    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(2).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS);

    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(3).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE);
    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(3).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE);
    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(3).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE);
}

void
BridgeCrossingBoardTest::testReturn()
{
    mBoard->startNewGame();

    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    QList<Identifier> movedPlayers{};
    std::for_each(boardChangeKeys.begin(), boardChangeKeys.begin() + 4,
                  [&](Identifier id) { mBoard->movePlayer(id); movedPlayers.push_back(id); });
    mBoard->cross();

    QCOMPARE(mBoard->getGameState(), BridgeCrossingTypes::GameState::RETURN_SELECTION);

    std::for_each(movedPlayers.begin(), movedPlayers.end(),
                  [this](Identifier id) { mBoard->movePlayer(id); });

    mBoard->cross();

    QCOMPARE(mBoard->getGameState(), BridgeCrossingTypes::GameState::CROSS_SELECTION);
    // 3 move + 1 cross + 3 move + 1 return
    QCOMPARE(mBoardChangedSignalSpy->count(), 8);

    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(4).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN);
    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(5).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN);
    QCOMPARE(qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(6).at(0)).first()->state,
             BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN);

    PlayerIdMap returnMap = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->at(7).at(0));

    QCOMPARE(returnMap.size(), BridgeCrossingSettingDefaults::playersCanCrossAtOneTime);

    for(const auto& playerData : returnMap)
    {
        QCOMPARE(playerData->state, BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
    }
}

void
BridgeCrossingBoardTest::testBridgeBufferOverflow()
{

}

QTEST_APPLESS_MAIN(BridgeCrossingBoardTest);

#include "BridgeCrossingBoardTest.moc"
