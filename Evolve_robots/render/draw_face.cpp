#include "draw_face.h"

void Face_draw::Draw(vector<vector<float>> m_p)
{
	glBegin(GL_QUADS);
	glColor4ub(188, 170, 67, 255);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(m_p[0][0], m_p[0][1], m_p[0][2]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(m_p[3][0], m_p[3][1], m_p[3][2]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(m_p[5][0], m_p[5][1], m_p[5][2]);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(m_p[1][0], m_p[1][1], m_p[1][2]);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[0][0], m_p[0][1], m_p[0][2]);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[2][0], m_p[2][1], m_p[2][2]);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[6][0], m_p[6][1], m_p[6][2]);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[3][0], m_p[3][1], m_p[3][2]);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(m_p[2][0], m_p[2][1], m_p[2][2]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(m_p[4][0], m_p[4][1], m_p[4][2]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(m_p[7][0], m_p[7][1], m_p[7][2]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(m_p[6][0], m_p[6][1], m_p[6][2]);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(m_p[0][0], m_p[0][1], m_p[0][2]);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(m_p[1][0], m_p[1][1], m_p[1][2]);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(m_p[4][0], m_p[4][1], m_p[4][2]);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(m_p[2][0], m_p[2][1], m_p[2][2]);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(m_p[3][0], m_p[3][1], m_p[3][2]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(m_p[6][0], m_p[6][1], m_p[6][2]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(m_p[7][0], m_p[7][1], m_p[7][2]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(m_p[5][0], m_p[5][1], m_p[5][2]);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[1][0], m_p[1][1], m_p[1][2]);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[5][0], m_p[5][1], m_p[5][2]);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[7][0], m_p[7][1], m_p[7][2]);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(m_p[4][0], m_p[4][1], m_p[4][2]);

	glEnd();
}