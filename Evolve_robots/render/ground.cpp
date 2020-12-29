#include "ground.h"

void Ground::Draw()
{
	glBegin(GL_QUADS);
	for (int y =0; y<100;++y)
	{
		float yStart = 50.0f - y*1.0f;
		for (int x=0;x<100;++x)
		{
			float xStart = x*1.0f - 50.0f;
			if ((y%2)^(x%2))
			{
				glColor4ub(136, 209, 154, 255);
			}
			else
			{
				glColor4ub(184, 163, 133, 255);
			}
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xStart, yStart, -0.1f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xStart+1.0f, yStart, -0.1f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xStart+1.0f, yStart-1.0f, -0.1f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xStart, yStart-1.0f, -0.1f);
		}
	}
	glEnd();
}
