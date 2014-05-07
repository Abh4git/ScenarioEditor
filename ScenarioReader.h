

#ifndef SCENEREADER_H
#define SCENEREADER_H
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDir>
#include <SceneAction.h>
#include <SceneItem.h>
#include <qstringlist.h>
#include <ComAction.h>
	//! ScenarioReader class
	/*!
		Responsibility: Reads and Parses scenarios from file and fills
		the in memory objects.
	*/
class ScenarioReader
{
public:
	//! Constructor
	/*!
		\param filename as string
	*/
    ScenarioReader(QString filename);
    //! SetDirectory
	/*!
		\param directoryName as string
	*/
	bool SetDirectory(QString directoryName);
    //! SetDirectory
	/*!
		Reads the definitions. Fills the in memory objects of SceneActions,SceneItems and ComActions
		Lists
	*/
	bool ReadDefintions();
    //! GetActionSequence
	/*!
		Returns the SceneAction(s) as list
	*/
	QList<SceneAction*> GetActionSequence()
	{
		return m_ActionsList;
	}
	//! GetSceneTopology
	/*!
		Returns the SceneItem(s) as list
	*/
	QList<SceneItem*> GetSceneTopology()
	{
		return m_TopologyItemsList;
	}
	//! GetComActions
	/*!
		Returns the ComAction(s) as list
	*/
	QList<ComAction*> GetComActions()
	{
		return m_CommunicationActionsList;
	}
    ~ScenarioReader();
private:
	bool ReadToplogy();
	bool ReadActions();
	bool ReadSceneItems();
	bool ReadComActions();

    QString filename;
    QFile file;
    QXmlStreamReader reader;
    QDir dir;
	QList<SceneAction*> m_ActionsList;
	QList<SceneItem*> m_TopologyItemsList;
	QList<ComAction*> m_CommunicationActionsList;
	
};



#endif // BOMADAPTATIONREADER_H
