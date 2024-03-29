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
#include "MeasureNet.h"
#include "Rainmeter.h"
#include "System.h"

BYTE* CMeasureNet::c_Table = NULL;
UINT CMeasureNet::c_NumOfTables = 0;
std::vector<ULONG64> CMeasureNet::c_StatValues;
std::vector<ULONG64> CMeasureNet::c_OldStatValues;

FPGETIFTABLE2 CMeasureNet::c_GetIfTable2 = NULL;
FPFREEMIBTABLE CMeasureNet::c_FreeMibTable = NULL;

extern CRainmeter* Rainmeter;

/*
** The constructor. This is the base class for the net-meters.
**
*/
CMeasureNet::CMeasureNet(CMeterWindow* meterWindow, const WCHAR* name) : CMeasure(meterWindow, name),
	m_CurrentTraffic(),
	m_TrafficValue(),
	m_Interface(),
	m_Cumulative(false)
{
}

/*
** The destructor
**
*/
CMeasureNet::~CMeasureNet()
{
}

/*
** Checks if Action should be executed.
**
*/
bool CMeasureNet::Update()
{
	if (!CMeasure::PreUpdate()) return false;

	if (m_MeterWindow)
	{
		if (!m_TrafficAction.empty())
		{
			if (m_CurrentTraffic > m_TrafficValue)
			{
				m_CurrentTraffic = 0;
				Rainmeter->ExecuteCommand(m_TrafficAction.c_str(), m_MeterWindow);
			}

			m_CurrentTraffic += m_Value;
		}
	}

	return PostUpdate();
}

