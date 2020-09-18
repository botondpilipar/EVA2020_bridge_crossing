#ifndef SINGLETONFACTORY_HPP
#define SINGLETONFACTORY_HPP

#include <assert.h>
namespace kd417d
{
namespace eva
{

template<typename T>
class SingletonFactory
{
public:
    static void setFactory(T* instance)
    {
        mSingletonInstance = instance;
    }
    static void deleteFactory() { delete mSingletonInstance; }
    static bool isFactorySet() { return mSingletonInstance != nullptr; }
    static T* instance()
    {
        assert(mSingletonInstance != nullptr);
        return mSingletonInstance;
    }
private:
    static T* mSingletonInstance;
};

}
}
#endif // SINGLETONFACTORY_HPP
