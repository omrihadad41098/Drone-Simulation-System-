#include "Compass.h"

namespace jb
{

Compass NORTH{ 0, Compass::STEPS_OF_90 };
Compass EAST{ 1, Compass::STEPS_OF_90};
Compass SOUTH{ 2, Compass::STEPS_OF_90};
Compass WEST{ 3, Compass::STEPS_OF_90};

static int toBoundedDegrees(int headingSteps, int stepSize)
{
	int unboundedDegrees = (headingSteps * stepSize);
	return (unboundedDegrees >= 0) 
		? unboundedDegrees % Compass::MAX_DEGREES 
		: Compass::MAX_DEGREES - (-unboundedDegrees % 360);
}

Compass::Compass(int initialHeadingSteps, StepsOf90_t dummy)
	: m_headingDegrees(toBoundedDegrees(initialHeadingSteps, 90))
{
}

Compass::Compass(int initialHeading, InDegrees_t dummy)
	: m_headingDegrees(toBoundedDegrees(initialHeading, 1))
{
}

Compass Compass::roatateInStepsOf90(int steps) const
{
	return Compass(m_headingDegrees + steps * 90, IN_DEGREES);
}

bool operator==(const Compass &a, const Compass &b)
{
	return a.getHeading() == b.getHeading();
}

bool operator<(const Compass &a, const Compass &b)
{
	return a.getHeading() < b.getHeading();
}

void turnLeft(Compass *compass)
{
	*compass = compass->roatateInStepsOf90(-1);
}

void turnRight(Compass *compass)
{
	*compass = compass->roatateInStepsOf90(1);
}

} // jb
