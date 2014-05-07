///////////////////////////////////////////////////////////
//  Glymph.h
//  Implementation of the Class Glymph
//  Created on:      23-Aug-2012 5:57:27 PM
//  Original author: INABG
///////////////////////////////////////////////////////////

#if !defined(EA_2C7B0E68_5C70_4647_8377_944552E9FE3E__INCLUDED_)
#define EA_2C7B0E68_5C70_4647_8377_944552E9FE3E__INCLUDED_
#include <QImage>
namespace BOMLIB
{
	//! Glymph class
	/*!
		Responsibility : Hold Images associated to the BOM Object.
		Mininum 2 - 1 for Toolbox Image, another for Scene Image
		3rd Image can be treated as Scene image to be based on
		certain state of the BOM Object.
	*/
class Glymph
{

public:
	//! Constructor
	Glymph();
	//! Destructor
	virtual ~Glymph();
	//! GetAlt
	/*!
		Return the Alternative
	*/
	double GetAlt();
	//! GetHeight
	/*!
		Return the Height of the image
	*/
	double GetHeight();
    //! GetImage
	/*!
		Return the Image itself as QImage.
	*/
	QImage GetImage();
	//! GetType
	/*!
		Return the Type (ICO, JPEG,PNG etc) of Image.
	*/
	QString GetType();
	//! GetWidth
	/*!
		Return the Width of the image.
	*/
	double GetWidth();
	//! SetAlt
	/*!
		Return the Alternative of the image.
	*/
	void SetAlt(double newVal);
	
	//! SetHeight
	/*!
		\param double newVal
		Set the height of the image associated with Glymph
	*/
	void SetHeight(double newVal);
    //! SetImage
	/*!
		\param double newVal
		Set the image associated with Glymph.
	*/
	void SetImage(QImage newVal);
	//! SetType
	/*!
		\param QString newVal
		Set the Type of File (ICO,JPEG..) associated with Glymph.
	*/
	void SetType(QString newVal);
	//! SetWidth
	/*!
		\param double newVal
		Set the width of the Image.
	*/
	void SetWidth(double newVal);
	//! GetFileName
	/*!
		Return the Filename of the image file
		associated with Glymph.
	*/
	QString GetFileName();
	//! SetFileName
	/*!
		\param QString fileName
		Sets the The filename of the Image file associated with the
		Glymph.
	*/
	void SetFileName(QString fileName);
private:
	double Alt;
	double Height;
        QImage Image;
	QString Type;
	double Width;
	QString m_FileName;

};
}
#endif // !defined(EA_2C7B0E68_5C70_4647_8377_944552E9FE3E__INCLUDED_)
