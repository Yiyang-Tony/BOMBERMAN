
// BOMBERMANView.cpp : implementation of the CBOMBERMANView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BOMBERMAN.h"
#endif

#include "BOMBERMANDoc.h"
#include "BOMBERMANView.h"

#include "BmpLoader.h"
#include"gl/gl.h"
#include"gl/glu.h"
#include "Font.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBOMBERMANView

IMPLEMENT_DYNCREATE(CBOMBERMANView, CView)

BEGIN_MESSAGE_MAP(CBOMBERMANView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CBOMBERMANView construction/destruction

CBOMBERMANView::CBOMBERMANView()
{
	// TODO: add construction code here

}

void CBOMBERMANView::Init(void)
{
	HGLRC hrc;
	m_pDC = new CClientDC(this);
	if (!bSetupPixelFormat())
		return;

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	glEnable(GL_TEXTURE_2D);

	loadTexture();

	MyGame._time = 0;


	MyGame.maze.Texture = Texture;
	SetTimer(1, 100, NULL);
}

CBOMBERMANView::~CBOMBERMANView()
{
}

BOOL CBOMBERMANView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// CBOMBERMANView drawing

void CBOMBERMANView::OnDraw(CDC* /*pDC*/)
{
	CBOMBERMANDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	MyGame.draw();
}


// CBOMBERMANView printing

BOOL CBOMBERMANView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBOMBERMANView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBOMBERMANView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBOMBERMANView diagnostics

#ifdef _DEBUG
void CBOMBERMANView::AssertValid() const
{
	CView::AssertValid();
}

void CBOMBERMANView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBOMBERMANDoc* CBOMBERMANView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBOMBERMANDoc)));
	return (CBOMBERMANDoc*)m_pDocument;
}
#endif //_DEBUG


// CBOMBERMANView message handlers

bool CBOMBERMANView::bSetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}
	return TRUE;


}

int CBOMBERMANView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	Init();
	return 0;
}


void CBOMBERMANView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	int w = cx;  int h = cy;
	glViewport(0, 0, w, h); //设置视口与窗口匹配
	glMatrixMode(GL_PROJECTION); //重新设置坐标系统
	glLoadIdentity();
	//建立正交变换下的剪切体
	gluPerspective(45.0, (float)w / h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void CBOMBERMANView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MyGame.player.move(nChar, MyGame._time);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//加载材质
void CBOMBERMANView::loadTexture()
{

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);

	loadBmp("res/normal.bmp", normal);
	loadBmp("res/boom.bmp", boom);
	loadBmp("res/obstacle.bmp", obstacle);
	loadBmp("res/brick.bmp", brick);
	loadBmp("res/explosion.bmp", explosion);
	loadBmp("res/reward.bmp", reward);

	loadBmp("res/playerUp.bmp", playerUp);
	loadBmp("res/playerRight.bmp", playerRight);
	loadBmp("res/playerDown.bmp", playerDown);
	loadBmp("res/playerLeft.bmp", playerLeft);

	loadBmp("res/monsterDown.bmp", monsterDown);
	loadBmp("res/monsterRight.bmp", monsterRight);
	loadBmp("res/monsterUp.bmp", monsterUp);
	loadBmp("res/monsterLeft.bmp", monsterLeft);

	loadBmp("res/playerWboomUp.bmp", playerWboomUp);
	loadBmp("res/playerWboomRight.bmp", playerWboomRight);
	loadBmp("res/playerWboomDown.bmp", playerWboomDown);
	loadBmp("res/playerWboomLeft.bmp", playerWboomLeft);
	loadBmp("res/boom.bmp", boom);
	loadBmp("res/explosion.bmp", explosion);


	loadBmp("res/Up2.bmp", playerUp2);
	loadBmp("res/Up3.bmp", playerUp3);
	loadBmp("res/Up4.bmp", playerUp4);
	Texture[playerUp1].ID = Texture[playerUp5].ID = Texture[playerUp].ID;
	loadBmp("res/Right2.bmp", playerRight2);
	loadBmp("res/Right3.bmp", playerRight3);
	loadBmp("res/Right4.bmp", playerRight4);
	Texture[playerRight1].ID = Texture[playerRight5].ID = Texture[playerRight].ID;
	loadBmp("res/Down2.bmp", playerDown2);
	loadBmp("res/Down3.bmp", playerDown3);
	loadBmp("res/Down4.bmp", playerDown4);
	Texture[playerDown1].ID = Texture[playerDown5].ID = Texture[playerDown].ID;
	loadBmp("res/Left2.bmp", playerLeft2);
	loadBmp("res/Left3.bmp", playerLeft3);
	loadBmp("res/Left4.bmp", playerLeft4);
	Texture[playerLeft1].ID = Texture[playerLeft5].ID = Texture[playerLeft].ID;


}

unsigned char color[3] = { 255,255,255 };
//加载bmp
void CBOMBERMANView::loadBmp(char * freName, int type)
{

	///**< 启用纹理映射 */
	//if (!Texture[type].LoadBitmap(freName))             /**< 载入位图文件 */
	//{
	//	MessageBox("装载位图文件失败！", "错误", MB_OK);  /**< 如果载入失败则弹出对话框 */
	//	return;
	//}
	//glGenTextures(1, &Texture[type].ID);
	//glBindTexture(GL_TEXTURE_2D, Texture[type].ID);

	////定义二维纹理
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, Texture[type].imageWidth,
	//	Texture[type].imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
	//	Texture[type].image);

	////控制滤波
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	////说明映射方式
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头        
	unsigned char*   bitmapData;                                       // 纹理数据        

	bitmapData = Texture[type].LoadBitmapFile(freName, &bitmapInfoHeader, color);

	glGenTextures(1, &Texture[type].ID);
	glBindTexture(GL_TEXTURE_2D, Texture[type].ID);
	// 指定当前纹理的放大/缩小过滤方式        
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0,         //mipmap层次(通常为，表示最上层)         
		GL_RGBA,    //我们希望该纹理有红、绿、蓝、alpha数据        
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2         
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2         
		0, //边框(0=无边框, 1=有边框)         
		GL_RGBA,    //bitmap数据的格式        
		GL_UNSIGNED_BYTE, //每个颜色数据的类型        
		bitmapData);    //bitmap数据指针        

}

void CBOMBERMANView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MyGame._time++;		//计时开始

	MyGame.manageBomb();
	
	Invalidate();
	CView::OnTimer(nIDEvent);
}