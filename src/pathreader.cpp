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

#include "PathReader.h"
#include "string_functions.h"

#include <memory>

// Registry value types:
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724884(v=vs.85).aspx

CPathReader::CPathReader(const HKEY hKey, const LPCTSTR keyName, const LPCTSTR valueName) :
    m_keyHandle( hKey)       // HKEY_CURRENT_USER
  , m_keyName( keyName)      // L"Environment"
  , m_valueName( valueName)  // L"Path"
{
}

bool CPathReader::Read( StringListT& strList)
{
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724897(v=vs.85).aspx
    HKEY hPathKey = 0;
    if( RegOpenKeyEx( m_keyHandle, m_keyName, 0, KEY_QUERY_VALUE, &hPathKey) != ERROR_SUCCESS)
        return false;

    std::shared_ptr<void> afPathKey( hPathKey, RegCloseKey);

    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724911(v=vs.85).aspx
    ULONG nChars = 0;
    if( RegQueryValueEx( hPathKey, m_valueName, 0, 0, 0, &nChars) != ERROR_SUCCESS)
        return false;

    // empty path is not failure
    if(nChars == 0)
        return true;

    std::wstring sBuffer(nChars / sizeof(wchar_t), 0);
    LPBYTE lpBuffer = reinterpret_cast<LPBYTE>(&sBuffer[0]);
    if( RegQueryValueEx( hPathKey, m_valueName, 0, 0, lpBuffer, &nChars) != ERROR_SUCCESS)
        return false;

    strList = fromRegistryString(sBuffer);
    return true;
}

bool CPathReader::Write( const StringListT& strList)
{
    HKEY hPathKey = 0;
    if( RegOpenKeyEx( m_keyHandle, m_keyName, 0, KEY_SET_VALUE, &hPathKey) != ERROR_SUCCESS)
        return false;

    std::shared_ptr<void> afPathKey( hPathKey, RegCloseKey);

    std::wstring strValue = toRegistryString(strList);
    const BYTE* lpcBuffer = reinterpret_cast<const BYTE*>( strValue.c_str());
    DWORD cbData = static_cast<DWORD>( strValue.size() * sizeof(wchar_t));
    LSTATUS lStatus = RegSetValueEx( hPathKey, m_valueName, 0, REG_EXPAND_SZ, lpcBuffer, cbData);
    return lStatus == ERROR_SUCCESS;
}

