#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <QStandardItemModel>
#include "Backend.h"

class PixmapBuilder : public QQuickImageProvider
{
public:
	explicit PixmapBuilder(QStandardItemModel *model) :
		QQuickImageProvider(QQuickImageProvider::Pixmap),
		m_model(model) {}

	QPixmap requestPixmap(const QString &id, QSize *, const QSize &) override {
		const QModelIndex &index(m_model->index(id.toInt(), 0));
		const QIcon &icon(m_model->data(index, Qt::DecorationRole).value<QIcon>());

		return icon.pixmap(QSize(16, 16));
	}

private:
	QStandardItemModel *m_model;
};

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);
	Backend backend;
	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));

	engine.rootContext()->setContextProperty("backend", &backend);
	engine.addImageProvider(QLatin1String("icons"), new PixmapBuilder(backend.model()));

	qmlRegisterUncreatableType<QStandardItemModel>("QStandardItemModel", 1, 0, "QStandardItemModel",
											"The model should be created in C++");

	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
