#include <QtGlobal>

// headers
#if defined Q_WS_X11
#include <X11/extensions/scrnsaver.h>

#elif defined Q_WS_WIN
#include <windows.h>

#endif
// ^ headers


// return idle time in seconds
int getIdleSecs()
{
// linux
#if defined Q_WS_X11
    int code, idle_sec;
    XScreenSaverInfo *ssinfo = 0;
    Display *display = 0;
    ssinfo = XScreenSaverAllocInfo();
    if (!ssinfo)
        goto fail;
    display = XOpenDisplay(0);
    if (!display)
        goto fail;
    code = XScreenSaverQueryInfo(display, DefaultRootWindow(display), ssinfo);
    if (!code)
        goto fail;
    idle_sec = ssinfo->idle / 1000;
    XFree(ssinfo);
    XCloseDisplay(display);
    return idle_sec;

fail:
    if (ssinfo)
        XFree(ssinfo);
    if (display)
        XCloseDisplay(display);
    return -1;
// ^ linux

// windows
#elif defined Q_WS_WIN
    BOOL ok;
    LASTINPUTINFO plii;
    DWORD msec;
    plii.cbSize = sizeof(LASTINPUTINFO);
    plii.dwTime = 0;
    ok = GetLastInputInfo(&plii);
    if (!ok)
        return -1;
    msec = GetTickCount();
    msec -= plii.dwTime;
    msec /= 1000;
    return msec;
// ^ windows

#else
    return -1;
#endif
}
