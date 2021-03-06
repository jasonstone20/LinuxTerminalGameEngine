#include "screen.h"



screen::screen()
{
    //ctor
    initscr();
	nodelay(stdscr, true);			//if there wasn't any key pressed don't wait for keypress
	keypad(stdscr, true);			//init the keyboard
	noecho();									//don't write
	curs_set(0);							//cursor invisible
	getmaxyx(stdscr, maxHeight, maxWidth);

	//partchar='x';
	//partchar = (char)200;

	//PlayerX = maxWidth / 2;
	//PlayerY = maxHeight / 2;
	partchar = 'O';
	//testHorizontal = (char)219;
	//testVertical = (char)219;
	testVertical = '#';
	testHorizontal = '#';
	oldalchar=(char)219;
	//etel='*';
	GamePlay = true;
	GameOver = "Game Over!";
	etel = (char)219;
	//food.x=0;
	//food.y=0;
	//snake starting size
//	for(int i=0;i<1;i++)
//		snake.push_back(snakepart(40+i,10));
	points = 0;
	del = 500; //speed
	get = 0;
	//direction='l'; //starting direction
	srand(time(NULL));

}

screen::~screen()
{
    //dtor
    nodelay(stdscr,false);		//turn back
	getch();				    //wait until a key is pressed
	endwin();
}



void screen::GetScreenSize()
{
    nodelay(stdscr, false);
    //clear();
    //char sel;
    //while ((sel = getch()) != 13);
    mvprintw(maxHeight / 3, maxWidth / 4, "Your screen size is %d wide and %d high", maxWidth, maxHeight);
    mvprintw(maxHeight / 2, maxWidth / 4, "If you want to the screen a different size,\
 resize your\n \t\t \
    terminal and restart the program\n\n\t\t \
    Press any key to continue");

    getch();
    nodelay(stdscr, true);
}


void screen::print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}
void screen::EditColor(int colorName, int redColor, int greenColor, int blueColor)
{
    init_color(colorName, redColor, greenColor, blueColor);
}

void screen::ColorFill(int posY, int posX, int foreColor, int backColor, char displayChar,  bool colorOn)
{

    //initscr();			/* Start curses mode 		*/

	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	//foreColor = rand() % 10;

	for (int i = 0; i < maxWidth; i++)
	{

        printw("\n");

       // foreColor = rand() % 20;
       // backColor = rand() % 10;

        for (int j = 0; j < maxHeight; j++) //add posY++ or posX++ to fill
        {
            //move(posY, j) //hoizontal line
            //move( j, posX) //vertical line
            foreColor = rand() % 20;
            init_pair(1, foreColor, backColor);
            attron(COLOR_PAIR(1));
            printw("%c", displayChar);
            //init_pair(1, foreColor, 0);

            attron(COLOR_PAIR(1));
         //   printw("%d \n", foreColor);



            //move(j, i); //file the whole screen
            //addch(ACS_CKBOARD); //use displayChar varible here
        }

     }
	//print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");

    //refresh;
    getch();
	//endwin();

}

void screen::ColorText(int foreColor, int backColor, int colorTextX, int colorTextY, bool colorOn, char* colorText)
{
    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();
	init_pair(1, foreColor, backColor);
    attron(COLOR_PAIR(colorOn));
    move (colorTextX, colorTextY);
    printw("%s", colorText);
    attroff(COLOR_PAIR(0));
    refresh();
}


void screen::DisplayScreen(int height, int width, bool GameMapOn)
{
    //maxHeight and maxWidth can also be used for full screen mode
    //fill background

     	for (int i = 0; i < width; i++)
	{
        printw("\n");
        for (int j = 0; j < height; j++)
        {
            move(j, i);
            printw(" ");
        }
	}
    // draw boarder

    //top-horizontal
    for(int i = 0; i < width - 1; i++)
	{
		move(0, i);
		//addch(oldalchar);
		addch(ACS_HLINE);
	}
	//left-vertical
	for(int i = 0; i < height - 1; i++)
	{
		move(i, 0);
		addch(ACS_VLINE);
		//addch(oldalchar);
	}
	//bottom-horizontal
	for(int i = 0; i < width - 1; i++)
	{
		move(height - 2, i);
		//addch(oldalchar);
		addch(ACS_HLINE);
	}
//	//right-vertical
//	for(int i = 0; i < height - 1; i++)
//	{
//		move(i, width - 2);
//		//addch(oldalchar);
//        addch(ACS_VLINE);
//
//	}
    //print the boards corners
    move(0,0);
    addch(ACS_ULCORNER);
//    move(0, width - 2);
//    addch(ACS_URCORNER);
    move(height - 2, 0);
    addch(ACS_LLCORNER);
//    move(height - 2, width - 2);
//    addch(ACS_LRCORNER);

    //print score
	move(height - 1, 0);
	printw("%d", points);

//	move(food.y,food.x);
	addch(etel);

	//moveplayer();
	//GameMap
	if (GameMapOn == 1)
	{
        GameMap(height, width);
    }
//	for (int i = 0; i < height / 4; i++)
//    {
//        printw("\n");
//        for (int j = 0; j < width / 4; j++ )
//        {
//            move(i + 2,j + 2);
//            printw(".");
//
//
//            if (PlayerX / 4 == j && PlayerY / 4 == i)
//            {
//                move(i + 2, j + 2);
//                printw("*");
//            }
//            else
//            {
//                printw(".");
//            }
//        }
//    }
	//right-vertical
	for(int i = 0; i < height - 1; i++)
	{
		move(i, width - 2);
		//addch(oldalchar);
        addch(ACS_VLINE);

	}
	//upper right hand corner
	move(0, width - 2);
    addch(ACS_URCORNER);

	//lower right hand corner
	move(height - 2, width - 2);
    addch(ACS_LRCORNER);
	refresh();
}

