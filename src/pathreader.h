/* Copyright (c) 2013, Masoom Shaikh
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "PathLib_export.h"
#include "types.h"

#include <windows.h>

/// Class for managing the list of environment paths
class PATHLIB_EXPORT CPathReader
{
public:
    /// @brief Constructor.
    /// @param hKey     [in] predefined root key.
    /// @param keyName  [in] Key.
    /// @param valueName[in] Value.
    CPathReader( const HKEY hKey = HKEY_CURRENT_USER,
                 const LPCTSTR keyName = L"Environment",
                 const LPCTSTR valueName = L"Path");

    /// @brief Read the paths from the registry into a list of strings.
    /// @note  The order of the strings is the same found in the windows registry.
    bool Read( StringListT& strList);

    /// @brief Write a list of strings into the registry.
    /// @note  The strings will be saved in the registry in the same order than in the list.
    bool Write( const StringListT& strList);

private:
    const HKEY m_keyHandle;
    const LPCTSTR m_keyName, m_valueName;
};
