#include "mass_draw.h"

void Mass_draw::Draw(vector<vector<float>> m_p) 
{
	int len_m = m_p.size();
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(225, 78, 83, 255);
	for (int i = 0; i < len_m; ++i) {
		glVertex3f(m_p[i][0], m_p[i][1], m_p[i][2]);
	}
	glEnd();
}