/*
** Reads the tables for all net interfaces
**
*/
void CMeasureNet::UpdateIFTable()
{
	bool logging = false;

	if (c_GetIfTable2)
	{
		if (c_Table)
		{
			c_FreeMibTable(c_Table);
			c_Table = NULL;
		}

		if (c_GetIfTable2((MIB_IF_TABLE2**)&c_Table) == NO_ERROR)
		{
			MIB_IF_TABLE2* ifTable = (MIB_IF_TABLE2*)c_Table;

			if (c_NumOfTables != ifTable->NumEntries)
			{
				c_NumOfTables = ifTable->NumEntries;
				logging = true;
			}

			if (Rainmeter->GetDebug() && logging)
			{
				Log(LOG_DEBUG, L"------------------------------");
				LogWithArgs(LOG_DEBUG, L"* NETWORK-INTERFACE: Count=%i", c_NumOfTables);

				for (size_t i = 0; i < c_NumOfTables; ++i)
				{
					std::wstring type;
					switch (ifTable->Table[i].Type)
					{
					case IF_TYPE_ETHERNET_CSMACD:
						type += L"Ethernet";
						break;
					case IF_TYPE_PPP:
						type += L"PPP";
						break;
					case IF_TYPE_SOFTWARE_LOOPBACK:
						type += L"Loopback";
						break;
					case IF_TYPE_IEEE80211:
						type += L"IEEE802.11";
						break;
					case IF_TYPE_TUNNEL:
						type += L"Tunnel";
						break;
					case IF_TYPE_IEEE1394:
						type += L"IEEE1394";
						break;
					default:
						type += L"Other";
						break;
					}

					LogWithArgs(LOG_DEBUG, L"%i: %s", (int)i + 1, ifTable->Table[i].Description);
					LogWithArgs(LOG_DEBUG, L"  Alias: %s", ifTable->Table[i].Alias);
					LogWithArgs(LOG_DEBUG, L"  Type=%s(%i), Hardware=%s, Filter=%s",
						type.c_str(), ifTable->Table[i].Type,
						(ifTable->Table[i].InterfaceAndOperStatusFlags.HardwareInterface == 1) ? L"Yes" : L"No",
						(ifTable->Table[i].InterfaceAndOperStatusFlags.FilterInterface == 1) ? L"Yes" : L"No");
				}
				Log(LOG_DEBUG, L"------------------------------");
			}
		}
		else
		{
			// Something's wrong. Unable to get the table.
			c_Table = NULL;
			c_NumOfTables = 0;
		}
	}
	else
	{
		if (c_Table == NULL)
		{
			// Gotta reserve few bytes for the tables
			DWORD value = 0;
			if (GetNumberOfInterfaces(&value) == NO_ERROR)
			{
				if (c_NumOfTables != value)
				{
					c_NumOfTables = value;
					logging = true;
				}

				if (c_NumOfTables > 0)
				{
					DWORD size = sizeof(MIB_IFTABLE) + sizeof(MIB_IFROW) * c_NumOfTables;
					c_Table = new BYTE[size];
				}
			}
		}

		if (c_Table)
		{
			DWORD ret, size = 0;

			MIB_IFTABLE* ifTable = (MIB_IFTABLE*)c_Table;

			if ((ret = GetIfTable(ifTable, &size, FALSE)) == ERROR_INSUFFICIENT_BUFFER)
			{
				delete [] c_Table;
				c_Table = new BYTE[size];

				ifTable = (MIB_IFTABLE*)c_Table;

				ret = GetIfTable(ifTable, &size, FALSE);
			}

			if (ret == NO_ERROR)
			{
				if (c_NumOfTables != ifTable->dwNumEntries)
				{
					c_NumOfTables = ifTable->dwNumEntries;
					logging = true;
				}

				if (Rainmeter->GetDebug() && logging)
				{
					Log(LOG_DEBUG, L"------------------------------");
					LogWithArgs(LOG_DEBUG, L"* NETWORK-INTERFACE: Count=%i", c_NumOfTables);

					for (size_t i = 0; i < c_NumOfTables; ++i)
					{
						std::string desc((char*)ifTable->table[i].bDescr, ifTable->table[i].dwDescrLen);

						std::wstring type;
						switch (ifTable->table[i].dwType)
						{
						case IF_TYPE_ETHERNET_CSMACD:
							type += L"Ethernet";
							break;
						case IF_TYPE_PPP:
							type += L"PPP";
							break;
						case IF_TYPE_SOFTWARE_LOOPBACK:
							type += L"Loopback";
							break;
						case IF_TYPE_IEEE80211:
							type += L"IEEE802.11";
							break;
						case IF_TYPE_TUNNEL:
							type += L"Tunnel";
							break;
						case IF_TYPE_IEEE1394:
							type += L"IEEE1394";
							break;
						default:
							type += L"Other";
							break;
						}

						LogWithArgs(LOG_DEBUG, L"%i: %s", (int)i + 1, ConvertToWide(desc.c_str()).c_str());
						LogWithArgs(LOG_DEBUG, L"  Type=%s(%i)",
							type.c_str(), ifTable->table[i].dwType);
					}
					Log(LOG_DEBUG, L"------------------------------");
				}
			}
			else
			{
				// Something's wrong. Unable to get the table.
				delete [] c_Table;
				c_Table = NULL;
				c_NumOfTables = 0;
			}
		}
	}
}

