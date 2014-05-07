#ifndef AUTOMATIONWIZARD_H
#define AUTOMATIONWIZARD_H

#include <QMainWindow>
#include "ui_automationwizard.h"
#include <qprocess.h>
#include <qdir.h>
#include <qpoint.h>
#include "..\BOMGraphicalLibrary\bominstance.h"

//! AutomationWizard Class
/*!
	Responsibility: Container for AutomationWizard
*/
class AutomationWizard : public QMainWindow
{
	Q_OBJECT

public:
    AutomationWizard(QWidget *parent = 0, Qt::WindowFlags flags = 0);//Qt::WFlags flags = 0);
	~AutomationWizard();
	private slots:
		void openScenarioPlayer();
        void loadScenario();
private:
	Ui::AutomationWizardClass ui;
	QAction* m_openAction;
	QAction* m_newAction;
	QAction* m_playScenario;
	
};

#endif // AUTOMATIONWIZARD_H
