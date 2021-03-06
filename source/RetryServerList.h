// FileZilla - a Windows ftp client

// Copyright (C) 2002 - Tim Kosse <tim.kosse@gmx.de>

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// RetryServerList.h: Schnittstelle f�r die Klasse CRetryServerList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RETRYSERVERLIST_H__88E61DD3_4782_40F3_B551_AA00B1AF988C__INCLUDED_)
#define AFX_RETRYSERVERLIST_H__88E61DD3_4782_40F3_B551_AA00B1AF988C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	t_server server;
	CTime time;
} t_retryserver;

class CRetryServerList  
{
public:
	BOOL StillWait(const t_server &server);
	void AddServer(const t_server &server);
	CRetryServerList();
	virtual ~CRetryServerList();
private:
	std::list<t_retryserver> m_List;
};

#endif // !defined(AFX_RETRYSERVERLIST_H__88E61DD3_4782_40F3_B551_AA00B1AF988C__INCLUDED_)
