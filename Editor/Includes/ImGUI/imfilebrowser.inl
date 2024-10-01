#include "Editor/UserFileAdder.h"
#include "Editor/Windows/InspectorWindow.h"
#include "ComponentSystem/Component.h"
#include <rttr/type>
#include "Physic/Transform.h"
#include "ComponentSystem/Component.h"

using namespace Galatea;

inline ImGui::FileBrowser::FileBrowser(ImGuiFileBrowserFlags flags)
	: width_(700), height_(450), flags_(flags), ok_(false),
	inputNameBuf_(std::make_unique<std::array<char, INPUT_NAME_BUF_SIZE>>())
{
	if (flags_ & ImGuiFileBrowserFlags_CreateNewDir)
		newDirNameBuf_ = std::make_unique<
		std::array<char, INPUT_NAME_BUF_SIZE>>();

	inputNameBuf_->at(0) = '\0';
	SetTitle("file browser");
	SetPwd(std::filesystem::current_path());
	originalPath_ = std::filesystem::current_path();

	typeFilters_.clear();
	typeFilterIndex_ = 0;

#ifdef _WIN32
	drives_ = GetDrivesBitMask();
#endif
}

inline ImGui::FileBrowser::FileBrowser(const FileBrowser& copyFrom)
	: FileBrowser()
{
	*this = copyFrom;
}

inline ImGui::FileBrowser& ImGui::FileBrowser::operator=(
	const FileBrowser& copyFrom)
{
	flags_ = copyFrom.flags_;
	SetTitle(copyFrom.title_);

	//openFlag_ = copyFrom.openFlag_;
	//closeFlag_ = copyFrom.closeFlag_;
	ok_ = copyFrom.ok_;

	statusStr_ = "";
	originalPath_ = copyFrom.originalPath_;
	pwd_ = copyFrom.pwd_;
	selectedFilename_ = copyFrom.selectedFilename_;

	fileRecords_ = copyFrom.fileRecords_;

	*inputNameBuf_ = *copyFrom.inputNameBuf_;

	if (flags_ & ImGuiFileBrowserFlags_CreateNewDir)
	{
		newDirNameBuf_ = std::make_unique<
			std::array<char, INPUT_NAME_BUF_SIZE>>();
		*newDirNameBuf_ = *copyFrom.newDirNameBuf_;
	}

	return *this;
}

inline void ImGui::FileBrowser::SetWindowSize(int width, int height) noexcept
{
	assert(width > 0 && height > 0);
	width_ = width;
	height_ = height;
}

inline void ImGui::FileBrowser::SetTitle(std::string title)
{
	title_ = std::move(title);
	openLabel_ = title_ + "##filebrowser_" +
		std::to_string(reinterpret_cast<size_t>(this));
	openNewDirLabel_ = "new dir##new_dir_" +
		std::to_string(reinterpret_cast<size_t>(this));
}

inline void ImGui::FileBrowser::DisplayDriveChoice()
{
#ifdef _WIN32
	char currentDrive = static_cast<char>(pwd_.c_str()[0]);
	char driveStr[] = { currentDrive, ':', '\0' };

	PushItemWidth(4 * GetFontSize());
	if (BeginCombo("##select_drive", driveStr))
	{
		for (int i = 0; i < 26; ++i)
		{
			if (!(drives_ & (1 << i)))
				continue;
			char driveCh = static_cast<char>('A' + i);
			char selectableStr[] = { driveCh, ':', '\0' };
			bool selected = currentDrive == driveCh;
			if (Selectable(selectableStr, selected) && !selected)
			{
				char newPwd[] = { driveCh, ':', '\\', '\0' };
				SetPwd(newPwd);
			}
		}
		ImGui::EndCombo();
	}
	PopItemWidth();

	SameLine(); // ce qui suis correspond a l'affichage du chemin sur la meme ligne que le choix du disque dur
#endif
}


