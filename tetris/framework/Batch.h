#ifndef _BATCH_H_
#define _BATCH_H_

namespace Framework
{
	/*
		A basic batch.

		This class handles vertex arrays right: adding points and rendering stuff.
		Meant to be subclassed
	*/
	class Batch
	{
	private:
		float *vertex;
		float *color;

		// Even if those thecnically do the same, I still leave both because the code
		// is more clear and understandable this way. And yes, that only costs 4 extra bytes
		int position;
		int elements;

	protected:
		unsigned int mode;
		Batch(size_t max_points);
		void AddPoint(float x, float y, float r, float g, float b, float a);
	public:
		void Begin();
		void End();
		virtual ~Batch();
	};

}
#endif