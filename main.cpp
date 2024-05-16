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
void print_interface(int board[4][4], int score, int step);
void play_game();

void play_game()
{
	// ��������
	int board[4][4] = {0}; // 4*4������
	int score = 0;		  // ����
	int step = 0;		  // ����
	char choice = '\0';	  // �û�ѡ��

	// ��Ϸ��ʼ������������������Ȳ���
	fill_space(board);
	fill_space(board);
	// ��ӡ��Ϸ����
	print_interface(board, score, step);

	while (1)
	{
		// ��ȡ�û�����
		choice = _getch();

		// �����û����������Ӧ����
		//cout << choice << '\n';
		switch (choice)
		{
		case 'P':
			to_down(board, &score);

			fill_space(board);
			step++;
			break;
		case 'K':
			to_left(board, &score);

			fill_space(board);
			step++;
			break;
		case 'H':
			to_up(board, &score);
			fill_space(board);
			step++;
			break;
		case 'M':
			to_right(board, &score);
			fill_space(board);
			step++;
			break;
		default:
			break;
		}
		// �����������

		// ��ӡ��Ϸ����
		print_interface(board, score, step);

		// �ж���Ϸ�Ƿ�������������������ѭ��
		if (find_space_count(board) == 0) break;
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
		cout << choice;
		// �����û�ѡ�������Ӧ����
		switch (choice)
		{
		case 'a':
			play_game();
			break;
		case 'b':
			print_help();
			break;
		case 'c':
			print_exit();
			exit(0);
			break;
		default:
			cout << "\n����������������" << endl;
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
	cout << "                b.��Ϸ����\n";
	cout << "                c.�˳���Ϸ\n";
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// ��ӡ�˵�
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";

	// �ָ�����̨������ɫΪĬ����ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n���������ѡ��(a-c):";
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

void print_interface(int board[4][4], int score, int step)
{
	// ����
	system("CLS");
	//��ȡ��׼�����豸���
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// ���ÿ���̨������ɫ
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	// ��ӡ��Ϸ����
	cout << "            --------------------------------------------\n";
	cout << "            ������" << setw(6) << score << "              ������" << setw(6) << step << endl;
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