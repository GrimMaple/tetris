#ifndef _FIGURE_H_
#define _FIGURE_H_


/*
	Represents a tetramino figure.

	Figures data is static and can be found in cpp file with another comment about that
*/
class Figure
{
private:
	int data[16];
	int rotation;
	int type;
	int color;

	void Fill();

public:

	static const int TotalFigures = 7;

	static int Rotations(int type);

	Figure(int type, int color, int rotation);

	int* GetData()
	{
		return data;
	}

	int GetDataAt(int x, int y)
	{
		return data[x + y * 4];
	}

	int CurrentRotation()
	{
		return rotation;
	}

	int CurrentType()
	{
		return type;
	}

	int CurrentColor()
	{
		return color;
	}

	void Rotate();
};

#endif 