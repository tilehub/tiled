/*
 * addremovemapobject.h
 * Copyright 2009, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QUndoCommand>

namespace Tiled {

class MapObject;
class ObjectGroup;

namespace Internal {

class MapDocument;

/**
 * Abstract base class for AddMapObject and RemoveMapObject.
 */
class AddRemoveMapObject : public QUndoCommand
{
public:
    AddRemoveMapObject(MapDocument *mapDocument,
                       ObjectGroup *objectGroup,
                       MapObject *mapObject,
                       bool ownObject,
                       QUndoCommand *parent = nullptr);
    ~AddRemoveMapObject();

protected:
    void addObject();
    void removeObject();

private:
    MapDocument *mMapDocument;
    MapObject *mMapObject;
    ObjectGroup *mObjectGroup;
    int mIndex;
    bool mOwnsObject;
};

/**
 * Undo command that adds an object to a map.
 */
class AddMapObject : public AddRemoveMapObject
{
public:
    AddMapObject(MapDocument *mapDocument, ObjectGroup *objectGroup,
                 MapObject *mapObject, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;
};

/**
 * Undo command that removes an object from a map.
 */
class RemoveMapObject : public AddRemoveMapObject
{
public:
    RemoveMapObject(MapDocument *mapDocument, MapObject *mapObject,
                    QUndoCommand *parent = nullptr);

    void undo() override
    { addObject(); }

    void redo() override
    { removeObject(); }
};

} // namespace Internal
} // namespace Tiled
