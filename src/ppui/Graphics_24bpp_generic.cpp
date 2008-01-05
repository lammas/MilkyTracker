/*
 *  Graphics_24bpp_generic.cpp
 *  milkytracker_sdl
 *
 *  Created by Peter Barth on 06.12.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Graphics.h"
#include "Font.h"

#define BPP 3

PPGraphics_24bpp_generic::PPGraphics_24bpp_generic(pp_int32 w, pp_int32 h, pp_int32 p, void* buff) :
	PPGraphicsAbstract(w, h, p, buff),
	bitPosR(0), bitPosG(8), bitPosB(16)	
{
}

void PPGraphics_24bpp_generic::setPixel(pp_int32 x, pp_int32 y)
{
	if (y >= currentClipRect.y1 && y < currentClipRect.y2 &&
		x >= currentClipRect.x1 && x < currentClipRect.x2)
	{
		pp_uint8* buff = (pp_uint8*)buffer+pitch*y+x*BPP;		
		const pp_uint32 rgb = (currentColor.r << bitPosR) + 
			(currentColor.g << bitPosG) +
			(currentColor.b << bitPosB);
#ifndef __ppc__
		buff[0] = rgb & 255;
		buff[1] = (rgb >> 8) & 255;
		buff[2] = (rgb >> 16) & 255;		
#else
		buff[0] = (rgb >> 16) & 255;
		buff[1] = (rgb >> 8) & 255;
		buff[2] = rgb & 255;		
#endif		
	}	
}

void PPGraphics_24bpp_generic::setPixel(pp_int32 x, pp_int32 y, const PPColor& color)
{
	if (y >= currentClipRect.y1 && y < currentClipRect.y2 &&
		x >= currentClipRect.x1 && x < currentClipRect.x2)
	{
		pp_uint8* buff = (pp_uint8*)buffer+pitch*y+x*BPP;
		const pp_uint32 rgb = (color.r << bitPosR) + 
			(color.g << bitPosG) +
			(color.b << bitPosB);
#ifndef __ppc__
		buff[0] = rgb & 255;
		buff[1] = (rgb >> 8) & 255;
		buff[2] = (rgb >> 16) & 255;		
#else
		buff[0] = (rgb >> 16) & 255;
		buff[1] = (rgb >> 8) & 255;
		buff[2] = rgb & 255;		
#endif		
	}	
}

void PPGraphics_24bpp_generic::fill(PPRect rect)
{
	
	if (rect.y1 < currentClipRect.y1)
		rect.y1 = currentClipRect.y1;

	if (rect.x1 < currentClipRect.x1)
		rect.x1 = currentClipRect.x1;

	if (rect.y2 > currentClipRect.y2)
		rect.y2 = currentClipRect.y2;

	if (rect.x2 > currentClipRect.x2)
		rect.x2 = currentClipRect.x2;

	const pp_uint32 rgb = (currentColor.r << bitPosR) + 
		(currentColor.g << bitPosG) +
		(currentColor.b << bitPosB);
	
	pp_int32 len = (rect.x2-rect.x1); 

	pp_uint8* buff = (pp_uint8*)buffer+(pitch*rect.y1+rect.x1*BPP); 
	
	for (pp_int32 y = rect.y1; y < rect.y2; y++)
	{				
		pp_uint8* ptr = buff;
		
		pp_int32 i;
		
		for (i = 0; i < len; i++)
		{
#ifndef __ppc__
			*ptr = rgb & 255;
			*(ptr+1) = (rgb >> 8) & 255;
			*(ptr+2) = (rgb >> 16) & 255;
#else
			*ptr = (rgb >> 16) & 255;
			*(ptr+1) = (rgb >> 8) & 255;
			*(ptr+2) = rgb & 255;
#endif
			ptr+=3;
		}
		
		buff+=pitch;
		
	}	

}

void PPGraphics_24bpp_generic::fill()
{

	fill(currentClipRect);

}

void PPGraphics_24bpp_generic::drawHLine(pp_int32 x1, pp_int32 x2, pp_int32 y)
{

	pp_int32 lx = x1;
	pp_int32 rx = x2;

	if (x1 > x2)
	{
		pp_int32 h = x2;
		x2 = x1;
		x1 = h;
	}

	if (lx < currentClipRect.x1)
		lx = currentClipRect.x1;

	if (rx > currentClipRect.x2)
		rx = currentClipRect.x2;

	if (y < currentClipRect.y1)
		return;

	if (y >= currentClipRect.y2)
		return;

	const pp_uint32 rgb = (currentColor.r << bitPosR) + 
		(currentColor.g << bitPosG) +
		(currentColor.b << bitPosB);

	pp_int32 len = (rx-lx); 
	pp_uint8* buff = (pp_uint8*)buffer+pitch*y+lx*BPP;

	pp_int32 i;		
	for (i = 0; i < len; i++)
	{
#ifndef __ppc__
		*buff = rgb & 255;
		*(buff+1) = (rgb >> 8) & 255;
		*(buff+2) = (rgb >> 16) & 255;
#else
		*buff = (rgb >> 16) & 255;
		*(buff+1) = (rgb >> 8) & 255;
		*(buff+2) = rgb & 255;
#endif
		buff+=3;
	}
	
}

void PPGraphics_24bpp_generic::drawVLine(pp_int32 y1, pp_int32 y2, pp_int32 x)
{

	pp_int32 ly = y1;
	pp_int32 ry = y2;

	if (y1 > y2)
	{
		pp_int32 h = y2;
		y2 = y1;
		y1 = h;
	}

	if (ly < currentClipRect.y1)
		ly = currentClipRect.y1;

	if (ry > currentClipRect.y2)
		ry = currentClipRect.y2;

	if (x < currentClipRect.x1)
		return;

	if (x >= currentClipRect.x2)
		return;

	pp_uint8* buff = (pp_uint8*)buffer+pitch*ly+x*BPP;

	const pp_uint32 rgb = (currentColor.r << bitPosR) + 
		(currentColor.g << bitPosG) +
		(currentColor.b << bitPosB);

	for (pp_int32 y = ly; y < ry; y++)
	{	
#ifndef __ppc__
		*buff = rgb & 255;
		*(buff+1) = (rgb >> 8) & 255;
		*(buff+2) = (rgb >> 16) & 255;
#else
		*buff = (rgb >> 16) & 255;
		*(buff+1) = (rgb >> 8) & 255;
		*(buff+2) = rgb & 255;
#endif
		buff+=pitch;
	}

}

void PPGraphics_24bpp_generic::drawLine(pp_int32 x1, pp_int32 y1, pp_int32 x2, pp_int32 y2)
{
	__PPGRAPHICSLINETEMPLATE
}

void PPGraphics_24bpp_generic::drawAntialiasedLine(pp_int32 x1, pp_int32 y1, pp_int32 x2, pp_int32 y2)
{
	__PPGRAPHICSAALINETEMPLATE
}

void PPGraphics_24bpp_generic::blit(SimpleBitmap& bitmap, PPPoint p)
{
	pp_uint8* src = (pp_uint8*)bitmap.buffer;

	for (int y = 0; y < bitmap.height; y++)
		for (int x = 0; x < bitmap.width; x++)
		{
		
			if (src[0]||src[1]||src[2])
			{
				pp_uint8* buff = (pp_uint8*)buffer+((y+p.y)*pitch+(x+p.x)*BPP);
				
				const pp_uint32 rgb = ((pp_uint32)src[0] << bitPosR) + 
					((pp_uint32)src[1] << bitPosG) +
					((pp_uint32)src[2] << bitPosB);
				
#ifndef __ppc__
				buff[0] = rgb & 255;
				buff[1] = (rgb >> 8) & 255;
				buff[2] = (rgb >> 16) & 255;		
#else
				buff[0] = (rgb >> 16) & 255;
				buff[1] = (rgb >> 8) & 255;
				buff[2] = rgb & 255;		
#endif										
			}

			src+=3;

		}
}

void PPGraphics_24bpp_generic::blit(const pp_uint8* src, const PPPoint& p, const PPSize& size, pp_uint32 pitch, pp_uint32 bpp, pp_int32 intensity/* = 256*/)
{
	pp_int32 w = size.width;
	pp_int32 h = size.height;
	
	const pp_int32 bytesPerPixel = bpp;
	
	pp_uint8* dst = (pp_uint8*)buffer+(this->pitch*p.y+p.x*BPP); 
	
	if (intensity == 256)
	{
		for (pp_int32 y = 0; y < h; y++)
		{
			for (pp_int32 x = 0; x < w; x++)
			{		
				const pp_uint32 rgb = ((pp_uint32)src[0] << bitPosR) + 
					((pp_uint32)src[1] << bitPosG) +
					((pp_uint32)src[2] << bitPosB);

#ifndef __ppc__
				dst[0] = rgb & 255;
				dst[1] = (rgb >> 8) & 255;
				dst[2] = (rgb >> 16) & 255;		
#else
				dst[0] = (rgb >> 16) & 255;
				dst[1] = (rgb >> 8) & 255;
				dst[2] = rgb & 255;		
#endif										
				dst+=BPP;
				src+=bytesPerPixel;
			}
			dst+=this->pitch - w*BPP;
			src+=pitch - w*bytesPerPixel;
		}
	}
	else
	{
		for (pp_int32 y = 0; y < h; y++)
		{
			for (pp_int32 x = 0; x < w; x++)
			{		
				const pp_uint32 rgb = ((((pp_uint32)src[0]*intensity)>>8) << bitPosR) + 
					((((pp_uint32)src[1]*intensity)>>8) << bitPosG) +
					((((pp_uint32)src[2]*intensity)>>8) << bitPosB);

#ifndef __ppc__
				dst[0] = rgb & 255;
				dst[1] = (rgb >> 8) & 255;
				dst[2] = (rgb >> 16) & 255;		
#else
				dst[0] = (rgb >> 16) & 255;
				dst[1] = (rgb >> 8) & 255;
				dst[2] = rgb & 255;		
#endif										
				dst+=BPP;
				src+=bytesPerPixel;
			}
			dst+=this->pitch - w*BPP;
			src+=pitch - w*bytesPerPixel;
		}
	}
}


