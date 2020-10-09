#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <windows.h>
using namespace std;

void SetPixel(int x, int y, COLORREF color) {
	HDC hdc = GetWindowDC(GetDesktopWindow());
	Sleep(1);
	SetPixel(hdc, x, y, color);
}

void drawpixel(int x, int y, COLORREF color) {
	SetPixel(x, y, color);
}

COLORREF getpixel(int x, int y) {
	HDC hdc = GetWindowDC(GetDesktopWindow());
	return GetPixel(hdc, x, y);
}

void Bresenham_Line(int x0, int y0, int x1, int y1, COLORREF color) {
	int dx, dy, e, x, y;
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

struct Line {
	int x0, y0, x1, y1;
};

struct Poly {
	vector<Line> lines;
};

struct AET_S {
	double x, delta_x;
	int ymax;

	bool operator < (AET_S part) {
		return x < part.x;
	}
};

void polyfill(Poly polygon, COLORREF color) {
	int max_y = 0;
	int min_y = 1e9;

	for (Line line : polygon.lines) {
		max_y = max(max_y, min(line.y0, line.y1));
		min_y = min(min_y, min(line.y0, line.y1));
	}

	vector<Line>* NET = new vector<Line>[max_y + 5];

	for (Line line : polygon.lines) {
		NET[min(line.y0, line.y1)].push_back(line);
	}

	vector<AET_S> AET;
	vector<AET_S> AET_tmp;

	for (int i = min_y; i <= max_y; i++) {
		for (Line line : NET[i]) {
			AET_S t;
			if (line.y0 - line.y1 == 0) continue;
			t.x = min(line.x0, line.x1);
			t.delta_x = ((double)line.x0 - line.x1) / ((double)line.y0 - line.y1);
			t.ymax = max(line.y0, line.y1);
			AET.push_back(t);
		}

		sort(AET.begin(), AET.end());

		int p1 = 0, p2 = 1, SZ = AET.size();
		while (p2 < SZ) {
			int L = AET[p1].x + 0.5;
			int R = AET[p2].x + 0.5;

			for (int x = L; x < R; x++) drawpixel(x, i, color);

			p1 += 2;
			p2 += 2;
		}

		AET_tmp.clear();
		for (AET_S it : AET) {
			if (it.ymax > i) {
				it.x += it.delta_x;
				AET_tmp.push_back(it);
			}
		}

		AET.clear();
		for (AET_S it : AET_tmp) {
			AET.push_back(it);
		}
	}

	delete[] NET;
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

int main() {

	return 0;
}