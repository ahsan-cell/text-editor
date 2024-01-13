#include <fstream>
#include <iostream>
#include <stdlib.h>

# include "myconsole.h"
# include "editor.h"
# include"DoublyLinkList.h"
using namespace std;


//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK = 0x00;	int B_Royal_Blue = 0x10;	int B_Dark_Green = 0x20;
int B_Tale_Blue = 0x30;	int B_Dark_Red = 0x40;	int B_Purple = 0x50;
int B_Tale_Green = 0x60;	int B_Light_Grey = 0x70; int B_Dark_Gray = 0x80;
int B_Light_Blue = 0x90; int B_Light_Green = 0xA0;	int B_Sky_Blue = 0xB0;
int B_Red = 0xC0;	int B_Pink = 0xD0;	int B_Yellow = 0xE0;
int B_White = 0xF0;

int F_BLACK = 0x00;	int F_Royal_Blue = 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue = 0x03;	int F_Dark_Red = 0x04;	int F_Purple = 0x05;
int F_Tale_Green = 0x06;	int F_Light_Grey = 0x07; int F_Dark_Gray = 0x08;
int F_Light_Blue = 0x09; int F_Light_Green = 0x0A;	int F_Sky_Blue = 0x0B;
int F_Red = 0x0C;	int F_Pink = 0x0D;	int F_Yellow = 0x0E;
int F_White = 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x < MaxPoint.x)
		x++;
	else if (y < MaxPoint.y)
	{
		x = 0;
		y = y + 1;
	}
	else
		returnValue = false;

	return returnValue;
}

