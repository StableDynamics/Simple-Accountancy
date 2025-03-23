#include "Windows_SelectFiles.h"

#include "TextConversion.h"
#include "Windows_CIDSampleFiles.h"

#include <combaseapi.h>
#include <objbase.h>
#include <ShObjIdl_core.h>
#include <shtypes.h>
#include <stdexcept>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>



const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
    {L"Comma Seperated Variable (*.csv)",       L"*.csv"} // Only csv is allowed
};

// Indices of file types
#define INDEX_CSV 1

std::vector<std::string> getCSV()
{
    // Create object that stores the filepath(s)
    std::vector<std::string> filePathVec;
    // CoCreate the File Open Dialog object.
    IFileOpenDialog* pfd = NULL;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE); // Opens thread for GUI, not sure if all flags are needed but used in the Common Dialog Item Example
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    if (SUCCEEDED(hr))
    {
        // Create an event handling object, and hook it up to the dialog.
        IFileDialogEvents* pfde = NULL;
        hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
        if (SUCCEEDED(hr))
        {
            // Hook up the event handler.
            DWORD dwCookie;
            hr = pfd->Advise(pfde, &dwCookie);
            if (SUCCEEDED(hr))
            {
                // Set the options on the dialog.
                DWORD dwFlags;

                // Before setting, always get the options first in order 
                // not to override existing options.
                hr = pfd->GetOptions(&dwFlags);
                if (SUCCEEDED(hr))
                {
                    // In this case, get shell items only for file system items, and specify multi select
                    hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT);
                    if (SUCCEEDED(hr))
                    {
                        // Set the file types to display only. 
                        // Notice that this is a 1-based array.
                        hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
                        if (SUCCEEDED(hr))
                        {
                            // Set the selected file type index to csvs.
                            hr = pfd->SetFileTypeIndex(INDEX_CSV);
                            if (SUCCEEDED(hr))
                            {
                                // Set the default extension to be ".csv" file.
                                hr = pfd->SetDefaultExtension(L"csv");
                                if (SUCCEEDED(hr))
                                {
                                    // Show the dialog
                                    hr = pfd->Show(NULL);
                                    if (SUCCEEDED(hr))
                                    {
                                        // Obtain the result once the user clicks 
                                        // the 'Open' button.
                                        // The result is an IShellItemArray object.
                                        IShellItemArray* psiaResults;
                                        hr = pfd->GetResults(&psiaResults);
                                        if (SUCCEEDED(hr))
                                        {
                                            // Retrieve amount of items that the user selected
                                            DWORD resMax;
                                            DWORD resIdx{ 0 };
                                            hr = psiaResults->GetCount(&resMax);
                                            if (SUCCEEDED(hr))
                                            {
                                                // Iterate through those items, note it is a 1 based array
                                                for (size_t i = 1; i <= resMax; i++)
                                                {
                                                    IShellItem* shellItem;
                                                    hr = psiaResults->GetItemAt(resIdx, &shellItem);
                                                    if (SUCCEEDED(hr))
                                                    {
                                                        PWSTR pszFilePath;
                                                        hr = shellItem->GetDisplayName(SIGDN_FILESYSPATH,
                                                            &pszFilePath);

                                                        // Convert to string and add to filePathVec
                                                        filePathVec.emplace_back(wc_tToString(pszFilePath));
                                                    }
                                                    shellItem->Release();
                                                    resIdx++;
                                                }
                                            }
                                            psiaResults->Release();
                                        }
                                    }
                                    else
                                    {
                                        throw std::runtime_error("User did not select file.");
                                    }
                                }
                            }
                        }
                    }
                }
                // Unhook the event handler.
                pfd->Unadvise(dwCookie);
            }
            pfde->Release();
        }
        pfd->Release();
    }
    CoUninitialize(); // Closes thread 
    
    return filePathVec;
}