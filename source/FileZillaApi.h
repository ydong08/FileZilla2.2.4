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

// FileZillaApi.h: Schnittstelle f�r die Klasse CFileZillaApi.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEZILLAAPI_H__F1970156_455F_4495_A813_4B676F0F03E5__INCLUDED_)
#define AFX_FILEZILLAAPI_H__F1970156_455F_4495_A813_4B676F0F03E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FzApiStructures.h"
#include "AsyncSslSocketLayer.h"

//This structure holds the commands which will be processed by the api.
//You don't have to fill this struct, you may use the command specific 
//functions which is easier.
//See below for a list of supported commands and their parameters.
typedef struct
{
	int id; //Type of command, see below
	CString param1; //Parameters for this command
	CString param2;
	int	param4;
	CServerPath path;
	CServerPath newPath; //Used for rename
	t_transferfile transferfile;
	t_server server;
} t_command;

//Description of all api commands
#define FZ_COMMAND_CONNECT 0x0001
//Connects to the server passed in t_command::server
//Possible return values:
//FZ_REPLY_BUSY, FZ_REPLY_ERROR, FZ_REPLY_INVALIDPARAM, 
//FZ_REPLY_NOTINITIALIZED, FZ_REPLY_OK, FZ_REPLY_WOULDBLOCK 

#define FZ_COMMAND_LIST 0x0002
//Lists the contents of a directory. If no parameter is given, the current
//directory will be listed, else t_command::path specifies the directory
//which contents will be listed. t_command::param1 may specify the name
//of a direct child or parent directory (Use only the last path segment or 
//".."). When the directory listing is successful, it will be sent to the
//owner window (see FZ_DATA_LIST)
//t_command::param4 controls the list mode. (See list modes section)
//Possible return values:
//FZ_REPLY_BUSY, FZ_REPLY_ERROR, FZ_REPLY_INVALIDPARAM, 
//FZ_REPLY_NOTCONNECTED, FZ_REPLY_NOTINITIALIZED, FZ_REPLY_OK,
//FZ_REPLY_WOULDBLOCK

#define FZ_COMMAND_FILETRANSFER 0x0004
//Transfers the file specified with t_command::transferfile, see 
//t_transferfile for detailed information
//Possible return values:
//FZ_REPLY_BUSY, FZ_REPLY_ERROR, FZ_REPLY_INVALIDPARAM,
//FZ_REPLY_NOTCONNECTED, FZ_REPLY_NOTINITIALIZED, FZ_REPLY_OK,
//FZ_REPLY_WOULDBLOCK

#define FZ_COMMAND_DISCONNECT 0x0008
#define FZ_COMMAND_CUSTOMCOMMAND 0x0010
#define FZ_COMMAND_DELETE		0x0020
#define FZ_COMMAND_REMOVEDIR	0x0040
#define FZ_COMMAND_RENAME		0x0080
#define FZ_COMMAND_MAKEDIR		0x0100
#define FZ_COMMAND_CHMOD		0x0200

#define FZ_MSG_OFFSET 16
#define FZ_MSG_OFFSETMASK 0xFFFF
#define FZ_MSG_ID(x) ((x >> FZ_MSG_OFFSET) & FZ_MSG_OFFSETMASK)
#define FZ_MSG_PARAM(x) ( x & FZ_MSG_OFFSETMASK)
#define FZ_MSG_MAKEMSG(id, param) ((((DWORD)(id & FZ_MSG_OFFSETMASK)) << FZ_MSG_OFFSET) + (param & FZ_MSG_OFFSETMASK) )

#define FZ_MSG_REPLY			0
#define FZ_MSG_LISTDATA			1
#define FZ_MSG_SOCKETSTATUS		3
#define FZ_MSG_SECURESERVER		4
#define FZ_MSG_ASYNCREQUEST		5
#define FZ_MSG_STATUS			6
#define FZ_MSG_TRANSFERSTATUS	7
#define FZ_MSG_QUITCOMPLETE		8

