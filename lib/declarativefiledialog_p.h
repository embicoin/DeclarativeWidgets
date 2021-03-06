/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef DECLARATIVEFILEDIALOG_P_H
#define DECLARATIVEFILEDIALOG_P_H

#include "staticdialogmethodattached_p.h"

#include <qdeclarative.h>
#include <QFileDialog>

class DeclarativeFileDialogAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(QString caption READ caption WRITE setCaption NOTIFY captionChanged)
  Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
  Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
  Q_PROPERTY(int options READ options WRITE setOptions NOTIFY optionsChanged)
  Q_PROPERTY(QString selectedFilter READ selectedFilter NOTIFY selectedFilterChanged)

  public:
    explicit DeclarativeFileDialogAttached(QObject *parent = 0);
    ~DeclarativeFileDialogAttached();

    void setCaption(const QString &caption);
    QString caption() const;

    void setDir(const QString &dir);
    QString dir() const;

    void setNameFilters(const QStringList &nameFilters);
    QStringList nameFilters() const;

    void setOptions(int options);
    int options() const;

    QString selectedFilter() const;

    Q_INVOKABLE QString getExistingDirectory();

    Q_INVOKABLE QString getOpenFileName();

    Q_INVOKABLE QStringList getOpenFileNames();

    Q_INVOKABLE QString getSaveFileName();

  Q_SIGNALS:
    void captionChanged(const QString &caption);
    void dirChanged(const QString &dir);
    void nameFiltersChanged(const QStringList &filters);
    void optionsChanged(int options);
    void selectedFilterChanged(const QString &filter);

  private:
    void setSelectedFilter(const QString &filter);

    class Private;
    Private *const d;
};

class DeclarativeFileDialog : public QFileDialog
{
  Q_OBJECT

  Q_PROPERTY(QStringList selectedFiles READ selectedFiles)

  public:
    explicit DeclarativeFileDialog(QWidget *parent = 0);

    static DeclarativeFileDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeFileDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
