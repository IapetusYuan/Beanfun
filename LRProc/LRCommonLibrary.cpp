#include "LRCommonLibrary.h"

//Create File Map to share memory
//https://docs.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory
int LRConfigFileMap::WrtieConfigFileMap(LRProfile *profile)
{
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szConfigFileMap);                 // name of mapping object
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return 1;
	if (hMapFile == NULL)
	{
		MessageBox(NULL, TEXT("Could not create file mapping object."), NULL, NULL);
		return 1;
	}
	pBuf = (LRProfile*)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_WRITE, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		MessageBox(NULL, TEXT("Could not map view of file."), NULL, NULL);

		CloseHandle(hMapFile);

		return 1;
	}

	CopyMemory((PVOID)pBuf, profile, BUF_SIZE);
	
	return 0;
}

int LRConfigFileMap::ReadConfigFileMap(LRProfile* profile)
{
	hMapFile = OpenFileMapping(
		FILE_MAP_READ,   // read/write access
		FALSE,                 // do not inherit the name
		szConfigFileMap);               // name of mapping object

	if (hMapFile == NULL)
	{
		MessageBox(NULL, TEXT("Could not open file mapping object."), NULL, NULL);
		return 1;
	}

	pBuf = (LRProfile*)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_READ,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		MessageBox(NULL, TEXT("Could not map view of file."), NULL, NULL);

		CloseHandle(hMapFile);

		return 1;
	}
	//CopyMemory(&settings, pBuf, BUF_SIZE);
	//settings.CodePage=pBuf->CodePage;
	//MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
	CopyMemory(profile, pBuf, BUF_SIZE);
	return 0;
}

void LRConfigFileMap::FreeConfigFileMap()
{
	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);
}