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

#include "StdAfx.h"
#include "MeterBitmap.h"
#include "Measure.h"
#include "Error.h"
#include "Rainmeter.h"
#include "System.h"

using namespace Gdiplus;

extern CRainmeter* Rainmeter;

/*
** The constructor
**
*/
CMeterBitmap::CMeterBitmap(CMeterWindow* meterWindow, const WCHAR* name) : CMeter(meterWindow, name),
	m_Image(L"BitmapImage", NULL, true),
	m_NeedsReload(false),
	m_ZeroFrame(false),
	m_FrameCount(1),
	m_TransitionFrameCount(),
	m_Align(ALIGN_LEFT),
	m_Extend(false),
	m_Separation(),
	m_Digits(),
	m_Value(),
	m_TransitionStartTicks(),
	m_TransitionStartValue()
{
}

/*
** The destructor
**
*/
CMeterBitmap::~CMeterBitmap()
{
}

/*
** Load the image and get the dimensions of the meter from it.
**
*/
void CMeterBitmap::Initialize()
{
	CMeter::Initialize();

	// Load the bitmaps if defined
	if (!m_ImageName.empty())
	{
		m_Image.LoadImage(m_ImageName, m_NeedsReload);

		if (m_Image.IsLoaded())
		{
			Bitmap* bitmap = m_Image.GetImage();

			m_W = bitmap->GetWidth();
			m_H = bitmap->GetHeight();

			if (m_H > m_W)
			{
				m_H = m_H / m_FrameCount;
			}
			else
			{
				m_W = m_W / m_FrameCount;
			}
		}
	}
	else if (m_Image.IsLoaded())
	{
		m_Image.DisposeImage();
	}
}

/*
** Checks if the given point is inside the meter.
**
*/
bool CMeterBitmap::HitTest(int x, int y)
{
	if (m_Extend)
	{
		// Calc the number of numbers
		int numOfNums = 0;

		if (m_Digits > 0)
		{
			numOfNums = m_Digits;
		}
		else
		{
			int tmpValue = (int)m_Value;
			tmpValue = max(0, tmpValue);		// Only positive integers are supported

			int realFrames = (m_FrameCount / (m_TransitionFrameCount + 1));
			do
			{
				++numOfNums;
				if (realFrames == 1)
				{
					tmpValue /= 2;
				}
				else
				{
					tmpValue /= realFrames;
				}
			}
			while (tmpValue > 0);
		}

		Rect rect(GetX(), GetY(), m_W * numOfNums + (numOfNums - 1) * m_Separation, m_H);

		if (m_Align == ALIGN_CENTER)
		{
			rect.Offset(-rect.Width / 2, 0);
		}
		else if (m_Align == ALIGN_RIGHT)
		{
			rect.Offset(-rect.Width, 0);
		}

		if (rect.Contains(x, y))
		{
			return true;
		}
		return false;
	}
	else
	{
		return CMeter::HitTest(x, y);
	}
}

