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

#ifndef __METERHISTOGRAM_H__
#define __METERHISTOGRAM_H__

#include "Meter.h"
#include "TintedImage.h"

class CMeterHistogram : public CMeter
{
public:
	CMeterHistogram(CMeterWindow* meterWindow, const WCHAR* name);
	virtual ~CMeterHistogram();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw(Gdiplus::Graphics& graphics);
	virtual void BindMeasure(const std::list<CMeasure*>& measures);

protected:
	virtual void ReadConfig(CConfigParser& parser, const WCHAR* section);

private:
	void DisposeBuffer();

	std::wstring m_SecondaryMeasureName;	// Name of the secondary measure
	CMeasure* m_SecondaryMeasure;		// Pointer ot the secondary measure
	Gdiplus::Color m_PrimaryColor;			// Color of the primary histogram
	Gdiplus::Color m_SecondaryColor;			// Color of the secondary histogram
	Gdiplus::Color m_BothColor;				// Color when the both histograms overlap

	int m_MeterPos;						// Position of the meter (i.e. where the new value should be placed)
	bool m_Autoscale;
	bool m_Flip;

	std::wstring m_PrimaryImageName;		// Name of the primary image for bitmap histograms
	std::wstring m_SecondaryImageName;	// Name of the secondary image for bitmap histograms
	std::wstring m_BothImageName;		// Name of the image for overlapping histograms

	CTintedImage m_PrimaryImage;			// The primary bitmap
	CTintedImage m_SecondaryImage;			// The secondary bitmap
	CTintedImage m_BothImage;				// The overlap bitmap

	bool m_PrimaryNeedsReload;
	bool m_SecondaryNeedsReload;
	bool m_BothNeedsReload;

	double* m_PrimaryValues;
	double* m_SecondaryValues;

	double m_MaxPrimaryValue;
	double m_MinPrimaryValue;
	double m_MaxSecondaryValue;
	double m_MinSecondaryValue;

	bool m_WidthChanged;

	static const WCHAR* c_PrimaryConfigArray[CTintedImage::ConfigCount];
	static const WCHAR* c_SecondaryConfigArray[CTintedImage::ConfigCount];
	static const WCHAR* c_BothConfigArray[CTintedImage::ConfigCount];
};

#endif
