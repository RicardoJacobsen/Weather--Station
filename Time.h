#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string.h>

using namespace std;

/**
 * @class Date
 * @brief Set and Get the date (hours, Month and minutes) of when the mark was assigned to the unit
 *
 * Consists of hours, Month and minutes
 *
 *
 * @author Ricardo Jacobsen
 * @version 02
 * @date 04/07/2021 Ricardo Jacobsen, Started
 *
 *
 *
 */

class Time
{
public:
    /**
     * @brief Constructs the time from hour and minute
     *
     */
    Time();

    /**
     * @brief Constructs the date from day, month and year
     * @param hour, minute
     */
    Time(unsigned hour, unsigned minute);

    /**
     * @brief Set the hour
     * @param h
     * @return void
     */
    void SetHour(unsigned h);

    /**
     * @brief Get (return) the hour
     * Nothing should be modified as it is const
     * @return unsigned
     */
    unsigned GetHour() const;

    /**
     * @brief Set the minute
     * @param m
     * @return void
     */
    void SetMinute(unsigned m);

    /**
     * @brief Get (return) the minute
     * Nothing should be modified as it is const
     * @return unsigned
     */
    unsigned GetMinute() const;

private:
    unsigned hour; //hour
    unsigned minute; //minute


} ;


#endif
