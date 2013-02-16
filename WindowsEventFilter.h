#pragma once
#include <QtCore\QAbstractNativeEventFilter>
class WindowsEventFilter :
	public QAbstractNativeEventFilter 
{
public:
	WindowsEventFilter(void);
	~WindowsEventFilter(void);
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE;
};

