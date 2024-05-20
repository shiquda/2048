#include <random>
#include "board.h"

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
	uniform_int_distribution<> dis(0, 3);
	return (dis(gen) == 0) ? 4 : 2; // 0.25概率生成4
}

int generate_random_int(int a, int b) {
	random_device rd;  // 用于生成种子
	mt19937 gen(rd()); // 采用Mersenne Twister随机数生成器
	uniform_int_distribution<> dis(a, b);
	return dis(gen);
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

void fill_space(int board[4][4], int mult) {
	int space_count = find_space_count(board);
	if (space_count == 0) return;
	int random_idx = generate_random_int(1, space_count);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
			{
				random_idx--;
				if (random_idx == 0)
				{
					board[i][j] = generate_two_or_four() * mult;
					return;
				}
			}
		}
	}
}

int get_max_number(int board[4][4]) {
	int max = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] > max)
			{
				max = board[i][j];
			}
		}
	}
	return max;
}

int get_min_score(int board[4][4], int step) {
	int max_num = get_max_number(board);
	int y = int(log2(step + 1) * sqrt(max_num * step) / 1.25) - 32; // 难度曲线
	return y >= 0 ? y : 0;
}

int is_over(int board[4][4], int score, int step, int mode, int win_score, int *save_me) {
	if (get_max_number(board) >= win_score && mode != INFINITE)
	{
		return 2; // Win
	}
	if (mode == CHALLENGE)
	{
		if (score < get_min_score(board, step))
		{
			return 1; // lose
		}
	}

	int board_copy[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board_copy[i][j] = board[i][j];
		}
	}
	int temp_score = 0;
	to_left(board_copy, &temp_score);
	to_right(board_copy, &temp_score);
	to_up(board_copy, &temp_score);
	to_down(board_copy, &temp_score);
	if (find_space_count(board_copy) == 0) // 满了
	{
		if (save_me != nullptr && *save_me > 0)
		{
			(*save_me)--;
			bump(board);
			return 0;
		}
		return 1; // lose
	}
	return 0;
}

string bonus_explain(int type) {
	switch (type)
	{
	case ELEVATE:
		return "“富有”：将场上的点数翻倍。你变得富有了……吗?";
	case BUMB:
		return "“湮灭”：随机炸掉 4 个最小的数字。毁灭吧……";
	case SAVE:
		return "“免死”：当你濒死的时候，随机炸掉一个最小数字，拯救你。你还活着……暂时的。";
	case ENHANCE_GENERATE:
		return "“下注”：将随机生成的数字翻倍。这笔投资看起来是件好事……";
	case MAGIC:
		return "“豪赌”：清零分数。将场上的所有数字变为最大数字。这是否值得呢……";
	case EASY_WIN:
		return "“祈求”：胜利所需的最大数字减半。你可能能更容易获胜……但也仅此而已。";
	default:
		break;
	}
	return "";
}

void elevate(int board[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board[i][j] *= 2;
		}
	}
}

void bump(int board[4][4]) { // 清除最小的数字
	int min_num = 65536;
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (min_num > board[i][j] && board[i][j] != 0)
			{
				min_num = board[i][j];
				count++;
			}
			else
			{
				count = 1;
			}
		}
	}
	// 随机去除最小的数
	int random_idx = generate_random_int(1, count);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == min_num)
			{
				random_idx--;
				if (random_idx == 0)
				{
					board[i][j] = 0;
					return;
				}
			}
		}
	}
}

void magic(int board[4][4]) {
	int max_num = get_max_number(board);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] != 0)
			{
				board[i][j] = max_num;
			}
		}
	}
}

