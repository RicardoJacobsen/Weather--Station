#include "SolarRadiation.h"

SolarRadiation::SolarRadiation()
{
    SolarR = 0;

}

SolarRadiation::SolarRadiation(float solar)
{
    SolarR=solar;
}

void SolarRadiation::SetSolarRadi(float solar)
{
    SolarR = solar;
}

float SolarRadiation::GetSolarRadi() const
{
    return SolarR;
}