#define FZ_ASYNCREQUEST_OVERWRITE 1
#define FZ_ASYNCREQUEST_VERIFYCERT 2
#define FZ_ASYNCREQUEST_GSS_AUTHFAILED 3
#define FZ_ASYNCREQUEST_GSS_NEEDPASS 4
#define FZ_ASYNCREQUEST_NEWHOSTKEY 5
#define FZ_ASYNCREQUEST_CHANGEDHOSTKEY 6
#define FZ_ASYNCREQUEST_KEYBOARDINTERACTIVE 7
#define FZ_ASYNCREQUEST_GSS_NEEDUSER 8

class CAsyncRequestData
{
public:
	CAsyncRequestData();
	virtual ~CAsyncRequestData();
	int nRequestType;
	__int64 nRequestID; //Unique for every request sent
	int nRequestResult;
};

class COverwriteRequestData : public CAsyncRequestData
{
public:
	COverwriteRequestData();
	virtual ~COverwriteRequestData();
	CString FileName1;
	CString FileName2;
	CString path1,path2;
	__int64 size1;
	__int64 size2;
	CTime *time1;
	CTime *time2;
	const t_transferfile *pTransferFile;
};

class CVerifyCertRequestData : public CAsyncRequestData
{
public:
	CVerifyCertRequestData();
	virtual ~CVerifyCertRequestData();
	t_SslCertData *pCertData;
};

class CGssNeedPassRequestData : public CAsyncRequestData
{
public:
	CGssNeedPassRequestData();
	virtual ~CGssNeedPassRequestData();
	CString pass;
	int nOldOpState;
};

class CGssNeedUserRequestData : public CAsyncRequestData
{
public:
	CGssNeedUserRequestData();
	virtual ~CGssNeedUserRequestData();
	CString user;
	int nOldOpState;
};

class CNewHostKeyRequestData : public CAsyncRequestData
{
public:
	CNewHostKeyRequestData();
	virtual ~CNewHostKeyRequestData();
	CString Hostkey;
};

class CChangedHostKeyRequestData : public CAsyncRequestData
{
public:
	CChangedHostKeyRequestData();
	virtual ~CChangedHostKeyRequestData();
	CString Hostkey;
};

class CKeyboardInteractiveRequestData : public CAsyncRequestData
{
public:
	char data[20480];
};

#define FZ_SOCKETSTATUS_RECV 0
#define FZ_SOCKETSTATUS_SEND 1

#define FZAPI_OPTION_SHOWHIDDEN 1


#define FTP_CONNECT 0 // SERVER USER PASS PORT
#define FTP_COMMAND 1 //COMMAND - - -
#define FTP_LIST 2 //- - - -
#define FTP_FILETRANSFER 3 //TRANSFERFILE
#define FTP_DISCONNECT 4 //- - - -
#define FTP_RECONNECT 5 //- - - -
#define FTP_LISTCACHE 6 //- - - - Directory listing may be read from cache
#define FTP_DELETE 7 //FILENAME
#define FTP_REMOVEDIR 8 //DIRNAME

#define FZ_REPLY_OK					0x0001
#define FZ_REPLY_WOULDBLOCK			0x0002
#define FZ_REPLY_ERROR				0x0004
#define FZ_REPLY_OWNERNOTSET		0x0008
#define FZ_REPLY_INVALIDPARAM		0x0010
#define FZ_REPLY_NOTCONNECTED		0x0020
#define FZ_REPLY_ALREADYCONNECTED	0x0040
#define FZ_REPLY_BUSY				0x0080
#define FZ_REPLY_IDLE				0x0100
#define FZ_REPLY_NOTINITIALIZED		0x0200
#define FZ_REPLY_ALREADYINIZIALIZED	0x0400
#define FZ_REPLY_CANCEL				0x0800
#define FZ_REPLY_DISCONNECTED		0x1000 //Always sent when disconnected from server
#define FZ_REPLY_CRITICALERROR		0x2000 //Used for FileTransfers only
#define FZ_REPLY_ABORTED			0x4000 //Used for FileTransfers only
#define FZ_REPLY_NOTSUPPORTED		0x8000 //Command is not supported for the current server

