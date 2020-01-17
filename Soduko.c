#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
#include<windows.h>

void init();
int rand_no(int x, int y);
bool check_full(int mat[9][9]);
bool check(int mat[9][9]);
bool full_check(int mat[9][9], int solu[9][9]);
void copy(int x[9][9], int y[9][9]);
void removee(int mat[9][9]);
void randomize(int x[9], int n);
void swap(int *a, int *b);
void shuffle(int x[9], size_t n);
void fill_mat(int mat[9][9]);
void solve(int mat[9][9]);
void play(int mat[9][9], int solu[9][9], int mat_cpy1[9][9]);
bool check_time(int ac_time);
void print(int mat[9][9], int mat_cpy1[9][9], int o);
void clear_sudoko(int mat[9][9], int mat_cpy1[9][9]);
bool isInteger(double x);


int number_list[] = { 1,2,3,4,5,6,7,8,9 };

int main(void)
{
	char st;
	printf("\t\t\t\t\tWELCOME PRESS 'ENTER' TO START\n");
	scanf("%c", &st);
	if (st == '\n')
	{
		init();
	}
}

void init()
{
	int mat[9][9];
	int mat_cpy[9][9];
	int solu[9][9];
	int mat_cpy1[9][9];
	char op[100];
	int mark = 0;
	int mark1 = 0;
	printf("Enter 1 to proceed to enter the matrix manaully\nEnter 2 to generate a random puzzles\nEnter 3 to exit\nYour input: ");
	scanf("%s", &op);
	while (1)
	{
		if (strlen(op) == 1 && ((int)op[0] - '0' == 1 || (int)op[0] - '0' == 2 || (int)op[0] - '0' == 3))
		{
			char i[100], j[100], val[100];
			char op1[100];
			if ((int)op[0] - '0' == 1)
			{
				int mod_mat[9][9];
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						mat[i][j] = 0;
					}
				}
				while (1)
				{
					print(mat, mat_cpy, 1);
					printf("\nEnter 1 to enter the column and row number and enter the value\nEnter 2 to start palying the puzzle\nYour input: ");
					scanf("%s", &op1);
					if (!((int)op1[0] - '0' == 1 || (int)op1[0] - '0' == 2 || (int)op1[0]-'0' == 3&& strlen(op1) == 1))
					{
						while (1)
						{
							printf("\nPlz enter a valid choice\n");
							printf("\nEnter 1 to enter the column and row number and enter the value\nEnter 2 to start palying the puzzle\nYour input: ");
							scanf("%s", &op1);
							if (strlen(op1) == 1)
							{
								if ((int)op1[0] - '0' == 1 || (int)op1[0] - '0' == 2)
								{
									break;
								}
							}
						}
					}
					if ((int)op1[0] - '0' == 1)
					{
						print(mat, mat_cpy, 1);
						printf("\n\nEnter the coordinates of the value that u want to change\nenter 'i': ");
						scanf("%s", &i);
						printf("enter 'j': ");
						scanf("%s", &j);
						printf("Enter the value: ");
						scanf("%s", &val);
						if ((int)i[0] - '0' < 1 || (int)i[0] - '0' > 9 || (int)j[0] - '0' < 1 || (int)j[0] - '0' > 9 || strlen(i) > 1 || strlen(j) > 1)
						{
							while (1)
							{
								printf("\n!!!please enter valid coordinate\n");
								printf("\n\nEnter the coordinates of the value that u want to change\nenter 'i' (1 -> 9): ");
								scanf("%s", &i);
								printf("enter 'j' (1 -> 9): ");
								scanf("%s", &j);
								if (strlen(i) == 1 && strlen(j) == 1)
								{
									if (!((int)i[0] - '0' < 1 || (int)i[0] - '0' > 9 || (int)j[0] - '0' < 1 || (int)j[0] - '0' > 9))
									{
										break;
									}
								}
							}
						}
						if (!isInteger((double)val[0] - '0') || (double)val[0] - '0' < 1 || (double)val[0] - '0' > 9 || strlen(val) > 1)
						{
							while (1)
							{
								printf("\n!!!plz enter a valid value (1 -> 9): ");
								scanf("%s", &val);
								if (strlen(val) == 1)
								{
									if (isInteger((double)val[0] - '0') && (double)val[0] - '0' >= 1 && (double)val[0] - '0' <= 9)
									{
										break;
									}
								}
							}
						}
						mat[((int)i[0] - '0') - 1][((int)j[0] - '0') - 1] = (int)val[0] - '0';
					}
					if ((int)op1[0] - '0' == 2)
					{
						printf("\nPlease wait...\n");
						int exist_mark[9][9];
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								if (mat[i][j] != 0)
								{
									exist_mark[i][j] = -1;
								}
								else
								{
									exist_mark[i][j] = 0;
								}
							}
						}
						copy(mat_cpy, mat);
						fill_mat(mat);
						if (!check_full(mat))
						{
							while (1)
							{
								for (int i = 0; i < 9; i++)
								{
									for (int j = 0; j < 9; j++)
									{
										if (exist_mark[i][j] != -1)
										{
											mat[i][j] = 0;
										}
									}
								}
								fill_mat(mat);
								if (check_full(mat))
								{
									break;
								}
							}
						}
						solve(mat);
						copy(solu, mat);
						copy(mat, mat_cpy);
						copy(mat_cpy1, mat);
						printf("\n\n");
						print(mat, mat_cpy1, 1);
						play(mat, solu, mat_cpy1);
						mark = 1;
					}
					if((int)op1[0] - '0' == 3)
					{
						printf("\n\nThanks for your time");
						mark=1;
					}
					if (mark == 1)
					{
						exit(0);
					}
				}
			}
			if ((int)op[0] - '0' == 2)
			{
				int exist_mark[9][9];
				int n = sizeof(number_list) / sizeof(number_list[0]);
				printf("Please wait while the SUDOKO is generating....\n\n");
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						mat[i][j] = 0;
					}
				}
				randomize(number_list, n);
				shuffle(number_list, 9);
				mat[0][0] = number_list[0];
				mat[0][1] = number_list[1];
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (mat[i][j] != 0)
						{
							exist_mark[i][j] = -1;
						}
						else
						{
							exist_mark[i][j] = 0;
						}
					}
				}
				fill_mat(mat);
				if (!check_full(mat))
				{
					while (1)
					{
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								if (exist_mark[i][j] != -1)
								{
									mat[i][j] = 0;
								}
							}
						}
						fill_mat(mat);
						if (check_full(mat))
						{
							break;
						}
					}
				}
				copy(mat_cpy, mat);
				solve(mat);
				copy(solu, mat);
				copy(mat, mat_cpy);
				removee(mat);
				copy(mat_cpy1, mat);
				print(mat, mat_cpy1, 1);
				play(mat, solu, mat_cpy1);
				mark = 1;
			}
			if ((int)op[0] - '0' == 3)
			{
				printf("\n\nThanks for your time");
				exit(0);
			}
		}
		else
		{
			while (1)
			{
				printf("\n!!!Plz enter a correct choice\n");
				printf("Enter 1 to proceed to enter the matrix manaully\nEnter 2 to generate a random puzzles\nEnter 3 to exit\nYour input: ");				scanf("%s", &op);
				if (strlen(op) == 1 && ((int)op[0] - '0' == 1 || (int)op[0] - '0' == 2))
				{
					break;
				}
			}
		}
		if (mark == 1)
		{
			break;
		}
	}
}

