// 本框架仅供参考，可以根据自己的需求随意进行修改

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

#include "board.h"
using namespace std;

// 请尽量不要使用全局变量

void wait_for_enter();
void print_menu();
void print_help();
void print_exit();
void print_interface(int board[4][4], int score, int step, int mode = CLASSIC);
void play_game(int mode = CLASSIC);
void print_rouge(int generate_mult, int save_me, int win_score);

void play_game(int mode)
{
	// 变量声明
	int board[4][4] = {0}; // 4*4的棋盘
	int score = 0;		  // 分数
	int step = 0;		  // 步数
	char choice = '\0';	  // 用户选择

	// ROUGE
	bool is_rouge = (mode == ROUGE);
	int bonus_count = 6; // 6种不同的奖励
	int choice_count = 2; // 待选个数
	int generate_mult = 1;
	int max_num = 4;
	int win_score = DEFAULT_WIN_SCORE;
	int save_me = 0; // 救命次数


	// 游戏初始化，包括生成随机数等操作
	fill_space(board, generate_mult);
	fill_space(board, generate_mult);
	// 打印游戏界面
	print_interface(board, score, step, mode);
	if (is_rouge) print_rouge(generate_mult, save_me, win_score);

	while (1)
	{
		// 获取用户输入
		choice = _getch();

		// 根据用户输入进行相应操作
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
		// 更新相关数据

		// 打印游戏界面

		print_interface(board, score, step, mode);
		if (is_rouge) print_rouge(generate_mult, save_me, win_score);

		if (is_rouge)
		{
			if (get_max_number(board) > max_num) // 触发肉鸽奖励
			{
				max_num = get_max_number(board);
				char bonus_input;
				cout << "            是时候选择你应得的了……\n";
				int choices[10]{0};
				for (int i = 0; i < choice_count; i++)
				{
					choices[i] = generate_random_int(1, bonus_count);
					cout << "            " << i + 1 << ' ' << bonus_explain(choices[i]) << '\n';
				}
				cout << "            好好选，否则就没机会反悔了……\n";
				bonus_input = _getch();
				int chosen_bonus;
				if (bonus_input < '1' or bonus_input > choice_count + '0')
				{
					chosen_bonus = -1; // 放到default
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
					cout << "            你选择了我未曾设想的选项……奖励已经湮灭……下次注意点……\n";
					wait_for_enter();
					break;
				}
			}
			//
			print_interface(board, score, step, mode);
			print_rouge(generate_mult, save_me, win_score);
		}
		
		// 判断游戏是否结束，如果结束则跳出循环
		int over = is_over(board, score, step, mode, win_score, &save_me);
		if (over == 1) {
			break;
		}
		else if (over == 2) // win
		{
			cout << "You beat the game!!!\n";
			cout << "是否进入无尽模式？输入y继续，按任意其他键结束:\n";
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

	// 游戏结束
	cout << "You lose!!!\n";

	wait_for_enter();
	print_exit();
}

int main()
{
	char choice = '\0';
	// 设置控制台标题为2048
	SetConsoleTitle(TEXT("2048"));
	// 主循环
	while (1)
	{
		// 调用菜单显示函数
		print_menu();
		// 获取用户选择
		choice = _getche();
		//cout << choice;
		// 根据用户选择进行相应操作
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
			cout << "\n输入错误，请再次输入" << endl;
			wait_for_enter();
			break;
		}
	}
	return 0;
}

void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

void print_menu()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "--------------------------------------------\n";
	cout << "********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印标题
	cout << "                   2048\n";
	cout << "                a.经典模式\n";
	cout << "                b.挑战模式\n";
	cout << "                c.ROUGE模式\n";
	cout << "                d.游戏规则\n";
	cout << "                e.退出游戏\n";

	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";

	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n请输入你的选择(a-e):";
}

void print_help()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印游戏规则
	cout << "操作说明：\n\n";
	cout << "↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	cout << "游戏介绍：\n\n";
	cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
	cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
	cout << "如果得到数字2048，则游戏胜利!\n";
	cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	wait_for_enter();
}

void print_exit()
{
	cout << "\n退出中";
	for (int i = 4; i > 0; --i)
	{
		Sleep(200);
		cout << ".";
	}
	cout << "\n欢迎再次来玩 2048 鸭~\n";
}

void print_number_with_color(int n) {
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄

	// 设置颜色的渐变
	if (n == 2) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN); // 黄色
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
	else if (n == 65536) SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 深紫色
	else SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 超过65536用白色

	cout << n;  // 输出数字n
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN); // 重置颜色
}

void print_interface(int board[4][4], int score, int step, int mode)
{
	// 清屏
	system("CLS");
	//获取标准输入设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	// 打印游戏界面
	cout << "            --------------------------------------------\n";
	cout << "            分数：" << setw(6) << score;
	if (mode == CHALLENGE)
	{
		cout << "    至少分数：" << setw(6) << get_min_score(board, step);
	}
	else
	{
		cout << "        ";
	}
	cout << "    步数：" << setw(6) << step << endl;
	cout << "            --------------------------------------------\n";
	cout << "            ********************************************\n";
	// 设置控制台文字颜色
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

	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            ********************************************\n";
	cout << "            --------------------------------------------\n";
	cout << "            ↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";

	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void print_rouge(int generate_mult, int save_me, int win_score) {
	//获取标准输入设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_GREEN);
	cout << "            --------------------------------------------\n";
	cout << "            倍率：" << setw(6) << generate_mult << "    免死金牌：" << setw(6) << save_me << "    胜利条件：" << setw(6) << win_score << endl;
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}