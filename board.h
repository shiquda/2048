#define CLASSIC 1
#define CHALLENGE 2
#define INFINITE 3
#define ROUGE 4

void to_left(int board[4][4], int* score);
void to_right(int board[4][4], int* score);
void to_up(int board[4][4], int* score);
void to_down(int board[4][4], int* score);

int generate_two_or_four();
int find_space_count(int board[4][4]);
void fill_space(int board[4][4]);
void print_number_with_color(int n);
int is_over(int board[4][4], int score, int step, int mode = CLASSIC); // 1�Ǿ���ģʽ��2����սģʽ, 3���޾�ģʽ
// mode 2
int get_min_score(int board[4][4], int step);
