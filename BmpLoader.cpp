// BmpLoader.cpp: implementation of the CBmpLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BmpLoader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/** 构造函数 */
CBmpLoader::CBmpLoader()
{
   /** 初始化成员值为0 */
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
}

/** 析构函数 */
CBmpLoader::~CBmpLoader()
{
   FreeImage(); /**< 释放图像数据占据的内存 */
}

/** 装载一个位图文件 */
bool CBmpLoader::LoadBitmap(char *file)
{
	FILE *pFile = 0; /**< 文件指针 */
	
	/** 创建位图文件信息和位图文件头结构 */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;
  
	unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

   /** 打开文件,并检查错误 */
	pFile = fopen(file, "rb");
		if(pFile == 0) return false;

	/** 读入位图文件头信息 */ 
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);
	
	/** 检查该文件是否为位图文件 */
	if(header.bfType != BITMAP_ID)
	   {
		   fclose(pFile);             /**< 若不是位图文件,则关闭文件并返回 */
		   return false;
	   }

	/** 读入位图文件信息 */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** 保存图像的宽度和高度 */
	imageWidth = bitmapInfoHeader.biWidth;
    imageHeight = bitmapInfoHeader.biHeight;

    /** 确保读取数据的大小 */
   if(bitmapInfoHeader.biSizeImage == 0)
      bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
      bitmapInfoHeader.biHeight * 3;

	/** 将指针移到数据开始位置 */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** 分配内存 */
	image = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** 检查内存分配是否成功 */
	if(!image)                        /**< 若分配内存失败则返回 */
	   {
		   delete[] image;
		   fclose(pFile);
		   return false;
	   }

	/** 读取图像数据 */
	fread(image, 1, bitmapInfoHeader.biSizeImage, pFile);

	/** 将图像颜色数据格式进行交换,由BGR转换为RGB */
	for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
	   {
		   textureColors = image[index];
		   image[index] = image[index + 2];
		   image[index + 2] = textureColors;
	   }
  
	fclose(pFile);       /**< 关闭文件 */
	return true;         /**< 成功返回 */
}

/** 释放内存 */
void CBmpLoader::FreeImage()
{
   /** 释放分配的内存 */
   if(image)
      {
        delete[] image;
         image = 0;
      }
}

//读纹理图片        
unsigned char *CBmpLoader::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{

	FILE *filePtr;    // 文件指针        
	BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头        
	unsigned char    *bitmapImage;        // bitmap图像数据        
	int    imageIdx = 0;        // 图像位置索引        
	unsigned char    tempRGB;    // 交换变量        

								 // 以“二进制+读”模式打开文件filename         
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		printf("file not open\n");
		return NULL;
	}
	// 读入bitmap文件图        
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件        
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// 读入bitmap信息头        
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据        
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存        
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功        
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据        
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功        
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式    

	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件       
	fclose(filePtr);
	return bitmapImage;
}

//读纹理图片        
unsigned char *CBmpLoader::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, unsigned char* backgroundColor)
{

	FILE *filePtr;    // 文件指针        
	BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头        
	unsigned char    *bitmapImage;        // bitmap图像数据        
	int    imageIdx = 0;        // 图像位置索引        

								// 以“二进制+读”模式打开文件filename         
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		printf("file not open\n");
		return NULL;
	}
	// 读入bitmap文件图        
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件        
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// 读入bitmap信息头        
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据        
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存        
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功        
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据        
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功        
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	unsigned char*   bitmapData;   // 纹理数据     

	bitmapData = new unsigned char[bitmapInfoHeader->biSizeImage / 3 * 4];

	int count = 0;
	//添加alpha通道    
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		bitmapData[count] = bitmapImage[imageIdx + 2];
		bitmapData[count + 1] = bitmapImage[imageIdx + 1];
		bitmapData[count + 2] = bitmapImage[imageIdx];
		if (bitmapData[count] >= backgroundColor[0]
			&& bitmapData[count + 1] >= backgroundColor[1]
			&& bitmapData[count + 2] >= backgroundColor[2]) {
			bitmapData[count + 3] = 0;
		}
		else bitmapData[count + 3] = 255;
		count += 4;
	}

	// 关闭bitmap图像文件       
	fclose(filePtr);
	return bitmapData;
}