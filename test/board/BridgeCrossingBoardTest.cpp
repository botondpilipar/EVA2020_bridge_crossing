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
        qRegisterMetaType<kd417d::eva::logic::bridge::PlayerData>();
        qRegisterMetaType<kd417d::eva::logic::bridge::PlayerData>();
    }

    virtual ~BridgeCrossingBoardTest() override = default;

    QVector<std::shared_ptr<PlayerData>>* getSamplePlayerData() const;
private slots:


    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testNewGameSignalsEmittedOnNewGameStarted();
    void testPlayerNumberOnNewGameStarted();
    void testPlayerCrossTimeOnNewGameStarted();
    void testPlayerStateOnNewGameStarted();

    void testPauseGame();
    void testContinueGame();

    void testInitialization();
    void testSave();

    void testMoveValidPlayer();
    void testMoveInvalidPlayer();

    void testThrowOnGetSetDimension();
private:
    std::unique_ptr<BridgeCrossingBoard> mBoard;
    std::unique_ptr<QSignalSpy> mBoardChangedSignalSpy;
    std::unique_ptr<QSignalSpy> mNewGameSignalSpy;
    std::unique_ptr<QSignalSpy> mPlayerMovedSignalSpy;
    std::unique_ptr<QSignalSpy> mGameOverSignalSpy;
    std::unique_ptr<QSignalSpy> mScoredPointChangedSignalSpy;

    BridgeCrossingSettings* mSettings;
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
BridgeCrossingBoardTest::initTestCase()
{
    qRegisterMetaType<PlayerIdMap>();
    qRegisterMetaType<PlayerData>();
}

void
BridgeCrossingBoardTest::init()
{
    BridgeCrossingSettings* settings = new BridgeCrossingSettings();
    SingletonFactory<BridgeCrossingSettings>::setFactory(settings);
    mSettings = SingletonFactory<BridgeCrossingSettings>::ptrInstance();


    CachedRandomDevice* randomDevice = new CachedRandomDevice();
    SingletonFactory<CachedRandomDevice>::setFactory(randomDevice);

    mBoard = std::unique_ptr<BridgeCrossingBoard>(new BridgeCrossingBoard());
    mBoardChangedSignalSpy = std::unique_ptr<QSignalSpy>(
                new QSignalSpy(mBoard.get(),
                SIGNAL(boardChangedSignal(PlayerIdMap))));

    mNewGameSignalSpy = std::unique_ptr<QSignalSpy>(
                new QSignalSpy(mBoard.get(),
                               SIGNAL(newGameSignal())));

    mPlayerMovedSignalSpy = std::unique_ptr<QSignalSpy>(
                new QSignalSpy(mBoard.get(),
                SIGNAL(playerMovedSignal(PlayerData))));

    mGameOverSignalSpy = std::unique_ptr<QSignalSpy>(
                new QSignalSpy(mBoard.get(),
                SIGNAL(gameOverSignal(ScoredPoint))));

    mScoredPointChangedSignalSpy = std::unique_ptr<QSignalSpy>(
                new QSignalSpy(mBoard.get(),
                SIGNAL(scoredPointChangedSignal(ScoredPoint))));


}

void
BridgeCrossingBoardTest::cleanup()
{
    if(SingletonFactory<BridgeCrossingSettings>::isFactorySet())
    {
        SingletonFactory<BridgeCrossingSettings>::deleteFactory();
    }
    if(SingletonFactory<CachedRandomDevice>::isFactorySet())
    {
        SingletonFactory<CachedRandomDevice>::deleteFactory();
    }
}

void
BridgeCrossingBoardTest::cleanupTestCase()
{
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
    auto slowPlayerList = QtConcurrent::filtered(values,
                                              [](auto data){ return data->type ==
                                                BridgeCrossingTypes::PlayerType::SLOW; });
    auto mediumPlayerList = QtConcurrent::filtered(values,
                                                [](auto data){ return data->type ==
                                                  BridgeCrossingTypes::PlayerType::MEDIUM; });
    auto fastPlayerList = QtConcurrent::filtered(values,
                                              [](auto data){ return data->type ==
                                                BridgeCrossingTypes::PlayerType::FAST;});

    int slowPlayers = slowPlayerList.results().size();
    int mediumPlayers = mediumPlayerList.results().size();
    int fastPlayers = fastPlayerList.results().size();

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

    QCOMPARE((*aSlowPlayer)->id, mSettings->getSlowPlayerCrossTime());
    QCOMPARE((*aMediumPlayer)->speed, mSettings->getMediumPlayerCrossTime());
    QCOMPARE((*aFastPlayer)->speed, mSettings->getFastPlayerCrossTime());
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
        savedValues.push_back(*data);
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

    QCOMPARE(mPlayerMovedSignalSpy->count(), 1);
    PlayerData playerMoved = qvariant_cast<PlayerData>(mPlayerMovedSignalSpy->takeFirst().at(0));
    QCOMPARE(playerMoved.id, boardChangeKeys.front());
}

void BridgeCrossingBoardTest::testMoveInvalidPlayer()
{
    mBoard->startNewGame();
    mBoard->movePlayer(SingletonFactory<CachedRandomDevice>::instance().random());

    QVERIFY(mPlayerMovedSignalSpy->empty());
}

void BridgeCrossingBoardTest::testThrowOnGetSetDimension()
{
    Dimension2D newDim(2, 3);
    QVERIFY_EXCEPTION_THROWN(mBoard->setDimensions(newDim), UnimplementedException);
    QVERIFY_EXCEPTION_THROWN(mBoard->getDimensions(), UnimplementedException);
}

void BridgeCrossingBoardTest::testPauseGame()
{
    mBoard->newGameSignal();
    mBoard->pauseGame();

    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    mBoard->movePlayer(boardChangeKeys.front());

    QVERIFY(mPlayerMovedSignalSpy->empty());
}

void BridgeCrossingBoardTest::testContinueGame()
{
    mBoard->newGameSignal();
    mBoard->pauseGame();
    mBoard->continueGame();

    QList<Identifier> boardChangeKeys = qvariant_cast<PlayerIdMap>(mBoardChangedSignalSpy->takeFirst().at(0)).keys();
    mBoard->movePlayer(boardChangeKeys.front());

    QCOMPARE(mPlayerMovedSignalSpy->count(), 1);
}

QTEST_APPLESS_MAIN(BridgeCrossingBoardTest);

#include "BridgeCrossingBoardTest.moc"
