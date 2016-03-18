/*
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2014,      Dominik Schmidt <domme@tomahawk-player.org>
 *   Copyright 2016,      Teo Mrnjavac <teo@kde.org>
 *
 *   libcrashreporter is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGlobal> // needed for Q_OS_LINUX here

#include <stdlib.h>

class QString;

namespace google_breakpad
{
    class ExceptionHandler;
}

namespace CrashReporter
{

#ifdef Q_OS_LINUX
static bool LinuxBacktraceParser( const void* crash_context, size_t crash_context_size, void* context );
#endif

class Handler
{
    const char* m_crashReporterChar; // yes! It MUST be const char[]
    const wchar_t* m_crashReporterWChar;

public:
#ifdef Q_OS_LINUX
    Handler(const QString& dumpFolderPath, bool active, const QString& crashReporter );
    const char* linuxBacktracePathChar() { return m_linuxBacktracePathChar; }
#else
    Handler(const QString& dumpFolderPath, bool active, const QString& crashReporter );
#endif
    virtual ~Handler();

    static void setActive( bool enabled );
    static bool isActive();

    void setCrashReporter( const QString& crashReporter );
    const char* crashReporterChar() const { return m_crashReporterChar; }
    const wchar_t* crashReporterWChar() const { return m_crashReporterWChar; }

private:
#ifdef Q_OS_LINUX
    const char* m_linuxBacktracePathChar;
#endif
    friend bool CrashReporter::LinuxBacktraceParser( const void* crash_context, size_t crash_context_size, void* context );
    google_breakpad::ExceptionHandler* m_crash_handler;
};

}
#undef char
