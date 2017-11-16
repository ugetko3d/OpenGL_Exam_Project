#pragma once
#include "Vertex.h"

class Diamond : public Vertex
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f, RADIUS = 0.5;
public:
	Diamond();
	Diamond(float width);
	~Diamond();
	void createDiamond(float width);
};

