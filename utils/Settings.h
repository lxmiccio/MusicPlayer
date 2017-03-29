#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QSettings>

namespace SettingsFiles
{
    static const QString SETTINGS_FILE = QString("%1/settings.ini").arg(QDir::currentPath());
    static const QString PLAYLISTS_FILE = QString("%1/settings.ini").arg(QDir::currentPath());
}

class Settings
{
    public:
        static void setVolume(quint8 volume);
        static quint8 volume();
};

#endif // SETTINGS_H