/*
** Reads the amount of octets. This is the same for in, out and total.
** the net-parameter informs which inherited class called this method.
**
*/
ULONG64 CMeasureNet::GetNetOctets(NET net)
{
	ULONG64 value = 0;

	if (c_GetIfTable2)
	{
		MIB_IF_ROW2* table = (MIB_IF_ROW2*)((MIB_IF_TABLE2*)c_Table)->Table;

		if (m_Interface == 0)
		{
			// Get all interfaces
			for (UINT i = 0; i < c_NumOfTables; ++i)
			{
				// Ignore the loopback and filter interfaces
				if (table[i].Type == IF_TYPE_SOFTWARE_LOOPBACK ||
					table[i].InterfaceAndOperStatusFlags.FilterInterface == 1) continue;

				switch (net)
				{
				case NET_IN:
					value += table[i].InOctets;
					break;

				case NET_OUT:
					value += table[i].OutOctets;
					break;

				case NET_TOTAL:
					value += table[i].InOctets;
					value += table[i].OutOctets;
					break;
				}
			}
		}
		else
		{
			// Get the selected interface
			if (m_Interface <= c_NumOfTables)
			{
				switch (net)
				{
				case NET_IN:
					value += table[m_Interface - 1].InOctets;
					break;

				case NET_OUT:
					value += table[m_Interface - 1].OutOctets;
					break;

				case NET_TOTAL:
					value += table[m_Interface - 1].InOctets;
					value += table[m_Interface - 1].OutOctets;
					break;
				}
			}
		}
	}
	else
	{
		MIB_IFROW* table = (MIB_IFROW*)((MIB_IFTABLE*)c_Table)->table;

		if (m_Interface == 0)
		{
			// Get all interfaces
			for (UINT i = 0; i < c_NumOfTables; ++i)
			{
				// Ignore the loopback
				if (table[i].dwType == IF_TYPE_SOFTWARE_LOOPBACK) continue;

				switch (net)
				{
				case NET_IN:
					value += table[i].dwInOctets;
					break;

				case NET_OUT:
					value += table[i].dwOutOctets;
					break;

				case NET_TOTAL:
					value += table[i].dwInOctets;
					value += table[i].dwOutOctets;
					break;
				}
			}
		}
		else
		{
			// Get the selected interface
			if (m_Interface <= c_NumOfTables)
			{
				switch (net)
				{
				case NET_IN:
					value += table[m_Interface - 1].dwInOctets;
					break;

				case NET_OUT:
					value += table[m_Interface - 1].dwOutOctets;
					break;

				case NET_TOTAL:
					value += table[m_Interface - 1].dwInOctets;
					value += table[m_Interface - 1].dwOutOctets;
					break;
				}
			}
		}
	}

	return value;
}

