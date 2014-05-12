#ifndef AUTOMGRAPHVIEW_H
#define AUTOMGRAPHVIEW_H
#include "qgraphicsview.h"
#include <qgraphicssceneevent.h>
#include "AutomGraphicsScene.h"
#include <QMouseEvent>
#include <qmenu.h>
#include <ScenarioWriter.h>
#include <ScenarioReader.h>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QMouseEvent;
QT_END_NAMESPACE

	using namespace BOMLIB;
//! AutomGraphicsView Class
/*!
	Responsibility: Inheriting from QGraphicsView this is responsible for
	Supporting drag and drop of BOM Object types. Holds QGraphicsScene which in turn
	holds BOM Instances and Graphics items and provides helper functions for finding 
	the BOMType based on name.
*/
class AutomGraphicsView :	public QGraphicsView
{
	Q_OBJECT
public:
	//! Constructor
	/*!
		\param bomTypesList BOMObjects as List
		\param iBOMTypeLoad IBOMTypeLoadInterface
		\param iBOMInstCreat IBOMInstanceCreation
	*/
	explicit AutomGraphicsView(QList<BOMObject*> bomTypesList,  IBOMTypeLoadInterface* iBOMTypeLoad, IBOMInstanceCreation* iBOMInstCreat, QWidget *parent=0) ;
	//AutomGraphicsView(QList<BOMObject*> BOMObjectTypes, IBOMTypeLoadInterface* iBOMTypeLoad,QWidget *parent = 0);
	//! Destructor
	~AutomGraphicsView(void);
	/*QGraphicsScene* getCurrentScene()
	{
		return scene;
	}*/
	//! getCurrentScene
	/*!
		Return the scene associated with the view
	*/
	AutomGraphicsScene* getCurrentScene()
	{
		return scene;
	}
	//! getCurrentSceneActions
	/*!
		Return the list of sceneAction(s)
	*/
	QList<SceneAction*> getCurrentSceneActions()
	{
		return m_currentSceneActions;
	}
	//! setCurrentSceneActionList
	/*!
		Set the sceneAction(s)
	*/
	void setCurrentSceneActionList(QList<SceneAction*> sceneActions)
	{
		m_currentSceneActions=sceneActions;
	}
    //! setCurrentSceneItems
    /*!
        Set the sceneItem(s)
    */
    void setCurrentSceneItemsList(QList<SceneItem*> sceneItems)
    {
        m_currentSceneItems=sceneItems;
    }
protected:
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void contextMenuEvent(QContextMenuEvent *event);
private:
      //QGraphicsScene * scene;
	  AutomGraphicsScene* scene;	
	  QList<BOMObject*> m_BOMTypesList;
	QList<BOMInstance*> m_BOMInstanceList;
	BOMObject* FindBOMType(QString BOMTypeName);
	IBOMTypeLoadInterface* m_BOMTypeLoader;
	IBOMInstanceCreation* m_BOMInstanceCreator;
	void ReadScenario(QString fileName);


	  QAction* m_actConnectItems;
	  QAction* m_actClearAll;
	  QAction* m_actSaveScene;
	  QAction* m_actActions;
	  QMenu* m_MainContextMenu;
	  QMenu* m_connectSubMenu;
	  QMenu* m_addActionSubMenu;

	  QAction* m_actOpenScenarioFromFile;


	  //current Actions and Topology
	QList<SceneAction*> m_currentSceneActions;
	QList<SceneItem*> m_currentSceneItems;

private slots:
    void doConnectItems();
	void clearAllItems();
	void doSaveScene();
	void openScenarioFromFile();
};

#endif
