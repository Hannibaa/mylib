/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                  Open Dialogue for Console Application                    *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 * URL :                                                                     *
 *                                                                           *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the                                                           *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/


#pragma once

#include <windows.h>
#include <shobjidl.h>
#include <ShlObj.h>
#include <string>


_COMDLG_FILTERSPEC default_ext[]{
    { L"default *.*" ,L"*.*" }
    ,{L"Application *.exe", L"*.exe"}
};

_COMDLG_FILTERSPEC empty_ext { L"",L"" };


namespace opendialog {

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     NOT USED OPENDIALOGBOX - --- -
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::wstring GetFileName()
    {
        //create pointer to wchar_t string for path name file;
        PWSTR pszFilePath;

        // create wstring for return type
        std::wstring filepath;

        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
            COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            IFileOpenDialog* pFileOpen;

            // Create the FileOpenDialog object.
            hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

            pFileOpen->SetTitle(L"Get The Name Of File");
            pFileOpen->SetFileTypes(2, default_ext);

            if (SUCCEEDED(hr))
            {
                // Show the Open dialog box.
                hr = pFileOpen->Show(NULL);

                // Get the file name from the dialog box.
                if (SUCCEEDED(hr))
                {
                    IShellItem* pItem;
                    hr = pFileOpen->GetResult(&pItem);
                    if (SUCCEEDED(hr))
                    {
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                        // put file name in string
                        filepath = pszFilePath;
                        // Display the file name to the user.
                       /* if (SUCCEEDED(hr))
                        {
                            MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        }*/
                        CoTaskMemFree(pszFilePath);
                        pItem->Release();
                    }
                }
                pFileOpen->Release();
            }
            CoUninitialize();
        }
        return filepath;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     SAVE DIALOGUE BOX - ANOTHER DIALOGUE BOX -
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::pair<std::wstring, std::wstring>
        SaveFile(const wchar_t* title, const wchar_t* extansion)
    {
        PWSTR pszFilePath;

        std::wstring path, folder;

        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

        if (SUCCEEDED(hr))
        {
            IFileSaveDialog* pFileSave;

            // Create the filesavedialog object.
            hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
                IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

            pFileSave->SetTitle(L"Save File");
            pFileSave->SetDefaultExtension(extansion);
            //pFileSave->SetOptions(FOS_PICKFOLDERS);
            //pFileSave->SetOkButtonLabel(L"helloAk");

            if (SUCCEEDED(hr))
            {
                // show the open save dialogue box.
                hr = pFileSave->Show(NULL);

                if (SUCCEEDED(hr)) {

                    IShellItem* item;
                    IShellItem* item2;
                    hr = pFileSave->GetResult(&item);
                    if (SUCCEEDED(hr)) {

                        item->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                        path = pszFilePath;

                        CoTaskMemFree(pszFilePath);

                        item->Release();
                    }

                    hr = pFileSave->GetFolder(&item2);
                    if (SUCCEEDED(hr)) {

                        item2->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                        folder = pszFilePath;

                        CoTaskMemFree(pszFilePath);

                        item2->Release();
                    }

                }

                pFileSave->Release();
            }

            CoUninitialize();
        }

        return std::make_pair(path, folder);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     OPEN FILE DIALOG BOX - ANOTHER DIALOGUE BOX -
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::wstring OpenFile(const wchar_t* title = L"File", const _COMDLG_FILTERSPEC extensions = empty_ext)
    {
        //Extension Array

        _COMDLG_FILTERSPEC ext2[]{
        { L"default *.*" ,L"*.*" }
        ,{L"Application *.exe", L"*.exe"}
        ,extensions
        };

        //create pointer to wchar_t string for path name file;
        PWSTR pszFilePath;

        // create wstring for return type
        std::wstring filepath;

        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
            COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            IFileOpenDialog* pFileOpen;

            // Create the FileOpenDialog object.
            hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

            // set option of file dialogue box

            pFileOpen->SetTitle(title);
            pFileOpen->SetFileTypes(3, ext2);

            // end of option

            if (SUCCEEDED(hr))
            {
                // Show the Open dialog box.
                hr = pFileOpen->Show(NULL);

                // Get the file name from the dialog box.
                if (SUCCEEDED(hr))
                {
                    IShellItem* pItem;
                    hr = pFileOpen->GetResult(&pItem);
                    if (SUCCEEDED(hr))
                    {
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                        // put file name in string
                        filepath = pszFilePath;
                        // Display the file name to the user.
                       /* if (SUCCEEDED(hr))
                        {
                            MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        }*/
                        CoTaskMemFree(pszFilePath);
                        pItem->Release();
                    }
                }
                pFileOpen->Release();
            }
            CoUninitialize();
        }
        return filepath;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     BROWSE FOLDER - FIRST APROCH -
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::wstring OpenFolder(const wchar_t* title)
    {
        //create pointer to wchar_t string for path name file;
        PWSTR pszFilePath;

        // create wstring for return type
        std::wstring filepath;

        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
            COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            IFileOpenDialog* pFileOpen;

            // Create the FileOpenDialog object.
            hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

            // Folder option for Folder Box
            pFileOpen->SetOptions(FOS_PICKFOLDERS);
            pFileOpen->SetTitle(title);

            if (SUCCEEDED(hr))
            {
                // Show the Open dialog box.
                hr = pFileOpen->Show(NULL);

                // Get the file name from the dialog box.
                if (SUCCEEDED(hr))
                {
                    IShellItem* pItem;
                    hr = pFileOpen->GetResult(&pItem);
                    if (SUCCEEDED(hr))
                    {
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                        // put file name in string
                        filepath = pszFilePath;
                        // Display the file name to the user.
                       /* if (SUCCEEDED(hr))
                        {
                            MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        }*/
                        CoTaskMemFree(pszFilePath);
                        pItem->Release();
                    }
                }
                pFileOpen->Release();
            }
            CoUninitialize();
        }
        return filepath;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     BROWSE FOLDER - ANOTHER DIALOGUE BOX -
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::wstring BrowseFolder(std::string saved_path) {

        TCHAR path[MAX_PATH];

        const char* path_param = saved_path.c_str();

        BROWSEINFO bi = { 0 };

        bi.lpszTitle = (L"Brows for folder...");
        bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_BROWSEINCLUDEFILES;
        bi.lpfn = NULL;// BCallBackProc;
        bi.lParam = (LPARAM)path_param;

        LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

        if (pidl != 0) {
            // get the name of the folder and put it in path
            SHGetPathFromIDList(pidl, path);

            // free memory used
            IMalloc* imalloc = 0;
            if (SUCCEEDED(SHGetMalloc(&imalloc))) {
                imalloc->Free(pidl);
                imalloc->Release();
            }

            return std::wstring(path);
        }

        return L"";
    }


}