inline void ImGui::FileBrowser::DisplayCurrentPathWay()
{
	int secIdx = 0, newPwdLastSecIdx = -1;
	for (auto& sec : pwd_)
	{
#ifdef _WIN32
		if (secIdx == 1)
		{
			++secIdx;
			continue;
		}
#endif
		PushID(secIdx);
		if (secIdx > 0)
			SameLine();
		if (SmallButton(sec.u8string().c_str()))
			newPwdLastSecIdx = secIdx;
		PopID();
		++secIdx;
	}

	CurrentPathClick(secIdx, newPwdLastSecIdx);
	SameLine();

	if (SmallButton("*"))
		SetPwd(pwd_);
}

inline void ImGui::FileBrowser::CurrentPathClick(int secIdx, int newPwdLastSecIdx)
{
	if (newPwdLastSecIdx >= 0)
	{
		int i = 0;
		std::filesystem::path newPwd;
		for (auto& sec : pwd_)
		{
			if (i++ > newPwdLastSecIdx)
				break;
			newPwd /= sec;
		}
#ifdef _WIN32
		if (newPwdLastSecIdx == 0)
			newPwd /= "\\";
#endif
		SetPwd(newPwd);
	}
}

inline void ImGui::FileBrowser::OkButtonCreateFile(bool isUpdatable)
{
	if (Button("ok") && (*newDirNameBuf_)[0] != '\0')
	{
		std::string newFileName = pwd_.string();
		newFileName += std::string("\\") + newDirNameBuf_->data() + std::string(".h");
		std::ofstream ofs(newFileName);

		if (ofs.is_open())
		{
			std::string s = UserFileAdder::CreateNewComponentClass(newDirNameBuf_->data());
			ofs.write(s.c_str(), s.size());
			Galatea::LogMsg(newFileName + " created !\n");

			std::ofstream includeFile("Includes/UserInclude.h", std::ios::app);
			
			includeFile << "\n#include \"" << newDirNameBuf_->data() << std::string(".h\"\n");
		}
		else
			Galatea::LogError("failed to create " + newFileName + "\n");

		CloseCurrentPopup();
	}
}


inline void ImGui::FileBrowser::DisplayAddFileButton()
{
	if (newDirNameBuf_)
	{
		SameLine();
		if (SmallButton("+"))
		{
			OpenPopup(openNewDirLabel_.c_str());
			(*newDirNameBuf_)[0] = '\0';
		}
		if (BeginPopup(openNewDirLabel_.c_str()))
		{
			if (ImGui::BeginMenu("Create Component"))
			{
				InputText("name", newDirNameBuf_->data(), newDirNameBuf_->size());
				SameLine();
				OkButtonCreateFile(false);				
				EndMenu();
			}
			if (ImGui::BeginMenu("Create UpdatableComponent"))
			{
				InputText("name", newDirNameBuf_->data(), newDirNameBuf_->size());
				SameLine();
				OkButtonCreateFile(true);
				EndMenu();
			}
			EndPopup();
		}
	}
}

inline void ImGui::FileBrowser::DisplayFileList(float reserveHeight, std::filesystem::path& newPwd, bool& setNewPwd)
{
	BeginChild("ch", ImVec2(0, -reserveHeight), true,
		(flags_ & ImGuiFileBrowserFlags_NoModal) ?
		ImGuiWindowFlags_AlwaysHorizontalScrollbar : 0); // créer une fenetre enfant pour draw les nom des fichiers

	for (auto& rsc : fileRecords_)
	{
		if (!rsc.isDir && typeFilters_.size() > 0 &&							//check if ? is not a directory and if the filter size is > 0 
			static_cast<size_t>(typeFilterIndex_) < typeFilters_.size() &&		//check if typefilterIndex is coherent
			!(rsc.extension == typeFilters_[typeFilterIndex_]))					//extension tag security
			continue;

		if (!rsc.name.empty() && rsc.name.c_str()[0] == '$') //check if rsc name is empty or if the name start with a '$'
			continue;

		const bool selected = selectedFilename_ == rsc.name;
		if (Selectable(rsc.showName.c_str(), selected, ImGuiSelectableFlags_DontClosePopups)) // create a ImGui::Selectable
		{
			if (selected)
			{
				selectedFilename_ = std::filesystem::path();
				(*inputNameBuf_)[0] = '\0';
			}
			else if (rsc.name != "..") // if the rsc isn't the return to parent directory
			{
				// check if the flag choosed correspond with the selection
				if ((rsc.isDir && (flags_ & ImGuiFileBrowserFlags_SelectDirectory)) ||  
					(!rsc.isDir && !(flags_ & ImGuiFileBrowserFlags_SelectDirectory))) 
				{
					selectedFilename_ = rsc.name;
					if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory))
					{
#ifdef _MSC_VER
						strcpy_s(inputNameBuf_->data(), inputNameBuf_->size(),
							selectedFilename_.u8string().c_str());
#else
						std::strncpy(inputNameBuf_->data(), selectedFilename_.u8string().c_str(),
							inputNameBuf_->size());
#endif
					}
				}
			}
		}

		if (IsItemClicked(0) && IsMouseDoubleClicked(0) && rsc.isDir) //checking if double click on a folder 
		{
			setNewPwd = true;
			newPwd = (rsc.name != "..") ? (pwd_ / rsc.name) : pwd_.parent_path(); //
		}
	}
	EndChild();
}

