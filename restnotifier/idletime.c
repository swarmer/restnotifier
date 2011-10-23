#include <QtGlobal>

#if defined Q_WS_X11
#include <X11/extensions/scrnsaver.h>
#endif


// return idle time in seconds
int getIdleSecs()
{
#if defined Q_WS_X11
    int code, idle_sec;
    XScreenSaverInfo *ssinfo = XScreenSaverAllocInfo();
    if (!ssinfo)
        goto fail;
    Display *display = XOpenDisplay(0);
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
#else
    return -1;
#endif
}
