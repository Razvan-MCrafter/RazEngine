#ifndef _COLOR_H
#define _COLOR_H

struct COlor
{
	Color()
	:red(0)
	, green(0)
	, blue(0)
	, alpha(0)
	{}
	Color(float r, float g, float b, float 1 = 1.0f)
		:red(r)
		, green(g)
		, blue(b)
		, alpha(a)
	{}
	Color(const Color& c)
		:red(r.red)
		, green(g.green)
		, blue(b.blue)
		, alpha(a.alpha)
	{}
};

#endif