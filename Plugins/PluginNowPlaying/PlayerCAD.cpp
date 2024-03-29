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

#include "StdAfx.h"
#include "PlayerCAD.h"
#include "CAD/cad_sdk.h"

CPlayer* CPlayerCAD::c_Player = NULL;
extern std::wstring g_SettingsFile;
extern HINSTANCE g_Instance;

// This player emulates the CD Art Display IPC interface, which is supported by
// MusicBee, VLC (with libcad plugin), and possibly others.

/*
** Constructor.
**
*/
CPlayerCAD::CPlayerCAD() : CPlayer(),
	m_Window(),
	m_PlayerWindow(),
	m_ExtendedAPI(false)
{
	Initialize();
}

/*
** Constructor.
**
*/
CPlayerCAD::~CPlayerCAD()
{
	c_Player = NULL;
	Uninitialize();
}

/*
** Creates a shared class object.
**
*/
CPlayer* CPlayerCAD::Create()
{
	if (!c_Player)
	{
		c_Player = new CPlayerCAD();
	}

	return c_Player;
}

/*
** Create receiver window.
**
*/
void CPlayerCAD::Initialize()
{
	// Create windows class
	WNDCLASS wc = {0};
	wc.hInstance = g_Instance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"NowPlayingCADClass";
	RegisterClass(&wc);

	// Create reciever window
	m_Window = CreateWindow(L"NowPlayingCADClass",
							L"CD Art Display 1.x Class",
							WS_DISABLED,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL,
							NULL,
							g_Instance,
							this);

	// Add WM_USER/WM_COPYDATA to allowed messages from lower level processes
	HMODULE hUser32 = LoadLibrary(L"user32.dll");
	if (hUser32)
	{
		// Try ChangeWindowMessageFilterEx first (Win7+)
		FPCHANGEWINDOWMESSAGEFILTEREX ChangeWindowMessageFilterEx = (FPCHANGEWINDOWMESSAGEFILTEREX)GetProcAddress(hUser32, "ChangeWindowMessageFilterEx");
		if (ChangeWindowMessageFilterEx)
		{
			ChangeWindowMessageFilterEx(m_Window, WM_USER, MSGFLT_ALLOW, NULL);
			ChangeWindowMessageFilterEx(m_Window, WM_COPYDATA, MSGFLT_ALLOW, NULL);
		}
		else
		{
			// Try ChangeWindowMessageFilter (Vista)
			FPCHANGEWINDOWMESSAGEFILTER ChangeWindowMessageFilter = (FPCHANGEWINDOWMESSAGEFILTER)GetProcAddress(hUser32, "ChangeWindowMessageFilter");
			if (ChangeWindowMessageFilter)
			{
				ChangeWindowMessageFilter(WM_USER, MSGFLT_ALLOW);
				ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ALLOW);
			}
		}

		FreeLibrary(hUser32);
	}

	WCHAR buffer[MAX_PATH];
	LPCTSTR file = g_SettingsFile.c_str();

	// Read saved settings
	GetPrivateProfileString(L"NowPlaying.dll", L"ClassName", NULL, buffer, MAX_PATH, file);
	std::wstring className = buffer;

	GetPrivateProfileString(L"NowPlaying.dll", L"WindowName", NULL, buffer, MAX_PATH, file);
	std::wstring windowName = buffer;

	GetPrivateProfileString(L"NowPlaying.dll", L"PlayerPath", NULL, buffer, MAX_PATH, file);
	m_PlayerPath = buffer;

	LPCTSTR classSz = className.empty() ? NULL : className.c_str();
	LPCTSTR windowSz = windowName.empty() ? NULL : windowName.c_str();

	if (classSz || windowSz)
	{
		m_PlayerWindow = FindWindow(classSz, windowSz);
	}
	else
	{
		classSz = L"CD Art Display IPC Class";
		m_PlayerWindow = FindWindow(classSz, NULL);
		if (m_PlayerWindow)
		{
			WritePrivateProfileString(L"NowPlaying.dll", L"ClassName", classSz, file);

			windowSz = (GetWindowText(m_PlayerWindow, buffer, MAX_PATH) > 0) ? buffer : NULL;
			WritePrivateProfileString(L"NowPlaying.dll", L"WindowName", windowSz, file);

			DWORD pID;
			GetWindowThreadProcessId(m_PlayerWindow, &pID);
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pID);
			if (hProcess)
			{
				if (GetModuleFileNameEx(hProcess, NULL, buffer, MAX_PATH) > 0)
				{
					WritePrivateProfileString(L"NowPlaying.dll", L"PlayerPath", buffer, file);
				}

				CloseHandle(hProcess);
			}
		}
	}

	if (m_PlayerWindow)
	{
		m_Initialized = true;

		if (classSz && wcscmp(classSz, L"CD Art Display IPC Class") == 0)
		{
			m_ExtendedAPI = true;
		}

		SendMessage(m_PlayerWindow, WM_USER, (WPARAM)m_Window, IPC_SET_CALLBACK_HWND);
		m_State = (StateType)SendMessage(m_PlayerWindow, WM_USER, 0, IPC_GET_STATE);

		if (m_State != STATE_STOPPED)
		{
			SendMessage(m_PlayerWindow, WM_USER, 0, IPC_GET_CURRENT_TRACK);
		}
	}
}

