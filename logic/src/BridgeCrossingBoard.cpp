#include <BridgeCrossingBoard.h>

using namespace kd417d::eva::logic;


void
BridgeCrossingBoard::cross()
{
    return;
}

void
BridgeCrossingBoard::movePlayer(int uniquePlayerId)
{
    return;
}

BridgeCrossingTypes::GameState
BridgeCrossingBoard::getGameState()
{
    return BridgeCrossingTypes::GameState::CROSS_SELECTION;
}

void
BridgeCrossingBoard::addPlayer(const BridgeCrossingPlayer& player){}
bool
BridgeCrossingBoard::removePlayer(int uniquePlayerId){}


Dimension2D
BridgeCrossingBoard::getDimensions() {}
void
BridgeCrossingBoard::setDimensions(Dimension2D&) {}

void
BridgeCrossingBoard::startNewGame() {}
void
BridgeCrossingBoard::pauseGame() {}
void
BridgeCrossingBoard::continueGame() {}

void
BridgeCrossingBoard::settingsChanged() {}

void
BridgeCrossingBoard::onPlayerActionPerformed(BridgeCrossingTypes::PlayerActionSet action)
{
    return;
}
