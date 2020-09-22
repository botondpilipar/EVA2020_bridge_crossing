#include <BridgeCrossingPlayer.h>
#include <UnimplementedException.h>

using namespace kd417d::eva::logic;

// IGameActor
 void BridgeCrossingPlayer::performAction(PlayerActionSet action)
 {
     return;
 }
 int BridgeCrossingPlayer::getUniqueId() { return 1; }

// IMovableObject
 void BridgeCrossingPlayer::move(QPair<int, int>) {}
 QPair<int, int> BridgeCrossingPlayer::getPositionOnBoard()
 {
     throw UnimplementedException("BridgeCrossingPlayer", "getPositionOnBoard");
 }

// IDataInitializable
 void BridgeCrossingPlayer::initialize(const PlayerData& representation)
 {
     return;
 }
 PlayerData* BridgeCrossingPlayer::save()
 {
     return nullptr;
 }

// ISettingsChangedObserver

 void BridgeCrossingPlayer::settingsChanged() {}