/*
** Returns the stats value of the interface
**
*/
ULONG64 CMeasureNet::GetNetStatsValue(NET net)
{
	ULONG64 value = 0;
	size_t statsSize = c_StatValues.size() / 2;

	if (m_Interface == 0)
	{
		// Get all interfaces
		for (size_t i = 0; i < statsSize; ++i)
		{
			// Ignore the loopback and filter interfaces
			if (c_NumOfTables == statsSize)
			{
				if (c_GetIfTable2)
				{
					if (((MIB_IF_TABLE2*)c_Table)->Table[i].Type == IF_TYPE_SOFTWARE_LOOPBACK ||
						((MIB_IF_TABLE2*)c_Table)->Table[i].InterfaceAndOperStatusFlags.FilterInterface == 1) continue;
				}
				else
				{
					if (((MIB_IFTABLE*)c_Table)->table[i].dwType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
				}
			}

			switch (net)
			{
			case NET_IN:
				value += c_StatValues[i * 2 + 0];
				break;

			case NET_OUT:
				value += c_StatValues[i * 2 + 1];
				break;

			case NET_TOTAL:
				value += c_StatValues[i * 2 + 0];
				value += c_StatValues[i * 2 + 1];
				break;
			}
		}
	}
	else
	{
		// Get the selected interface
		if (m_Interface <= statsSize)
		{
			switch (net)
			{
			case NET_IN:
				value += c_StatValues[(m_Interface - 1) * 2 + 0];
				break;

			case NET_OUT:
				value += c_StatValues[(m_Interface - 1) * 2 + 1];
				break;

			case NET_TOTAL:
				value += c_StatValues[(m_Interface - 1) * 2 + 0];
				value += c_StatValues[(m_Interface - 1) * 2 + 1];
				break;
			}
		}
	}

	return value;
}

/*
** Reads the measure specific configs. This is the same for in, out and total.
** the net-parameter informs which inherited class called this method.
**
*/
void CMeasureNet::ReadConfig(CConfigParser& parser, const WCHAR* section, NET net)
{
	double value;
	const WCHAR* netName = NULL;

	if (net == NET_IN)
	{
		netName = L"NetInSpeed";
		value = Rainmeter->GetGlobalConfig().netInSpeed;
	}
	else if (net == NET_OUT)
	{
		netName = L"NetOutSpeed";
		value = Rainmeter->GetGlobalConfig().netOutSpeed;
	}
	else
	{
		netName = L"NetTotalSpeed";
		value = Rainmeter->GetGlobalConfig().netInSpeed + Rainmeter->GetGlobalConfig().netOutSpeed;
	}

	double maxValue = parser.ReadFloat(section, L"MaxValue", -1);
	if (maxValue == -1)
	{
		maxValue = parser.ReadFloat(section, netName, -1);
		if (maxValue == -1)
		{
			maxValue = value;
		}
	}

	m_Interface = parser.ReadInt(section, L"Interface", 0);

	m_Cumulative = 0!=parser.ReadInt(section, L"Cumulative", 0);
	if (m_Cumulative)
	{
		Rainmeter->SetNetworkStatisticsTimer();
	}

	m_TrafficValue = parser.ReadFloat(section, L"TrafficValue", 0.0);
	m_TrafficAction = parser.ReadString(section, L"TrafficAction", L"", false);

	if (maxValue == 0)
	{
		m_MaxValue = 1;
		m_LogMaxValue = true;
	}
	else
	{
		m_MaxValue = maxValue / 8;
	}
}

/*
** Updates the statistics.
**
*/
void CMeasureNet::UpdateStats()
{
	if (c_Table)
	{
		size_t statsSize = c_NumOfTables * 2;

		// Fill the vectors
		if (c_StatValues.size() < statsSize)
		{
			c_StatValues.resize(statsSize, 0);
		}

		if (c_OldStatValues.size() < statsSize)
		{
			c_OldStatValues.resize(statsSize, 0);
		}

		for (UINT i = 0; i < c_NumOfTables; ++i)
		{
			ULONG64 in, out;

			if (c_GetIfTable2)
			{
				in = ((MIB_IF_TABLE2*)c_Table)->Table[i].InOctets;
				out = ((MIB_IF_TABLE2*)c_Table)->Table[i].OutOctets;
			}
			else
			{
				in = ((MIB_IFTABLE*)c_Table)->table[i].dwInOctets;
				out = ((MIB_IFTABLE*)c_Table)->table[i].dwOutOctets;
			}

			if (c_OldStatValues[i * 2 + 0] != 0)
			{
				if (in > c_OldStatValues[i * 2 + 0])
				{
					c_StatValues[i * 2 + 0] += in - c_OldStatValues[i * 2 + 0];
				}
			}

			if (c_OldStatValues[i * 2 + 1] != 0)
			{
				if (out > c_OldStatValues[i * 2 + 1])
				{
					c_StatValues[i * 2 + 1] += out - c_OldStatValues[i * 2 + 1];
				}
			}

			c_OldStatValues[i * 2 + 0] = in;
			c_OldStatValues[i * 2 + 1] = out;
		}
	}
}

/*
** Resets the statistics.
**
*/
void CMeasureNet::ResetStats()
{
	c_StatValues.clear();
}

/*
** Reads statistics.
**
*/
void CMeasureNet::ReadStats(const WCHAR* iniFile, std::wstring& statsDate)
{
	WCHAR buffer[64];

	CConfigParser parser;
	parser.Initialize(iniFile, NULL, NULL, L"Statistics");

	const std::wstring& date = parser.ReadString(L"Statistics", L"Since", L"", false);
	if (!date.empty())
	{
		statsDate = date;
	}

	int count = parser.ReadInt(L"Statistics", L"NetStatsCount", 0);

	c_StatValues.clear();
	c_StatValues.reserve(count * 2);

	for (int i = 1; i <= count; ++i)
	{
		ULARGE_INTEGER value;

		_snwprintf_s(buffer, _TRUNCATE, L"NetStatsInHigh%i", i);
		value.HighPart = parser.ReadUInt(L"Statistics", buffer, 0);

		_snwprintf_s(buffer, _TRUNCATE, L"NetStatsInLow%i", i);
		value.LowPart = parser.ReadUInt(L"Statistics", buffer, 0);

		c_StatValues.push_back(value.QuadPart);

		_snwprintf_s(buffer, _TRUNCATE, L"NetStatsOutHigh%i", i);
		value.HighPart = parser.ReadUInt(L"Statistics", buffer, 0);

		_snwprintf_s(buffer, _TRUNCATE, L"NetStatsOutLow%i", i);
		value.LowPart = parser.ReadUInt(L"Statistics", buffer, 0);

		c_StatValues.push_back(value.QuadPart);
	}
}

/*
** Appends "key=value\0" to given string.
**
*/
inline void AppendStatsValue(std::wstring& data, const WCHAR* key, size_t key_len, const WCHAR* value, size_t value_len)
{
	data.append(key, key_len);
	data += L'=';
	data.append(value, value_len);
	data += L'\0';
}

/*
** Writes statistics.
**
*/
void CMeasureNet::WriteStats(const WCHAR* iniFile, const std::wstring& statsDate)
{
	WCHAR buffer[64];
	WCHAR buffer2[32];
	size_t len, len2;

	size_t statsSize = c_StatValues.size() / 2;

	// Reserve sufficient buffer for statistics
	std::wstring data;
	data.reserve((64 * 2) + 128 * statsSize);

	// Add date
	AppendStatsValue(data, L"Since", 5, statsDate.c_str(), statsDate.size());

	// Add stats count
	len = _snwprintf_s(buffer, _TRUNCATE, L"%i", (int)statsSize);
	AppendStatsValue(data, L"NetStatsCount", 13, buffer, len);

	// Add stats
	for (size_t i = 0; i < statsSize; ++i)
	{
		ULARGE_INTEGER value;

		value.QuadPart = c_StatValues[i * 2];

		len  = _snwprintf_s(buffer, _TRUNCATE, L"NetStatsInHigh%i", (int)i + 1);
		len2 = _snwprintf_s(buffer2, _TRUNCATE, L"%u", value.HighPart);
		AppendStatsValue(data, buffer, len, buffer2, len2);

		len  = _snwprintf_s(buffer, _TRUNCATE, L"NetStatsInLow%i", (int)i + 1);
		len2 = _snwprintf_s(buffer2, _TRUNCATE, L"%u", value.LowPart);
		AppendStatsValue(data, buffer, len, buffer2, len2);

		value.QuadPart = c_StatValues[i * 2 + 1];

		len  = _snwprintf_s(buffer, _TRUNCATE, L"NetStatsOutHigh%i", (int)i + 1);
		len2 = _snwprintf_s(buffer2, _TRUNCATE, L"%u", value.HighPart);
		AppendStatsValue(data, buffer, len, buffer2, len2);

		len  = _snwprintf_s(buffer, _TRUNCATE, L"NetStatsOutLow%i", (int)i + 1);
		len2 = _snwprintf_s(buffer2, _TRUNCATE, L"%u", value.LowPart);
		AppendStatsValue(data, buffer, len, buffer2, len2);
	}

	// Write statistics
	WritePrivateProfileSection(L"Statistics", data.c_str(), iniFile);
}

/*
** Prepares in order to use the new APIs which are available on Vista or newer.
**
*/
void CMeasureNet::InitializeNewApi()
{
	if (CSystem::GetOSPlatform() >= OSPLATFORM_VISTA)
	{
		HMODULE IpHlpApiLibrary = GetModuleHandle(L"IpHlpApi.dll");
		if (IpHlpApiLibrary)
		{
			c_GetIfTable2 = (FPGETIFTABLE2)GetProcAddress(IpHlpApiLibrary, "GetIfTable2");
			c_FreeMibTable = (FPFREEMIBTABLE)GetProcAddress(IpHlpApiLibrary, "FreeMibTable");
		}

		if (!c_GetIfTable2 || !c_FreeMibTable)
		{
			c_GetIfTable2 = NULL;
			c_FreeMibTable = NULL;
		}
	}

	if (Rainmeter->GetDebug())
	{
		UpdateIFTable();
	}
}

/*
** Frees the resources.
**
*/
void CMeasureNet::FinalizeNewApi()
{
	if (c_GetIfTable2)
	{
		if (c_Table)
		{
			c_FreeMibTable(c_Table);
		}

		c_GetIfTable2 = NULL;
		c_FreeMibTable = NULL;
	}
	else
	{
		delete [] c_Table;
	}
	c_Table = NULL;
	c_NumOfTables = 0;
}
