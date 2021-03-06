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

#if !defined(AFX_TRANSFERSOCKET_H__3F95A3A8_478E_45D4_BFD5_6102B42E12DA__INCLUDED_)
#define AFX_TRANSFERSOCKET_H__3F95A3A8_478E_45D4_BFD5_6102B42E12DA__INCLUDED_

#include "FtpListResult.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransferSocket.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Befehlsziel CTransferSocket 

#include "controlsocket.h"
#include "ApiLog.h"

class CFtpControlSocket;
class CAsyncProxySocketLayer;
class CAsyncSslSocketLayer;
class CAsyncGssSocketLayer;

#define SPEED_SECONDS		60

class CTransferSocket : public CAsyncSocketEx, public CApiLog
{
// Attribute
public:
	CFtpListResult *m_pListResult;

// Operationen
public:
	CTransferSocket(CFtpControlSocket *pOwner, int nMode);
	virtual ~CTransferSocket();

// Überschreibungen
public:
	int m_nInternalMessageID;
	virtual void Close();
	virtual BOOL Create(BOOL bUseSsl);
	BOOL m_bListening;
	CFile *m_pFile;
	t_transferdata m_transferdata;
	void SetActive();
	int CheckForTimeout(int delay);
	void UseGSS(CAsyncGssSocketLayer *pGssLayer);
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CTransferSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CTransferSocket)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG

// Implementierung
protected:
	
	virtual int OnLayerCallback(const CAsyncSocketExLayer *pLayer, int nType, int nParam1, int nParam2);

	CFtpControlSocket *m_pOwner;
	CAsyncProxySocketLayer* m_pProxyLayer;
	CAsyncSslSocketLayer* m_pSslLayer;
	CAsyncGssSocketLayer* m_pGssLayer;
	void UpdateRecvLed();
	void UpdateSendLed();
	void UpdateStatusBar(bool forceUpdate);
	BOOL m_bSentClose;
	char m_cLastChar;
	int m_ReadSize;
	int m_ReadPos;
	char *m_ReadBuffer;
	int m_bufferpos;
	char *m_pBuffer;
	BOOL m_bCheckTimeout;
	CTime m_LastActiveTime;
	BOOL m_bOK;
	CTime m_StartTime;
	BOOL m_nTransferState;
	int m_nMode;
	int m_nNotifyWaiting;
	BOOL m_bShutDown;

	void Transfered(int count, CTime time);

	DWORD m_Transfered[SPEED_SECONDS];
	bool m_UsedForTransfer[SPEED_SECONDS];
	CTime m_TransferedFirst;
	LARGE_INTEGER m_LastUpdateTime;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_TRANSFERSOCKET_H__3F95A3A8_478E_45D4_BFD5_6102B42E12DA__INCLUDED_
