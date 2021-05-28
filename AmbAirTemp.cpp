#include "AmbAirTemp.h"

AmbAirTemp::AmbAirTemp()
{
    Amb = 0;

}

AmbAirTemp::AmbAirTemp(float amb)
{
    Amb=amb;
}

void AmbAirTemp::SetAmbAirTemp(float amb)
{
    Amb = amb;
}

float AmbAirTemp::GetAmbAirTemp() const
{
    return Amb;
}
