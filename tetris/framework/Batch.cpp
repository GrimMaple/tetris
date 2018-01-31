#include "Batch.h"
#include "Renderer.h"

namespace Framework
{
	/*
		This batch can actually have different size, but I went with static size afterwards
	*/
	Batch::Batch(size_t max_points)
	{
		vertex = new float[max_points * 3];
		color = new float[max_points * 4];
	}

	Batch::~Batch()
	{
		delete vertex;
		delete color;
	}

	void Batch::AddPoint(float x, float y, float r, float g, float b, float a)
	{
		int current = position * 3;
		vertex[current] = x;
		vertex[current + 1] = y;
		vertex[current + 2] = 0;

		current = position * 4;
		color[current] = r;
		color[current + 1] = g;
		color[current + 2] = b;
		color[current + 3] = a;

		position++;
		elements++;
	}

	/*
		Begin function simply resets class variables
	*/
	void Batch::Begin()
	{
		position = elements = 0;
	}

	void Batch::End()
	{
		Renderer::DrawArray((void*)vertex, (void*)color, elements, mode);
	}

}