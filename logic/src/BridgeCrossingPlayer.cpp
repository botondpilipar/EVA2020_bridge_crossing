#include <BridgeCrossingPlayer.h>
#include <UnimplementedException.h>

using namespace kd417d::eva::logic;

// IGameActor
 void
 BridgeCrossingPlayer::performAction(BridgeCrossingTypes::PlayerActionSet action)
 {
     return;
 }

// IMovableObject
 void
 BridgeCrossingPlayer::move(QPair<int, int>) {}
 QPair<int, int> BridgeCrossingPlayer::getPositionOnBoard() const
 {
     throw UnimplementedException("BridgeCrossingPlayer", "getPositionOnBoard");
 }

// IDataInitializable
 void
 BridgeCrossingPlayer::initialize(const PlayerData& representation)
 {
     return;
 }
 PlayerData*
 BridgeCrossingPlayer::save() const
 {
     return nullptr;
 }

// ISettingsChangedObserver

 void BridgeCrossingPlayer::settingsChanged() {}
