#define CLASSIC 1
#define CHALLENGE 2
#define INFI 3
#define ROUGE 4
#define DEFAULT_WIN_SCORE 2048

// rouge
#define ELEVATE 1
#define BUMB 2
#define SAVE 3
#define ENHANCE_GENERATE 4
#define MAGIC 5
#define EASY_WIN 6

#define endl '\n'

bool to_left(int board[4][4], int* score);
bool to_right(int board[4][4], int* score);
bool to_up(int board[4][4], int* score);
bool to_down(int board[4][4], int* score);

int generate_two_or_four();
int find_space_count(int board[4][4]);
void fill_space(int board[4][4], int mult = 1);
void print_number_with_color(int n);
int is_over(int board[4][4], int score, int step, int mode = CLASSIC, int win_score=DEFAULT_WIN_SCORE, int *save_me = nullptr); // 1是经典模式，2是挑战模式, 3是无尽模式
int generate_random_int(int a, int b);
// mode 2
int get_min_score(int board[4][4], int step);
int get_max_number(int board[4][4]);
// rouge
void elevate(int board[4][4]);
void bump(int board[4][4]);
void magic(int board[4][4]);
std::string bonus_explain(int type);

