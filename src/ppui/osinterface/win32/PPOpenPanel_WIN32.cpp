#include <windows.h>
#ifdef _WIN32_WCE
	#include <Commdlg.h>
#endif
#include <tchar.h>
#include "OSInterface\PPOpenPanel.h"

extern HWND hWnd;

PPOpenPanel::PPOpenPanel(PPScreen* screen, const char* caption) :
	PPModalDialog(screen)
{
}

PPOpenPanel::~PPOpenPanel()
{
}

void PPOpenPanel::addExtension(const PPString& ext, const PPString& desc)
{
	Descriptor* d = new Descriptor(ext, desc);

	items.add(d);
}

PPOpenPanel::ReturnCodes PPOpenPanel::runModal()
{
	TCHAR			szFile[MAX_PATH+1];
	OPENFILENAME	ofn;
	
	memset(szFile, 0, sizeof(szFile));
	memset(&ofn, 0, sizeof(ofn));
	
	ofn.lStructSize   = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;

	if (items.size() == 1)
		ofn.nFilterIndex = 0;
	else if (items.size() > 1)
		ofn.nFilterIndex = items.size()+1;

	PPString sourceFilter;

	pp_int32 i = 0;

	// single types
	for (i = 0; i < items.size(); i++)
	{
		sourceFilter.append(items.get(i)->description);
		sourceFilter.append(" (.");
		sourceFilter.append(items.get(i)->extension);
		sourceFilter.append(")|");
		sourceFilter.append("*.");
		sourceFilter.append(items.get(i)->extension);
		sourceFilter.append("|");
	}

	// all supported types
	if (items.size() > 1)
	{
		sourceFilter.append("All supported types|");
		for (i = 0; i < items.size(); i++)		
		{
			sourceFilter.append("*.");
			sourceFilter.append(items.get(i)->extension);
			if (i < items.size()-1) 
				sourceFilter.append(";");
		}
		sourceFilter.append("|");
	}

	// all files
	sourceFilter.append("All files (*.*)|");
	sourceFilter.append("*.*");
	sourceFilter.append("|");

	const char* src = sourceFilter;

	TCHAR* dstFilter = new TCHAR[sourceFilter.length()+2];
	memset(dstFilter, 0, (sourceFilter.length()+2)*sizeof(TCHAR));
	
	for (i = 0; i < (signed)sourceFilter.length(); i++)
	{
		if (src[i] == '|')
			dstFilter[i] = '\0';
		else
			dstFilter[i] = src[i];
	}

	ofn.lpstrFilter = dstFilter;
	ofn.lpstrTitle = _T("Open File");
	ofn.Flags = OFN_EXPLORER;

	ReturnCodes err = ReturnCodeCANCEL;

	if (GetOpenFileName(&ofn))
	{
		fileName = szFile;
		err = ReturnCodeOK;
	}

	delete[] dstFilter;
	
	return err;
}
