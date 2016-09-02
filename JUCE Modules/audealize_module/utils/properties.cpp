/*
 Audealize
 
 http://music.cs.northwestern.edu
 http://github.com/interactiveaudiolab/audealize-plugin
 
 Licensed under the GNU GPLv2 <https://opensource.org/licenses/GPL-2.0>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "properties.h"

using namespace Audealize;

const Identifier Properties::propertyIds::darkMode = "darkmode";
const Identifier Properties::propertyIds::eqDataPath = "eqDataPath";
const Identifier Properties::propertyIds::reverbDataPath = "reverbDataPath";

void Properties::writePropertiesToFile (var properties)
{
    File prop_file = loadPropertiesFile ();

    if (!prop_file.exists ())
    {
        prop_file.create ();
    }

    prop_file.replaceWithText (JSON::toString (properties));
}

File Properties::loadPropertiesFile ()
{
    PropertiesFile::Options properties;
    properties.osxLibrarySubFolder = "Application Support";

#ifdef JUCE_LINUX
    properties.folderName = ".Audealize";
#else
    properties.folderName = "Audealize";
#endif

    properties.applicationName = "Audealize";
    properties.filenameSuffix = "cfg";

    File defaultFile = properties.getDefaultFile ();

    // if no config file exists, create one using the default settings
    if (!defaultFile.existsAsFile ())
    {
        DynamicObject* temp = new DynamicObject ();
        temp->setProperty ("darkmode", DEFAULT_DARKMODE);
        temp->setProperty (propertyIds::eqDataPath, DEFAULT_EQ_DATA_PATH);
        temp->setProperty (propertyIds::reverbDataPath, DEFAULT_REVERB_DATA_PATH);

        defaultFile.create ();

        defaultFile.replaceWithText (JSON::toString (var (temp)));
    }

    return defaultFile;
}

var Properties::loadPropertiesVar ()
{
    var properties;

    if (JSON::parse (loadPropertiesFile ().loadFileAsString (), properties).wasOk ())
    {
        return properties;
    }

    return var ();
}

var Properties::getProperty (Identifier propertyId)
{
    var property = loadPropertiesVar ().getDynamicObject ()->getProperty (propertyId);

    return loadPropertiesVar ().getDynamicObject ()->getProperty (propertyId);
}
