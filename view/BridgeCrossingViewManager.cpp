#include <SingletonFactory.hpp>
#include <QSizePolicy>
#include <QMessageBox>

#include "BridgeCrossingViewManager.h"
#include "ui_bridgecrossingviewmanager.h"

const char * const buttonIdPropertyName = "uniqueIdentifier";

using namespace kd417d::eva;

BridgeCrossingViewManager::BridgeCrossingViewManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BridgeCrossingViewManager)
    , mSettingsDialog(this)
    , mIsInitialState(true)
{
    ui->setupUi(this);

    // connect
    QObject::connect(&mBoard, &BridgeCrossingBoard::newGameSignal, this, &BridgeCrossingViewManager::onNewGameStarted);
    QObject::connect(&mBoard, &BridgeCrossingBoard::boardChangedSignal, this, &BridgeCrossingViewManager::onGameBoardChanged);
    QObject::connect(ui->crossButton, &QPushButton::clicked, this, &BridgeCrossingViewManager::onCrossButtonPushed);
    QObject::connect(&mBoard, &BridgeCrossingBoard::scoredPointChangedSignal,
                     this, &BridgeCrossingViewManager::onScoredPointChanged);
    QObject::connect(&mBoard, &BridgeCrossingBoard::gameOverSignal,
                     this, &BridgeCrossingViewManager::onGameOver);

    QPixmap background(":/image/media/bridge.png");
    background = background.scaled(ui->playerAreaWidget->size(), Qt::IgnoreAspectRatio);
    QPalette p;
    p.setBrush(QPalette::Window, background);
    ui->playerAreaWidget->setAutoFillBackground(true);
    ui->playerAreaWidget->setPalette(p);

    QState* playing = new QState();
    QState* paused = new QState();
    QState* settings = new QState();

    playing->addTransition(ui->pauseContinueButton, &QPushButton::clicked, paused);
    playing->addTransition(ui->settingsButton, &QPushButton::clicked, settings);
    playing->addTransition(ui->newGameButton, &QPushButton::clicked, settings);
    paused->addTransition(ui->pauseContinueButton, &QPushButton::clicked, playing);
    paused->addTransition(ui->settingsButton, &QPushButton::clicked, settings);
    paused->addTransition(ui->newGameButton, &QPushButton::clicked, settings);
    settings->addTransition(&mSettingsDialog, &QDialog::finished, playing);

    QObject::connect(playing, &QState::entered, this,
                     &BridgeCrossingViewManager::onPlayingStateEntered);
    QObject::connect(paused, &QState::entered, this,
                     &BridgeCrossingViewManager::onPausedStateEntered);
    QObject::connect(settings, &QState::entered, this,
                     &BridgeCrossingViewManager::onSettingsStateEntered);

    mGameState.addState(playing);
    mGameState.addState(paused);
    mGameState.addState(settings);
    mGameState.setInitialState(playing);
    mGameState.start();

    qRegisterMetaType<Identifier>();

    mBoard.startNewGame();
}

BridgeCrossingViewManager::~BridgeCrossingViewManager()
{
    SingletonFactory<BridgeCrossingSettings>::deleteFactory();
    SingletonFactory<CachedRandomDevice>::deleteFactory();

    delete ui;
}

void
BridgeCrossingViewManager::onGameBoardChanged(PlayerIdMap change)
{
    mLastGameState = change;

    if(mIsInitialState)
    {
        initialBoardSetup(change);
    }
    else
    {
        std::for_each(change.keyValueBegin(), change.keyValueEnd(),
                      [this](const auto& kwp) {
            auto [playerId, playerDataPtr] = kwp;
            std::shared_ptr<QPushButton> player = *mIdentifiedPlayers.find(playerId);
            QLayout* oldContainingLayout = *mPlayerPositions.find(player);
            oldContainingLayout->removeWidget(player.get());
            QLayout* newContainingLayout = nullptr;

            switch(playerDataPtr->state)
            {
                case BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE:
                {
                    newContainingLayout = ui->crossSideLayout;
                    break;
                }
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS:
                {
                    newContainingLayout = ui->bridgeCrossLayout;
                    break;
                }
                case BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE:
                {
                    newContainingLayout = ui->returnSideLayout;
                    break;
                }
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN:
                {
                    newContainingLayout = ui->bridgeReturnLayout;
                    break;
                }
            }
            newContainingLayout->addWidget(player.get());
        });
    }
}

