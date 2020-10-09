#include <stack>
#include <windows.h>
using namespace std;

void SetPixel(int x, int y, COLORREF color) {
	HDC hdc = GetWindowDC(GetDesktopWindow());
	Sleep(1);
	SetPixel(hdc, x, y, color);
}

COLORREF getpixel(int x, int y) {
	HDC hdc = GetWindowDC(GetDesktopWindow());
	return GetPixel(hdc, x, y);
}

struct Seed {
	int x;
	int y;
};

void ScanLineFill4(int x, int y, COLORREF oldcolor, COLORREF newcolor) {
	int xl, xr, i;
	bool spanNeedFill;
	Seed pt;
	stack<Seed> st;
	pt.x = x; pt.y = y;
	st.push(pt);

	while (!st.empty()) {
		pt = st.top(); st.pop();
		y = pt.y;

		x = pt.x;
		while (getpixel(x, y) == oldcolor) {
			SetPixel(x, y, newcolor);
			x++;
		}
		xr = x - 1;

		x = pt.x - 1;
		while (getpixel(x, y) == oldcolor) {
			SetPixel(x, y, newcolor);
			x--;
		}
		xl = x + 1;

		x = xl;
		y = y + 1;
		while (x < xr) {
			spanNeedFill = false;
			while (getpixel(x, y) == oldcolor) {
				spanNeedFill = true;
				x++;
			}

			if (spanNeedFill) {
				pt.x = x - 1;
				pt.y = y;
				st.push(pt);
				spanNeedFill = false;
			}

			while (getpixel(x, y) != oldcolor && x < xr) x++;
		}

		x = xl;
		y = y - 2;
		while (x < xr) {
			spanNeedFill = false;
			while (getpixel(x, y) == oldcolor) {
				spanNeedFill = true;
				x++;
			}

			if (spanNeedFill) {
				pt.x = x - 1;
				pt.y = y;
				st.push(pt);
				spanNeedFill = false;
			}

			while (getpixel(x, y) != oldcolor && x < xr) x++;
		}
	}
}
