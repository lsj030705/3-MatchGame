#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int Map[7][7] = { 0, };
int LineCheckMap[7][7] = { 0, };
int x = 6, y = 3;
int score = 0;
int LimitTime = 20;
void MapMaker();
void MapDrawer();
void CursorMove();
void CharacterMove();
void LineChecker1();
void LineChecker2();
void CrushCheck();
void EmptyCheck();
void NewCharacter();
void CanCrush();
void SuccessiveCrush();
void gotoxy(int x, int y);

int main(void)
{
	MapMaker();
	MapDrawer();
	Sleep(450);
	LineChecker1();
	LineChecker2();
	CrushCheck();
	EmptyCheck();
	MapDrawer();
	Sleep(50);
	NewCharacter();
	MapDrawer();
	Sleep(450);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			LineCheckMap[i][j] = 0;
	} //LineCheckMap을 초기화 
	SuccessiveCrush();
	
	MapDrawer();

	gotoxy(x, y);
	CursorMove();

    return 0;
}

void MapMaker()
{
	int random;
	int randomi, randomj;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			random = (rand() % 7) + 1;
			Map[i][j] = random;
		}
	} //보드를 랜덤한 캐릭터로 채움
	
	randomi = rand() % 7;
	randomj = rand() % 7; //임의의 좌표 
	
	random = rand() % 6;
	
	if(random == 0)
	{
		Map[randomi][randomj] = 8;
	}
	
	else if(random == 1)
	{
		Map[randomi][randomj] = 9;
	}
	
	else if(random == 2)
	{
		Map[randomi][randomj] = 10;
	}
	
	else if(random == 3)
	{
		Map[randomi][randomj] = 11;
	}
	
	else if(random == 4)
	{
		Map[randomi][randomj] = 12;
	}
	
	else
	{
		Map[randomi][randomj] = 13;
	} //특수 캐릭터들 생성 
}
//맵 생성
void MapDrawer()
{
	system("cls");
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Map[i][j] == 0)
			{
				printf("  "); 
			}
			
			else if (Map[i][j] == 1)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 6);
				printf("★");
			}

			else if (Map[i][j] == 2)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 11);
				printf("●");
			}

			else if (Map[i][j] == 3)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 2);
				printf("◆");
			}

			else if (Map[i][j] == 4)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 5);
				printf("■");
			}

			else if (Map[i][j] == 5)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 8);
				printf("▲");
			}

			else if (Map[i][j] == 6)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
				printf("♠");
			}

			else if (Map[i][j] == 7)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 4);
				printf("♥");
			}
			
			else if (Map[i][j] == 8)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("↔");//column
			} 
			
			else if (Map[i][j] == 9)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("↕");//Row
			}
			
			else if (Map[i][j] == 10)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("RR");//reset
			}
			
			else if (Map[i][j] == 11)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("┼");//column+row
			}
			
			else if (Map[i][j] == 12)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("▦");//box
			}
			
			else if (Map[i][j] == 13)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("？");//randompang
			}
		}
		printf("\n");
	}
	
	gotoxy(0,7);
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
	printf("Score : %d\n",score);
	printf("Time : %d",LimitTime);
	
	if(LimitTime == 0)
	{
		gotoxy(0,10);
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
		printf("Game Over");
		exit(0);
	}
}
//맵 표시
void CursorMove()
{
	int keycode,start, end, checkTime = 0;
	
	
	while (1)
	{
		start = clock();
		
		if (_kbhit())
		{
			keycode = _getch();
			
			if (keycode == 72) //UP
			{
				if (y == 0) //맨 위에 커서가 있으면 
					y = 6; //아래로 내려라 

				else
					y -= 1;
				
				gotoxy(x, y);
			}

			else if (keycode == 80) //DOWN
			{
				if (y == 6)
					y = 0;

				else
					y += 1;

				gotoxy(x, y);
			}

			else if (keycode == 75) //LEFT
			{
				if (x == 0)
					x = 12;

				else
					x -= 2;

				gotoxy(x, y);
			}

			else if (keycode == 77) //RIGHT
			{
				if (x == 12)
					x = 0;

				else
					x += 2;

				gotoxy(x, y);
			}

			else if (keycode == 32) //SPACE BAR
			{
				if(Map[y][x/2] == 8)//가로 
				{
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[y][i] = 1;
					}//가로 친구 다 빈칸 
					
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 9)//세로 
				{
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[i][x/2] = 1; 
					}//세로 친구는 다 빈칸 
					
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 10)//리셋 
				{	
					MapMaker();
					MapDrawer();
					Sleep(450);
					LineChecker1();
					LineChecker2();
					CrushCheck();
					EmptyCheck();
					MapDrawer();
					Sleep(50);
					NewCharacter();
					MapDrawer();
					Sleep(450);
					SuccessiveCrush();
					MapDrawer();
				
					gotoxy(x, y);
					CursorMove();
				}
				
				else if(Map[y][x/2] == 11)//가로+세로
				{
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[y][i] = 1;
					}//가로 친구 다 빈칸 
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[i][x/2] = 1; 
					}//세로 친구는 다 빈칸 
					
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 12)//박스 3*3 
				{
					if(y==0)//박스가 맨 위에 있으면 
					{
						if(x == 0)//좌측 상단 
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y+1][x/2] = 1;
							LineCheckMap[y+1][x/2+1] = 1;
							LineCheckMap[y][x/2+1] = 1;
						}
						
						else if(x == 12)//우측 상단 
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y+1][x/2] = 1;
							LineCheckMap[y+1][x/2-1] = 1;
							LineCheckMap[y][x/2-1] = 1;
						}
						
						else
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y][x/2-1] = 1;
							LineCheckMap[y+1][x/2-1] = 1;
							LineCheckMap[y+1][x/2] = 1;
							LineCheckMap[y+1][x/2+1] = 1;
							LineCheckMap[y][x/2+1] = 1;
							
						}
					}
					
					else if(y == 6)
					{
						if(x == 0)//좌측 하단 
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y-1][x/2] = 1;
							LineCheckMap[y-1][x/2+1] = 1;
							LineCheckMap[y][x/2+1] = 1;
						}
						
						else if(x == 12)//우측 하단 
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y-1][x/2] = 1;
							LineCheckMap[y-1][x/2-1] = 1;
							LineCheckMap[y][x/2-1] = 1;
						}
						
						else
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y][x/2-1] = 1;
							LineCheckMap[y-1][x/2-1] = 1;
							LineCheckMap[y-1][x/2] = 1;
							LineCheckMap[y-1][x/2+1] = 1;
							LineCheckMap[y][x/2+1] = 1;
							
						}
					}
					
					else if(x == 0)//좌측 
					{
						LineCheckMap[y][x/2] = 1;
						LineCheckMap[y-1][x/2] = 1;
						LineCheckMap[y-1][x/2+1] = 1;
						LineCheckMap[y][x/2+1] = 1;
						LineCheckMap[y+1][x/2+1] = 1;
						LineCheckMap[y+1][x/2] = 1;
					}
					
					else if(x == 12)//우측 
					{
						LineCheckMap[y][x/2] = 1;
						LineCheckMap[y-1][x/2] = 1;
						LineCheckMap[y-1][x/2-1] = 1;
						LineCheckMap[y][x/2-1] = 1;
						LineCheckMap[y+1][x/2-1] = 1;
						LineCheckMap[y+1][x/2] = 1;
					}
					
					else
					{
						LineCheckMap[y][x/2] = 1;
						LineCheckMap[y-1][x/2] = 1;
						LineCheckMap[y-1][x/2-1] = 1;
						LineCheckMap[y][x/2-1] = 1;
						LineCheckMap[y+1][x/2-1] = 1;
						LineCheckMap[y+1][x/2] = 1;
						LineCheckMap[y+1][x/2+1] = 1;
						LineCheckMap[y][x/2+1] = 1;
						LineCheckMap[y-1][x/2+1] = 1;
					} 
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 13)//랜덤팡
				{
					LineCheckMap[y][x/2] = 1; //자신도 특정 캐릭터가 됨 
					
					int random = (rand()%6) + 1;//특정 캐릭터 선정 
					
					for(int i = 0;i<7;i++)
					{
						for(int j=0;j<7;j++)
						{
							if(Map[i][j]==random)
							{
								LineCheckMap[i][j] = 1;
							}
						}
					}
					SuccessiveCrush();
				}
				
				else
				{
					CharacterMove();
					
					LineChecker1();
					LineChecker2();
					SuccessiveCrush();		
				}
				
				MapDrawer();
				gotoxy(x, y);
			}

			else if (keycode == 27) //ESC
			{
				gotoxy(0, 8);
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				break;
			}
		}
		end = clock();
		checkTime += end-start;
		
		if(checkTime >= 1000)
		{
			system("cls");
			MapDrawer();
			gotoxy(x,y);
			checkTime = 0;
			LimitTime--;
		}
	}
}
//키보드 움직임
void CharacterMove()
{
	int keycode, cnt = 0;
	int prevcha, nextcha;
	int start, end, checkTime = 0;

	while (1)
	{
		start = clock();
		if (_kbhit())
		{
			keycode = _getch();

			if (keycode == 72) //UP
			{
				if (y == 0) //맨 위에서 올리려고하면 취소 
					break;

				prevcha = Map[y][x / 2]; //현재좌표 
				nextcha = Map[y - 1][x / 2];//위에좌표 

				Map[y][x / 2] = nextcha;
				Map[y - 1][x / 2] = prevcha;//서로바꿈 

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
						LineCheckMap[i][j] = 0;
				} //LineCheckMap을 초기화 

				LineChecker1();
				LineChecker2();//가로세로맞는지 체크 

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (LineCheckMap[i][j] == 0)
							cnt++;
					}
				}//빈칸개수체크 

				if (cnt == 49)//다빈칸이면 
				{
					Map[y][x / 2]  = prevcha;
					Map[y - 1][x / 2] = nextcha;//원상태로바꾸고 

					cnt = 0;//초기화 
					system("cls");
					MapDrawer();
					y--;
					gotoxy(x, y);
				}
				
				else
				{
					system("cls");
					MapDrawer();
					Sleep(500);
					y--;
					gotoxy(x, y);
				} 

				break;
			}

			else if (keycode == 80) //DOWN
			{
				if (y == 6)
					break;

				prevcha = Map[y][x / 2];
				nextcha = Map[y + 1][x / 2];

				Map[y][x / 2] = nextcha;
				Map[y + 1][x / 2] = prevcha;

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
						LineCheckMap[i][j] = 0;
				}

				LineChecker1();
				LineChecker2();

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (LineCheckMap[i][j] == 0)
							cnt++;
					}
				}

				if (cnt == 49)
				{
					Map[y][x / 2] = prevcha;
					Map[y + 1][x / 2] = nextcha;

					cnt = 0;
					system("cls");
					MapDrawer();
					y++;
					gotoxy(x, y);
				}
				else
				{
					system("cls");
					MapDrawer();
					Sleep(500);
					y++;
					gotoxy(x, y);
				}

				

				break;
			}

			else if (keycode == 75) //LEFT
			{
				if (x == 0)
					break;

				prevcha = Map[y][x / 2];
				nextcha = Map[y][x / 2 - 1];

				Map[y][x / 2] = nextcha;
				Map[y][x / 2 - 1] = prevcha;

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
						LineCheckMap[i][j] = 0;
				}

				LineChecker1();
				LineChecker2();

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (LineCheckMap[i][j] == 0)
							cnt++;
					}
				}

				if (cnt == 49)
				{
					Map[y][x / 2] = prevcha;
					Map[y][x / 2 - 1] = nextcha;

					cnt = 0;
					system("cls");
					MapDrawer();
					x -= 2;
					gotoxy(x, y);
				}
				else
				{
					system("cls");
					MapDrawer();
					Sleep(500);
					x -= 2;
					gotoxy(x, y);
				}
				break;
			}

			else if (keycode == 77) //RIGHT
			{
				if (x == 12)
					break;

				prevcha = Map[y][x / 2];
				nextcha = Map[y][x / 2 + 1];

				Map[y][x / 2] = nextcha;
				Map[y][x / 2 + 1] = prevcha;

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
						LineCheckMap[i][j] = 0;
				}

				LineChecker1();
				LineChecker2();

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (LineCheckMap[i][j] == 0)
							cnt++;
					}
				}

				if (cnt == 49)
				{
					Map[y][x / 2] = prevcha;
					Map[y][x / 2 + 1] = nextcha;

					cnt = 0;
					system("cls");
					MapDrawer();
					x += 2;
					gotoxy(x, y);
				}
				else
				{
					system("cls");
					MapDrawer();
					Sleep(500);
					x += 2;
					gotoxy(x, y);
				}
				break;
			}

			else if (keycode == 32) //SPACE BAR
				break;
		}
		end = clock();
		
		checkTime += end-start;
		
		if(checkTime >= 1000)
		{
			system("cls");
			MapDrawer();
			gotoxy(x,y);
			checkTime = 0;
			LimitTime--;
		}
	}
}
//캐릭터 움직임
void LineChecker1()
{
	int cnt = 0;
	int i = 0, j = 0;

	while (1)
	{
		if (Map[i][j] == Map[i][j + 1] && j != 6)//양 옆에 두개가 같고 맨 끝이 기준이 아니면 
			cnt++;

		else
			cnt = 0;

		if (cnt == 2)
		{
			LineCheckMap[i][j + 1] = 1;
			LineCheckMap[i][j] = 1;
			LineCheckMap[i][j - 1] = 1;//3개는 맞춰지니까 일단 두고 

			while (1) //4개이상으로가는곳 
			{
				if (j == 6)//끝이면 걍 꺼지고 
					break;

				if (Map[i][j] == Map[i][j + 1])
				{
					LineCheckMap[i][j + 1] = 1;
					j++;

					if (j == 7) //6초과하면 꺼지고 
						break;
				}

				else
				{
					cnt = 0;
					break;
				}
			}
		}

		if (i == 6 && j == 6) //맵 맨 끝에 오게 되면 탈출 
			break;

		if (j == 6) //가로줄 맨 끝에 오면 세로줄 ++ 가로줄 0 
		{
			j = 0;
			i++;
			cnt = 0;

		}
		else
			j++;
	}
}
//가로 움직임 가능확인
void LineChecker2()
{
	int cnt = 0;
	int i = 0, j = 0;

	while (1)
	{
		if (Map[i][j] == Map[i + 1][j] && i != 6)
			cnt++;

		else
			cnt = 0;

		if (cnt == 2)
		{
			LineCheckMap[i - 1][j] = 1;
			LineCheckMap[i][j] = 1;
			LineCheckMap[i + 1][j] = 1;

			while (1)
			{
				if (i == 6)
					break;

				if (Map[i][j] == Map[i + 1][j])
				{
					LineCheckMap[i + 1][j] = 1;
					i++;

					if (i == 7)
						break;
				}

				else
				{
					cnt = 0;
					break;
				}
			}
		}

		if (i == 6 && j == 6)
			break;

		if (i == 6)
		{
			i = 0;
			j++;
			cnt = 0;
		}

		else
			i++;
	}
}
//세로 움직임 가능확인
void CrushCheck()
{
	int check=0, additionalTime = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (LineCheckMap[i][j] == 1)
			{
				Map[i][j] = 0;
				score++;
				check++;
			}
		}//LineCheckMap의 좌표가 1이면 Map의 좌표는 빈칸으로 만듦 
	}
	
	additionalTime = check/2;
	if(LimitTime<20)
	{
		LimitTime += additionalTime;
		if(LimitTime>20)
			LimitTime = 20;
	}
}
//사라진 캐릭터 0으로 변환
void EmptyCheck()
{
	int prevcha, nextcha;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{			
			if (Map[i][j] == 0) //특정 좌표가 빈칸이면 
			{
				MapDrawer();
				Sleep(100);
				for (int k = i; k > 0; k--) //빈칸을 계속 위로 올림 
				{
					prevcha = Map[k][j];
					nextcha = Map[k - 1][j];

					Map[k][j] = nextcha;
					Map[k - 1][j] = prevcha;
				}
			}
		}
	}
}
//캐릭터들 떨어짐 표현
void NewCharacter()
{
	int random,cnt = 0,onlyone = 0;

	srand((unsigned int)time(NULL));
	
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			if(Map[i][j] >= 8)
				cnt = 1;
		}
	} //만약 맵에 특수 블록이 있으면 cnt를 1로 만들어 특수블록이 만들어지지 않게 함 
	
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Map[i][j] == 0)
			{
				if(cnt == 0) //맵에 특수블록이 없으면 
				{
					random = rand()%29; //1/30의 확률로 
					
					if(random==0 && onlyone == 0) //그리고 onlyone으로 필드에 특수블록이 하나도 없어야해 
					{
						random = rand()%6;
						
						if(random == 0)
						{
							Map[i][j] = 8;
						}
						
						else if(random == 1)
						{
							Map[i][j] = 9;
						}
						
						else if(random == 2)
						{
							Map[i][j] = 10;
						}
						
						else if(random == 3)
						{
							Map[i][j] = 11;
						}
						
						else if(random == 4)
						{
							Map[i][j] = 12;
						}
						
						else
						{
							Map[i][j] = 13;
						} //특수 캐릭터들 생성 
						onlyone = 1; //onlyone을 1로 만들어서 맵에 2개 이상 만들어지지 않게 함 
					}
					
					else //일반 블록 생성 
					{
						random = (rand() % 7) + 1;
						Map[i][j] = random;
					}
				}
				
				else //일반 블록 생성 
				{			
					random = (rand() % 7) + 1;
					Map[i][j] = random;
				}
			}
		}
	}
}
//새 캐릭터 생성
void CanCrush()
{
	int cnt = 0, cha1, cha2,exitcode = 0;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i != 0) //올림
			{
				cha1 = Map[i][j];
				cha2 = Map[i - 1][j];

				Map[i][j] = cha2;
				Map[i - 1][j] = cha1;

				LineChecker1();
				LineChecker2();

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						if (LineCheckMap[m][n] == 0)//빈칸체크 
							cnt++;
					}
				}

				Map[i][j] = cha1;
				Map[i - 1][j] = cha2;

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						LineCheckMap[m][n] = 0;
					}
				}

				if (cnt != 49)//맞출 수 있는 것이 있으면 
				{
					cnt = 0;
					exitcode = 1;//exitcode로 빠르게탈출 
					break;
				}

				else
					cnt = 0;
			}

			if (i != 6) //내림
			{
				cha1 = Map[i][j];
				cha2 = Map[i + 1][j];

				Map[i][j] = cha2;
				Map[i + 1][j] = cha1;

				LineChecker1();
				LineChecker2();

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						if (LineCheckMap[m][n] == 0)
							cnt++;
					}
				}

				Map[i][j] = cha1;
				Map[i + 1][j] = cha2;

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						LineCheckMap[m][n] = 0;
					}
				}

				if (cnt != 49)
				{
					cnt = 0;
					exitcode = 1;
					break;
				}

				else
					cnt = 0;
			}

			if (j != 0) //왼쪽이동
			{
				cha1 = Map[i][j];
				cha2 = Map[i][j - 1];

				Map[i][j] = cha2;
				Map[i][j - 1] = cha1;

				LineChecker1();
				LineChecker2();

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						if (LineCheckMap[m][n] == 0)
							cnt++;
					}
				}

				Map[i][j] = cha1;
				Map[i][j - 1] = cha2;

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						LineCheckMap[i][j] = 0;
					}
				}

				if (cnt != 49)
				{
					cnt = 0;
					exitcode = 1;
					break;
				}

				else
					cnt = 0;
			}

			if (j != 6) //오른쪽이동
			{
				cha1 = Map[i][j];
				cha2 = Map[i][j + 1];

				Map[i][j] = cha2;
				Map[i][j + 1] = cha1;

				LineChecker1();
				LineChecker2();

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						if (LineCheckMap[m][n] == 0)
							cnt++;
					}
				}

				Map[i][j] = cha1;
				Map[i][j + 1] = cha2;

				for (int m = 0; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						LineCheckMap[m][n] = 0;
					}
				}

				if (cnt != 49)
				{
					cnt = 0;
					exitcode = 1;
					break;
				}

				else
					cnt = 0;
			}
		}
		if(exitcode == 1)//exitcode로 빠르게 탈출 
			break;
	}
	
	if(exitcode != 1)
	{
		system("cls");
		MapDrawer();
		gotoxy(14, 3);
	
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
		printf("움직일 수 있는 것이 없습니다");
		Sleep(500);
		
		MapMaker(); 
		LineChecker1();
		LineChecker2();
		CrushCheck();
		EmptyCheck();
		NewCharacter();
		MapDrawer();
		SuccessiveCrush();
		
		MapDrawer();
	
		gotoxy(x, y);
		CursorMove();
	}
	
	else
		;
}
//맞출 수 있는가 ->없으면 재배열
void SuccessiveCrush()
{
	int cnt = 0;
	
	CrushCheck(); //0으로 만들고 
	MapDrawer();
	Sleep(50);
	EmptyCheck(); //빈칸 위로 올리고 
	NewCharacter(); //빈칸에 새로운 캐릭터 만들고 
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			LineCheckMap[i][j] = 0;
	} //LineCheckMap을 초기화 

	while (1)
	{
		LineChecker1(); //가로체크 
		LineChecker2(); //세로체크 

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (LineCheckMap[i][j] == 0) //만약 맵이 빈칸이다 
					cnt++;
			}
		}

		if (cnt != 49) //만약 맵에서 3개이상 맞춰지는 것이 있다! 
		{
			MapDrawer();
			Sleep(450);
			CrushCheck(); //0으로만들고 
			MapDrawer();
			Sleep(50);
			EmptyCheck(); //빈거 위로올리고 
			NewCharacter(); //빈곳에 새캐릭터만들고 

			cnt = 0; //다시 초기화 

			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
					LineCheckMap[i][j] = 0;
			} //LineCheckMap도 초기화 
		}
	
		else //맵이 빈칸이면 
		{
			CanCrush();
			break;
		}
	}		
}
//연속적인 충돌 
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//커서 이동 함수9y
