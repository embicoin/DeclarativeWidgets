/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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

#include "declarativestatusbar_p.h"

#include <QDeclarativeInfo>

class DeclarativeStatusBarAttached::Private
{
  public:
    int stretch;
};

DeclarativeStatusBarAttached::DeclarativeStatusBarAttached(QObject *parent)
  : QObject(parent), d(new DeclarativeStatusBarAttached::Private)
{
  d->stretch = 0;
}

DeclarativeStatusBarAttached::~DeclarativeStatusBarAttached()
{
  delete d;
}

void DeclarativeStatusBarAttached::setStretch(int stretch)
{
  if (d->stretch == stretch)
    return;

  d->stretch = stretch;
  emit stretchChanged();
}

int DeclarativeStatusBarAttached::stretch() const
{
  return d->stretch;
}

DeclarativeStatusBar::DeclarativeStatusBar(QWidget *parent)
  : QStatusBar(parent)
{
}

DeclarativeStatusBarAttached *DeclarativeStatusBar::qmlAttachedProperties(QObject *object)
{
  return new DeclarativeStatusBarAttached(object);
}

DeclarativeStatusBarExtension::DeclarativeStatusBarExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
{
}

QStatusBar *DeclarativeStatusBarExtension::extendedStatusBar() const
{
  QStatusBar *statusBar = qobject_cast<QStatusBar*>(extendedWidget());
  Q_ASSERT(statusBar);

  return statusBar;
}

void DeclarativeStatusBarExtension::addWidget(QWidget *widget)
{
  // TODO: error when layout is set

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeStatusBar>(widget, false);
  DeclarativeStatusBarAttached *attached = qobject_cast<DeclarativeStatusBarAttached*>(attachedProperties);

  int stretch = 0;
  if (attached) {
    stretch = attached->stretch();
  }

  extendedStatusBar()->addPermanentWidget(widget, stretch);
}

void DeclarativeStatusBarExtension::setLayout(QLayout *layout)
{
  Q_UNUSED(layout);
  qmlInfo(extendedStatusBar()) << "Can not add Layout to StatusBar";
}
