/*
  Copyright (C) 2011 Birunthan Mohanathas (www.poiru.net)

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

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "fileref.h"
#include "tag.h"
#include "Cover.h"
#include "Internet.h"
#include "Lyrics.h"

enum StateType
{
	STATE_STOPPED,
	STATE_PLAYING,
	STATE_PAUSED
};

enum MeasureType
{
	MEASURE_NONE     = 0x00000000,
	MEASURE_ARTIST   = 0x00000001,
	MEASURE_TITLE    = 0x00000002,
	MEASURE_ALBUM    = 0x00000004,
	MEASURE_LYRICS   = 0x00000008,
	MEASURE_COVER    = 0x00000010,
	MEASURE_FILE     = 0x00000020,
	MEASURE_DURATION = 0x00000040,
	MEASURE_POSITION = 0x00000080,
	MEASURE_PROGRESS = 0x00000100,
	MEASURE_RATING   = 0x00000200,
	MEASURE_VOLUME   = 0x00000400,
	MEASURE_STATE    = 0x00000800,
	MEASURE_STATUS   = 0x00001000,
	MEASURE_SHUFFLE  = 0x00002000,
	MEASURE_REPEAT   = 0x00004000,
	MEASURE_NUMBER   = 0x00008000,
	MEASURE_YEAR     = 0x00010000
};

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer() = 0;

	void AddInstance();
	void RemoveInstance();
	void UpdateMeasure();
	void AddMeasure(INT type);
	virtual void UpdateData() = 0;

	bool IsInitialized() const { return m_Initialized; }
	UINT GetTrackCount() const { return m_TrackCount; }

	void FindCover();
	void FindLyrics();

	virtual void Pause() {}
	virtual void Play() {}
	virtual void Stop() {}
	virtual void Next() {}
	virtual void Previous() {}
	virtual void SetPosition(int position) {}		// position: position in seconds
	virtual void SetRating(int rating) {}			// rating: 0 - 5
	virtual void SetVolume(int volume) {}			// volume: 0 - 100
	virtual void SetShuffle(bool state) {}			// state: off = 0, on = 1
	virtual void SetRepeat(bool state) {}			// state: off = 0, on = 1
	virtual void OpenPlayer(std::wstring& path) {}
	virtual void ClosePlayer() {}

	INT GetMeasures() const { return m_Measures; }
	void SetMeasures(INT measures) { m_Measures = measures; }

	StateType GetState() const { return m_State; }
	LPCTSTR GetArtist() const { return m_Artist.c_str(); }
	LPCTSTR GetAlbum() const { return m_Album.c_str(); }
	LPCTSTR GetTitle() const { return m_Title.c_str(); }
	LPCTSTR GetLyrics() const { return m_Lyrics.c_str(); }
	LPCTSTR GetCoverPath() const { return m_CoverPath.c_str(); }
	LPCTSTR GetFilePath() const { return m_FilePath.c_str(); }
	UINT GetDuration() const { return m_Duration; }
	UINT GetPosition() const { return m_Position; }
	UINT GetRating() const { return m_Rating; }
	UINT GetVolume() const { return m_Volume; }
	UINT GetNumber() const { return m_Number; }
	UINT GetYear() const { return m_Year; }
	bool GetShuffle() const { return m_Shuffle; }
	bool GetRepeat() const { return m_Repeat; }

protected:
	void ClearData();

	bool m_Initialized;
	UINT m_InstanceCount;
	UINT m_UpdateCount;
	UINT m_TrackCount;
	std::wstring m_TempCoverPath;

	INT m_Measures;

	StateType m_State;
	std::wstring m_Artist;
	std::wstring m_Title;
	std::wstring m_Album;
	std::wstring m_Lyrics;
	std::wstring m_CoverPath;		// Path to cover art image
	std::wstring m_FilePath;		// Path to playing file
	UINT m_Duration;				// Track duration in seconds
	UINT m_Position;				// Current position in seconds
	UINT m_Rating;					// Track rating from 0 to 100
	UINT m_Volume;					// Volume from 0 to 100
	UINT m_Number;
	UINT m_Year;
	bool m_Shuffle;
	bool m_Repeat;

private:
	static unsigned __stdcall LyricsThreadProc(void* pParam);

	HANDLE m_InternetThread;
};

#endif