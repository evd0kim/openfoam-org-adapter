/*---------------------------------------------------------------------------*\
preCICE-adapter for OpenFOAM

Copyright (c) 2017 Gerasimos Chourdakis

Based on previous work by Lucia Cheung Yau. See also the README.md.
-------------------------------------------------------------------------------

License
    This adapter is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This adapter is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with the adapter.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "preciceAdapterFunctionObject.H"

// OpenFOAM header files
#include "Time.H"
#include "fvMesh.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{
defineTypeNameAndDebug(preciceAdapterFunctionObject, 0);
addToRunTimeSelectionTable(functionObject, preciceAdapterFunctionObject, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::functionObjects::preciceAdapterFunctionObject::preciceAdapterFunctionObject(
    const word& name,
    const Time& runTime,
    const dictionary& dict)
: fvMeshFunctionObject(name, runTime, dict),
  adapter_(runTime, mesh_)
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::functionObjects::preciceAdapterFunctionObject::~preciceAdapterFunctionObject()
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::functionObjects::preciceAdapterFunctionObject::read(const dictionary& dict)
{
    // We disable executeAtStart explicitly here and don't read the respective entry from the
    // dictionary(fvMeshFunctionObject::read(dict)). Have a look at issue #179 for the rationale.
    //this->executeAtStart_ = false;
    //DEBUG(adapterInfo("Execute at start set to (dictionary input is ignored): " this->executeAtStart()));
    adapter_.configure();

    return true;
}


bool Foam::functionObjects::preciceAdapterFunctionObject::execute()
{
    adapter_.execute();

    return true;
}


bool Foam::functionObjects::preciceAdapterFunctionObject::end()
{
    adapter_.end();

    return true;
}


bool Foam::functionObjects::preciceAdapterFunctionObject::write()
{
    return true;
}

bool Foam::functionObjects::preciceAdapterFunctionObject::setTimeStep()
{
    adapter_.setTimeStep();

    return true;
}

// ************************************************************************* //
