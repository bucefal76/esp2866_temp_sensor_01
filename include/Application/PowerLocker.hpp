#ifndef POWER_LOCKER_HPP
#define POWER_LOCKER_HPP

/// @brief Class locks the CPU in deep sleep in case when battery has to low voltage.
///        This shall protect battery being damaged.
class PowerLocker
{
public:
    PowerLocker();
};

#endif