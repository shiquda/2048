#include <random>

using namespace std;

void to_left(int board[4][4], int* score) {
	// 重力
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (board[i][k] == 0)
				{
					board[i][k] = board[i][k + 1];
					board[i][k + 1] = 0;
				}
			}
		}
	}
	// 合并
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == board[i][j + 1]) {
				(*score) += board[i][j];
				board[i][j] *= 2;
				board[i][j + 1] = 0;
			}
		}
	}
	// 重力
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (board[i][k] == 0)
				{
					board[i][k] = board[i][k + 1];
					board[i][k + 1] = 0;
				}
			}
		}
	}
}

void to_right(int board[4][4], int* score) {
	// 右移重力
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			for (int k = 2; k >= 0; k--) {
				if (board[i][k + 1] == 0) {
					board[i][k + 1] = board[i][k];
					board[i][k] = 0;
				}
			}
		}
	}
	// 合并
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (board[i][j + 1] == board[i][j]) {
				(*score) += board[i][j + 1];
				board[i][j + 1] *= 2;
				board[i][j] = 0;
			}
		}
	}
	// 重力
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			for (int k = 2; k >= 0; k--) {
				if (board[i][k + 1] == 0) {
					board[i][k + 1] = board[i][k];
					board[i][k] = 0;
				}
			}
		}
	}
}


void to_up(int board[4][4], int* score) {
	// 向上重力
	for (int j = 0; j < 4; j++) {
		for (int i = 1; i < 4; i++) {
			for (int k = i; k > 0; k--) {
				if (board[k - 1][j] == 0) {
					board[k - 1][j] = board[k][j];
					board[k][j] = 0;
				}
			}
		}
	}
	// 合并
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (board[i][j] == board[i + 1][j]) {
				(*score) += board[i][j];
				board[i][j] *= 2;
				board[i + 1][j] = 0;
			}
		}
	}
	// 重力
	for (int j = 0; j < 4; j++) {
		for (int i = 1; i < 4; i++) {
			for (int k = i; k > 0; k--) {
				if (board[k - 1][j] == 0) {
					board[k - 1][j] = board[k][j];
					board[k][j] = 0;
				}
			}
		}
	}
}


void to_down(int board[4][4], int* score) {
	// 向下重力
	for (int j = 0; j < 4; j++) {
		for (int i = 2; i >= 0; i--) {
			for (int k = i; k < 3; k++) {
				if (board[k + 1][j] == 0) {
					board[k + 1][j] = board[k][j];
					board[k][j] = 0;
				}
			}
		}
	}
	// 合并
	for (int j = 0; j < 4; j++) {
		for (int i = 2; i >= 0; i--) {
			if (board[i + 1][j] == board[i][j]) {
				(*score) += board[i + 1][j];
				board[i + 1][j] *= 2;
				board[i][j] = 0;
			}
		}
	}
	// 重力
	for (int j = 0; j < 4; j++) {
		for (int i = 2; i >= 0; i--) {
			for (int k = i; k < 3; k++) {
				if (board[k + 1][j] == 0) {
					board[k + 1][j] = board[k][j];
					board[k][j] = 0;
				}
			}
		}
	}
}


inline int generate_two_or_four() {
	random_device rd;  // 用于生成种子
	mt19937 gen(rd()); // 采用Mersenne Twister随机数生成器
	uniform_int_distribution<> dis(0, 1);
	return (dis(gen) == 0) ? 2 : 4;
}

int find_space_count(int board[4][4]) {
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j]==0)
			{
				count++;
			}
		}
	}
	return count;
}

void fill_space(int board[4][4]) {
	int space_count = find_space_count(board);
	random_device rd;  // 用于生成种子
	mt19937 gen(rd()); // 采用Mersenne Twister随机数生成器
	uniform_int_distribution<> dis(1, space_count);
	int random_idx = dis(gen);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
			{
				random_idx--;
				if (random_idx == 0)
				{
					board[i][j] = generate_two_or_four();
					return;
				}
			}
		}
	}
}