/*
** Read the meter-specific configs from the ini-file.
**
*/
void CMeterBitmap::ReadConfig(CConfigParser& parser, const WCHAR* section)
{
	// Store the current values so we know if the image needs to be updated
	std::wstring oldImageName = m_ImageName;
	int oldW = m_W;
	int oldH = m_H;

	// Read common configs
	CMeter::ReadConfig(parser, section);

	m_ImageName = parser.ReadString(section, L"BitmapImage", L"");
	if (!m_ImageName.empty())
	{
		m_MeterWindow->MakePathAbsolute(m_ImageName);

		// Read tinting configs
		m_Image.ReadConfig(parser, section);
	}
	else
	{
		m_Image.ClearConfigFlags();
	}

	m_FrameCount = parser.ReadInt(section, L"BitmapFrames", 1);
	m_ZeroFrame = 0!=parser.ReadInt(section, L"BitmapZeroFrame", 0);

	m_Separation = parser.ReadInt(section, L"BitmapSeparation", 0);
	m_Extend = 0!=parser.ReadInt(section, L"BitmapExtend", 0);
	m_Digits = parser.ReadInt(section, L"BitmapDigits", 0);

	m_TransitionFrameCount = parser.ReadInt(section, L"BitmapTransitionFrames", 0);

	const WCHAR* align = parser.ReadString(section, L"BitmapAlign", L"LEFT").c_str();
	if (_wcsicmp(align, L"LEFT") == 0)
	{
		m_Align = ALIGN_LEFT;
	}
	else if (_wcsicmp(align, L"RIGHT") == 0)
	{
		m_Align = ALIGN_RIGHT;
	}
	else if (_wcsicmp(align, L"CENTER") == 0)
	{
		m_Align = ALIGN_CENTER;
	}
	else
	{
		std::wstring error = L"BitmapAlign=";
		error += align;
		error += L" is not valid in [";
		error += m_Name;
		error += L']';
		throw CError(error);
	}

	if (m_Initialized)
	{
		m_NeedsReload = (wcscmp(oldImageName.c_str(), m_ImageName.c_str()) != 0);

		if (m_NeedsReload ||
			m_Image.IsConfigsChanged())
		{
			Initialize();  // Reload the image
		}
		else
		{
			// Reset to old dimensions
			m_W = oldW;
			m_H = oldH;
		}
	}
}

/*
** Updates the value(s) from the measures.
**
*/
bool CMeterBitmap::Update()
{
	if (CMeter::Update() && m_Measure)
	{
		double value = (m_Extend) ? m_Measure->GetValue() : m_Measure->GetRelativeValue();

		if (m_TransitionFrameCount > 0)
		{
			int realFrames = m_FrameCount / (m_TransitionFrameCount + 1);
			if ((int)(value * realFrames) != (int)(m_Value * realFrames))
			{
				m_TransitionStartValue = m_Value;
				m_TransitionStartTicks = CSystem::GetTickCount64();
			}
			else
			{
				m_TransitionStartTicks = 0;
			}
		}

		m_Value = value;

		return true;
	}
	return false;
}

/*
** Returns true if the meter has active transition animation.
**
*/
bool CMeterBitmap::HasActiveTransition()
{
	if (m_TransitionStartTicks > 0)
	{
		return true;
	}
	return false;
}

