/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::functionObjects::writeRegisteredObject

Group
    grpUtilitiesFunctionObjects

Description
    This function object allows specification of different writing frequency
    of objects registered to the database. It has similar functionality
    as the main time database through the writeControl setting:

    \li \c timeStep
    \li \c writeTime
    \li \c adjustableRunTime
    \li \c runTime
    \li \c clockTime
    \li \c cpuTime

    Example of function object specification:
    \verbatim
    writeRegisteredObject1
    {
        type        writeRegisteredObject;
        libs ("libutilityFunctionObjects.so");
        exclusiveWriting     true;
        ...
        objectNames (obj1 obj2);
    }
    \endverbatim

    \heading Function object usage
    \table
        Property     | Description             | Required    | Default value
        type         | type name: writeRegisteredObject | yes |
        objectNames  | objects to write        | yes         |
        exclusiveWriting    | Takes over object writing | no | yes
    \endtable

    \c exclusiveWriting disables automatic writing (i.e through database) of the
    objects to avoid duplicate writing.

SeeAlso
    Foam::functionObject
    Foam::functionObjects::timeControl

SourceFiles
    writeRegisteredObject.C

\*---------------------------------------------------------------------------*/

#ifndef functionObjects_writeRegisteredObject_H
#define functionObjects_writeRegisteredObject_H

#include "functionObject.H"
#include "wordReList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class objectRegistry;

namespace functionObjects
{

/*---------------------------------------------------------------------------*\
                   Class writeRegisteredObject Declaration
\*---------------------------------------------------------------------------*/

class writeRegisteredObject
:
    public functionObject
{
    // Private data

        //- Refererence to Db
        const objectRegistry& obr_;

        //- Takes over the writing from Db
        bool exclusiveWriting_;

        //- Names of objects to control
        wordReList objectNames_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        writeRegisteredObject(const writeRegisteredObject&);

        //- Disallow default bitwise assignment
        void operator=(const writeRegisteredObject&);


public:

    //- Runtime type information
    TypeName("writeRegisteredObject");


    // Constructors

        //- Construct from Time and dictionary
        writeRegisteredObject
        (
            const word& name,
            const Time& runTime,
            const dictionary& dict
        );


    //- Destructor
    virtual ~writeRegisteredObject();


    // Member Functions

        //- Read the writeRegisteredObject data
        virtual bool read(const dictionary&);

        //- Do nothing
        virtual bool execute(const bool postProcess = false);

        //- Write the registered objects
        virtual bool write(const bool postProcess = false);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace functionObjects
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
