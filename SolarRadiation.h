#ifndef SOLARRADIATION_H
#define SOLARRADIATION_H

#include <iostream>
#include <string.h>

using namespace std;

/**
 * @class Solar Radiation
 * @brief Set and Get the Solar Radiation
 *
 * Consists of Solar Radiation
 *
 *
 * @author Ricardo Jacobsen
 * @version 01
 * @date 14/04/2021 Ricardo Jacobsen, Started
 *
 *
 *
 */

class SolarRadiation
{
public:
    /**
     * @brief Constructs the Solar Radiation
     *
     */
    SolarRadiation();

    /**
     * @brief Constructs Solar Radiation
     * @param Solar Radiation
     */
    SolarRadiation(float solar);
    /**
     * @brief Set the AmbAirTemp
     * @param  AmbAirTemp
     * @return void
     */
    void SetSolarRadi(float solar);

    /**
     * @brief Get (return) the Solar Radiation
     * Nothing should be modified when this function is called as it is const
     * @return string
     */
    float GetSolarRadi() const;


private:
    float SolarR; //Solar Radiation



} ;


#endif
