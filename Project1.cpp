// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include <afxinet.h>
#include <conio.h>
#include <thread>
#include <chrono>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWinApp theApp;

using namespace std;
BOOL RequestHTTP()
{
	BOOL bResult = FALSE;
	CInternetSession session;

	CHttpConnection* pConnection = NULL;
	try
	{
		pConnection = (CHttpConnection*)session.GetHttpConnection(_T("httpbin.org"), (INTERNET_PORT)INTERNET_DEFAULT_HTTP_PORT);

		if (pConnection)
		{
			CHttpFile* pHTTPFile = NULL;

			pHTTPFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, _T("/get"));
			if (pHTTPFile)
			{
			
				bResult = pHTTPFile->SendRequest(NULL, NULL, 0);
				if (bResult)
				{
					CString strResponse;
					char* pszBuff = new char[1025];
					int nRead = 0;
					while ((nRead = pHTTPFile->Read(pszBuff, 1024)) > 0)
					{
						pszBuff[nRead] = 0;
						strResponse += pszBuff;

					};

					delete[] pszBuff;

					wcout << LPCTSTR(strResponse) << endl;
					bResult = TRUE;
				}

				pHTTPFile->Close();

				delete pHTTPFile;
			}

			pConnection->Close();
			delete pConnection;
		}
	}
	catch (CInternetException* pEx)
	{
		pConnection = NULL;
		pEx->Delete();
	}

	session.Close();


	return bResult;
}
int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
			char key;
			while (true) {
				bool val = RequestHTTP();
				this_thread::sleep_for(chrono::seconds(5));
				if (_kbhit()) {
					key = _getch();
					if (key == 'e') {
						break;
					}
				}
			}
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
