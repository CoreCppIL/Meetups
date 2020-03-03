#pragma once

class WidgetBase
{
public:
	virtual bool True() const;

#if LIB_VERSION == 2
private:
	virtual void f() const;
#endif
};

class Widget : public WidgetBase
{
public:
	virtual bool False() const;
};

void weird(const Widget&);
const Widget& getWidget();
