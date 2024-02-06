#ifndef INPUT_RECIEVER_H
#define INPUT_RECIEVER_H

class InputReciever {
public:
	virtual void onScroll(float offset) = 0;
	virtual void onMouseClick(int button, int action) = 0;
};

#endif