#ifndef DATECHOOSER_H
#define DATECHOOSER_H

#include <QWindow>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class datechooser : public QWindow
{
	Q_OBJECT
public:
	explicit datechooser(QWindow *parent = 0);

signals:

public slots:

};

#endif // DATECHOOSER_H