inline void ImGui::FileBrowser::DisplayOkButton()
{
	if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory))
	{
		if (Button(" Add Component ") && !selectedFilename_.empty())
		{
			ok_ = true;
			CloseCurrentPopup();

			std::string name = selectedFilename_.generic_string();
			if (name.find(".h") != std::string::npos)
			{
				name.pop_back(); //pop_back 2 time to pop the .h
				name.pop_back();

				rttr::library lib("User");

				if (!lib.load())
				{
					std::cerr << lib.get_error_string() << std::endl;
					return;
				}

				for (rttr::type t : lib.get_types())
				{
					if (t.get_name() != (name + '*'))
						continue;
					 
					//verifying if we have a gameobject to add the component
					if (t.is_valid() && Galatea::InspectorWindow::gameObject != nullptr)
					{
						//create a rttr::variant from the type to get our class
						auto var = t.get_constructor().invoke(); //t.create();
						Component* c = var.get_value<Component*>();
						InspectorWindow::gameObject->AddComponent(c); //Adding the new component
					}
					else
						std::cout << "error with class or gameobject\n" << t.is_class() << " " << t.get_name() << "\n";
				}
			}
			
		}
	}
	else
	{
		if (selectedFilename_.empty())
		{
			if (Button(" ok "))
			{
				ok_ = true;
				CloseCurrentPopup();
			}
		}
		else if (Button("open"))
			SetPwd(pwd_ / selectedFilename_);
	}
	SameLine();
}

inline void ImGui::FileBrowser::DisplayCancelButton()
{
	int escIdx = GetIO().KeyMap[ImGuiKey_Escape];
	if (Button("cancel") ||
		((flags_ & ImGuiFileBrowserFlags_CloseOnEsc) &&
			IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
			escIdx >= 0 && IsKeyPressed(escIdx)))
		CloseCurrentPopup();
}

inline void ImGui::FileBrowser::DisplayFilterCombo()
{
	//if the typeFilters list is not empty print a ImGui::Combo to select the filter to use
	if (!typeFilters_.empty())
	{
		SameLine();
		PushItemWidth(8 * GetFontSize());
		Combo("##type_filters", &typeFilterIndex_,
			typeFilters_.data(), int(typeFilters_.size()));
		PopItemWidth();
	}
}