void screen::SimpleStart()
{
    while(1)
    {
     //   ColorFill(10, 10, 1, 0, '*', 1);

    }
}
void screen::StartAuto(int height, int width, int speed, bool GameMapOn)
{
    //std::cout << "Jason" << std::endl;
    //std::cout << "Test" << std::endl;
    //std::cout << "Hello" << std::endl;
    //std::cout << maxHeight;
    //moveplayer();
//    std::cout << height << std::endl;
//    std::cout << width << std::endl;
//    std::cout << forecolor << std::endl;
//    std::cout << backcolor << std::endl;
    ScreenSize = true;
    if (height > maxHeight ||width > maxWidth ||speed < 50 || GameMapOn > 1)
        {
            printw("Error, please adjust your screen size or re-enter settings\n");
            exit(0);
        }
    if (height == 0 && width == 0)
    {
        height = maxHeight;
        width = maxWidth;
    }
    PlayerX = width / 2;
    PlayerY = height / 2;
    speed = del;
    clear();
    //GetScreenSize();
    DisplayScreen(height, width, GameMapOn);
    while (GamePlay)
    {
//      GameMap(height, width);
        int width = COLS;
        int height = LINES;
        DisplayScreen(height, width, GameMapOn);
        MovePlayer();
       // ScreenResize();


        //DisplayScreen(height, width, GameMapOn);
        //MovePlayer();
//      if (PlayerX == 0 || PlayerX == maxWidth - 2
//       || PlayerY == 0 || PlayerY == maxHeight - 2 )
        if (PlayerX == 0 || PlayerX == width - 2
         || PlayerY == 0 || PlayerY == height - 2 )
//            Collision();

        {
            move(height / 2, width / 2);
            printw("Game Over!");
            GamePlay = false;
            //break;
        }
        if( direction == 'q')				//exit
		{
            move(height / 2, width / 2);
            printw("Game Over!");
            GamePlay = false;
            //break;
        }
     napms(del); // or use usleep(100000)
    }


}

void screen::StartFixed(int height, int width, int speed, bool GameMapOn)
{
    //std::cout << "Jason" << std::endl;
    //std::cout << "Test" << std::endl;
    //std::cout << "Hello" << std::endl;
    //std::cout << maxHeight;
    //moveplayer();
//    std::cout << height << std::endl;
//    std::cout << width << std::endl;
//    std::cout << forecolor << std::endl;
//    std::cout << backcolor << std::endl;
    ScreenSize = false;
    if (height > maxHeight ||width > maxWidth ||speed < 50 || GameMapOn > 1)
        {
            printw("Error, please adjust your screen size or re-enter settings\n");
            exit(0);
        }
    if (height == 0 && width == 0)
    {
        height = maxHeight;
        width = maxWidth;
    }
    PlayerX = width / 2;
    PlayerY = height / 2;
    speed = del;
    clear();
    //GetScreenSize();
    while (GamePlay)
    {
//      GameMap(height, width);
        DisplayScreen(height, width, GameMapOn);
        MovePlayer();
       // ScreenResize();


        //DisplayScreen(height, width, GameMapOn);
        //MovePlayer();
//      if (PlayerX == 0 || PlayerX == maxWidth - 2
//       || PlayerY == 0 || PlayerY == maxHeight - 2 )
        if (PlayerX == 0 || PlayerX == width - 2
         || PlayerY == 0 || PlayerY == height - 2 )
//            Collision();

        {
            move(height / 2, width / 2);
            printw("Game Over!");
            GamePlay = false;
            //break;
        }
        if( direction == 'q')				//exit
		{
            move(height / 2, width / 2);
            printw("Game Over!");
            GamePlay = false;
            //break;
        }
     napms(del); // or use usleep(100000)
    }


}


