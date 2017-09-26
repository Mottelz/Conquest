#pragma once

class Die {

public:
	//ctor declaration
	Die();
	Die(int v);

	//function delcaration
	int getValue();
	void setValue(int v);

private:
	//instance variables
	int value;
};
