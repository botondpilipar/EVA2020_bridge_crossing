#ifndef CACHEDRANDOMDEVICE_HPP
#define CACHEDRANDOMDEVICE_HPP

#include <common_pch.h>

namespace kd417d
{
namespace eva
{
class CachedRandomDevice
{
public:
    CachedRandomDevice() :
        device(),
        generator(device()),
        dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()),
        used()
    {}

    virtual ~CachedRandomDevice() = default;
    virtual int random();

private:
    std::random_device device;
    std::mt19937 generator;
    std::uniform_int_distribution<int> dist;
    std::unordered_set<int> used;
};

}
}
#endif // CACHEDRANDOMDEVICE_HPP
