#ifndef AMBAIRTEMP_H
#define AMBAIRTEMP_H

#include <iostream>
#include <string.h>

using namespace std;

/**
 * @class Ambient Air Temperature
 * @brief Set and Get the Ambient Air Temperature
 *
 * Consists of Ambient Air Temperature
 *
 *
 * @author Ricardo Jacobsen
 * @version 01
 * @date 12/04/2021 Ricardo Jacobsen, Started
 *
 *
 *
 */

class AmbAirTemp
{
public:
    /**
     * @brief Constructs the Ambient Air Temperature
     *
     */
    AmbAirTemp();

    /**
     * @brief Constructs the Ambient Air Temperature
     * @param hour, minute
     */
    AmbAirTemp(float amb);
    /**
     * @brief Set the AmbAirTemp
     * @param AmbAirTemp
     * @return void
     */
    void SetAmbAirTemp(float amb);

    /**
     * @brief Get (return) the AmbAirTemp
     * Nothing should be modified when this function is called as it is const
     * @return string
     */
    float GetAmbAirTemp() const;


private:
    float Amb; //Ambient Air Temperature



} ;


#endif
