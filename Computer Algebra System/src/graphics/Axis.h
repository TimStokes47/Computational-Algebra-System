#ifndef AXIS_H
#define AXIS_H

class Axis2D {
public:
	static void generateVertexArrays();
	static void render();
	static unsigned int getXAxis() { return m_xAxis; }
	static unsigned int getYAxis() { return m_yAxis; }
	static unsigned int getZAxis() { return m_zAxis; }

private:
	static unsigned int m_xAxis;
	static unsigned int m_yAxis;
	static unsigned int m_zAxis;
};


#endif