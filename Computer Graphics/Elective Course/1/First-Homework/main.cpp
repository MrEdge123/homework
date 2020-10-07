#include <iostream>
#include <gl/glut.h>
using namespace std;

void SetPixel(int x, int y, int color) {
	printf("x:%d y:%d color:%d\n", x, y, color);
}

void Bresenham_Line(int x0, int y0, int x1, int y1, int color) {
	int dx, dy, e, i, x, y;
	dx = x1 - x0, dy = y1 - y0;

	if (dx < 0) {             //从左到右画点
		swap(x0, x1);
		swap(y0, y1);
		dx = -dx;
		dy = -dy;
	}

	bool flag_y = false;      //沿y轴对称变换
	if (dy < 0) {
		y0 = -y0;
		y1 = -y1;
		dy = -dy;
		flag_y = true;
	}

	bool flag_swap = false;   //沿着y=x对称变换
	if (dx == 0 || dy > dx) {
		swap(x0, y0);
		swap(x1, y1);
		swap(dx, dy);
		flag_swap = true;
	}

	e = 2 * dy - dx;
	x = x0, y = y0;

	for (int i = 0; i <= dx; i++) {
		if (!flag_y) {
			if (!flag_swap) SetPixel(x, y, color);
			else SetPixel(y, x, color);
		}
		else {
			if (!flag_swap) SetPixel(x, -y, color);
			else SetPixel(y, -x, color);
		}

		x++;
		if (e >= 0) {
			y++;
			e = e + 2 * dy - 2 * dx;
		}
		else {
			e = e + 2 * dy;
		}
	}
}

int main() {

	return 0;
}