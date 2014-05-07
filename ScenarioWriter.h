
#ifndef SCENEWRITE_H
#define SCENEWRITE_H


#include <qstring.h>
#include <qfile.h>
#include <qxmlstream.h>
#include <qdir.h>
#include <SceneAction.h>
#include <SceneItem.h>
#include <qstringlist.h>
#include <ComAction.h>
	//! ScenarioWriter class
	/*!
		Responsibility: From SceneItems, SceneActions and ComActions list
		Writes Scenario XML file
	*/
class ScenarioWriter
{
    

public:
	//! Constructor
	/*!
		\param fileName as string
	*/
    ScenarioWriter(QString fileName);
	//! WriteAndColose
	/*!
		Writes the in memory objects as string and writes to the specified file
		and returns true on success
	*/
	bool WriteAndClose();
	//! AddTopologyItem
	/*!
		\param item as SceneItem
		Add scene items to topology list
	*/
	void AddTopologyItem(SceneItem* item);
	//! AddActions
	/*!
		\param action as SceneAction
		Add scene actions to actions list
	*/
	void AddActions(SceneAction* action);
	//! AddComActions
	/*!
		\param comAction as ComAction
		Add communication actions to com actions list
	*/
	void AddComActions(ComAction* comAction);
private:
    
    QFile file;
    QXmlStreamReader reader;
	//QXmlStreamWriter writer;
    QDir dir;
	QString m_currentFileName;
	QList<SceneAction*> m_ActionsList;
	QList<SceneItem*> m_TopologyItemsList;
	QList<ComAction*> m_CommunicationActionsList;
	
};

#endif
