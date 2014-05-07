#ifndef INTERFACE_H
#define INTERFACE_H
#include <QString>
namespace BOMLIB
{
enum Type
{
    Storage,
    Commmunication,
    OperatingSystem,
    Processor,
    Field,
	IEC61850LNClass,
	ProcessObjectClass

};
//! Interface class
	/*!
		Responsibility : All Interfaces associated to BOM Objects including
		Communication Processing, File, Process Objects, Storage etc can be
		defined as interfaces and added to BOM Object.
	*/

class Interface
{

public:

	//! Constructor
	/*!
		\param int id
		Identifier for the Interface. A running number.
		\param Qstring name
		Name of the Interface. Like Ethernet
		\param Type typeEnumVal
		Type meaning Storage, Processor, OS etc
		\param bool external
		Whether External or internal to BOM Object
		Note: Only External interfaces are displayed while
		instance is created as graphical items.
	*/

    Interface(int id, QString name, Type typeEnumVal,bool external=false)
    {
        _typeOfInterface=typeEnumVal;
        _id=id;
        _name=name  ;
        if(typeEnumVal==BOMLIB::Commmunication ||typeEnumVal==BOMLIB::Field)  external=true;
        _externalInterface=external;
    }

	//! GetId
	/*!
		Returns the identifier
	*/
    int GetId()
    {
        return _id;
    }
	//! GetName
	/*!
		Returns the Name of the interface
	*/
    QString GetName()
    {
        return _name;
    }
	//! GetExternal
	/*!
		Returns true if the interface is external (Or needs to be dispplayed)
		For example processor is internal whereas ethernet communication is
		externl interface.
	*/
    bool GetExternal()
    {
        return _externalInterface;
    }
	//! EndianNess
	/*!
		Enum to mention what Endian the interface follows
		In many cases it is sometimes a huge effort to convert
		endian
	*/
    enum EndianNess
    {
        litte=1,
        Big=2
    };
	//! getTypeOfInterface
	/*!
		Returns the type of interface Storage, Process etc.
	*/
	Type getTypeOfInterface()
	{
		return _typeOfInterface;
	}
private:
    Type _typeOfInterface;
    int _id;
    QString _name;
    bool _externalInterface;
};
}
#endif // INTERFACE_H
