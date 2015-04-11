#ifndef CARDINAL_H
#define CARDINAL_H

enum Cardinal {
		EAST = 0, // East is terminal angle of 0 degress of the standard unit circle
		NORTH = 1,
		WEST = 2,
		SOUTH = 3,
		SIZE_OF_ENUM
};

static const char* CardinalNames[SIZE_OF_ENUM] = {"EAST", "NORTH", "WEST", "SOUTH"};

#endif
