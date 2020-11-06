#ifndef TESTLISTWIDGETWITHIMAGE_H
#define TESTLISTWIDGETWITHIMAGE_H

#include <QWidget>
#include "ui_testlistwidgetwithimage.h"
#include <TypesList.h>
#include <QHBoxLayout>
#include <qstandarditemmodel.h>
class TestListWidgetwithImage : public QWidget
{
	Q_OBJECT

public:
	TestListWidgetwithImage(QWidget *parent = 0);
	~TestListWidgetwithImage();

private:
	void setupWidgets();

	Ui::TestListWidgetwithImage ui;
	TypesList * m_typesList;
	QStandardItemModel* iStandardModel;
	QListView* contentsListView;
};

#endif // TESTLISTWIDGETWITHIMAGE_H
