#ifndef IDATAINITIALIZABLE_HPP
#define IDATAINITIALIZABLE_HPP

#endif // IDATAINITIALIZABLE_HPP
namespace kd417d
{
namespace eva
{
namespace access
{
template<class DataReprType>
class IDataInitializable
{
    virtual ~IDataInitializable() = default;
    IDataInitializable() = default;

    void initialize(const DataReprType& representation) = 0;
    DataReprType* save() = 0;
};

}
}
}