bool point::incrementY()
{
	bool returnValue = true;
	if (y < MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else if (y > 0)
	{
		y--;
		x = MaxPoint.x;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//

bool isBetween(DoublyLinkList<char>::iterator& obj, DoublyLinkList<char>::iterator& end)
{
	DoublyLinkList<char>::iterator temp2 = obj;

	temp2++;
	if (temp2 != end)
	{
		return true;
	}
	else
		return false;
}
//--------------------------The function Where you will write code--------------------------------//
int mainEditor()
{
	int key = 0;
	bool stop = false;
	point currentPosition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;
	bool space = false;
	DoublyLinkList<char> list;
	DoublyLinkList<char>::iterator start = list.Begin();
	DoublyLinkList<char>::iterator it = list.Begin();
	DoublyLinkList<char>::iterator printing = list.Begin();
	DoublyLinkList<char>:: iterator end = list.End();
	DoublyLinkList<char>::iterator temp = list.Begin();
	bool between = false;

	while (!stop)
	{
		key = CheckWhichKeyPressed(specialKey);
		between = isBetween(it, end);
		if (key == ESCKEY)
			stop = true;
		else if (between == true && !specialKey && key >= 32 && key <= 126)
		{
			list.Insert(it, key);
			it++;
			int y = currentPosition.getY();
			temp = it;
			printing = list.Begin();
			printing++;
			currentPosition.set(0, 0);
			ClearScreen();
			for (; printing != end; printing++)
			{
				PlaceCursor(currentPosition.getX(), currentPosition.getY());
				cout << *printing;
				if (currentPosition.getX() < MAX_X)
				{
					if (*printing == '\n')
					{
						currentPosition.incrementY();
						currentPosition.setX(0);
					}
					else
						currentPosition.incrementX();
				}
				else
				{
					currentPosition.incrementY();
					currentPosition.setX(0);

				}

			}
			currentPosition.setY(y);
			currentPosition.setX(0);
			temp = it;
			while (temp != start && *temp!='\n')
			{
				
				temp--;
			}
			while (temp != it)
			{
				currentPosition.incrementX();
				temp++;
			}
			///////                                 FAULTY
			//int count = 0;
			//int count2 = 0;
			//while (temp != end)//
			//{
			//	count++;
			//	temp++;
			//}
			//temp = it;
			//while (temp != start && *temp != '\n')
			//{
			//	temp--;
			//}
			//while (temp!=end && *temp != '\n')
			//{
			//	count2++;
			//	temp++;
			//}
			////currentPosition.setY(y);
			//for (int i = count; i > 0; i--)
			//{
			//	if (temp != end )
			//	{
			//		if (currentPosition.getX() == 0 && currentPosition.getY() > 0)
			//		{
			//			currentPosition.decrementY();
			//			currentPosition.setX(count2);

			//		}
			//	}
			//	currentPosition.decrementX();
			//}
			//currentPosition.incrementX();
		}
		else if (!specialKey && key >= 32 && key <= 126)
		{
			
			if (key == 32)
				space = true;
			list.Insert(it, key);
			
		    if (currentPosition.getX() < MAX_X)
			{
				
				SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), B_White | F_BLACK); 
                currentPosition.incrementX();
				it++;
				cout << *it;
			}
			else if (currentPosition.getY() < MAX_Y)
			{
				currentPosition.incrementY();
				currentPosition.setX(0);
				it++;
				cout << *it;
			}
			if (currentPosition.getX() == 98 && space == true)
			{
				temp = it;

				while (*temp != 32)
					temp--;
				list.Insert(temp, '\n');

				printing = list.Begin();
				printing++;
				currentPosition.set(0, 0);
				ClearScreen();
				for (; printing != end; printing++)
				{
					PlaceCursor(currentPosition.getX(), currentPosition.getY());
					cout << *printing;
					if (currentPosition.getX() < MAX_X)
					{
						if (*printing == '\n')
						{
							currentPosition.incrementY();
							currentPosition.setX(0);
						}
						else
							currentPosition.incrementX();
					}
					else
					{
						currentPosition.incrementY();
						currentPosition.setX(0);

					}

				}
			}
		}
		else if (specialKey && key == LEFTKEY)
		{
			if (currentPosition.decrementX())
				it--;
		}
		else if (specialKey && key == RIGHTKEY)
		{
			temp = it;
			temp++;
			if (temp != end)
			{
				currentPosition.incrementX();
				it++;
			}
		}
		else if (specialKey && key == UPKEY)
		{
			if (currentPosition.getY() > 0)
			{
				DoublyLinkList<char>::iterator temp2;
				int x = currentPosition.getX();
				temp = it;
				bool special_case = false;
				if (*temp == '\n')
					temp--;
				while (temp != end)
				{
					if (*temp == '\n')
					{
						temp2 = temp;
						break;
					}
					temp--;
					if (temp == end)
					{
						special_case = true;
						break;
					}
				}
				if (!special_case)
				{
					int count = 1;
					temp2--;
					while (temp2 != end && *temp2 != '\n')
					{
						count++;
						temp2--;
					}
					count = count - 1;
					if (temp2 == end)
						count = count - 1;
					if (count < x)
					{
						currentPosition.decrementY();
						currentPosition.setX(count + 1);
						it = temp;

					}
					else
					{

						currentPosition.decrementY();
						for (int i = 0; i < count; i++)
							it--;
						it--;
					}
				}
				else
				{
					it = list.Begin();
					it++;
					currentPosition.set(0, 0);
				}
			}
		}
		else if (specialKey && key == DOWNKEY)
		{	
			DoublyLinkList<char>::iterator temp2;
			bool down = false;
			temp = it;
			while (temp != end && !down)
			{
				if (*temp == '\n')
				{
					temp2 = temp;
					down = true;
				}
				temp++;
			}
			if (down)
			{
				int x = currentPosition.getX();
				int count = 0;
				
				temp2++;
				while (temp2 != end && *temp2 != '\n')
				{
					count++;
					temp2++;
				}
				if (x > count)
				{
					currentPosition.incrementY();
					currentPosition.setX(0);
					for (int i = 0; i < count; i++)
						currentPosition.incrementX();
					it = temp;
					it--;
					for (int i = 0; i < count; i++)
						it++;
				}
				else
				{
					it = --temp;

					currentPosition.incrementY();
					currentPosition.setX(0);
					for (int i = 0; i < x; i++)
						currentPosition.incrementX();
					for (int i = 0; i < x; i++)
						it++;
					
				}
				

			}
		}
		else if (key == ENTERKEY) {
			//cout << ('\n');
			list.Insert(it,'\n');
			it++;
			//cout << *it;
			currentPosition.setX(0);
			currentPosition.incrementY();
			////////////////////////////
			printing = list.Begin();
			printing++;
			currentPosition.set(0, 0);
			ClearScreen();
			for (; printing != end; printing++)
			{
				PlaceCursor(currentPosition.getX(), currentPosition.getY());
				cout << *printing;
				if (currentPosition.getX() < MAX_X)
				{
					if (*printing == '\n')
					{
						currentPosition.incrementY();
						currentPosition.setX(0);
					}
					else
						currentPosition.incrementX();
				}
				else
				{
					currentPosition.incrementY();
					currentPosition.setX(0);

				}

			}
			currentPosition.setX(0);
			
		}
		else if (key == DELKEY)
		{
			//call a function to handle
			cout << '\0';
			//handle backspace here

			DoublyLinkList<char>::iterator mark;
			DoublyLinkList<char>::iterator check;
			check = it;
			check++;
			if (check != end)
			{
				it++;
				temp = it;
				it--;
				mark = it;
				list.Delete(temp);
				currentPosition.set(0, 0);
				printing = list.Begin();
				printing++;
				ClearScreen();
				for (; printing != end; printing++)
				{
					PlaceCursor(currentPosition.getX(), currentPosition.getY());
					cout << *printing;
					if (currentPosition.getX() < MAX_X)
					{
						if (*printing == '\n')
						{
							currentPosition.incrementY();
							currentPosition.setX(0);
						}
						else
							currentPosition.incrementX();
					}
					else
					{
						currentPosition.incrementY();
						currentPosition.setX(0);

					}

				}
				currentPosition.set(0, 0);
				PlaceCursor(currentPosition.getX(), currentPosition.getY());
				temp = list.Begin();
				while (temp != it)
				{
					if (currentPosition.getX() < MAX_X)
					{
						if (*temp == '\n')
						{
							currentPosition.incrementY();
							currentPosition.setX(0);
						}
						else
							currentPosition.incrementX();
					}
					else
					{
						currentPosition.incrementY();
						currentPosition.setX(0);

					}
					temp++;
				}
				if (currentPosition.getY() > 0)
				{
					currentPosition.incrementX();
				}

			}
		}
		else if (key == BACKSPACE)
		{
			cout << '\0';
			DoublyLinkList<char>::iterator mark;
			if (it != start)
			{
			    temp = it;
				it--;
			    mark = it;
				list.Delete(temp);
				currentPosition.set(0, 0);
				printing = list.Begin();
				printing++;
				ClearScreen();
				for (; printing != end; printing++)
				{			
					PlaceCursor(currentPosition.getX(), currentPosition.getY());
					cout << *printing;
					if (currentPosition.getX() < MAX_X)
					{
						if (*printing == '\n')
						{
							currentPosition.incrementY();
							currentPosition.setX(0);
						}
						else
						currentPosition.incrementX();
					}
					else
					{
						currentPosition.incrementY();
						currentPosition.setX(0);

					}

				}
				currentPosition.set(0, 0);
				PlaceCursor(currentPosition.getX(), currentPosition.getY());
				temp = list.Begin();
				while (temp != it)
				{
					if (currentPosition.getX() < MAX_X)
					{
						if (*temp == '\n')
						{
							currentPosition.incrementY();
							currentPosition.setX(0);
						}
						else
						currentPosition.incrementX();
					}
					else
					{
						currentPosition.incrementY();
						currentPosition.setX(0);

					}
					temp++;
				}
				if (currentPosition.getY() > 0)
				{
					currentPosition.incrementX();
				}
				
			}

			
		}
		else if (key == F1KEY || key == F2KEY || key == F3KEY)
		{
			PlaceCursor(0, MAX_Y);
			cout << "Enter Search Query: " << endl;
			currentPosition.setX(0 + strlen("Enter Search Text : "));
			currentPosition.setY(MAX_Y);
			PlaceCursor(currentPosition.getX(), currentPosition.getY());
			char query[50];
			cin.getline(query, 50);
			int size = strlen(query);
			if (key == F1KEY) {
				
				
				it = list.Search_First(query, size);
				temp = list.Begin();
				temp++;
				currentPosition.set(0, 0);
				PlaceCursor(currentPosition.getX(), currentPosition.getY());
				for (; temp != it; temp++)
				{
					if (currentPosition.getX() < MAX_X)
					{
						if (*temp == '\n')
						{
							currentPosition.incrementY();
							currentPosition.setX(0);
						}
						else
							currentPosition.incrementX();
					}
					else
					{
						currentPosition.incrementY();
						currentPosition.setX(0);

					}
				}

			}
			else if (key == F2KEY)
			{
				DoublyLinkList<DoublyLinkList<char>::iterator> list2;
				DoublyLinkList<DoublyLinkList<char>::iterator>::iterator it2 = list2.Begin();
				DoublyLinkList<DoublyLinkList<char>::iterator>::iterator end2 = list2.End();
				DoublyLinkList<char>::iterator temp3 = list.Begin();
				list.Search_all(query, size, list2);
				//-------------------------------------
				currentPosition.set(0, 0);
				it2++;
				if (it2 == end2)
				{
					cout << "NOT FOUND";
					cin.get();
					printing = list.Begin();
					printing++;
					currentPosition.set(0, 0);
					ClearScreen();
					for (; printing != end; printing++)
					{
						PlaceCursor(currentPosition.getX(), currentPosition.getY());
						cout << *printing;
						if (currentPosition.getX() < MAX_X)
						{
							if (*printing == '\n')
							{
								currentPosition.incrementY();
								currentPosition.setX(0);
							}
							else
								currentPosition.incrementX();
						}
						else
						{
							currentPosition.incrementY();
							currentPosition.setX(0);

						}

					}
				}
				else
				{
					while (it2 != end2)
					{
						temp3 = list.Begin();
						temp3++;
						currentPosition.set(0, 0);
						PlaceCursor(currentPosition.getX(), currentPosition.getY());
						for (; temp3 != *it2; temp3++)
						{
							if (currentPosition.getX() < MAX_X)
							{
								if (*temp3 == '\n')
								{
									currentPosition.incrementY();
									currentPosition.setX(0);
								}
								else
									currentPosition.incrementX();
							}
							else
							{
								currentPosition.incrementY();
								currentPosition.setX(0);

							}
						}
						for (int i = 0; i < size; i++)
						{
							SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Yellow); //ForeGround|BackGround
							if (!currentPosition.incrementX())
							{
								currentPosition.decrementY();
								currentPosition.setX(0);
							}
						}
						it2++;
					}


				}
				it = list.Begin();
				it++;
				currentPosition.set(0, 0);
				
			}
			else if(key == F3KEY)
			{
				
				cout << "Enter replacement: ";
				char replacement[50];
				cin.getline(replacement, 50);
				int size_replace= strlen(replacement);
				DoublyLinkList<DoublyLinkList<char>::iterator> list2;
				DoublyLinkList<DoublyLinkList<char>::iterator>::iterator it2 = list2.Begin();
				DoublyLinkList<DoublyLinkList<char>::iterator>::iterator end2 = list2.End();
				DoublyLinkList<char>::iterator temp3 = list.Begin();
				list.Search_all(query, size, list2);
				//-------------------------------------
				currentPosition.set(0, 0);
				it2++;
				if (it2 == end2)
				{
					cout << "NOT FOUND";
					cin.get();
					printing = list.Begin();
					printing++;
					currentPosition.set(0, 0);
					ClearScreen();
					for (; printing != end; printing++)
					{
						PlaceCursor(currentPosition.getX(), currentPosition.getY());
						cout << *printing;
						if (currentPosition.getX() < MAX_X)
						{
							if (*printing == '\n')
							{
								currentPosition.incrementY();
								currentPosition.setX(0);
							}
							else
								currentPosition.incrementX();
						}
						else
						{
							currentPosition.incrementY();
							currentPosition.setX(0);

						}

					}
				}
				else
				{
					while (it2 != end2)
					{
						list.Delete_Multiple(*it2, query, size);
						list.Print();
						if ((*it2) != end)
							(*it2)--;
						list.Insert_Multiple(*it2, replacement, size_replace);
						it2++;
					}
					printing = list.Begin();
					printing++;
					ClearScreen();
					for (; printing != end; printing++)
					{
						PlaceCursor(currentPosition.getX(), currentPosition.getY());
						cout << *printing;
						if (currentPosition.getX() < MAX_X)
						{
							if (*printing == '\n')
							{
								currentPosition.incrementY();
								currentPosition.setX(0);
							}
							else
								currentPosition.incrementX();
						}
						else
						{
							currentPosition.incrementY();
							currentPosition.setX(0);

						}

					}
				}
				

			}

		}
		else if (key == F4KEY)
		{
		   ofstream fout;
		   char filename[50];
		   PlaceCursor(0, MAX_Y);
		   cout << "Enter Filename: " << endl;
		   currentPosition.setX(0 + strlen("Enter Filename : "));
		   currentPosition.setY(MAX_Y);
		   PlaceCursor(currentPosition.getX(), currentPosition.getY());
		   cin.getline(filename, 50);
		   fout.open(filename);
		   temp = list.Begin();
		   temp++;
		   end = list.End();
		   while (temp != end)
		   {
			   fout << *temp;
			   temp++;
		   }
		   fout.close();
		   cout << "SAVE SUCCESSFUL";
		   cin.get();

		   printing = list.Begin();
		   printing++;
		   currentPosition.set(0, 0);
		   ClearScreen();
		   for (; printing != end; printing++)
		   {
			   PlaceCursor(currentPosition.getX(), currentPosition.getY());
			   cout << *printing;
			   if (currentPosition.getX() < MAX_X)
			   {
				   if (*printing == '\n')
				   {
					   currentPosition.incrementY();
					   currentPosition.setX(0);
				   }
				   else
					   currentPosition.incrementX();
			   }
			   else
			   {
				   currentPosition.incrementY();
				   currentPosition.setX(0);

			   }

		   }
        }
		PlaceCursor(currentPosition.getX(), currentPosition.getY());

	}
		
		
		
	list.Print();

	return 0;
}



