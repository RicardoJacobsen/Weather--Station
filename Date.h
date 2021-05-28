#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string.h>

using namespace std;

/**
 * @class Date
 * @brief Set and Get the date (Day, Month and Year) of when the mark was assigned to the unit
 *
 * Consists of Day, Month and Year
 *
 *
 * @author Ricardo Jacobsen
 * @version 01
 * @date 22/03/2021 Ricardo Jacobsen, Started
 *
 *
 *
 */

class Date
{
public:
    /**
     * @brief Constructs the date from day, month and year
     *
     */
    Date();
    Date(unsigned d, unsigned mon, unsigned y);

    /**
     * @brief Set the day
     * @param d
     * @return void
     */
    void SetDay(unsigned d);

    /**
     * @brief Get (return) the day
     * Nothing should be modified when this function is called as it is const
     * @return unsigned
     */
    unsigned GetDay() const;

    /**
     * @brief Set the month
     * @param mon
     * @return void
     */
    void SetMonth(unsigned mon);

    /**
    * @brief Get (return) the month
    * Nothing should be modified when this function is called as it is const
    * @return string
    */
    unsigned GetMonth() const;

    /**
     * @brief Set the year
     * @param y
     * @return void
     */
    void SetYear(unsigned y);

    /**
    * @brief Get (return) the year
    * Nothing should be modified when this function is called as it is const
    * @return unsigned
    */
    unsigned GetYear() const;

    string ConvertMonthToString(const int num);
private:
    unsigned day; //Day
    unsigned month; //Month
    unsigned year; //Year
};

#endif
