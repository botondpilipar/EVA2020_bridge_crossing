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

void BridgeCrossingBoard::initialize(const BoardData&) {}
BoardData* BridgeCrossingBoard::save() const { return nullptr; }
