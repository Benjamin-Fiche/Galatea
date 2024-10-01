#pragma once

#pragma region Properties

SoundChannelGroup* SoundChannelGroup::GetChild(const char* _name) noexcept
{
	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = children.begin(); it != children.end(); ++it)
		if ((*it)->name == _name)
			return *it;
}

size_t SoundChannelGroup::GetChildCount() const noexcept
{
	return children.size();
}

SoundChannelGroup* SoundChannelGroup::GetParent() const noexcept
{
	return parent;
}

SoundChannelGroup* SoundChannelGroup::SetParent(SoundChannelGroup* _scg) noexcept
{
	parent = _scg;
	return this;
}

#pragma endregion