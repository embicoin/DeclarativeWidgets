/*
  Copyright (C) 2012-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEFORMLAYOUT_P_H
#define DECLARATIVEFORMLAYOUT_P_H

#include "declarativelayoutextension.h"

#include <qdeclarative.h>
#include <QFormLayout>

class DeclarativeFormLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

  public:
    explicit DeclarativeFormLayoutAttached(QWidget *parent);
    explicit DeclarativeFormLayoutAttached(QLayout *parent);
    ~DeclarativeFormLayoutAttached();

    void setParentLayout(QFormLayout *parentLayout);

    void setLabel(const QString &label);
    QString label() const;

  Q_SIGNALS:
    void labelChanged(const QString &label);

  private:
    class Private;
    Private *const d;
};

class DeclarativeFormLayout : public QFormLayout
{
  Q_OBJECT

  public:
    explicit DeclarativeFormLayout(QObject *parent = 0);

    static DeclarativeFormLayoutAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeFormLayout, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeFormLayoutExtension : public DeclarativeLayoutExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)
  Q_PROPERTY(DeclarativeLayoutContentsMargins* contentsMargins READ contentsMargins CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeFormLayoutExtension(QObject *parent = 0);
};

#endif
