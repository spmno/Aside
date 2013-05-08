#pragma once
#include <QtWidgets\qwidget.h>
class Aside;
class WindowsManager
{
public:
	static WindowsManager& getInstance() 
	{
		static WindowsManager instance;
		return instance;
	}
	
	~WindowsManager(void);
	Aside* mainWindow;
	
private:
	WindowsManager(void);
	
};