void PPGraphics_24bpp_generic::drawChar(pp_uint8 chr, pp_int32 x, pp_int32 y, bool underlined)
{

	if (currentFont == NULL)
		return;


	pp_int32 charWidth = (signed)currentFont->getCharWidth();
	pp_int32 charHeight = (signed)currentFont->getCharHeight(); 
	pp_int32 charDim = currentFont->charDim;

	if (x + (signed)charWidth < currentClipRect.x1 ||
		x > currentClipRect.x2 ||
		y + (signed)charHeight < currentClipRect.y1 ||
		y > currentClipRect.y2)
		return;
	
	const pp_uint32 rgb = (currentColor.r << bitPosR) + 
		(currentColor.g << bitPosG) +
		(currentColor.b << bitPosB);

	Bitstream* bitstream = currentFont->bitstream;
	pp_uint8* fontbuffer = bitstream->buffer;

	pp_uint8* buff = (pp_uint8*)buffer + y*pitch + x*BPP;
	pp_uint32 cchrDim = chr*charDim;

	if (x>= currentClipRect.x1 && x + charWidth < currentClipRect.x2 &&
		y>= currentClipRect.y1 && y + charHeight < currentClipRect.y2)
	{
		
		pp_uint32 yChr = cchrDim;
		for (pp_uint32 i = 0; i < (unsigned)charHeight; i++)
		{
			pp_uint32 xChr = yChr;
			for (pp_uint32 j = 0; j < (unsigned)charWidth; j++)
			{
				if ((fontbuffer[xChr>>3]>>(xChr&7)&1))
				{
#ifndef __ppc__
					buff[0] = rgb & 255;
					buff[1] = (rgb >> 8) & 255;
					buff[2] = (rgb >> 16) & 255;		
#else
					buff[0] = (rgb >> 16) & 255;
					buff[1] = (rgb >> 8) & 255;
					buff[2] = rgb & 255;		
#endif		
				}
				buff+=BPP;
				xChr++;
			}
			buff+=pitch-(charWidth*BPP);
			yChr+=charWidth;
		}
	}
	else
	{
		pp_uint32 yChr = cchrDim;
		for (pp_uint32 i = 0; i < (unsigned)charHeight; i++)
		{
			pp_uint32 xChr = yChr;
			for (pp_uint32 j = 0; j < (unsigned)charWidth; j++)
			{
				
				if (y+(signed)i >= currentClipRect.y1 && y+(signed)i < currentClipRect.y2 &&
					x+(signed)j >= currentClipRect.x1 && x+(signed)j < currentClipRect.x2 &&
					(fontbuffer[xChr>>3]>>(xChr&7)&1))
				{					
					pp_uint8* buff = (pp_uint8*)buffer+((y+i)*pitch+(x+j)*BPP);
#ifndef __ppc__
					buff[0] = rgb & 255;
					buff[1] = (rgb >> 8) & 255;
					buff[2] = (rgb >> 16) & 255;		
#else
					buff[0] = (rgb >> 16) & 255;
					buff[1] = (rgb >> 8) & 255;
					buff[2] = rgb & 255;		
#endif		
				}
				xChr++;

			}
			yChr+=charWidth;
		}

	}

	if (underlined)
		drawHLine(x, x+charWidth, y+charHeight);

}

