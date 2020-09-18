#ifndef ISETTINGSCHANGEDOBSERVER_H
#define ISETTINGSCHANGEDOBSERVER_H

namespace kd417d
{
namespace eva
{
namespace logic
{

class ISettingsChangedObserver
{
public:
    virtual void settingsChanged() = 0;
};

}
}
}
#endif // ISETTINGSCHANGEDOBSERVER_H
