#include <windows.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "evolve.h"
#include "ground.h"
#include "mass_draw.h"
#include "spring_draw.h"
#include "draw_face.h"
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//register window
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = GLWindowProc;
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom)
	{
		return 0;
	}
	//create window
	HWND hwnd = CreateWindowEx(NULL,L"GLWindow",L"OpenGL Window",WS_OVERLAPPEDWINDOW,
		100,100,800,600,NULL,NULL,hInstance,NULL);
	//create opengl render context
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	Ground ground;
	Mass_draw m_draw;
	Spring_draw s_draw;
	Face_draw f_draw, f_draw_2;
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);//setup opengl context complete
	//opengl init
	glMatrixMode(GL_PROJECTION);//tell the gpu processer that i would select the projection matrix
	gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);//set some values to projection matrix
	glMatrixMode(GL_MODELVIEW);//tell .... model view matrix
	glLoadIdentity();
	gluLookAt(-8.0f, -8.0f, 10.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 24.0f);

	glClearColor(0.4,0.15,0.2,1);//set "clear color" for background
	//show window
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);

	float blackColor[] = { 0.0f,0.0f,0.0f,1.0f };
	float whiteColor[] = { 0.8f,0.8f,0.8f,1.0f };
	float lightPos[] = { -1.0f,1.0f,0.5f,0.0f };//
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);//direction light,point,spot

	GLfloat mat_ambient[] = { 0.4,0.4,0.4,1.0 };
	GLfloat mat_diffuse[] = {188,221,67,255 };
	GLfloat mat_specular[] = { 188,221,67,255 };
	GLfloat mat_emission[] = { 1.0, 0.0, 0.0, 1.0 };

	GLfloat mat_shininess[] = { 80.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	MSG msg;

	srand(time(NULL));
	vector<int> kbc_e;
	//ifstream rf;
	//rf.open("D:\\data_a3\\PB\\best.txt");
	//rf.close();
	for (int i = 0; i < 248; ++i) kbc_e.push_back(rand() % 4);      // kbc_seq should depend on the results from EA. Here I randomly generate one.
	evolve evolve1(kbc_e);
	vector<vector<float>> t;
	vector<vector<float>> m_p;
	vector<vector<vector<float>>> p_g;
	vector<vector<float>> p_g_sub;
	vector<float> m_p1 = {0.0,0.0};
	vector<vector<int>> s_i;

	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		vector<mass> Mass = evolve1.getMass();
		vector<spring> Spring = evolve1.getSpring();
		vector<vector<int>> Mass_group = evolve1.getMg();


		int len_m = Mass.size();
		int len_s = Spring.size();
		for (int i = 0; i < len_m; ++i) m_p.push_back(get<1>(Mass[i][1]));
		for (int i = 0; i < len_s; ++i) s_i.push_back(get<1>(Spring[i][2]));


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_p1[0] = 0; m_p1[1] = 0;
		for (int i = 0; i < len_m; ++i) {
			m_p[i][0] *= 15;
			m_p[i][1] *= 15;
			m_p[i][2] *= 15;
			m_p1[0] += m_p[i][0];
			m_p1[1] += m_p[i][1];
		}

		for (int i = 0; i < Mass_group.size(); ++i) {
			p_g_sub.clear();
			for (int j = 0; j < Mass_group[i].size(); ++j) {
				p_g_sub.push_back(m_p[Mass_group[i][j]]);
			}
			p_g.push_back(p_g_sub);
		}

		m_p1[0] /= float(len_m);
		m_p1[1] /= float(len_m);
		glLoadIdentity();
		gluLookAt(m_p1[0]-12.0f, m_p1[1] - 12.0f, 10.0f, m_p1[0], m_p1[1], 0.0f, 0.0f, 0.0f, 24.0f);
		ground.Draw();
		//m_draw.Draw(m_p);
		//s_draw.Draw(m_p, s_i);
		for(int i=0;i<p_g.size();++i)
			f_draw.Draw(p_g[i]);
		evolve1.evolve_update();
		p_g.clear();
		m_p.clear();
		s_i.clear();
		SwapBuffers(dc);
	}
	
	return 0;
}

