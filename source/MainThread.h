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

/*CMainThread
Main thread of FileZilla. Processes the command messages passed by the main window
*/

#include "DirectoryCache.h"	// Hinzugefügt von der Klassenansicht
#pragma once

#include "controlsocket.h"
#include "SFtpControlSocket.h"
#include "FtpControlSocket.h"
#include "structures.h"	// Hinzugefügt von der Klassenansicht
#include "FileZillaApi.h"	// Hinzugefügt von der Klassenansicht
#include "ApiLog.h"

/////////////////////////////////////////////////////////////////////////////
// Thread CMainThread 

#define FZAPI_THREADMSG_PROCESSREPLY 0
#define FZAPI_THREADMSG_COMMAND 1
#define FZAPI_THREADMSG_TRANSFEREND 2
#define FZAPI_THREADMSG_CANCEL 3
#define FZAPI_THREADMSG_DISCONNECT 4
#define FZAPI_THREADMSG_ASYNCREQUESTREPLY 5
#define FZAPI_THREADMSG_POSTKEEPALIVE 6

class CIdentServerControl;
class CMainThread : public CApiLog
{
protected:
	CMainThread();           // Dynamische Erstellung verwendet geschützten Konstruktor

// Attribute
public:

// Operationen
public:
	DWORD m_dwThreadId;
	HANDLE m_hThread;
	static CMainThread *Create(int nPriority = THREAD_PRIORITY_NORMAL, DWORD dwCreateFlags = 0);
	CServerPath GetWorkingDirPath();
	void SetWorkingDir(t_directory *pWorkingDir);
	BOOL GetWorkingDir(t_directory* pWorkingDir);
	void SetOption(int nOption, int nValue);
	int GetOption(int nOption);
	t_command m_LastCommand;
	CDirectoryCache *m_pDirectoryCache;
	void SetCurrentPath(CServerPath path);
	void Quit();
	BOOL GetCurrentServer(t_server &server);
	BOOL GetCurrentPath(CServerPath &dir);
	void SetConnected(BOOL bConnected = TRUE);
	BOOL m_bConnected;
	void SetBusy(BOOL bBusy);
	BOOL LastOperationSuccessful();
	void Command(const t_command& command);
	BOOL IsBusy();
	HWND m_hOwnerWnd;
	BOOL m_bBusy;
	unsigned int m_nReplyMessageID;
	unsigned int m_nInternalMessageID;
	BOOL IsConnected();
	__int64 GetAsyncRequestID() const;
	__int64 GetNextAsyncRequestID();
	virtual int OnThreadMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	DWORD SuspendThread();
	DWORD ResumeThread();
	BOOL PostThreadMessage( UINT message , WPARAM wParam, LPARAM lParam);

	BOOL IsValid() const;

protected:
	BOOL InitInstance();
	DWORD ExitInstance();
	DWORD Run();
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);

	CCriticalSection m_CriticalSection;
	void ShowStatus(CString status,int type);
	void ShowStatus(UINT nID, int type);

	CControlSocket *m_pControlSocket;
	CFtpControlSocket *m_pFtpControlSocket;
	CSFtpControlSocket *m_pSFtpControlSocket;
	__int64 m_nAsyncRequestID;
	void OnTimer(WPARAM wParam,LPARAM lParam);
// Überschreibungen

// Implementierung
protected:
	CIdentServerControl *m_pIdentServer;
	t_directory *m_pWorkingDir;
	std::map<int, int> m_Options;
	BOOL m_bQuit;
	t_command *m_pPostKeepAliveCommand;
	CServerPath m_CurrentPath;
	UINT m_nTimerID;
	virtual ~CMainThread();
	CEvent m_EventStarted;
};

/////////////////////////////////////////////////////////////////////////////
