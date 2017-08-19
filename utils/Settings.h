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
            NO_VIEW = 0,
            ARTIST_VIEW,
            ALBUM_VIEW,
            TRACK_VIEW,
            PLAYLIST_VIEW,
            PLAYING_VIEW
        };

        static void setVolume(quint8 volume);
        static quint8 volume();

        static void setView(Settings::View view);
        static Settings::View view();

        static QString playlistsFile();

        static QString apiKeyLastFm();
        static QString apiKeyMusixMatch();

    private:
        static Settings::View stringToView(QString string);
};

#endif// SETTINGS_H