void PPGraphics_24bpp_generic::drawString(const char* str, pp_int32 x, pp_int32 y, bool underlined/* = false*/)
{
	if (currentFont == NULL)
		return;

	pp_int32 charWidth = (signed)currentFont->getCharWidth();
	pp_int32 charHeight = (signed)currentFont->getCharHeight();

	pp_int32 sx = x;

    while (*str) 
	{
		switch (*str)
		{
			case '\xf4':
				setPixel(x+(charWidth>>1), y+(charHeight>>1));
				break;
			case '\n':
				y+=charHeight;
				x=sx-charWidth;
				break;
			default:
				drawChar(*str, x, y, underlined);
		}
        x += charWidth;
        str++;
    }
}

void PPGraphics_24bpp_generic::drawStringVertical(const char* str, pp_int32 x, pp_int32 y, bool underlined/* = false*/)
{
	if (currentFont == NULL)
		return;

	pp_int32 charWidth = (signed)currentFont->getCharWidth();
	pp_int32 charHeight = (signed)currentFont->getCharHeight();

    while (*str) 
	{
		switch (*str)
		{
			case '\xf4':
				setPixel(x+(charWidth>>1), y+(charHeight>>1));
				break;
			default:
				drawChar(*str, x, y, underlined);
		}
        y += charHeight;
        str++;
    }
}