/*
** Draws the meter on the double buffer
**
*/
bool CMeterBitmap::Draw(Graphics& graphics)
{
	if (!CMeter::Draw(graphics)) return false;

	int newY, newX;

	if (m_FrameCount == 0 || !m_Image.IsLoaded()) return false;	// Unable to continue

	Bitmap* bitmap = m_Image.GetImage();

	int x = GetX();
	int y = GetY();

	if (m_Extend)
	{
		int value = (int)m_Value;
		value = max(0, value);		// Only positive integers are supported

		int transitionValue = (int)m_TransitionStartValue;
		transitionValue = max(0, transitionValue);		// Only positive integers are supported

		// Calc the number of numbers
		int numOfNums = 0;

		if (m_Digits > 0)
		{
			numOfNums = m_Digits;
		}
		else
		{
			int tmpValue = value;

			do
			{
				++numOfNums;
				if (m_FrameCount == 1)
				{
					tmpValue /= 2;
				}
				else
				{
					tmpValue /= m_FrameCount;
				}
			}
			while (tmpValue > 0);
		}

		// Blit the images
		int offset;
		if (m_Align == ALIGN_RIGHT)
		{
			offset = 0;
		}
		else if (m_Align == ALIGN_CENTER)
		{
			offset = numOfNums * (m_W + m_Separation) / 2;
		}
		else
		{
			offset = numOfNums * (m_W + m_Separation);
		}

		do
		{
			offset = offset - (m_W + m_Separation);

			Rect r(x + offset, y, m_W, m_H);

			int realFrames = (m_FrameCount / (m_TransitionFrameCount + 1));
			int frame = (value % realFrames) * (m_TransitionFrameCount + 1);

			// If transition is ongoing the pick the correct frame
			if (m_TransitionStartTicks > 0)
			{
				int diffTicks = (int)(CSystem::GetTickCount64() - m_TransitionStartTicks);

				int range = ((value % realFrames) - (transitionValue % realFrames)) * (m_TransitionFrameCount + 1);
				if (range < 0)
				{
					range += m_FrameCount;
				}
				int frameAdjustment = range * diffTicks / ((m_TransitionFrameCount + 1) * m_MeterWindow->GetTransitionUpdate());
				if (frameAdjustment > range)
				{
					m_TransitionStartTicks = 0;		// The transition is over. Draw with the real value.
				}
				else
				{
					frame = (transitionValue % realFrames) * (m_TransitionFrameCount + 1);
					frame += frameAdjustment;
					frame %= m_FrameCount;
				}
			}

//			LogWithArgs(LOG_DEBUG, L"[%u] Value: %f Frame: %i (Transition = %s)", GetTickCount(), m_Value, frame, m_TransitionStartTicks > 0 ? L"true" : L"false");

			if (bitmap->GetHeight() > bitmap->GetWidth())
			{
				newX = 0;
				newY = m_H * frame;
			}
			else
			{
				newX = m_W * frame;
				newY = 0;
			}

			graphics.DrawImage(bitmap, r, newX, newY, m_W, m_H, UnitPixel);
			if (m_FrameCount == 1)
			{
				value /= 2;
				transitionValue /= 2;
			}
			else
			{
				value /= realFrames;
				transitionValue /= realFrames;
			}
			--numOfNums;
		}
		while (numOfNums > 0);
	}
	else
	{
		int frame = 0;
		int realFrames = (m_FrameCount / (m_TransitionFrameCount + 1));

		if (m_ZeroFrame)
		{
			// Use the first frame only if the value is zero
			if (m_Value > 0)
			{
				frame = (int)(m_Value * (realFrames - 1)) * (m_TransitionFrameCount + 1);
			}
		}
		else
		{
			// Select the correct frame linearly
			frame = (int)(m_Value * realFrames) * (m_TransitionFrameCount + 1);
		}

		// If transition is ongoing the pick the correct frame
		if (m_TransitionStartTicks > 0)
		{
			int diffTicks = (int)(CSystem::GetTickCount64() - m_TransitionStartTicks);

			if (diffTicks > ((m_TransitionFrameCount + 1) * m_MeterWindow->GetTransitionUpdate()))
			{
				m_TransitionStartTicks = 0;		// The transition is over. Draw with the real value.
			}
			else
			{
				double range = (m_Value - m_TransitionStartValue);
				double adjustment = range * diffTicks / ((m_TransitionFrameCount + 1) * m_MeterWindow->GetTransitionUpdate());
				double frameAdjustment = adjustment * m_FrameCount;

				frame = (int)(m_TransitionStartValue * realFrames) * (m_TransitionFrameCount + 1);
				frame += (int)frameAdjustment;
				frame %= m_FrameCount;
				frame = max(0, frame);
			}
		}

//		LogWithArgs(LOG_DEBUG, L"[%u] Value: %f Frame: %i (Transition = %s)", GetTickCount(), m_Value, frame, m_TransitionStartTicks > 0 ? L"true" : L"false");

		if (bitmap->GetHeight() > bitmap->GetWidth())
		{
			newX = 0;
			newY = frame * m_H;
		}
		else
		{
			newX = frame * m_W;
			newY = 0;
		}

		// Blit the image
		Rect r(x, y, m_W, m_H);
		graphics.DrawImage(bitmap, r, newX, newY, m_W, m_H, UnitPixel);
	}

	return true;
}

