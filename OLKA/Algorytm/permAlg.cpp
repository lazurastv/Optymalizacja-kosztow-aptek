

int getPivotColumn(char* col, int len) {
	int min = 0;
	int min_i = -1;
	for (int i = 0; i < len; i++) {
		if (col[i] < min) {
			min = col[i];
			min_i = i;
		}
	}
	return min_i;
}

int getPivotRow(char* row, char* b int height) {
	if (height < 1) {
		throw std::illegal_argument("Height must be greater than 0, but is " + height.to_string() + "!");
	}
	double min = 1.0 * b[0] / row[0];
	int min_i = 0;
	for (int i = 1; i < height; i++) {
		double ratio = 1.0 * b[i] / row[i];
		if (ratio < min) {
			min = ratio;
			min_i = i;
		}
	}
	return min_i;
}

void loadData(double** 

int main() {
	return 0;
}