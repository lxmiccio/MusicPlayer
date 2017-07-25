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
        enum View
        {
            ARTIST_VIEW = 0,
            ALBUM_VIEW,
            TRACK_VIEW,
            PLAYING_VIEW
        };

        static void setVolume(quint8 volume);
        static quint8 volume();

        static void setView(Settings::View view);
        static Settings::View view();

        static QString playlistsFile();

        static QString apiKey();

    private:
        static Settings::View stringToView(QString string);
};

#endif// SETTINGS_H
