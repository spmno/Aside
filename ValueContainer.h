#pragma once
class ValueContainer
{
public:
	static ValueContainer& getInstance()
	{
		static ValueContainer instance;
		return instance;
	}
	~ValueContainer(void);
	unsigned short collectHotkeyId;
private:
	ValueContainer(void);


};