void
BridgeCrossingViewManager::onNewGameStarted()
{
    mIsInitialState = true;
    if(mIdentifiedPlayers.size() != 0)
    {
        mIdentifiedPlayers.clear();
    }
    if(mPlayerPositions.size() != 0)
    {
        mPlayerPositions.clear();
    }
    ui->pointCounter->display("0");
}

void BridgeCrossingViewManager::initialBoardSetup(PlayerIdMap& change)
{
    mIsInitialState = false;

    std::for_each(mLastGameState.keyValueBegin(), mLastGameState.keyValueEnd(),
                  [this](const auto& kwp) {
        auto [playerId, playerDataPtr] = kwp;
        std::shared_ptr<QPushButton> button = std::shared_ptr<QPushButton>(new QPushButton(ui->playerAreaWidget));
        std::shared_ptr<QPushButton> button2 = button;
        std::shared_ptr<QPushButton> button3 = button;

        button->setVisible(true);
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        button->setText(QString::number(playerDataPtr->speed));
        button->setProperty(buttonIdPropertyName, playerDataPtr->id);
        ui->crossSideLayout->addWidget(button2.get());

        QObject::connect(button.get(), &QPushButton::clicked, this, &BridgeCrossingViewManager::onPlayerStep);

        mIdentifiedPlayers.insert(playerId, std::move(button));
        mPlayerPositions.insert(std::move(button2), ui->crossSideLayout);});
}

void BridgeCrossingViewManager::onPlayerStep()
{
    QPushButton* sender = qobject_cast<QPushButton*>(QObject::sender());

    Identifier id = qvariant_cast<Identifier>(sender->property(buttonIdPropertyName));

    mBoard.movePlayer(id);
}

void BridgeCrossingViewManager::onCrossButtonPushed()
{
    mBoard.cross();
}

void BridgeCrossingViewManager::onScoredPointChanged(ScoredPoint point)
{
    ui->pointCounter->display(QString::number(point));
}

void BridgeCrossingViewManager::onGameOver(ScoredPoint finalScore)
{
    QMessageBox box(QMessageBox::Information, "Játék vége",
                    "Játék befejeződött " + QString::number(finalScore) + " ponttal.",
                    QMessageBox::Ok);
    box.exec();
}

void BridgeCrossingViewManager::onPlayingStateEntered()
{
    mBoard.continueGame();
    ui->pauseContinueButton->setText("Megállít");
}

void BridgeCrossingViewManager::onPausedStateEntered()
{
    mBoard.pauseGame();
    ui->pauseContinueButton->setText("Folytat");

}
void BridgeCrossingViewManager::onSettingsStateEntered()
{
    BridgeCrossingSettings* settings = SingletonFactory<BridgeCrossingSettings>::ptrInstance();

    mSettingsDialog.setSlowPlayerSpinBox(settings->getSlowPlayerNumber());
    mSettingsDialog.setMediumPlayerSpinBox(settings->getMediumPlayerNumber());
    mSettingsDialog.setFastPlayerSpinBox(settings->getFastPlayerNumber());

    mSettingsDialog.exec();

    settings->setSlowPlayerNumber(mSettingsDialog.getSelectedSlowPlayerNumber());
    settings->setMediumPlayerNumber(mSettingsDialog.getSelectedMediumPlayerNumber());
    settings->setFastPlayerNumber(mSettingsDialog.getSelectedFastPlayerNumber());

    mBoard.settingsChanged();
}
