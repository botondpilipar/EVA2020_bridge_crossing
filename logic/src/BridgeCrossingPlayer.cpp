#include <BridgeCrossingPlayer.h>
#include <UnimplementedException.h>

using namespace kd417d::eva::logic;

PlayerState BridgeCrossingPlayer::getPlayerState(){}

// IGameActor
 void BridgeCrossingPlayer::performAction(PlayerActionSet action) {}
 int BridgeCrossingPlayer::getUniqueId() {}

// IMovableObject
 void BridgeCrossingPlayer::move(QPair<int, int> newPosition) {}
 QPair<int, int> BridgeCrossingPlayer::getPositionOnBoard() {}

// IDataInitializable
 void BridgeCrossingPlayer::initialize(const PlayerData& representation) {}
 PlayerData* BridgeCrossingPlayer::save() {}

// ISettingsChangedObserver

 void BridgeCrossingPlayer::settingsChanged() {}