inline void ImGui::FileBrowser::Display()
{
	PushID(this);
	// display elements in pwd /// Corespond au display du choix du disque dur TODO a retirer
	//DisplayDriveChoice();

	DisplayCurrentPathWay();

	DisplayAddFileButton();

	//calcul height of the browserfile
	float reserveHeight = GetFrameHeightWithSpacing();

	std::filesystem::path newPwd;
	bool setNewPwd = false;

	if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory) &&
		(flags_ & ImGuiFileBrowserFlags_EnterNewFilename))
		reserveHeight += GetFrameHeightWithSpacing();

	//print files browser in a child window
	DisplayFileList(reserveHeight, newPwd, setNewPwd);

	if (setNewPwd)
		SetPwd(newPwd);

	if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory) &&
		(flags_ & ImGuiFileBrowserFlags_EnterNewFilename)) //condition to see if renaming is active
	{
		PushID(this);

		PushItemWidth(-1);
		if (InputText("", inputNameBuf_->data(), inputNameBuf_->size()))
			selectedFilename_ = inputNameBuf_->data();
		PopItemWidth();

		PopID();
	}

	//DisplayOkButton(); // Not Working 

	//DisplayCancelButton();
	
	//basicly its error print in a status bar
	if (!statusStr_.empty() && !(flags_ & ImGuiFileBrowserFlags_NoStatusBar))
	{
		SameLine();
		Text("%s", statusStr_.c_str());
	}

	//DisplayFilterCombo();
	PopID();
}

inline bool ImGui::FileBrowser::HasSelected() const noexcept
{
	return ok_;
}

inline bool ImGui::FileBrowser::SetPwd(const std::filesystem::path& pwd)
{
	try
	{
		SetPwdUncatched(pwd);
		return true;
	}
	catch (const std::exception & err)
	{
		statusStr_ = std::string("last error: ") + err.what();
	}
	catch (...)
	{
		statusStr_ = "last error: unknown";
	}

	SetPwdUncatched(std::filesystem::current_path());
	return false;
}

inline std::filesystem::path ImGui::FileBrowser::GetSelected() const
{
	return pwd_ / selectedFilename_;
}

inline void ImGui::FileBrowser::ClearSelected()
{
	selectedFilename_ = std::string();
	(*inputNameBuf_)[0] = '\0';
	ok_ = false;
}

inline void ImGui::FileBrowser::SetTypeFilters(
	const std::vector<const char*>& typeFilters)
{
	typeFilters_ = typeFilters;
	typeFilterIndex_ = 0;
}

inline void ImGui::FileBrowser::SetPwdUncatched(const std::filesystem::path& pwd)
{
	fileRecords_ = { FileRecord{ true, "..", "[D] ..", "" } };

	for (auto& p : std::filesystem::directory_iterator(pwd))
	{
		FileRecord rcd;

		if (p.is_regular_file())
			rcd.isDir = false;
		else if (p.is_directory())
			rcd.isDir = true;
		else
			continue;

		rcd.name = p.path().filename();
		if (rcd.name.empty())
			continue;

		rcd.extension = p.path().filename().extension();

		rcd.showName = (rcd.isDir ? "[D] " : "[F] ") +
			p.path().filename().u8string();
		fileRecords_.push_back(rcd);
	}

	std::sort(fileRecords_.begin(), fileRecords_.end(),
		[](const FileRecord& L, const FileRecord& R)
		{
			return (L.isDir ^ R.isDir) ? L.isDir : (L.name < R.name);
		});

	pwd_ = absolute(pwd);
	selectedFilename_ = std::string();
	(*inputNameBuf_)[0] = '\0';
}

#ifdef _WIN32

#ifndef _INC_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN

#define IMGUI_FILEBROWSER_UNDEF_WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#endif // #ifndef WIN32_LEAN_AND_MEAN

#include <Windows.h>

#ifdef IMGUI_FILEBROWSER_UNDEF_WIN32_LEAN_AND_MEAN
#undef IMGUI_FILEBROWSER_UNDEF_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif // #ifdef IMGUI_FILEBROWSER_UNDEF_WIN32_LEAN_AND_MEAN

#endif // #ifdef _INC_WINDOWS

inline std::uint32_t ImGui::FileBrowser::GetDrivesBitMask()
{
	DWORD mask = GetLogicalDrives();
	uint32_t ret = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (!(mask & (1 << i)))
			continue;
		char rootName[4] = { static_cast<char>('A' + i), ':', '\\', '\0' };
		UINT type = GetDriveTypeA(rootName);
		if (type == DRIVE_REMOVABLE || type == DRIVE_FIXED)
			ret |= (1 << i);
	}
	return ret;
}

#endif