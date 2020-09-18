#ifndef IGAMEACTOR_HPP
#define IGAMEACTOR_HPP

#include "IMovableObject.hpp"

namespace kd417d
{
namespace eva
{
namespace logic
{

template<class DataReprType, class ActionSet>
class IGameActor : public IMovableObject<DataReprType, true>
{
public:
    virtual ~IGameActor() override = default;
    IGameActor() = default;

    virtual void performAction(ActionSet action) = 0;
};

}
}
}
#endif // IGAMEACTOR_HPP
