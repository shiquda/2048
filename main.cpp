// ����ܽ����ο������Ը����Լ���������������޸�

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

#include "board.h"
using namespace std;

// �뾡����Ҫʹ��ȫ�ֱ���

void wait_for_enter();
void print_menu();
void print_help();
void print_exit();
void print_interface(int board[4][4], int score, int step, int mode = CLASSIC);
void play_game(int mode = CLASSIC);
void print_rouge(int generate_mult, int save_me, int win_score);

void play_game(int mode)
{
	// ��������
	int board[4][4] = {0}; // 4*4������
	int score = 0;		  // ����
	int step = 0;		  // ����
	char choice = '\0';	  // �û�ѡ��

	// ROUGE
	bool is_rouge = (mode == ROUGE);
	int bonus_count = 6; // 6�ֲ�ͬ�Ľ���
	int choice_count = 2; // ��ѡ����
	int generate_mult = 1;
	int max_num = 4;
	int win_score = DEFAULT_WIN_SCORE;
	int save_me = 0; // ��������


	// ��Ϸ��ʼ������������������Ȳ���
	fill_space(board, generate_mult);
	fill_space(board, generate_mult);
	// ��ӡ��Ϸ����
	print_interface(board, score, step, mode);
	if (is_rouge) print_rouge(generate_mult, save_me, win_score);

	while (1)
	{
		// ��ȡ�û�����
		choice = _getch();

		// �����û����������Ӧ����
		switch (choice)
		{
		case 'P':
			to_down(board, &score);

			fill_space(board, generate_mult);
			step++;
			break;
		case 'K':
			to_left(board, &score);
			fill_space(board, generate_mult);
			step++;
			break;
		case 'H':
			to_up(board, &score);
			fill_space(board, generate_mult);
			step++;
			break;
		case 'M':
			to_right(board, &score);
			fill_space(board, generate_mult);
			step++;
			break;
		case 27: // esc
			print_exit();
			return;
		default:
			//cout << choice;
			break;
		}
		// �����������

		// ��ӡ��Ϸ����

		print_interface(board, score, step, mode);
		if (is_rouge) print_rouge(generate_mult, save_me, win_score);

		if (is_rouge)
		{
			if (get_max_number(board) > max_num) // ������뽱��
			{
				max_num = get_max_number(board);
				char bonus_input;
				cout << "            ��ʱ��ѡ����Ӧ�õ��ˡ���\n";
				int choices[10]{0};
				for (int i = 0; i < choice_count; i++)
				{
					choices[i] = generate_random_int(1, bonus_count);
					cout << "            " << i + 1 << ' ' << bonus_explain(choices[i]) << '\n';
				}
				cout << "            �ú�ѡ�������û���ᷴ���ˡ���\n";
				bonus_input = _getch();
				int chosen_bonus;
				if (bonus_input < '1' or bonus_input > choice_count + '0')
				{
					chosen_bonus = -1; // �ŵ�default
				}
				else
				{
					chosen_bonus = choices[bonus_input - 1 - '0'];
				}
				switch (chosen_bonus)
				{
				case ELEVATE:
					elevate(board);
					max_num *= 2;
					break;
				case BUMB:
					for (int i = 0; i < 4; i++)
					{
						bump(board);
					}
					break;
				case SAVE:
					save_me++;
					break;
				case ENHANCE_GENERATE:
					generate_mult *= 2;
					break;
				case MAGIC:
					score = 0;
					magic(board);
					break;
				case EASY_WIN:
					win_score /= 2;
					break;
				default:
					cout << "            ��ѡ������δ�������ѡ��������Ѿ����𡭡��´�ע��㡭��\n";
					wait_for_enter();
					break;
				}
			}
			//
			print_interface(board, score, step, mode);
			print_rouge(generate_mult, save_me, win_score);
		}
		
		// �ж���Ϸ�Ƿ�������������������ѭ��
		int over = is_over(board, score, step, mode, win_score, &save_me);
		if (over == 1) {
			break;
		}
		else if (over == 2) // win
		{
			cout << "You beat the game!!!\n";
			cout << "�Ƿ�����޾�ģʽ������y����������������������:\n";
			char key = _getch();
			if (key == 'y' || key == 'Y')
			{
				mode = INFINITE;
				print_interface(board, score, step, mode);
			}
			else
			{
				print_exit();
				return;
			}
		}
	}

	// ��Ϸ����
	cout << "You lose!!!\n";

	wait_for_enter();
	print_exit();
}