#define FZ_LIST_USECACHE			0x0001
#define FZ_LIST_FORCECACHE			0x0002
#define FZ_LIST_REALCHANGE			0x0004
#define FZ_LIST_EXACT   			0x0008

//Additional replies
#define FZ_REPLY_NOTBUSY FZ_REPLY_IDLE


//Servertypes

//General types

#define FZ_SERVERTYPE_HIGHMASK  0x0F00
#define FZ_SERVERTYPE_SUBMASK	0x000F
#define FZ_SERVERTYPE_LAYERMASK 0x00F0

#define FZ_SERVERTYPE_FTP		0x0100
#define FZ_SERVERTYPE_LOCAL		0x0200

#define FZ_SERVERTYPE_LAYER_SSL_IMPLICIT 0x0010
#define FZ_SERVERTYPE_LAYER_SSL_EXPLICIT 0x0020
#define FZ_SERVERTYPE_LAYER_TLS_EXPLICIT 0x0040

#define FZ_SERVERTYPE_SUB_FTP_VMS		0x0001
#define FZ_SERVERTYPE_SUB_FTP_SFTP		0x0002
#define FZ_SERVERTYPE_SUB_FTP_WINDOWS	0x0004
#define FZ_SERVERTYPE_SUB_FTP_UNKNOWN	0x0008

//Log messages
#define FZ_LOG_STATUS 0
#define FZ_LOG_ERROR 1
#define FZ_LOG_COMMAND 2
#define FZ_LOG_REPLY 3
#define FZ_LOG_LIST 4
//By calling CFileZillaApi::SetDebugLevel, the aplication can enable loggint of the following messages:
#define FZ_LOG_APIERROR 5
#define FZ_LOG_WARNING 6
#define FZ_LOG_INFO 7
#define FZ_LOG_DEBUG 8

class CMainThread;
class CFileZillaApi  
{
public:
	BOOL IsValid() const;
	int GetOption( int nOption, int &value );
	int SetOption( int nOption, int value );
	int SetDebugLevel( int nDebugLevel );

	int CustomCommand(CString command);
	int Delete(CString FileName, const CServerPath &path = CServerPath());
	int RemoveDir(CString DirName, const CServerPath &path = CServerPath());
	int Rename(CString oldName,CString newName, const CServerPath &path = CServerPath(), const CServerPath &newPath = CServerPath());
	int MakeDir(const CServerPath &path);
	
	
	//Functions to reply to async requests

	//General reply function
	int SetAsyncRequestResult(int nAction, CAsyncRequestData *pData);
	
	int Command(t_command *pCommand);
	int Disconnect();
	void Destroy();
	int Cancel();
	int Chmod(int nValue, CString FileName, const CServerPath &path = CServerPath());
	CFileZillaApi();
	virtual ~CFileZillaApi();
	//Initialization
	int Init(HWND hOwnerWnd, int nReplyMessageID = 0);
	unsigned int GetMessageID();

	//Status
	int IsConnected();
	int IsBusy();
	
	//Operations
	int Connect(const t_server& server);
	
	int List(int nListMode=FZ_LIST_USECACHE); //Lists current folder
	int List(const CServerPath& path, int nListMode=FZ_LIST_USECACHE);
	int List(const CServerPath& parent, CString dirname, int nListMode=FZ_LIST_USECACHE);

	int FileTransfer(const t_transferfile &TransferFile);
	int GetCurrentServer(t_server &server);
	
	//Debugging functions
	static BOOL DumpDirectoryCache(LPCTSTR pFileName);
protected:
	CMainThread* m_pMainThread;
	unsigned int m_nInternalMessageID;
	BOOL m_bInitialized;
	unsigned int m_nReplyMessageID;
	HWND m_hOwnerWnd;
};

#endif // !defined(AFX_FILEZILLAAPI_H__F1970156_455F_4495_A813_4B676F0F03E5__INCLUDED_)