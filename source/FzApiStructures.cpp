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

#include "stdafx.h"
#include "FzApiStructures.h"

t_server::t_server()
{
	nPasv = 0;
	nTimeZoneOffset = 0;
}

t_server::~t_server()
{
}

const bool operator == (const t_server &a,const t_server &b)
{
	if (a.host!=b.host)
		return false;
	if (a.port!=b.port)
		return false;
	if (a.user!=b.user)
		return false;
	if (a.pass!=b.pass && a.user!="anonymous")
		return false;
	if (a.nServerType!=b.nServerType)
		return false;
	if (a.nPasv != b.nPasv)
		return false;
	if (a.nTimeZoneOffset != b.nTimeZoneOffset)
		return false;
	return true;
}

const bool operator != (const t_server &a,const t_server &b)
{
	if (a.host!=b.host)
		return true;
	if (a.port!=b.port)
		return true;
	if (a.user!=b.user)
		return true;
	if (a.pass!=b.pass && a.user!="anonymous")
		return true;
	if (a.nServerType!=b.nServerType)
		return true;
	if (a.nPasv != b.nPasv)
		return true;
	if (a.nTimeZoneOffset != b.nTimeZoneOffset)
		return true;
	return false;
}

bool t_server::operator<(const t_server &op) const
{
	if (host<op.host)
		return true;
	if (port<op.port)
		return true;
	if (user<op.user)
		return true;
	if (pass<op.pass)
		return true;
	if (nServerType<op.nServerType)
		return true;
	if (nPasv < op.nPasv)
		return true;
	if (nTimeZoneOffset < op.nTimeZoneOffset)
		return true;

	return false;
}