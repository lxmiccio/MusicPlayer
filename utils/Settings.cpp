#include "Settings.h"

void Settings::setVolume(quint8 volume)
{
    if(volume >= 0 && volume <= 100)
    {
        QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);
        settings.setValue("MAIN/volume", volume);
    }
}

quint8 Settings::volume()
{
    QSettings settings(SettingsFiles::SETTINGS_FILE, QSettings::IniFormat);
    return settings.value("MAIN/volume", 75).toUInt();
}
