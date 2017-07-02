#include "Settings.h"

void Settings::setVolume(quint8 volume)
{
    QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);

    if(volume <= 100)
    {
        settings.setValue("DEFAULT/volume", volume);
    }
    else
    {
        settings.setValue("DEFAULT/volume", 75);
    }
}

quint8 Settings::volume()
{
    QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);
    return settings.value("DEFAULT/volume", 75).toUInt();
}

void Settings::setView(Settings::View view)
{
    QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);

    switch(view)
    {
        case View::ARTIST_VIEW:
        {
            settings.setValue("DEFAULT/view", "ARTIST_VIEW");
            break;
        }
        case View::ALBUM_VIEW:
        {
            settings.setValue("DEFAULT/view", "ALBUM_VIEW");
            break;
        }
        case View::TRACK_VIEW:
        {
            settings.setValue("DEFAULT/view", "TRACK_VIEW");
            break;
        }
        default:
        {
            settings.setValue("DEFAULT/view", "ARTIST_VIEW");
            break;
        }
    }
}

Settings::View Settings::view()
{
    QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);
    return stringToView(settings.value("DEFAULT/view", "ARTIST_VIEW").toString());
}

Settings::View Settings::stringToView(QString string)
{
    Settings::View view = View::ARTIST_VIEW;

    if(string == "ALBUM_VIEW")
    {
        view = View::ALBUM_VIEW;
    }
    else if(string == "TRACK_VIEW")
    {
        view = View::TRACK_VIEW;
    }

    return view;
}

QString Settings::apiKey()
{
    QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);
    return settings.value("API/musixmatch_key").toString();
}
