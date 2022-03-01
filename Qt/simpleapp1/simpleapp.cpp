#include <iostream>
#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	QWidget window;
	window.setMinimumSize(720,360);
	
	//widget layout
	QVBoxLayout vlayout;
	QHBoxLayout hlayout;
	//text
	QLabel helloworld{"hello world"};
	//button
	QPushButton button{"close"};

	//add widgets to layout
	hlayout.addStretch(0);
	hlayout.addLayout(&vlayout);
	vlayout.addStretch(0);
	vlayout.addWidget(&helloworld);
	vlayout.addWidget(&button);
	vlayout.addStretch(0);
	hlayout.addStretch(0);

	//signal slot
	QObject::connect(&button, SIGNAL(clicked()), &app, SLOT(quit()));


	window.setLayout(&hlayout);	
	window.show();
	return app.exec();
}
