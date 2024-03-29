/*
  Copyright (C) 2001 Kimmo Pekkola

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __METERBAR_H__
#define __METERBAR_H__

#include "Meter.h"
#include "TintedImage.h"

class CMeterBar : public CMeter
{
public:
	CMeterBar(CMeterWindow* meterWindow, const WCHAR* name);
	virtual ~CMeterBar();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw(Gdiplus::Graphics& graphics);

protected:
	virtual void ReadConfig(CConfigParser& parser, const WCHAR* section);

private:
	enum ORIENTATION
	{
		HORIZONTAL,
		VERTICAL
	};

	CTintedImage m_Image;
	std::wstring m_ImageName;	// Name of the bar-image
	bool m_NeedsReload;

	Gdiplus::Color m_Color;			// Color of the bar
	ORIENTATION m_Orientation;	// Orientation (i.e. the growth direction)
	double m_Value;
	int m_Border;
	bool m_Flip;
};

#endif
