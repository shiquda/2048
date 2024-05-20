#include <random>
#include "board.h"

using namespace std;

void to_left(int board[4][4], int* score) {
	// ����
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
	// �ϲ�
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
	// ����
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
	// ��������
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
	// �ϲ�
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (board[i][j + 1] == board[i][j]) {
				(*score) += board[i][j + 1];
				board[i][j + 1] *= 2;
				board[i][j] = 0;
			}
		}
	}
	// ����
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
	// ��������
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
	// �ϲ�
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (board[i][j] == board[i + 1][j]) {
				(*score) += board[i][j];
				board[i][j] *= 2;
				board[i + 1][j] = 0;
			}
		}
	}
	// ����
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
	// ��������
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
	// �ϲ�
	for (int j = 0; j < 4; j++) {
		for (int i = 2; i >= 0; i--) {
			if (board[i + 1][j] == board[i][j]) {
				(*score) += board[i + 1][j];
				board[i + 1][j] *= 2;
				board[i][j] = 0;
			}
		}
	}
	// ����
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
	random_device rd;  // ������������
	mt19937 gen(rd()); // ����Mersenne Twister�����������
	uniform_int_distribution<> dis(0, 3);
	return (dis(gen) == 0) ? 4 : 2; // 0.25��������4
}

int generate_random_int(int a, int b) {
	random_device rd;  // ������������
	mt19937 gen(rd()); // ����Mersenne Twister�����������
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
	int y = int(log2(step + 1) * sqrt(max_num * step) / 1.25) - 32; // �Ѷ�����
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
	if (find_space_count(board_copy) == 0) // ����
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
		return "�����С��������ϵĵ������������ø����ˡ�����?";
	case BUMB:
		return "�����𡱣����ը�� 4 ����С�����֡�����ɡ���";
	case SAVE:
		return "�������������������ʱ�����ը��һ����С���֣������㡣�㻹���š�����ʱ�ġ�";
	case ENHANCE_GENERATE:
		return "����ע������������ɵ����ַ��������Ͷ�ʿ������Ǽ����¡���";
	case MAGIC:
		return "�����ġ�����������������ϵ��������ֱ�Ϊ������֡����Ƿ�ֵ���ء���";
	case EASY_WIN:
		return "�����󡱣�ʤ�������������ּ��롣������ܸ����׻�ʤ������Ҳ���˶��ѡ�";
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

void bump(int board[4][4]) { // �����С������
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
	// ���ȥ����С����
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

