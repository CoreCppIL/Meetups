#pragma once

class Widget
{
public:
	virtual bool True() const;

#if LIB_VERSION == 2
private:
	virtual void f() const;
#endif

public:
	virtual bool False() const;
};

void weird(const Widget&);
const Widget& getWidget();
