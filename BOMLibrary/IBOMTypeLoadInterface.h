#ifndef IBOMTYPELOADINTERFACE_H
#define IBOMTYPELOADINTERFACE_H
#include <../BOMLibrary/bomobject.h>
#include <qplugin.h>
using namespace BOMLIB;
//! IBOMTypeLoadInterface Interface
	/*!
		Interface to be complied for BOM Object type loading.
		The Library exposes this interface thereby letting the
		applications access the library and load the BOM Object types.
		Contains only virtual functions.
	*/
class IBOMTypeLoadInterface
 {
 public:
	 //! LoadDefinitions
	/*!
		\param QString relativeFolderName
		Loads the defintions from the folder 
	*/
	 virtual bool LoadDefinitions(QString relativeFolderName)=0;
	 //! getCurrentDefintions method
	/*!
		Returns the BOM Objects read from sepcified folder as a list.
	*/
	 virtual QList<BOMObject*> getCurrentDefintions()=0;
	 //! FindBOMType method
	/*!
		\param QString BOMTypeName
		Helper funtion which can browse through the list and return the 
		Type with TypeName as specified in parameter.
	*/
     virtual BOMObject* FindBOMType(QString BOMTypeName)=0;
     
 };

Q_DECLARE_INTERFACE(IBOMTypeLoadInterface,
                     "BOMLoader/1.0");

#endif
