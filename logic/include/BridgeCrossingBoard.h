#ifndef BRIDGECROSSINGBOARD_H
#define BRIDGECROSSINGBOARD_H

#include "IGameBoard.h"
#include "BridgeCrossingBoardData.h"

namespace kd417d
{
namespace eva
{
namespace logic
{
using namespace bridge;

class BridgeCrossingBoard : public IGameBoard<BoardData>
{


    virtual Dimension2D getDimensions() override;
    virtual void setDimensions(Dimension2D&) override;
    virtual void startNewGame() override;
    virtual void pauseGame() override;
    virtual void continueGame() override;
    virtual void settingsChanged() override;
};

}
}
}
#endif // BRIDGECROSSINGBOARD_H