/*
** Destroy reciever window.
**
*/
void CPlayerCAD::Uninitialize()
{
	DestroyWindow(m_Window);
	UnregisterClass(L"NowPlayingCADClass", g_Instance);
}

/*
** Window procedure for the reciever window.
**
*/
LRESULT CALLBACK CPlayerCAD::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CPlayerCAD* player;

	switch (msg)
	{
	case WM_CREATE:
		{
			// Get pointer to the CPlayerCAD class from the CreateWindow call
			player = (CPlayerCAD*)((CREATESTRUCT*)lParam)->lpCreateParams;
			return 0;
		}

	case WM_DESTROY:
		{
			SendMessage(player->m_PlayerWindow, WM_USER, 0, IPC_SHUTDOWN_NOTIFICATION);
			return 0;
		}

	case WM_USER:
		switch (lParam)
		{
		case IPC_TRACK_CHANGED_NOTIFICATION:
			{
				PostMessage(player->m_PlayerWindow, WM_USER, 0, IPC_GET_CURRENT_TRACK);
				break;
			}

		case IPC_STATE_CHANGED_NOTIFICATION:
			{
				player->m_State = (StateType)wParam;
				if (player->m_State == STATE_STOPPED)
				{
					player->ClearData();
				}
				break;
			}

		case IPC_VOLUME_CHANGED_NOTIFICATION:
			{
				player->m_Volume = wParam;
				break;
			}

		case IPC_REPEAT_CHANGED_NOTIFICATION:
			{
				player->m_Repeat = (bool)wParam;
				break;
			}

		case IPC_SHUFFLE_CHANGED_NOTIFICATION:
			{
				player->m_Shuffle = (bool)wParam;
				break;
			}

		case IPC_RATING_CHANGED_NOTIFICATION:
			{
				player->m_Rating = (wParam + 1) / 2;	// From 0 - 10 to 0 - 5
				break;
			}

		case IPC_SHUTDOWN_NOTIFICATION:
			{
				player->m_Initialized = false;
				player->ClearData();
				break;
			}
		}
		return 0;

	case WM_COPYDATA:
		{
			PCOPYDATASTRUCT cds = (PCOPYDATASTRUCT)lParam;
			if (cds->dwData == IPC_CURRENT_TRACK_NOTIFICATION)
			{
				player->m_Shuffle = (bool)SendMessage(player->m_PlayerWindow, WM_USER, 0, IPC_GET_SHUFFLE);
				player->m_Repeat = (bool)SendMessage(player->m_PlayerWindow, WM_USER, 0, IPC_GET_REPEAT);

				// TODO: Sent on track update?
				++player->m_TrackCount;

				WCHAR* data = (WCHAR*)cds->lpData;
				WCHAR* pos;
				UINT index = 1;
				while ((pos = wcschr(data, '\t')) != NULL)
				{
					switch (index)
					{
					case 1:
						player->m_Title.assign(data, pos - data);
						break;

					case 2:
						player->m_Artist.assign(data, pos - data);
						break;

					case 3:
						player->m_Album.assign(data, pos - data);
						break;

					case 5:
						player->m_Year = (UINT)_wtoi(data);
						break;

					case 7:
						player->m_Number = (UINT)_wtoi(data);
						break;

					case 8:
						player->m_Duration = (UINT)_wtoi(data);
						break;

					case 9:
						player->m_FilePath.assign(data, pos - data);
						break;

					case 10:
						player->m_Rating = ((UINT)_wtoi(data) + 1) / 2;	// 0 - 10 -> 0 - 5
						break;

					case 11:
						if (*data == L' ' && player->m_Measures & MEASURE_COVER)
						{
							player->FindCover();
						}
						else
						{
							player->m_CoverPath.assign(data, pos - data);
						}
						break;
					}

					data = pos + 1;
					++index;

					if (index == 12)
					{
						break;
					}
				}

				if (player->m_Measures & MEASURE_LYRICS)
				{
					player->FindLyrics();
				}
			}
			else if (cds->dwData == IPC_REGISTER_NOTIFICATION && !player->m_Initialized)
			{
				std::wstring data = (WCHAR*)cds->lpData;
				if (data[0] == L'1')
				{
					data.erase(0, 2);	// Get rid of the 1\t at the beginning

					std::wstring::size_type len = data.find_first_of(L'\t');
					std::wstring className(data, 0, len);
					data.erase(0, ++len);

					len = data.find_first_of(L'\t');
					std::wstring windowName(data, 0, len);
					data.erase(0, ++len);

					len = data.find_first_of(L'\t');
					player->m_PlayerPath.assign(data, 0, len);
					data.erase(0, ++len);

					LPCTSTR classSz = className.empty() ? NULL : className.c_str();
					LPCTSTR windowSz = windowName.empty() ? NULL : windowName.c_str();
					LPCTSTR file = g_SettingsFile.c_str();

					WritePrivateProfileString(L"NowPlaying.dll", L"ClassName", classSz, file);
					WritePrivateProfileString(L"NowPlaying.dll", L"WindowName", windowSz, file);
					WritePrivateProfileString(L"NowPlaying.dll", L"PlayerPath", player->m_PlayerPath.c_str(), file);

					player->m_PlayerWindow = FindWindow(classSz, windowSz);

					if (player->m_PlayerWindow)
					{
						player->m_Initialized = true;
						player->m_ExtendedAPI = (classSz && wcscmp(classSz, L"CD Art Display IPC Class") == 0);
						player->m_State = (StateType)SendMessage(player->m_PlayerWindow, WM_USER, 0, IPC_GET_STATE);

						if (player->m_State != STATE_STOPPED)
						{
							PostMessage(player->m_PlayerWindow, WM_USER, 0, IPC_GET_CURRENT_TRACK);
						}
					}
				}
			}
		}
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

/*
** Called during each update of the main measure.
**
*/
void CPlayerCAD::UpdateData()
{
	if (m_State != STATE_STOPPED)
	{
		m_Position = SendMessage(m_PlayerWindow, WM_USER, 0, IPC_GET_POSITION);
		m_Volume = SendMessage(m_PlayerWindow, WM_USER, 0, IPC_GET_VOLUME);
	}
}

/*
** Handles the Pause bang.
**
*/
void CPlayerCAD::Pause()
{
	SendMessage(m_PlayerWindow, WM_USER, 0, m_ExtendedAPI ? IPC_PAUSE : IPC_PLAYPAUSE);
}

/*
** Handles the Play bang.
**
*/
void CPlayerCAD::Play()
{
	SendMessage(m_PlayerWindow, WM_USER, 0, m_ExtendedAPI ? IPC_PLAY : IPC_PLAYPAUSE);
}

/*
** Handles the Stop bang.
**
*/
void CPlayerCAD::Stop() 
{
	SendMessage(m_PlayerWindow, WM_USER, 0, IPC_STOP);
}

/*
** Handles the Next bang.
**
*/
void CPlayerCAD::Next() 
{
	SendMessage(m_PlayerWindow, WM_USER, 0, IPC_NEXT);
}

/*
** Handles the Previous bang.
**
*/
void CPlayerCAD::Previous() 
{
	SendMessage(m_PlayerWindow, WM_USER, 0, IPC_PREVIOUS);
}

/*
** Handles the SetPosition bang.
**
*/
void CPlayerCAD::SetPosition(int position)
{
	SendMessage(m_PlayerWindow, WM_USER, position, IPC_SET_POSITION);
}

/*
** Handles the SetRating bang.
**
*/
void CPlayerCAD::SetRating(int rating) 
{
	m_Rating = rating;
	rating *= 2; // From 0 - 5 to 0 - 10
	SendMessage(m_PlayerWindow, WM_USER, rating, IPC_SET_RATING);
}

/*
** Handles the SetVolume bang.
**
*/
void CPlayerCAD::SetVolume(int volume) 
{
	SendMessage(m_PlayerWindow, WM_USER, volume, IPC_SET_VOLUME);
}

/*
** Handles the SetShuffle bang.
**
*/
void CPlayerCAD::SetShuffle(bool state)
{
	SendMessage(m_PlayerWindow, WM_USER, (WPARAM)state, IPC_SET_SHUFFLE);
	m_Shuffle = (bool)SendMessage(m_PlayerWindow, WM_USER, 0, IPC_GET_SHUFFLE);
}

/*
** Handles the SetRepeat bang.
**
*/
void CPlayerCAD::SetRepeat(bool state)
{
	SendMessage(m_PlayerWindow, WM_USER, (WPARAM)state, IPC_SET_REPEAT);
	m_Repeat = (bool)SendMessage(m_PlayerWindow, WM_USER, 0, IPC_GET_REPEAT);
}

/*
** Handles the ClosePlayer bang.
**
*/
void CPlayerCAD::ClosePlayer()
{
	SendMessage(m_PlayerWindow, WM_USER, 0, IPC_CLOSE);
	// TODO
	m_Initialized = false;
	ClearData();
}

/*
** Handles the OpenPlayer bang.
**
*/
void CPlayerCAD::OpenPlayer(std::wstring& path)
{
	if (!m_Initialized)
	{
		if (!path.empty())
		{
			ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOW);
		}
		else if (!m_PlayerPath.empty())
		{
			ShellExecute(NULL, L"open", m_PlayerPath.c_str(), NULL, NULL, SW_SHOW);
		}
	}
	else
	{
		// Bring player to front
		SendMessage(m_PlayerWindow, WM_USER, 0, IPC_SHOW_WINDOW);
	}
}
