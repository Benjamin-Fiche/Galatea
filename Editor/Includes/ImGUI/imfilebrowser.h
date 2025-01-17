﻿/*
MIT License

Copyright (c) 2019-2020 Zhuang Guan

https://github.com/AirGuanZ

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <array>
#include <cstring>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <Debug/Log.h>
#include <rttr/type.h>

#ifndef IMGUI_VERSION
#   error "include imgui.h before this header"
#endif

using ImGuiFileBrowserFlags = int;

enum ImGuiFileBrowserFlags_
{
    ImGuiFileBrowserFlags_SelectDirectory    = 1 << 0, // select directory instead of regular file
    ImGuiFileBrowserFlags_EnterNewFilename   = 1 << 1, // allow user to enter new filename when selecting regular file
    ImGuiFileBrowserFlags_NoModal            = 1 << 2, // file browsing window is modal by default. specify this to use a popup window
    ImGuiFileBrowserFlags_NoTitleBar         = 1 << 3, // hide window title bar
    ImGuiFileBrowserFlags_NoStatusBar        = 1 << 4, // hide status bar at the bottom of browsing window
    ImGuiFileBrowserFlags_CloseOnEsc         = 1 << 5, // close file browser when pressing 'ESC'
    ImGuiFileBrowserFlags_CreateNewDir       = 1 << 6, // allow user to create new directory
};

namespace ImGui
{
    class FileBrowser
    {
    public:

        // pwd is set to current working directory by default
        explicit FileBrowser(ImGuiFileBrowserFlags flags = ImGuiFileBrowserFlags_CreateNewDir);

        FileBrowser(const FileBrowser &copyFrom);

        FileBrowser &operator=(const FileBrowser &copyFrom);

        // set the window size (in pixels)
        // default is (700, 450)
        void SetWindowSize(int width, int height) noexcept;

        // set the window title text
        void SetTitle(std::string title);

        // open the browsing window
        //void Open();

        // close the browsing window
        //void Close();

        // display the browsing window if opened
        void Display();

        // returns true when there is a selected filename and the "ok" button was clicked
        bool HasSelected() const noexcept;

        // set current browsing directory
        bool SetPwd(const std::filesystem::path &pwd =
                                    std::filesystem::current_path());

        // returns selected filename. make sense only when HasSelected returns true
        std::filesystem::path GetSelected() const;

        // set selected filename to empty
        void ClearSelected();

        // set file type filters. eg. { ".h", ".cpp", ".hpp", ".cc", ".inl" }
        void SetTypeFilters(const std::vector<const char*> &typeFilters);

    private:
		void DisplayDriveChoice();
		void DisplayCurrentPathWay();
		void CurrentPathClick(int secIdx, int newPwdLastSecIdx);
		void OkButtonCreateFile(bool isUpdatable);
		void DisplayAddFileButton();
		void DisplayFileList(float reserveHeight, std::filesystem::path& newPwd, bool& setNewPwd);
		void DisplayOkButton();
		void DisplayCancelButton();
		void DisplayFilterCombo();

        void SetPwdUncatched(const std::filesystem::path &pwd);

#ifdef _WIN32
        static std::uint32_t GetDrivesBitMask();
#endif

        int width_;
        int height_;
        ImGuiFileBrowserFlags flags_;

        std::string title_;
        std::string openLabel_;

        bool ok_; // used to see if the user push the ok button in the FileBrowser

        std::string statusStr_;

        std::vector<const char*> typeFilters_;
        int typeFilterIndex_;

		std::filesystem::path originalPath_;
        std::filesystem::path pwd_;
        std::filesystem::path selectedFilename_;

        struct FileRecord
        {
            bool isDir = false;					// is the file a directory
            std::filesystem::path name;			// path of the file/folder ???
            std::string showName;				// name of the file/folder different form the path
            std::filesystem::path extension;	// type of the file/folder ???
        };
        std::vector<FileRecord> fileRecords_;

        // IMPROVE: truncate when selectedFilename_.length() > inputNameBuf_.size() - 1
        static constexpr size_t INPUT_NAME_BUF_SIZE = 512;
        std::unique_ptr<std::array<char, INPUT_NAME_BUF_SIZE>> inputNameBuf_;

        std::string openNewDirLabel_;
        std::unique_ptr<std::array<char, INPUT_NAME_BUF_SIZE>> newDirNameBuf_;

#ifdef _WIN32
        uint32_t drives_;
#endif
    };
} // namespace ImGui

#include "ImGUI/imfilebrowser.inl"