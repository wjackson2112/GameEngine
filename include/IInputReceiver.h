#ifndef IINPUT_RECEIVER_H
#define IINPUT_RECEIVER_H

class IInputReceiver
{
public:
	virtual void mouseInputCallback(double xpos, double ypos) {};
	virtual void keyInputCallback(int key, int scancode, int action, int mods) {};
};

#endif