void main()
{
	mainEditor();
	////DoublyLinkList<char> d1;
	////d1.Insert_at_Head('s');
	////d1.Insert_at_Head('i');
	////d1.Insert_at_Head('x');
	////d1.Insert_at_Head(' ');
	////d1.Insert_at_Head('e');
	////d1.Insert_at_Head('w');
	////d1.Insert_at_Head('a');
	////d1.Insert_at_Head(' ');
	////d1.Insert_at_Head('s');
	////d1.Insert_at_Head('i');
	////d1.Insert_at_Head(' ');
	////d1.Insert_at_Head('n');
	////d1.Insert_at_Head('a');
	////d1.Insert_at_Head('s');
	////d1.Insert_at_Head('h');
	////d1.Insert_at_Head('a');
	////DoublyLinkList<char>::iterator *a1;
	///*int sizet = 0;
	//char element[50] = { 'i','s','\0' };
	//int size = strlen(element);
	//DoublyLinkList<DoublyLinkList<char>::iterator> a1;
	//d1.Search_all(element, size, a1);*/
	//DoublyLinkList<char>::iterator b = d1.Begin();
	//b++;
	//DoublyLinkList<char>::iterator c = d1.Begin();
 //  c++;
 //  c++;
 //  c++;
 //  c++;
 //  c++;
 //  char name[5] = { 'a','h','s','a','n' };
 //  d1.Delete_Multiple(b, name, 5);
 //  d1.Print();




}