void screen::TurnBased(int height, int width, int speed, bool GameMapOn)
{
    nodelay(stdscr,false);
    if (height == 0 && width == 0)
    {
        height = maxHeight;
        width = maxWidth;
    }
    PlayerX = width / 2;
    PlayerY = height / 2;
    speed = del;
    clear();
    //GetScreenSize();
    while (1)
    {
//      GameMap(height, width);
        //refresh();
        DisplayScreen(height, width, GameMapOn);
        MovePlayer();
        getch();
        refresh();
        // Collision Detection
//      if (PlayerX == 0 || PlayerX == maxWidth - 2
//       || PlayerY == 0 || PlayerY == maxHeight - 2 )
        if (PlayerX == 0 || PlayerX == width - 2
         || PlayerY == 0 || PlayerY == height - 2 )
        {
            move(height / 2, width / 2);
            printw("Game Over!");
            break;
        }
        if( direction == 'q')				//exit
		{
            move(height / 2, width / 2);
            printw("Game Over!");
            break;
        }
     napms(del); // or use usleep(100000)
    }

}

void screen::DisplayPlayer()
{
        move(PlayerY, PlayerX);
		addch(partchar);

}

void screen::MovePlayer()
{
    //Move Player
	//detect key
	int tmp = getch();
	switch(tmp)
	{
		case KEY_LEFT:
			//if(direction != 'r')
				direction = 'l';
			break;

		case KEY_UP:
			//if(direction != 'd')
				direction = 'u';
			break;

		case KEY_DOWN:
			//if(direction != 'u')
				direction = 'd';
			break;

		case KEY_RIGHT:
			//if(direction != 'l')
                direction = 'r';
			break;
        case KEY_HOME : //'q':
            direction = 'w';
            break;
        case KEY_END: //'z':
            direction = 'a';
            break;
        case KEY_PPAGE: // 'e':
            direction = 'x';
            break;
        case KEY_NPAGE: //'c':
            direction = 'c';
            break;
        case KEY_BACKSPACE:
			direction = 'q';
			break;
		case KEY_ENTER:
            direction = 's';
            break;

        case KEY_RESIZE:
        {
            ScreenResize();
            break;
        }
	}


	if (!get)
	{
		move(PlayerY, PlayerX);
		printw(" ");
		refresh();
	}
	if (direction == 'l')
	{
		PlayerX--;
	}
	else if (direction == 'r')
	{
		PlayerX++;
	}
	else if (direction == 'u')
	{
		PlayerY--;
	}
	else if (direction == 'd')
	{
		PlayerY++;
    }
    else if (direction == 's')
    {
        PlayerY = PlayerY;
        PlayerX = PlayerX;
    }

    else if (direction == 'a')
    {
        PlayerX--;
        PlayerY++;
    }
    else if (direction == 'w')
    {
        PlayerX--;
        PlayerY--;
    }
    else if (direction == 'x')
    {
        PlayerX++;
        PlayerY--;
    }
    else if (direction == 'c')
    {
        PlayerX++;
        PlayerY++;
    }
//    else if (direction == 'q')
//    {
//        printw("quit");
//    }
		//Print Player

    //move(PlayerY,PlayerX);
    //addch(partchar);
    DisplayPlayer();
	refresh();
}

int screen::EndGame()
{
    exit(0);
}

bool screen::Collision()
{
    if (PlayerX == 0 || PlayerX == width ||
        PlayerY == 0 || PlayerY == height )
        {
            move(height / 2, width / 2);
            printw("Game Over");
            EndGame();
        }
}

void screen::DrawHorzLine(int startLineX, int startLineY, int lineLength)
{
    for (int i = 0; i < lineLength; i++)
    {
        move(startLineX, startLineY + i);
        addch(ACS_HLINE);
    }
}

void screen::DrawVertLine(int startLineX, int startLineY, int lineLength)
{
    for (int i = 0; i < lineLength; i++)
    {
        move(startLineX + i, startLineY);
        addch(ACS_VLINE);
    }
}

void screen::DrawDiagDownLine(int startLineX, int startLineY, int lineLength)
{
    for (int i = 0; i < lineLength; i++)
    {
        move(startLineX + i, startLineY + i);
        printw("\\");
    }
}

void screen::DrawDiagUpLine(int startLineX, int startLineY, int lineLength)
{
    for (int i = 0; i < lineLength; i++)
    {
        move(startLineX + i, startLineY - i);
        printw("/");
    }
}
void screen::GameMap(int height, int width)
{
  	 for (int i = 0; i < height / 4; i++)
    {
        printw("\n");
        for (int j = 0; j < width / 4; j++ )
        {
            move(i + 2,j + 2);
            printw(".");


            if (PlayerX / 4 == j && PlayerY / 4 == i)
            {
                move(i + 2, j + 2);
                printw("*");
            }
            else
            {
                printw(".");
            }
        }
    }
    refresh();
}

void screen::ScreenResize()
{
    if (ScreenSize == true)
    {
        clear();
        int width = COLS;
        int height = LINES;
        DisplayScreen(height, width, GameMapOn);
        refresh();
    }
    else
    {
        clear();
    }
}

