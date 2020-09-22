#ifndef BRIDGECROSSINGSETTINGS_H
#define BRIDGECROSSINGSETTINGS_H

#include <common_pch.h>

namespace kd417d
{
namespace eva
{
namespace logic
{

class BridgeCrossingSettingDefaults
{
public:
    static constexpr unsigned int slowPlayerNumber = 3;
    static constexpr unsigned int mediumPlayerNumber = 2;
    static constexpr unsigned int fastPlayerNumber = 1;
    static constexpr unsigned int slowPlayerCrossSpeed = 12;
    static constexpr unsigned int mediumPlayerCrossSpeed = 8;
    static constexpr unsigned int fastPlayerCrossSpeed = 4;


};

class BridgeCrossingSettings : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(unsigned int mSlowPlayerNumber
               READ getSlowPlayerNumber
               WRITE setSlowPlayerNumber
               RESET resetSlowPlayerNumber
               NOTIFY notifySlowPlayerNumberChanged)
    Q_PROPERTY(unsigned int mMediumPlayerNumber
               READ getMediumPlayerNumber
               WRITE setMediumPlayerNumber
               RESET resetMediumPlayerNumber
               NOTIFY notifyMediumPlayerNumberChanged)
    Q_PROPERTY(unsigned int mFastPlayerNumber
               READ getFastPlayerNumber
               WRITE setFastPlayerNumber
               RESET resetFastPlayerNumber
               NOTIFY notifyFastPlayerNumberChanged)
    Q_PROPERTY(unsigned int mSlowPlayerCrossTime
               READ getSlowPlayerCrossTime
               WRITE setSlowPlayerCrossTime
               RESET resetSlowPlayerCrossTime
               NOTIFY notifySlowPlayerCrossTimePropertyChanged)
    Q_PROPERTY(unsigned int mMediumPlayerCrossTime
               READ getMediumPlayerCrossTime
               WRITE setMediumPlayerCrossTime
               RESET resetMediumPlayerCrossTime
               NOTIFY notifyMediumPlayerCrossTimePropertyChanged)
    Q_PROPERTY(unsigned int mFastPlayerCrossTime
               READ getFastPlayerCrossTime
               WRITE setFastPlayerCrossTime
               RESET resetFastPlayerCrossTime
               NOTIFY notifyFastPlayerCrossTimePropertyChanged)
signals:
    void notifySlowPlayerNumberChanged();
    void notifyMediumPlayerNumberChanged();
    void notifyFastPlayerNumberChanged();
    void notifySlowPlayerCrossTimePropertyChanged();
    void notifyMediumPlayerCrossTimePropertyChanged();
    void notifyFastPlayerCrossTimePropertyChanged();

public:

    constexpr inline unsigned int allPlayers() noexcept { return mSlowPlayerNumber
                                                      + mMediumPlayerNumber
                                                      + mFastPlayerNumber; }

    unsigned int getSlowPlayerNumber() { return mSlowPlayerCrossTime; }
    void setSlowPlayerNumber(unsigned int newPlayerNumber)
    {
        mSlowPlayerNumber = newPlayerNumber;
        emit notifySlowPlayerNumberChanged();
    }
    void resetSlowPlayerNumber()
    {
        mSlowPlayerNumber = BridgeCrossingSettingDefaults::slowPlayerNumber;
        emit notifySlowPlayerNumberChanged();
    }
    unsigned int getSlowPlayerCrossTime() { return mSlowPlayerCrossTime; }
    void setSlowPlayerCrossTime(unsigned int newCrossTime)
    {
        mSlowPlayerCrossTime = newCrossTime;
        emit notifySlowPlayerCrossTimePropertyChanged();
    }
    void resetSlowPlayerCrossTime()
    {
        mSlowPlayerCrossTime = BridgeCrossingSettingDefaults::slowPlayerCrossSpeed;
        emit notifySlowPlayerCrossTimePropertyChanged();
    }

    unsigned int getMediumPlayerNumber() { return mMediumPlayerCrossTime; }
    void setMediumPlayerNumber(unsigned int newPlayerNumber)
    {
        mMediumPlayerNumber = newPlayerNumber;
        emit notifyMediumPlayerNumberChanged();
    }
    void resetMediumPlayerNumber()
    {
        mMediumPlayerNumber = BridgeCrossingSettingDefaults::mediumPlayerNumber;
        emit notifyMediumPlayerNumberChanged();
    }
    unsigned int getMediumPlayerCrossTime() { return mMediumPlayerCrossTime; }
    void setMediumPlayerCrossTime(unsigned int newCrossTime)
    {
        mMediumPlayerCrossTime = newCrossTime;
        emit notifyMediumPlayerCrossTimePropertyChanged();
    }
    void resetMediumPlayerCrossTime()
    {
        mMediumPlayerCrossTime = BridgeCrossingSettingDefaults::mediumPlayerCrossSpeed;
        emit notifyMediumPlayerCrossTimePropertyChanged();
    }

    unsigned int getFastPlayerNumber() { return mFastPlayerCrossTime; }
    void setFastPlayerNumber(unsigned int newPlayerNumber)
    {
        mFastPlayerNumber = newPlayerNumber;
        emit notifyFastPlayerNumberChanged();
    }
    void resetFastPlayerNumber()
    {
        mFastPlayerNumber = BridgeCrossingSettingDefaults::fastPlayerNumber;
        emit notifyFastPlayerNumberChanged();
    }
    unsigned int getFastPlayerCrossTime() { return mFastPlayerCrossTime; }
    void setFastPlayerCrossTime(unsigned int newCrossTime)
    {
        mFastPlayerCrossTime = newCrossTime;
        emit notifyFastPlayerCrossTimePropertyChanged();
    }
    void resetFastPlayerCrossTime()
    {
        mFastPlayerCrossTime = BridgeCrossingSettingDefaults::fastPlayerCrossSpeed;
        emit notifyFastPlayerCrossTimePropertyChanged();
    }
private:
    unsigned int mSlowPlayerNumber;
    unsigned int mMediumPlayerNumber;
    unsigned int mFastPlayerNumber;
    unsigned int mSlowPlayerCrossTime;
    unsigned int mMediumPlayerCrossTime;
    unsigned int mFastPlayerCrossTime;
};

}
}
}
#endif // BRIDGECROSSINGSETTINGS_H
