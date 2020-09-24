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

Dimension2D
BridgeCrossingBoard::getDimensions() const {}

void
BridgeCrossingBoard::setDimensions(Dimension2D&) {}

BridgeCrossingTypes::GameState BridgeCrossingBoard::getGameState() const {}
ScoredPoint BridgeCrossingBoard::getTimeEllapsed() const {}

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
