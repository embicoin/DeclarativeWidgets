/*
  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "uiactionnode.h"

#include "parser.h"
#include "uinodevisitor.h"
#include "uipropertynode.h"

#include <QDebug>
#include <QXmlStreamAttributes>
#include <QXmlStreamReader>

UiActionNode::UiActionNode()
  :UiObjectNode(QLatin1String("action"))
{
  setClassName(QStringList() << QLatin1String("Action"));
}

UiNode *UiActionNode::parse(Parser *parser)
{
  const QString objectName = parser->reader()->attributes().value(QLatin1String("name")).toString();
  if (objectName.isEmpty()) {
    parser->reader()->raiseError(QLatin1String("action element is missing the name attribute"));
    return 0;
  }

  UiActionNode *target = new UiActionNode;
  target->setName(objectName);

  while (!parser->reader()->atEnd()) {
    if (!parser->reader()->readNextStartElement()) {
      if (parser->reader()->isEndElement() && parser->reader()->name().compare(target->m_elementName, Qt::CaseInsensitive) == 0) {
        break;
      } else {
        continue;
      }
    }

   if (parser->reader()->name().compare(QLatin1String("property"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiPropertyNode::parse(parser);
      if (childNode != 0) {
        target->appendChild(childNode);
      }
    } else {
      qDebug() << "Skipping unsupported" << parser->reader()->name().toString()
               << "sub element of" << target->m_elementName << "element" << objectName << ", line"
               << parser->reader()->lineNumber();
      parser->reader()->skipCurrentElement();
    }
  }

  return target;
}

void UiActionNode::accept(UiNodeVisitor *visitor)
{
  visitor->visit(this);
}
