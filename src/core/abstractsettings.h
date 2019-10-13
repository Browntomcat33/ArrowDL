/* - DownZemAll! - Copyright (C) 2019 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORE_ABSTRACT_SETTINGS_H
#define CORE_ABSTRACT_SETTINGS_H

#include <exception>        /* std::exception */
#include <QtCore/QObject>
#include <QtCore/QString>

/*!
 * \class AbstractSettings
 * \brief The AbstractSettings class manages the persistence of the User preferences
 *
 */
class AbstractSettings : public QObject
{
    Q_OBJECT
    enum KeyType { BOOL, INTEGER, STRING };
    class SettingsItem;

public:
    explicit AbstractSettings(QObject *parent = Q_NULLPTR);
    virtual ~AbstractSettings();

    void beginRestoreDefault();
    void endRestoreDefault();

    void readSettings();
    void writeSettings();

signals:
    void changed();

protected:
    /* Exceptions */
    class IllegalValueException : public std::exception {};
    class MissingKeyException : public std::exception {};

    void addDefaultSetting(const QString &key, bool defaultValue);
    void setSetting(const QString &key, bool value);
    bool getSettingBool(const QString &key) const;

    void addDefaultSetting(const QString &key, int defaultValue);
    void setSetting(const QString &key, int value);
    int getSettingInt(const QString &key) const;

    void addDefaultSetting(const QString &key, const QString &defaultValue);
    void setSetting(const QString &key, const QString &value);
    QString getSettingString(const QString &key) const;

    void addDefaultSettingStringList(const QString &key, const QStringList &defaultValue);
    void setSettingStringList(const QString &key, const QStringList &value);
    QStringList getSettingStringList(const QString &key) const;

private:
    QList<SettingsItem*> m_items;
    bool m_default;

    void _q_addDefaultSetting(const QString &key, const QString &defaultValue, KeyType keyType);
    void _q_setSetting(const QString &key, const QString &defaultValue, KeyType keyType);
    QString _q_getSetting(const QString &key, KeyType keyType) const;

    QString _q_unique_name(const AbstractSettings::SettingsItem *item) const;
};

#endif // CORE_ABSTRACT_SETTINGS_H
