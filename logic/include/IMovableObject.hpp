#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <common_pch.h>
#include <IDataInitializable.hpp>
#include <ISerializable.h>
#include "ISettingsChangedObserver.h"

namespace kd417d
{
namespace eva
{
namespace logic
{

using namespace kd417d::eva::access;

template<class DataReprType,
         std::enable_if<
             std::is_base_of<ISerializable, DataReprType>::value>>
class IMovableObject : public IDataInitializable<DataReprType>,
                       public ISettingsChangedObserver
{
public:
    virtual ~IMovableObject() = default;
    IMovableObject() = default;

    virtual void move(QPair<int, int> newPosition) = 0;
    virtual QPair<int, int> getPositionOnBoard() = 0;
    virtual long getObjectId() = 0;

};

}
}
}
#endif // IGAMEOBJECT_H
