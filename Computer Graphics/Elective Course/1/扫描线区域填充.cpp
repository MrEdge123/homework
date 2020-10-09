#include <vector>
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