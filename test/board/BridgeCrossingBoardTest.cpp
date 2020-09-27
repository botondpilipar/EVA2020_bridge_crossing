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

    void testSave();

    void testMoveValidPlayer();
    void testMoveInvalidPlayer();

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

    mNewGameSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(boardChangedSignal(PlayerIdMap)));

    mGameOverSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(boardChangedSignal(PlayerIdMap)));

    mScoredPointChangedSignalSpy = std::make_unique<QSignalSpy>(mBoard.get(), SIGNAL(boardChangedSignal(PlayerIdMap)));
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

}

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

QTEST_APPLESS_MAIN(BridgeCrossingBoardTest);

#include "BridgeCrossingBoardTest.moc"
