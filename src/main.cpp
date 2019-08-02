#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>

#include "app/app.h"

#ifdef LINUX_SIGNALS
#include <sigwatch.h>
#endif

int main(int argc, char *argv[])
{           
#if defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    Application a(argc, argv);
    a.initModels();
    a.initQml();

    #ifdef LINUX_SIGNALS
    UnixSignalWatcher sigwatch;
    sigwatch.watchForSignal(SIGINT);
    sigwatch.watchForSignal(SIGTERM);
    QObject::connect(&sigwatch, SIGNAL(unixSignal(int)), &a, SLOT(quit()));
    #endif

    return a.exec();
}

