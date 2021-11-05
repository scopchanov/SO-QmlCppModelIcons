#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QStandardItemModel>
#include <qqml.h>

class Backend : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStandardItemModel *model READ model CONSTANT)
	QML_ELEMENT
	QML_ADDED_IN_MINOR_VERSION(1)
public:
	explicit Backend(QObject *parent = nullptr) :
		QObject(parent),
		m_model(new QStandardItemModel(this)) {
		m_model->appendRow(new QStandardItem(QIcon(":/pix/icons/person.png"),
											 tr("Person")));
		m_model->appendRow(new QStandardItem(QIcon(":/pix/icons/search.png"),
											 tr("Search")));
		m_model->appendRow(new QStandardItem(QIcon(":/pix/icons/cross.png"),
											 tr("Cross")));
		m_model->appendRow(new QStandardItem(QIcon(":/pix/icons/restart.png"),
											 tr("Restart")));
		m_model->appendRow(new QStandardItem(QIcon(":/pix/icons/exit.png"),
											 tr("Exit")));
	}

	QStandardItemModel *model() const { return m_model; }

private:
	QStandardItemModel *m_model;
};

#endif // BACKEND_H
