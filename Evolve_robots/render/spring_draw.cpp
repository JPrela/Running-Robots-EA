#include "spring_draw.h"

void Spring_draw::Draw(vector<vector<float>> m_p, vector<vector<int>> s_i)
{
	int len_m = m_p.size();
	int len_s = s_i.size();
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor4ub(57, 85, 223, 255);
	for (int i = 0; i < len_s; ++i) {
		glVertex3f(m_p[s_i[i][0]][0], m_p[s_i[i][0]][1], m_p[s_i[i][0]][2]);
		glVertex3f(m_p[s_i[i][1]][0], m_p[s_i[i][1]][1], m_p[s_i[i][1]][2]);
	}
	glEnd();
}