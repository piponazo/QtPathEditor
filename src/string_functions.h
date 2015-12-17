#pragma once

#include "types.h"
#include "PathLib_export.h"

/// Split a registry string into a list of strings containing the environment paths
PATHLIB_EXPORT StringListT fromRegistryString( const std::wstring& string,
											   wchar_t separator = L';');

/// Joint a list of environment paths to form a registry string
PATHLIB_EXPORT std::wstring toRegistryString( const StringListT& paths,
											  wchar_t separator = L';');
