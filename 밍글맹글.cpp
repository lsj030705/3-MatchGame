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
	} //LineCheckMap�� �ʱ�ȭ 
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
	} //���带 ������ ĳ���ͷ� ä��
	
	randomi = rand() % 7;
	randomj = rand() % 7; //������ ��ǥ 
	
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
	} //Ư�� ĳ���͵� ���� 
}
//�� ����
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
				printf("��");
			}

			else if (Map[i][j] == 2)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 11);
				printf("��");
			}

			else if (Map[i][j] == 3)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 2);
				printf("��");
			}

			else if (Map[i][j] == 4)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 5);
				printf("��");
			}

			else if (Map[i][j] == 5)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 8);
				printf("��");
			}

			else if (Map[i][j] == 6)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
				printf("��");
			}

			else if (Map[i][j] == 7)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 4);
				printf("��");
			}
			
			else if (Map[i][j] == 8)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("��");//column
			} 
			
			else if (Map[i][j] == 9)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("��");//Row
			}
			
			else if (Map[i][j] == 10)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("RR");//reset
			}
			
			else if (Map[i][j] == 11)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("��");//column+row
			}
			
			else if (Map[i][j] == 12)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("��");//box
			}
			
			else if (Map[i][j] == 13)
			{
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
				printf("��");//randompang
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
//�� ǥ��
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
				if (y == 0) //�� ���� Ŀ���� ������ 
					y = 6; //�Ʒ��� ������ 

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
				if(Map[y][x/2] == 8)//���� 
				{
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[y][i] = 1;
					}//���� ģ�� �� ��ĭ 
					
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 9)//���� 
				{
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[i][x/2] = 1; 
					}//���� ģ���� �� ��ĭ 
					
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 10)//���� 
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
				
				else if(Map[y][x/2] == 11)//����+����
				{
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[y][i] = 1;
					}//���� ģ�� �� ��ĭ 
					for(int i = 0;i<7;i++)
					{
						LineCheckMap[i][x/2] = 1; 
					}//���� ģ���� �� ��ĭ 
					
					SuccessiveCrush();
				}
				
				else if(Map[y][x/2] == 12)//�ڽ� 3*3 
				{
					if(y==0)//�ڽ��� �� ���� ������ 
					{
						if(x == 0)//���� ��� 
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y+1][x/2] = 1;
							LineCheckMap[y+1][x/2+1] = 1;
							LineCheckMap[y][x/2+1] = 1;
						}
						
						else if(x == 12)//���� ��� 
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
						if(x == 0)//���� �ϴ� 
						{
							LineCheckMap[y][x/2] = 1;
							LineCheckMap[y-1][x/2] = 1;
							LineCheckMap[y-1][x/2+1] = 1;
							LineCheckMap[y][x/2+1] = 1;
						}
						
						else if(x == 12)//���� �ϴ� 
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
					
					else if(x == 0)//���� 
					{
						LineCheckMap[y][x/2] = 1;
						LineCheckMap[y-1][x/2] = 1;
						LineCheckMap[y-1][x/2+1] = 1;
						LineCheckMap[y][x/2+1] = 1;
						LineCheckMap[y+1][x/2+1] = 1;
						LineCheckMap[y+1][x/2] = 1;
					}
					
					else if(x == 12)//���� 
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
				
				else if(Map[y][x/2] == 13)//������
				{
					LineCheckMap[y][x/2] = 1; //�ڽŵ� Ư�� ĳ���Ͱ� �� 
					
					int random = (rand()%6) + 1;//Ư�� ĳ���� ���� 
					
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
//Ű���� ������
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
				if (y == 0) //�� ������ �ø������ϸ� ��� 
					break;

				prevcha = Map[y][x / 2]; //������ǥ 
				nextcha = Map[y - 1][x / 2];//������ǥ 

				Map[y][x / 2] = nextcha;
				Map[y - 1][x / 2] = prevcha;//���ιٲ� 

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
						LineCheckMap[i][j] = 0;
				} //LineCheckMap�� �ʱ�ȭ 

				LineChecker1();
				LineChecker2();//���μ��θ´��� üũ 

				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (LineCheckMap[i][j] == 0)
							cnt++;
					}
				}//��ĭ����üũ 

				if (cnt == 49)//�ٺ�ĭ�̸� 
				{
					Map[y][x / 2]  = prevcha;
					Map[y - 1][x / 2] = nextcha;//�����·ιٲٰ� 

					cnt = 0;//�ʱ�ȭ 
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
//ĳ���� ������
void LineChecker1()
{
	int cnt = 0;
	int i = 0, j = 0;

	while (1)
	{
		if (Map[i][j] == Map[i][j + 1] && j != 6)//�� ���� �ΰ��� ���� �� ���� ������ �ƴϸ� 
			cnt++;

		else
			cnt = 0;

		if (cnt == 2)
		{
			LineCheckMap[i][j + 1] = 1;
			LineCheckMap[i][j] = 1;
			LineCheckMap[i][j - 1] = 1;//3���� �������ϱ� �ϴ� �ΰ� 

			while (1) //4���̻����ΰ��°� 
			{
				if (j == 6)//���̸� �� ������ 
					break;

				if (Map[i][j] == Map[i][j + 1])
				{
					LineCheckMap[i][j + 1] = 1;
					j++;

					if (j == 7) //6�ʰ��ϸ� ������ 
						break;
				}

				else
				{
					cnt = 0;
					break;
				}
			}
		}

		if (i == 6 && j == 6) //�� �� ���� ���� �Ǹ� Ż�� 
			break;

		if (j == 6) //������ �� ���� ���� ������ ++ ������ 0 
		{
			j = 0;
			i++;
			cnt = 0;

		}
		else
			j++;
	}
}
//���� ������ ����Ȯ��
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
//���� ������ ����Ȯ��
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
		}//LineCheckMap�� ��ǥ�� 1�̸� Map�� ��ǥ�� ��ĭ���� ���� 
	}
	
	additionalTime = check/2;
	if(LimitTime<20)
	{
		LimitTime += additionalTime;
		if(LimitTime>20)
			LimitTime = 20;
	}
}
//����� ĳ���� 0���� ��ȯ
void EmptyCheck()
{
	int prevcha, nextcha;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{			
			if (Map[i][j] == 0) //Ư�� ��ǥ�� ��ĭ�̸� 
			{
				MapDrawer();
				Sleep(100);
				for (int k = i; k > 0; k--) //��ĭ�� ��� ���� �ø� 
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
//ĳ���͵� ������ ǥ��
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
	} //���� �ʿ� Ư�� ����� ������ cnt�� 1�� ����� Ư������� ��������� �ʰ� �� 
	
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Map[i][j] == 0)
			{
				if(cnt == 0) //�ʿ� Ư������� ������ 
				{
					random = rand()%29; //1/30�� Ȯ���� 
					
					if(random==0 && onlyone == 0) //�׸��� onlyone���� �ʵ忡 Ư������� �ϳ��� ������� 
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
						} //Ư�� ĳ���͵� ���� 
						onlyone = 1; //onlyone�� 1�� ���� �ʿ� 2�� �̻� ��������� �ʰ� �� 
					}
					
					else //�Ϲ� ��� ���� 
					{
						random = (rand() % 7) + 1;
						Map[i][j] = random;
					}
				}
				
				else //�Ϲ� ��� ���� 
				{			
					random = (rand() % 7) + 1;
					Map[i][j] = random;
				}
			}
		}
	}
}
//�� ĳ���� ����
void CanCrush()
{
	int cnt = 0, cha1, cha2,exitcode = 0;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i != 0) //�ø�
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
						if (LineCheckMap[m][n] == 0)//��ĭüũ 
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

				if (cnt != 49)//���� �� �ִ� ���� ������ 
				{
					cnt = 0;
					exitcode = 1;//exitcode�� ������Ż�� 
					break;
				}

				else
					cnt = 0;
			}

			if (i != 6) //����
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

			if (j != 0) //�����̵�
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

			if (j != 6) //�������̵�
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
		if(exitcode == 1)//exitcode�� ������ Ż�� 
			break;
	}
	
	if(exitcode != 1)
	{
		system("cls");
		MapDrawer();
		gotoxy(14, 3);
	
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
		printf("������ �� �ִ� ���� �����ϴ�");
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
//���� �� �ִ°� ->������ ��迭
void SuccessiveCrush()
{
	int cnt = 0;
	
	CrushCheck(); //0���� ����� 
	MapDrawer();
	Sleep(50);
	EmptyCheck(); //��ĭ ���� �ø��� 
	NewCharacter(); //��ĭ�� ���ο� ĳ���� ����� 
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			LineCheckMap[i][j] = 0;
	} //LineCheckMap�� �ʱ�ȭ 

	while (1)
	{
		LineChecker1(); //����üũ 
		LineChecker2(); //����üũ 

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (LineCheckMap[i][j] == 0) //���� ���� ��ĭ�̴� 
					cnt++;
			}
		}

		if (cnt != 49) //���� �ʿ��� 3���̻� �������� ���� �ִ�! 
		{
			MapDrawer();
			Sleep(450);
			CrushCheck(); //0���θ���� 
			MapDrawer();
			Sleep(50);
			EmptyCheck(); //��� ���οø��� 
			NewCharacter(); //����� ��ĳ���͸���� 

			cnt = 0; //�ٽ� �ʱ�ȭ 

			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
					LineCheckMap[i][j] = 0;
			} //LineCheckMap�� �ʱ�ȭ 
		}
	
		else //���� ��ĭ�̸� 
		{
			CanCrush();
			break;
		}
	}		
}
//�������� �浹 
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//Ŀ�� �̵� �Լ�9y
