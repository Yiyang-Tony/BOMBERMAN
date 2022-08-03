// BmpLoader.h: interface for the CBmpLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPLOADER_H__D57606C8_D3C1_4A3F_A114_1FEE047DAE5F__INCLUDED_)
#define AFX_BMPLOADER_H__D57606C8_D3C1_4A3F_A114_1FEE047DAE5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BITMAP_ID 0x4D42	/**< 位图文件的标志 */

class CBmpLoader  
{
public:
	CBmpLoader();
	virtual ~CBmpLoader();
	  bool LoadBitmap(char *filename); /**< 装载一个bmp文件 */
      void FreeImage();                /**< 释放图像数据 */

      unsigned int ID;                 /**< 生成纹理的ID号 */
      int imageWidth;                  /**< 图像宽度 */
      int imageHeight;                 /**< 图像高度 */
      unsigned char *image;            /**< 指向图像数据的指针 */
	  unsigned char *CBmpLoader::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, unsigned char* backgroundColor);
	  unsigned char *CBmpLoader::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
};

#endif // !defined(AFX_BMPLOADER_H__D57606C8_D3C1_4A3F_A114_1FEE047DAE5F__INCLUDED_)
