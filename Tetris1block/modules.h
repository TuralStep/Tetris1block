#pragma once

struct Pixel {
	char element = ' ';
	bool isPlaced = false;
};

struct Table {
	short level = 0;
	Pixel** pixels = nullptr;
};