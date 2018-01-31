#include "Figure.h"

// Helper array to determine figure base in figures array
const int figureBases[] = {
	0,
	2,
	3,
	7,
	11,
	13,
	15
};

// Helper array to determine number of variations of a figure
const int figureTiles[] = {
	2,
	1,
	4,
	4,
	2,
	2,
	4
};


/*
	This thing is questionable for some people.

	I have nothing against leaving this as it is, but some might want
	to move this into a file.

	Also, 1 is "visible" and -1 is "invisible"
*/
const int figures[] = {
	// I
	1, -1, -1, -1,
	1, -1, -1, -1,
	1, -1, -1, -1,
	1, -1, -1, -1,

	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	 1,  1,  1,  1,

	 // O
	 -1, -1, -1, -1,
	 -1, -1, -1, -1,
	  1,  1, -1, -1,
	  1,  1, -1, -1,

	  // J
	  -1, -1, -1, -1,
	  -1, -1, -1, -1,
	   1, -1, -1, -1,
	   1,  1,  1, -1,

	  -1, -1, -1, -1,
	   1,  1, -1, -1,
	   1, -1, -1, -1,
	   1, -1, -1, -1,

	  -1, -1, -1, -1,
	  -1, -1, -1, -1,
	   1,  1,  1, -1,
	  -1, -1,  1, -1,

	  -1, -1, -1, -1,
	  -1,  1, -1, -1,
	  -1,  1, -1, -1,
	   1,  1, -1, -1,

	   // L
	   -1, -1, -1, -1,
	   -1, -1, -1, -1,
	   -1, -1,  1, -1,
	    1,  1,  1, -1,

	   -1, -1, -1, -1,
	    1, -1, -1, -1,
	    1, -1, -1, -1,
	    1,  1, -1, -1,

	   -1, -1, -1, -1,
	   -1, -1, -1, -1,
	    1,  1,  1, -1,
	    1, -1, -1, -1,

	   -1, -1, -1, -1,
	    1,  1, -1, -1,
	   -1,  1, -1, -1,
	   -1,  1, -1, -1,

	   // Z
	   -1, -1, -1, -1,
	   -1, -1, -1, -1,
	    1,  1, -1, -1,
	   -1,  1,  1, -1,

	   -1, -1, -1, -1,
	   -1,  1, -1, -1,
	    1,  1, -1, -1,
		1, -1, -1, -1,

		// S
		-1, -1, -1, -1,
		-1, -1, -1, -1,
		-1,  1,  1, -1,
		 1,  1, -1, -1,

		-1, -1, -1, -1,
		 1, -1, -1, -1,
		 1,  1, -1, -1,
		-1,  1, -1, -1,

		// T
		-1, -1, -1, -1,
		-1, -1, -1, -1,
		-1,  1, -1, -1,
		 1,  1,  1, -1,

		-1, -1, -1, -1,
		 1, -1, -1, -1,
		 1,  1, -1, -1,
		 1, -1, -1, -1,

		-1, -1, -1, -1,
		-1, -1, -1, -1,
		 1,  1,  1, -1,
		-1,  1, -1, -1,

		-1, -1, -1, -1,
		-1,  1, -1, -1,
		 1,  1, -1, -1,
		-1,  1, -1, -1

};

Figure::Figure(int type, int color, int rotation) : rotation(rotation), type(type), color(color)
{
	Fill();
}

/*
	Returns maximum ammount of rotations for certain figure type
*/
int Figure::Rotations(int type)
{
	return figureTiles[type];
}

/*
	Fill figure data with corresponding items
*/
void Figure::Fill()
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = figures[(figureBases[type] + rotation) * 16 + i];
		// Also, select color for visible tiles
		if (data[i] > 0)
			data[i] *= color;
	}
}

void Figure::Rotate()
{
	// Loop through all possible rotation phases
	if (++rotation >= figureTiles[type])
		rotation = 0;

	Fill();
}