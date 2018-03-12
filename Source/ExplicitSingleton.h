/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _EXPLICIT_SINGLETON_H_
#define _EXPLICIT_SINGLETON_H_

// Includes...

    // System headers...
    #include <cassert>

// Explicit singleton pattern whose creation and deconstruction are managed by
//  the client. Subclasses must declare themselves a friend of this pattern in
//  order to protect themselves from being manually instantiated on the stack...
template <class SingletonType>
class ExplicitSingleton
{
    // Public methods...
    public:

        // Create the object...
        static SingletonType &CreateSingleton()
        {
            // Runtime error if already created...
            assert(!IsInstantiated());

            // Construct and return the new instance...
            ms_Instance = new SingletonType;
            return *ms_Instance;
        }

        // Destroy the object...
        static void DestroySingleton()
        {
            // Runtime error if it did not already exist...
            assert(IsInstantiated());

            // Deconstruct...
            delete ms_Instance;
            ms_Instance = nullptr;
        }

        // Get the instance. Error if called and it didn't already exist...
        static SingletonType &GetInstance()
        {
            assert(IsInstantiated());
            return *ms_Instance;
        }

        // Get the read only instance. Error if called and it didn't already exist...
        static const SingletonType &GetInstanceConst()
        {
            assert(IsInstantiated());
            return *ms_Instance;
        }

        // Get the instance. Error if called and it didn't already exist...
        static SingletonType *GetInstancePointer()
        {
            assert(IsInstantiated());
            return ms_Instance;
        }

        // Get the read only instance. Error if called and it didn't already exist...
        static const SingletonType *GetInstancePointerConst()
        {
            assert(IsInstantiated());
            return ms_Instance;
        }

        // Check if the singleton is instantiated...
        static bool IsInstantiated() { return ms_Instance ? true : false; }

    // Protected methods...
    protected:

        // Protected constructor forbids clients from manually instantiating...
        ExplicitSingleton()
        {
            assert(!IsInstantiated());
        }

        // Deconstructor...
       ~ExplicitSingleton()
        {
        }

    // Private methods...
    private:

        // Forbid copy constructor and assignment...
        ExplicitSingleton(const ExplicitSingleton<SingletonType> &);
        ExplicitSingleton &operator=(const ExplicitSingleton &);

        // The actual object instance...
        static SingletonType *ms_Instance;
};

// Start by marking the singleton as uninitialized...
template <class SingletonType>
SingletonType *ExplicitSingleton<SingletonType>::ms_Instance = nullptr;

#endif

