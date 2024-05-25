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
void print_red(string str);
void print_green(string str);

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
			if (to_down(board, &score))
			{
				fill_space(board, generate_mult);
				step++;
			}
			break;
		case 'K':
			if (to_left(board, &score)) {
				fill_space(board, generate_mult);
				step++;
			}
			break;
		case 'H':
			if (to_up(board, &score)) {
				fill_space(board, generate_mult);
				step++;
			}
			break;
		case 'M':
			if (to_right(board, &score))
			{
				fill_space(board, generate_mult);
				step++;
			}
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
					print_red("            你选择了我未曾设想的选项……奖励已经湮灭……下次注意点……\n");
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
			print_green("You beat the game!!!\n");
			print_green("是否进入无尽模式？输入y继续，按任意其他键结束:\n");
			char key = _getch();
			if (key == 'y' || key == 'Y')
			{
				mode = INFI;
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
	print_red("You lose!!!");

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
			exit(0);
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
	cout << endl << "按回车键继续……";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

void print_red(string str) {
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED);
	// 恢复控制台文字颜色为默认颜色
	cout << str;
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void print_green(string str) {
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle_out, FOREGROUND_GREEN);
	// 恢复控制台文字颜色为默认颜色
	cout << str;
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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
	
	// 打印标题
	SetConsoleTextAttribute(handle_out, FOREGROUND_GREEN);
	cout << R"(                                                                    
 .-----.    .----.       .---.     .-----.   
/ ,-.   \  /  ..  \     / .  |    /  .-.  \  
'-'  |  | .  /  \  .   / /|  |   |   \_.' /  
   .'  /  |  |  '  |  / / |  |_   /  .-. '.  
 .'  /__  '  \  /  ' /  '-'    | |  |   |  | 
|       |  \  `'  /  `----|  |-'  \  '-'  /  
`-------'   `---''        `--'     `----''   
)";
	//cout << "                   2048\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE);
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
	cout << "经典模式：\n\n";
	cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
	cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
	cout << "如果得到数字2048，则游戏胜利!\n";
	cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
	cout << "--------------------------------------------\n";
	cout << "挑战模式：\n\n";
	cout << "在经典模式的基础上，给那些不满足于基础难度的玩家准备，增加了最低分数这一限制条件。\n";
	cout << "最低分数与游戏当前的状态相关：步数和最大数字越高，所需的最低分数越高。\n";
	cout << "当分数低于最低分数的时候，游戏结束。\n";
	cout << "--------------------------------------------\n";
	cout << "ROUGE模式：\n\n";
	cout << "在经典模式的基础上，为游戏添加了更多的决策挑战。\n";
	cout << "在该模式中，玩家的目的是：在通关的基础上，挑战达到更高的分数。\n";
	cout << "每次游戏中的最大数字提升时，玩家可以从以下6种增益中的两个选择其一：\n";
	cout << "	“富有”：将场上的点数翻倍。你变得富有了……吗?\n";
	cout << "	“湮灭”：随机炸掉 4 个最小的数字。毁灭吧……\n";
	cout << "	“免死”：当你濒死的时候，随机炸掉一个最小数字，拯救你。你还活着……暂时的\n";
	cout << "	“下注”：将随机生成的数字翻倍。看起来是件好事……\n";
	cout << "	“豪赌”：清零分数。将场上的所有数字变为最大数字。这是否值得呢……\n";
	cout << "	“祈求”：胜利所需的最大数字减半。你可能能更容易获胜……但也仅此而已。\n";
	print_red("“增益”可能会有负面选项，请谨慎选择，此选项会在本局中永久生效。\n");

	
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

inline void clearScreen() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	if (hConsole == INVALID_HANDLE_VALUE) return;

	// 获取控制台屏幕缓冲区信息
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	// 用空格填充整个缓冲区
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) return;

	// 设置控制台缓冲区属性
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

	// 设置光标位置
	SetConsoleCursorPosition(hConsole, homeCoords);
}

void print_interface(int board[4][4], int score, int step, int mode)
{
	// 清屏
	clearScreen();
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