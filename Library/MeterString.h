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

#ifndef __METERSTRING_H__
#define __METERSTRING_H__

#include "Meter.h"
#include "Measure.h"
#include <unordered_map>

class CMeterString : public CMeter
{
public:
	CMeterString(CMeterWindow* meterWindow, const WCHAR* name);
	virtual ~CMeterString();

	virtual int GetX(bool abs = false);

	virtual void Initialize();
	virtual bool Update();
	void SetText(const WCHAR* text) { m_Text = text; }
	virtual bool Draw(Gdiplus::Graphics& graphics);
	virtual void BindMeasure(const std::list<CMeasure*>& measures);
	Gdiplus::RectF GetRect() { return m_Rect; }

	static void FreeFontCache(Gdiplus::PrivateFontCollection* collection = NULL);
	static void EnumerateInstalledFontFamilies();

protected:
	virtual void ReadConfig(CConfigParser& parser, const WCHAR* section);

private:
	enum TEXTSTYLE
	{
		NORMAL,
		BOLD,
		ITALIC,
		BOLDITALIC
	};

	enum TEXTEFFECT
	{
		EFFECT_NONE,
		EFFECT_SHADOW,
		EFFECT_BORDER
	};

	enum TEXTCASE
	{
		TEXTCASE_NONE,
		TEXTCASE_UPPER,
		TEXTCASE_LOWER,
		TEXTCASE_PROPER
	};

	bool DrawString(Gdiplus::Graphics& graphics, Gdiplus::RectF* rect);

	Gdiplus::Color m_Color;				// The color of the text
	Gdiplus::Color m_EffectColor;		// The color of the text effect
	std::wstring m_Postfix;				// The postfix of the text
	std::wstring m_Prefix;				// The prefix of the text
	std::wstring m_Text;				// The text
	std::wstring m_FontFace;			// name of the font face
	AUTOSCALE m_AutoScale;				// true, if the value should be autoscaled
	METER_ALIGNMENT m_Align;			// Alignment of the text
	TEXTSTYLE m_Style;					// Style of the text
	TEXTEFFECT m_Effect;				// Text effect
	TEXTCASE m_textCase;				// Case of the text
	int m_FontSize;						// Size of the fonts
	double m_Scale;						// Scaling if autoscale is not used
	bool m_NoDecimals;					// Number of decimals to use
	bool m_Percentual;					// True, if the value should be given as %
	bool m_ClipString;					// True, the text is clipped in borders (adds ellipsis to the end of the string)
	Gdiplus::Font* m_Font;				// The font
	Gdiplus::FontFamily* m_FontFamily;	// The font family
	int m_NumOfDecimals;				// Number of decimals to be displayed
	Gdiplus::REAL m_Angle;
	Gdiplus::RectF m_Rect;

	std::wstring m_String;

	std::vector<std::wstring> m_MeasureNames;
	std::vector<CMeasure*> m_Measures;

	static std::wstring FontFaceToString(const std::wstring& fontFace, Gdiplus::PrivateFontCollection* collection);
	static std::wstring FontPropertiesToString(Gdiplus::REAL size, Gdiplus::FontStyle style);

	static std::unordered_map<std::wstring, Gdiplus::FontFamily*> c_FontFamilies;		// Cache for the font families
	static std::unordered_map<std::wstring, Gdiplus::Font*> c_Fonts;					// Cache for the fonts
};

#endif

/*
E	eksa	10^18
P	peta	10^15
T	tera	10^12
G	giga	10^9
M	mega	10^6
k	kilo	10^3
*/	
