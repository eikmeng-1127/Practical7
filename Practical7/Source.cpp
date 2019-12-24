#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "P7 Q1"

//24  bit bmp, save using paint

//Step 1: declare var
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

float x = 0.0, y = 0.0, z = 0.0, angle = 0.0;
int textures = 3;
int displayNo = 1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 'X')
			angle = 0.5, x = 1.0, y = 0.0, z = 0.0;
		else if (wParam == 'Y')
			angle = 0.5, x = 0.0, y = 1.0, z = 0.0;
		else if (wParam == 'Z')
			angle = 0.5, x = 0.0, y = 0.0, z = -1.0;
		else if (wParam == VK_SPACE)
			angle = 0.0, x = 0.0, y = 0.0, z = 0.0;
		else if (wParam == 'I') textures = 1;//wood
		else if (wParam == 'O') textures = 2;//metal
		else if (wParam == 'P') textures = 3;//brick
		else if (wParam == 0x31)
			displayNo = 1;
		else if (wParam == 0x32)
			displayNo = 2;
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawCube(float size) {


	glBegin(GL_QUADS);
	// Face 1 (Front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	// Face 2 (must hv connection with face1
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	// Face 3
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, size);
	// Face 4

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	// Face 5

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	// Face 6(back

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, size, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, size, size);

	glEnd();



}


void drawPyramid(float size) {

	float size2 = size / 2;

	glBegin(GL_QUADS);
	// Face 1 (Front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	// Face 2 (must hv connection with face1
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size2, size, size2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0.0f, 0.0f);
	// Face 3
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size2, size, size2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0.0f, size);
	// Face 4

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0.0f, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size2, size, size2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	// Face 5

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size2, size, size2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);


	glEnd();

}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);//Don't show hidden surface
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//	glLoadIdentity();
	glRotatef(angle, x, y, z);



	//Initialise texture info
	//4byte for 24bit data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (textures == 1)
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "wood.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	else if (textures == 2)
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "metal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	else if (textures == 3)
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "brick.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);


	GetObject(hBMP, sizeof(BMP), &BMP);

	//STEP 4 assign texture to the object
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//type of texture, what filter used?magnified?,minimize?,
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	switch (displayNo) {
	case 1:
		drawPyramid(0.5);

		break;
	case 2:
		drawCube(0.5);

		break;
	default:
		break;
	}


	//STEP5
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------