int main()
{
	char choice = '\0';
	// ���ÿ���̨����Ϊ2048
	SetConsoleTitle(TEXT("2048"));
	// ��ѭ��
	while (1)
	{
		// ���ò˵���ʾ����
		print_menu();
		// ��ȡ�û�ѡ��
		choice = _getche();
		//cout << choice;
		// �����û�ѡ�������Ӧ����
		switch (choice)
		{
		case 'a':
			play_game(CLASSIC);
			break;
		case 'b':
			play_game(CHALLENGE);
			break;
		case 'c':
			play_game(ROUGE);
			break;
		case 'd':
			print_help();
			break;
		case 'e':
			print_exit();
			break;
		default:
			cout << "\n����������ٴ�����" << endl;
			wait_for_enter();
			break;
		}
	}
	return 0;
}

void wait_for_enter()
{
	cout << endl << "���س�������";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

void print_menu()
{
	// ����
	system("CLS");
	// ��ȡ��׼����豸���
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// ��ӡ�˵�
	cout << "--------------------------------------------\n";
	cout << "********************************************\n";
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// ��ӡ����
	cout << "                   2048\n";
	cout << "                a.����ģʽ\n";
	cout << "                b.��սģʽ\n";
	cout << "                c.ROUGEģʽ\n";
	cout << "                d.��Ϸ����\n";
	cout << "                e.�˳���Ϸ\n";

	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// ��ӡ�˵�
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";

	// �ָ�����̨������ɫΪĬ����ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n���������ѡ��(a-e):";
}

void print_help()
{
	// ����
	system("CLS");
	// ��ȡ��׼����豸���
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n\n";
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// ��ӡ��Ϸ����
	cout << "����˵����\n\n";
	cout << "������   ������  ������  ������  ESC�����˳�\n\n";
	cout << "��Ϸ���ܣ�\n\n";
	cout << "ÿ��ѡ��һ�������ƶ����ƶ�ʱ������÷���£\n";
	cout << "��ͬ���ֿɺϲ����ƶ���ո񴦻������������2/4\n";
	cout << "����õ�����2048������Ϸʤ��!\n";
	cout << "������̱������������޷������ƶ�������Ϸʧ��!\n\n";
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	// �ָ�����̨������ɫΪĬ����ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	wait_for_enter();
}

void print_exit()
{
	cout << "\n�˳���";
	for (int i = 4; i > 0; --i)
	{
		Sleep(200);
		cout << ".";
	}
	cout << "\n��ӭ�ٴ����� 2048 Ѽ~\n";
}

void print_number_with_color(int n) {
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���

	// ������ɫ�Ľ���
	if (n == 2) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN); // ��ɫ
	else if (n == 4) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (n == 8) SetConsoleTextAttribute(handle_out, FOREGROUND_RED);
	else if (n == 16) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_INTENSITY);
	else if (n == 32) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_BLUE);
	else if (n == 64) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	else if (n == 128) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE);
	else if (n == 256) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	else if (n == 512) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	else if (n == 1024) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (n == 2048) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (n == 4096) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_RED);
	else if (n == 8192) SetConsoleTextAttribute(handle_out, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	else if (n == 16384) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (n == 32768) SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (n == 65536) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ����ɫ
	else SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ����65536�ð�ɫ

	cout << n;  // �������n
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN); // ������ɫ
}

void print_interface(int board[4][4], int score, int step, int mode)
{
	// ����
	system("CLS");
	//��ȡ��׼�����豸���
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	// ��ӡ��Ϸ����
	cout << "            --------------------------------------------\n";
	cout << "            ������" << setw(6) << score;
	if (mode == CHALLENGE)
	{
		cout << "    ���ٷ�����" << setw(6) << get_min_score(board, step);
	}
	else
	{
		cout << "        ";
	}
	cout << "    ������" << setw(6) << step << endl;
	cout << "            --------------------------------------------\n";
	cout << "            ********************************************\n";
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                       |----|----|----|----|\n";

	for (int i = 0; i < 4; i++)
	{
		cout << "                       |";
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] != 0)
			{
				cout << setw(4);
				print_number_with_color(board[i][j]);
				cout << "|";
			}
			else
			{
				cout << "    |";
			}
		}
		cout << "\n                       |----|----|----|----|\n";
	}

	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            ********************************************\n";
	cout << "            --------------------------------------------\n";
	cout << "            ������   ������  ������  ������  ESC�����˳�\n\n";

	// �ָ�����̨������ɫΪĬ����ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void print_rouge(int generate_mult, int save_me, int win_score) {
	//��ȡ��׼�����豸���
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_GREEN);
	cout << "            --------------------------------------------\n";
	cout << "            ���ʣ�" << setw(6) << generate_mult << "    �������ƣ�" << setw(6) << save_me << "    ʤ��������" << setw(6) << win_score << endl;
	// �ָ�����̨������ɫΪĬ����ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}