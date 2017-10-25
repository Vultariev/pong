#include <math.h>
#include "clamp.h"

double clamp(double x, double min, double max)
{
	if(x != min && x != max)
	{
		return x - (min - max)*floor((x - max)/(min - max));
	}
	else
	{
		return x == min ? min : max;
	}
}
