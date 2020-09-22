#ifndef DESERIALIZATIONFAILEDEXCEPTION_H
#define DESERIALIZATIONFAILEDEXCEPTION_H

#include <QException>
#include <string.h>

namespace kd417d
{
namespace eva
{
namespace access
{

class DeserializationFailedException : public std::exception
{
public:
    virtual ~DeserializationFailedException() override = default;
    DeserializationFailedException(std::string objectName) :
        objectFailed(objectName) {}

    virtual const char* what() const noexcept override
    {
        char* buffer = new char[100];
        snprintf(buffer, sizeof(buffer),
                 "Failed to initialize %s, fallback to default value",
                 objectFailed.c_str());
        return buffer;
    }

private:
    std::string objectFailed;
};

}
}
}
#endif // DESERIALIZATIONFAILEDEXCEPTION_H
