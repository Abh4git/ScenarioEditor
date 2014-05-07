#pragma once
#include <QMutex>

#include "../BOMLibrary/IBOMTypeLoadInterface.h"
#include "../BOMGraphicalLibrary/IBOMInstanceCreation.h"

using namespace BOMLIB;
//! Singleton
	/*!
		Responsibility: Creates singleton instance of objects
	*/
class Singleton
{
public:
	//! instance 
	/*!
		Returns an instance of BPOM
	*/
    static Singleton* instance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();
 
            if (!m_Instance)
                m_Instance = new Singleton;
 
            mutex.unlock();
        }
 
        return m_Instance;
    }
 
    static void drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_Instance;
        m_Instance = 0;
        mutex.unlock();
    }
	//! getCurrentBOMInstance
	/*!
		Returns the current BOM Instance in memory
	*/
	BOMInstance* getCurrentBOMInstance()
	{
		return m_currentBOM;
	}

	void setCurrentBOMInstance(BOMInstance* bomInst)
	{
		m_currentBOM=bomInst;
	}
 
private:
    Singleton() {}
 
    Singleton(const Singleton &); // hide copy constructor
    Singleton& operator=(const Singleton &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us 
                                 // if we try to use those two functions by accident
 
    static Singleton* m_Instance;
	BOMInstance* m_currentBOM;
};
 