void copy(int x[9][9], int y[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			x[i][j] = y[i][j];
		}
	}
}

int rand_no(int x, int y)
{
	return rand() % (y - x + 1) + x;
}

bool check_full(int mat[9][9])
{
	int cnt = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mat[i][j] == 0)
			{
				if (j == 8)
				{
					cnt += 4;
				}
				else
				{
					cnt++;
				}
				if (cnt >= 3)
				{
					return false;
				}

			}
		}
	}
	return true;
}

bool check(int mat[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mat[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

void fill_mat(int mat[9][9])
{
	int rw, cl;
	int val;
	int mark = 0;
	int n = sizeof(number_list) / sizeof(number_list[0]);
	randomize(number_list, n);
	for (int i = 0; i < 81; i++)
	{
		rw = i / 9;
		cl = i % 9;
		shuffle(number_list, 9);
		if (mat[rw][cl] == 0)
		{
			for (int p = 0; p < 9; p++)
			{
				mark = 0;
				val = number_list[p];
				if (val != mat[rw][0] && val != mat[rw][1] && val != mat[rw][2] && val != mat[rw][3] && val != mat[rw][4] && val != mat[rw][5] && val != mat[rw][6] && val != mat[rw][7] && val != mat[rw][8])
				{
					if (val != mat[0][cl] && val != mat[1][cl] && val != mat[2][cl] && val != mat[3][cl] && val != mat[4][cl] && val != mat[5][cl] && val != mat[6][cl] && val != mat[7][cl] && val != mat[8][cl])
					{
						if (rw < 3)
						{
							if (cl < 3)
							{
								for (int j = 0; j < 3; j++)
								{
									for (int k = 0; k < 3; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
							if (cl < 6 && cl >= 3)
							{
								for (int j = 0; j < 3; j++)
								{
									for (int k = 3; k < 6; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
							if (cl >= 6)
							{
								for (int j = 0; j < 3; j++)
								{
									for (int k = 6; k < 9; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
						}
						if (rw >= 3 && rw < 6)
						{
							if (cl < 3)
							{
								for (int j = 3; j < 6; j++)
								{
									for (int k = 0; k < 3; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
							if (cl < 6 && cl >= 3)
							{
								for (int j = 3; j < 6; j++)
								{
									for (int k = 3; k < 6; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
							if (cl >= 6)
							{
								for (int j = 3; j < 6; j++)
								{
									for (int k = 6; k < 9; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
						}
						if (rw >= 6)
						{
							if (cl < 3)
							{
								for (int j = 6; j < 9; j++)
								{
									for (int k = 0; k < 3; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
							if (cl < 6 && cl >= 3)
							{
								for (int j = 6; j < 9; j++)
								{
									for (int k = 3; k < 6; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
							if (cl >= 6)
							{
								for (int j = 6; j < 9; j++)
								{
									for (int k = 6; k < 9; k++)
									{
										if (val == mat[j][k])
										{
											mark = 1;
											break;
										}
									}
									if (mark == 1)
									{
										break;
									}
								}
							}
						}
						if (mark != 1)
						{
							mat[rw][cl] = val;

						}
					}
				}
			}
		}
	}

}

void solve(int mat[9][9])
{
	int number_list_ind[9];
	int rw, cl;
	int val, mark;
	for (int i = 0; i < 81; i++)
	{
		for (int i = 0; i < 9; i++)
		{
			number_list_ind[i] = 0;
		}
		rw = i / 9;
		cl = i % 9;
		if (mat[rw][cl] == 0)
		{
			for (int x = 0; x < 9; x++)
			{

				for (int y = 0; y < 9; y++)
				{
					mark = 0;
					val = number_list[y];
					if (rw < 3)
					{
						if (cl < 3)
						{
							for (int j = 0; j < 3; j++)
							{
								for (int k = 0; k < 3; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
						if (cl < 6 && cl >= 3)
						{
							for (int j = 0; j < 3; j++)
							{
								for (int k = 3; k < 6; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
						if (cl >= 6)
						{
							for (int j = 0; j < 3; j++)
							{
								for (int k = 6; k < 9; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
					}
					if (rw >= 3 && rw < 6)
					{
						if (cl < 3)
						{
							for (int j = 3; j < 6; j++)
							{
								for (int k = 0; k < 3; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
						if (cl < 6 && cl >= 3)
						{
							for (int j = 3; j < 6; j++)
							{
								for (int k = 3; k < 6; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
						if (cl >= 6)
						{
							for (int j = 3; j < 6; j++)
							{
								for (int k = 6; k < 9; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
					}
					if (rw >= 6)
					{
						if (cl < 3)
						{
							for (int j = 6; j < 9; j++)
							{
								for (int k = 0; k < 3; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
						if (cl < 6 && cl >= 3)
						{
							for (int j = 6; j < 9; j++)
							{
								for (int k = 3; k < 6; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
						if (cl >= 6)
						{
							for (int j = 6; j < 9; j++)
							{
								for (int k = 6; k < 9; k++)
								{
									if (val == mat[j][k])
									{
										mark = 1;
										break;
									}
								}
								if (mark == 1)
								{
									number_list_ind[y] = -1;
									break;
								}
							}
						}
					}
				}
			}
			for (int n = 0; n < 9; n++)
			{
				if (number_list_ind[n] == 0)
				{
					mat[rw][cl] = number_list[n];
					break;
				}
			}
		}
	}
}

void removee(int mat[9][9])
{
	int rn_rmv;
	int zro_cnt;
	int *rn_p;
	for (int i = 0; i < 9; i++)
	{
		zro_cnt = 0;
		for (int j = 0; j < 9; j++)
		{
			if (mat[i][j] == 0)
			{
				zro_cnt++;
			}
		}
		switch (zro_cnt)
		{
		case 1:
			rn_rmv = rand_no(2, 3);
			rn_p = (int*)malloc(rn_rmv * sizeof(int));
			for (int q = 0; q < rn_rmv; q++)
			{
				rn_p[q] = rand_no(0, 8);
			}
			for (int j = 0; j < 9; j++)
			{
				for (int q = 0; q < rn_rmv; q++)
				{
					if (j == rn_p[q])
					{
						mat[i][j] = 0;
					}
				}
			}
			free(rn_p);
			rn_p = NULL;
			break;
		case 2:
			rn_rmv = rand_no(2, 3);
			rn_p = (int*)malloc(rn_rmv * sizeof(int));
			for (int q = 0; q < rn_rmv; q++)
			{
				rn_p[q] = rand_no(0, 8);
			}
			for (int j = 0; j < 9; j++)
			{
				for (int q = 0; q < rn_rmv; q++)
				{
					if (j == rn_p[q])
					{
						mat[i][j] = 0;
					}
				}
			}
			free(rn_p);
			rn_p = NULL;
			break;
		case 3:
			rn_rmv = rand_no(1, 3);
			rn_p = (int*)malloc(rn_rmv * sizeof(int));
			for (int q = 0; q < rn_rmv; q++)
			{
				rn_p[q] = rand_no(0, 8);
			}
			for (int j = 0; j < 9; j++)
			{
				for (int q = 0; q < rn_rmv; q++)
				{
					if (j == rn_p[q])
					{
						mat[i][j] = 0;
					}
				}
			}
			free(rn_p);
			rn_p = NULL;
			break;
		default:
			rn_rmv = rand_no(2, 4);
			rn_p = (int*)malloc(rn_rmv * sizeof(int));
			for (int q = 0; q < rn_rmv; q++)
			{
				rn_p[q] = rand_no(0, 8);
			}
			for (int j = 0; j < 9; j++)
			{
				for (int q = 0; q < rn_rmv; q++)
				{
					if (j == rn_p[q])
					{
						mat[i][j] = 0;
					}
				}
			}
			free(rn_p);
			rn_p = NULL;
			break;
		}

	}
}

void play(int mat[9][9], int solu[9][9], int mat_cpy1[9][9])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if (tm.tm_min + 3 > 60)
	{
		printf("\n\n\t\t\t\tYOU HAVE 3 MINUTES TO SOLVE THE PUZZLE GOOD LUCK!!!\n\t\t\t\tSTARTED AT: %02d:%02d\t\t\tFINISHES AT: %02d:%02d", tm.tm_hour, (tm.tm_min), (tm.tm_hour + 1), (tm.tm_min + 3) - 60);
	}
	else
	{
		printf("\n\n\t\t\t\tYOU HAVE 3 MINUTES TO SOLVE THE PUZZLE GOOD LUCK!!!\n\t\t\t\tSTARTED AT: %02d:%02d\t\tFINISHES AT: %02d:%02d", tm.tm_hour, (tm.tm_min), tm.tm_hour, tm.tm_min + 3);
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("\n\n!!! note !!! You cannot change the numbers in 'BLUE' during the game");
	SetConsoleTextAttribute(hConsole, saved_attributes);
	char i[100], j[100], val[100], op[100], option[50];
	int mark;
	int mod_mat[9][9];
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (mat[x][y] != 0)
			{
				mod_mat[x][y] = -1;
			}
			else
			{
				mod_mat[x][y] = 0;
			}
		}
	}
	int ac_time = 180; // give 3 minutes to solve the puzzle
	clock_t start, end;
	while (1)
	{
		start = clock();
		mark = 0;
		printf("\n\nEnter '1' to 'MODIFY' value\nEnter '2' to verify your solution of the soduko\nEnter '3' to 'EXIT AND SHOW SOLUTION'\nEnter '4' to Clear the sudoko: ");
		scanf("%s", &op);
		if (!((int)op[0] - '0' == 1 || (int)op[0] - '0' == 2 || (int)op[0] - '0' == 3 || (int)op[0] - '0' == 4) || strlen(op) > 1)
		{
			while (1)
			{
				printf("\nPlz enter a valid choice\n");
				printf("\n\nEnter '1' to 'MODIFY' value\nEnter '2' to verify your solution of the soduko\nEnter '3' to 'EXIT AND SHOW SOLUTION'\nEnter '4' to Clear the sudoko: ");
				scanf("%s", &op);
				if (strlen(op) == 1)
				{
					if ((int)op[0] - '0' == 1 || (int)op[0] - '0' == 2 || (int)op[0] - '0' == 3 || (int)op[0] - '0' == 4)
					{
						break;
					}
				}
			}
		}
		if ((int)op[0] - '0' == 1)
		{
			printf("\n\nEnter the coordinates of the value that u want to change\nenter 'i': ");
			scanf("%s", &i);
			printf("enter 'j': ");
			scanf("%s", &j);
			printf("Enter the value: ");
			scanf("%s", &val);
			if ((int)i[0] - '0' < 1 || (int)i[0] - '0' > 9 || (int)j[0] - '0' < 1 || (int)j[0] - '0' > 9 || strlen(i) > 1 || strlen(j) > 1)
			{
				while (1)
				{
					printf("\n!!!please enter valid coordinate\n");
					printf("\n\nEnter the coordinates of the value that u want to change\nenter 'i' (1 -> 9): ");
					scanf("%s", &i);
					printf("enter 'j' (1 -> 9): ");
					scanf("%s", &j);
					if (strlen(i) == 1 && strlen(j) == 1)
					{
						if (!((int)i[0] - '0' < 1 || (int)i[0] - '0' > 9 || (int)j[0] - '0' < 1 || (int)j[0] - '0' > 9))
						{
							break;
						}
					}
				}
			}
			if (!isInteger((double)val[0] - '0') || (double)val[0] - '0' < 1 || (double)val[0] - '0' > 9 || strlen(val) > 1)
			{
				while (1)
				{
					printf("\n!!!plz enter a valid value (1 -> 9): ");
					scanf("%s", &val);
					if (strlen(val) == 1)
					{
						if (isInteger((double)val[0] - '0') && (double)val[0] - '0' >= 1 && (double)val[0] - '0' <= 9)
						{
							break;
						}
					}
				}
			}
			if (mod_mat[((int)i[0] - '0') - 1][((int)j[0] - '0') - 1] == 0 && mark == 0)
			{
				mat[((int)i[0] - '0') - 1][((int)j[0] - '0') - 1] = (int)val[0] - '0';
				print(mat, mat_cpy1, 0);
			}
			else
			{
				printf("\nyou cannot modify this value!!!!\n");
			}

		}
		if ((int)op[0] - '0' == 2)
		{
			if (check(mat))
			{
				if (full_check(mat, solu))
				{
					printf("\n\n\nCongratulations you have solved the Sudoko :)");
					mark = 1;
				}
				else
				{
					printf("\n\n\nSorry your solution isn't corrent ;(\n\n");
					printf("DO you want to play again: 'YES' or 'NO': ");
					scanf("%s", &option);
					if (tolower(option[0]) == 'y' || memcmp(option, "YES", 50) == 0)
					{
						system("cls");
						init();
						mark = 1;
					}
					if (tolower(option[0]) == 'n' || memcmp(option, "NO", 50) == 0)
					{
						printf("\n\nThx for playing\n\n");
						mark = 1;
					}
					printf("\n\nEnter a valid choice!!!");
					while (1)
					{
						printf("\nDO you want to play again: 'YES' or 'NO': ");
						scanf("%s", &option);
						if (tolower(option[0]) == 'n' || memcmp(option, "NO", 50) == 0)
						{
							printf("\n\nThx for playing\n\n");
							mark = 1;
							break;
						}
						if (tolower(option[0]) == 'y' || memcmp(option, "YES", 50) == 0)
						{
							system("cls");
							init();
							mark = 1;
							break;
						}
						else
						{
							printf("Enter a valid choice!!!\n");
						}
					}
				}
			}
			else
			{
				printf("\n\n\nYou have to fill all the missing numbers!!!\n");
			}
		}
		end = clock();
		ac_time -= (end - start) / CLOCKS_PER_SEC;
		if (ac_time <= 0)
		{
			mark = 1;
			printf("\n\n\n\t\t\t\t\tTIME IS UP SORRY BETTER LUCK NEXT TIME\n\n\n");
		}
		if ((int)op[0] - '0' == 3 && mark == 0)
		{
			printf("\n\nThe solution is:\n\n");
			print(solu, mat_cpy1, 1);
			printf("\nThanks for your time");
			break;
		}
		if ((int)op[0] - '0' == 4 && mark == 0)
		{
			clear_sudoko(mat, mat_cpy1);
		}
		if (mark == 1)
		{
			break;
		}
	}
}

bool full_check(int mat[9][9], int solu[9][9])
{
	int mark = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mat[i][j] != solu[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool check_time(int ac_time)
{
	if (ac_time <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void print(int mat[9][9], int mat_cpy1[9][9], int o)
{
	switch (o)
	{
	case 1:
	{
		printf("\t 1     2     3        4     5     6        7     8     9\n");
		for (int i = 0; i < 9; i++)
		{
			printf("\t");
			if (i == 3 || i == 6)
			{
				printf("\n\t");
				for (int m = 0; m < 58; m++)
				{
					printf("-");
				}
				printf("\n");
			}
			else
			{
				for (int m = 0; m < 58; m++)
				{
					printf("-");
				}
			}
			printf("\n   %d   |", i + 1);
			for (int j = 0; j < 9; j++)
			{
				if (j == 3 || j == 6)
				{
					printf("  |");
				}
				if (mat[i][j] == 0)
				{
					printf(" .  | ");
				}
				else
				{
					if (mat[i][j] != mat_cpy1[i][j])
					{
						printf(" %d  ", mat[i][j]);
					}
					if (mat[i][j] == mat_cpy1[i][j])
					{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
						WORD saved_attributes;
						GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
						saved_attributes = consoleInfo.wAttributes;
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
						printf(" %d  ", mat[i][j]);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					printf("| ");
				}
			}
			printf("\n");
		}
		printf("\t");
		for (int m = 0; m < 58; m++)
		{
			printf("-");
		}
		break;
	}
	default:
	{
		int mark[9][9];
		int rw, cl;
		int val;
		for (int m = 0; m < 9; m++)
		{
			for (int n = 0; n < 9; n++)
			{
				mark[m][n] = 0;
			}
		}
		for (int i = 0; i < 81; i++)
		{
			rw = i / 9;
			cl = i % 9;
			val = mat[rw][cl];
			for (int m = 0; m < 9; m++)
			{
				if (mat[rw][cl] == mat[m][cl] && rw != m)
				{
					mark[rw][cl] == -1;
					mark[m][cl] = -1;
				}
			}
			for (int n = 0; n < 9; n++)
			{
				if (mat[rw][cl] == mat[rw][n] && cl != n)
				{
					mark[rw][cl] == -1;
					mark[rw][n] = -1;
				}
			}
			if (cl < 3 && rw < 3)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl < 6 && cl >= 3 && rw < 3)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 3; k < 6; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl >= 6 && rw < 3)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 6; k < 9; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl < 3 && rw >= 3 && rw < 6)
			{
				for (int j = 3; j < 6; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl < 6 && cl >= 3 && rw >= 3 && rw < 6)
			{
				for (int j = 3; j < 6; j++)
				{
					for (int k = 3; k < 6; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl >= 6 && rw >= 3 && rw < 6)
			{
				for (int j = 3; j < 6; j++)
				{
					for (int k = 6; k < 9; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl < 3 && rw >= 6)
			{
				for (int j = 6; j < 9; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl < 6 && cl >= 3 && rw >= 6)
			{
				for (int j = 6; j < 9; j++)
				{
					for (int k = 3; k < 6; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
			if (cl >= 6 && rw >= 6)
			{
				for (int j = 6; j < 9; j++)
				{
					for (int k = 6; k < 9; k++)
					{
						if (val == mat[j][k] && rw != j && cl != k)
						{
							mark[rw][cl] = -1;
							mark[j][k] = -1;
						}
					}
				}
			}
		}
		printf("\n\t 1     2     3        4     5     6        7     8     9\n\t");
		for (int m = 0; m < 58; m++)
		{
			printf("-");
		}
		for (int i = 0; i < 9; i++)
		{

			if (i == 3 || i == 6)
			{
				printf("\n\t");
				for (int m = 0; m < 58; m++)
				{
					printf("-");
				}
				printf("\n");
			}
			printf("\n   %d   |", i + 1);
			for (int j = 0; j < 9; j++)
			{
				if (j == 3 || j == 6)
				{
					printf("  |");
				}
				if (mat[i][j] == 0)
				{
					printf(" .  | ");
				}
				else
				{
					if (mark[i][j] == -1)
					{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
						WORD saved_attributes;
						GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
						saved_attributes = consoleInfo.wAttributes;
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf(" %d  ", mat[i][j]);
						SetConsoleTextAttribute(hConsole, saved_attributes);
						printf("| ");
					}
					else
					{
						if (mark[i][j] != -1 && mat[i][j] != mat_cpy1[i][j])
						{
							printf(" %d  | ", mat[i][j]);
						}
						else
						{
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
							WORD saved_attributes;
							GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
							saved_attributes = consoleInfo.wAttributes;
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
							printf(" %d  ", mat[i][j]);
							SetConsoleTextAttribute(hConsole, saved_attributes);
							printf("| ");
						}
					}
				}
			}
			printf("\n");
			printf("\t");
		}
		for (int m = 0; m < 58; m++)
		{
			printf("-");
		}
		break;
	}
	}
}

void clear_sudoko(int mat[9][9], int mat_cpy1[9][9])
{
	copy(mat, mat_cpy1);
	printf("\n\n");
	print(mat, mat_cpy1, 1);
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void randomize(int number_list[9], int n)
{
	srand(time(NULL));
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swap(&number_list[i], &number_list[j]);
	}
}

void shuffle(int x[9], size_t n)
{
	if (n > 1)
	{
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = x[j];
			x[j] = x[i];
			x[i] = t;
		}
	}
}

bool isInteger(double x)
{
	int a = (int)x;
	return (a == x);
}