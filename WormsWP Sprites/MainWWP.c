// C Source File
// Created 6/27/2004; 1:52:27 PM

// Delete or comment out the items you do not need.
#if 0
#define COMMENT_STRING         "Place your comment here."
#define COMMENT_PROGRAM_NAME   "Place your program name here."
#define COMMENT_VERSION_STRING "Place your version string here."
#define COMMENT_VERSION_NUMBER 0,0,0,0 /* major, minor, revision, subrevision */
#define COMMENT_BW_ICON \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}
#define COMMENT_GRAY_ICON \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}, \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}
#endif

#include <tigcclib.h>
#include "extgraph.h"
#include "WWPSprites.c"

//FUNCTION DECLARATIONS
static void GGrayOn();
static void GGrayOff();
static void MainLoop();
static void DrawScreen();
static void KeyHandle();
static void drawtxt(int x, int y, const char *str, short col);
static void drawtxtbox(int x, int y, int width, const char *str, short col);
static void drawdropbox(int x, int y, int width, const char *cap);
static void DoAni();
static void drawokx();
static void InputStr(int x, int y, char *buffer, unsigned short maxlen);
static void SaveTeam();
static void LoadTeam();
static void GetTeams(short boxx, short boxy);
static void MsgBox(const char *msg, const char *cap);
static short DoPopUp(short x, short y, const char *List, short MaxList);
static short CheckAr(const char *fold, const char *str);
static void ClrNames();
static void SaveSettings();
static void StartGame();


//VARIABLES!
void *DBuffer;
char exitexe; //boolean to hold whether or not to exit the exe
char screen; //holds what screen the user is on.. (weapons, options, etc)
short cx=5, cx2=70, cy=20, cy2=40; //holds the position of the moving clouds
short sel=1; //hols what item is selected
char names[10][9] =
{
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
};
short Worms1=8, Worms2=8;
char team1[]="<Name>  ";
char team2[]="<Name>  ";
char map[]="<Map>   ";
char *maps;
short WX=0, WY=0;
short WeaponSet[5][14]={
	{0,9,9,9,9,1,1,3,5,0,2,0,9,1},
	{0,1,3,9,9,2,1,3,2,0,1,0,9,1},
	{0,5,0,9,1,1,0,3,2,0,0,0,3,1},
	{0,0,2,0,0,0,0,1,2,0,0,0,0,1},
	{0,0,0,2,9,0,0,0,0,0,0,0,0,1}};
short Opt[12]={1,0,0,0,0,0,1,1,1,0,0,0};

INT_HANDLER save_1a;
INT_HANDLER save_5a;
	
//ENUMERATIONS:
enum BOOLEANS {false, true};
enum SCREENS {gtronics, team17, titus, title, mainmenu, setup, teams, teamsetup, mapedit, weapons, scheme, options, cake, newteam, editteam};


// Main Function
void _main(void)
{
  //INT_HANDLER save_1 = GetIntVec(AUTO_INT_1); 
  //INT_HANDLER save_5 = GetIntVec(AUTO_INT_5); 
  save_1a= GetIntVec(AUTO_INT_1);
  save_5a = GetIntVec(AUTO_INT_5); 
  // Sets It Up For _keytest usage..
	SetIntVec(AUTO_INT_1, DUMMY_HANDLER); 
	SetIntVec(AUTO_INT_5, DUMMY_HANDLER); 
	
	// Place your code here.
	ClearScreen();
	
	//turns gs on
	GGrayOn();
	
	MainLoop();
	
	
	//kills the gs
	GGrayOff();
	
	//resets some stuff
	SetIntVec(AUTO_INT_1, save_1a); 
	SetIntVec(AUTO_INT_5, save_5a); 
}


//TURNS GREYSCALE ON!
void GGrayOn()
{
	GrayOn();
	void *dbuffer=malloc(GRAYDBUFFER_SIZE); // allocate space for double-buffering
  GrayDBufInit(dbuffer); // enable double-buffering
  DBuffer=dbuffer;
}
//TURNS GRAYSCALE OFF!
void GGrayOff() // gray scalc off
{
	GrayOff();
	free(DBuffer);
}



//BIG SUPRISE: THE CODES MAIN LOOP!!
void MainLoop()
{
  exitexe=false;
	while(exitexe==false)
	{
	  //hanles key presses
	  KeyHandle();
	  
	  //Does the animated need for the current screen
	  DoAni();
	  
	  //draws the screen
		DrawScreen();
		
	}//wend
}



//DOES THE ANIMATION FOR THE CURRENT SCREEN...
void DoAni()
{
	if(screen==title)
	  {
	  	//animats the moving clouds
	  	//moves them right
	  	cx++;
	  	cx2+=2;
	  	//if theyve disapered, time to respawn them
	  	if(cx>156)
	  	  {
	  	  	cx=-32;
	  	  	cy=random(83);
	  	  }
	  	if(cx2>156)
	  	  {
	  	  	cx2=-32;
	  	  	cy2=random(83);
	  	  }
	  }//end if title
}


//DRAW CODE, TO DRAW THE VARIOUS THINGS
void DrawScreen()
{
  short x, y;
  
  //clears teh planes
  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
	ClrScr();
	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
	ClrScr();
  void * lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void * dplane = GrayDBufGetHiddenPlane(DARK_PLANE);

	//draws the screen based on the screen num, as well as certain variables
	if(screen==gtronics)
		{

		  //draws the gt logo
		  GrayClipSprite32_OR_R(30, 5, 53, gt1, gt1, lplane, dplane);
			ClipSprite32_OR_R(30+3, 5+3, 53, gt1, lplane);
	    GrayClipSprite32_OR_R(30 + 32, 5, 74, gt2, gt2, lplane, dplane);
			ClipSprite32_OR_R(30+32+3, 5+3, 74, gt2, lplane);
	    GrayClipSprite32_OR_R(30 + 64, 5, 74, gt3, gt3, lplane, dplane);
			ClipSprite32_OR_R(30+64+3, 5+3, 74, gt3, lplane);
	
			
			drawtxt(30,85,"Proudly Presents...", 0);
		}//end if gtronics
	else if(screen==team17)
	  {
	  	GrayClipSprite32_OR_R(35, 18, 52, t171, t171, lplane, dplane);
			GrayClipSprite32_OR_R(35 + 32, 18, 55, t172, t172, lplane, dplane);
			GrayClipSprite32_OR_R(35 + 64, 18, 46, t173, t173, lplane, dplane);
			
			drawtxt(15,5,"A Game Originally By:",0);
			
			
	  }//end if team17
  else if(screen==titus)
	  {
	  	GrayClipSprite32_OR_R(45, 23, 59, tit1, tit1, lplane, dplane);
			GrayClipSprite32_OR_R(45 + 32, 23, 59, tit2, tit2, lplane, dplane);
			ClipSprite8_OR_R(45+64, 23, 59, tit3, dplane);
			ClipSprite8_OR_R(45+64, 23, 59, tit3, lplane);
			
			drawtxt(60,5,"And By:",0);
	  }//end if titus
	else if(screen==title)
	  {
	  	//draws the animated clouds
			GrayClipSprite32_OR_R(cx, cy, 17, cloudi, cloud, lplane, dplane);
			GrayClipSprite32_OR_R(cx2, cy2, 17, cloudi, cloud, lplane, dplane);
			
	  	GrayClipSprite32_AND_R(5, 0, 100, tsm1, tsm1, lplane, dplane);
			GrayClipSprite32_AND_R(5 + 32, 0, 100, tsm2, tsm2, lplane, dplane);
			GrayClipSprite32_AND_R(5 + 64, 0, 100, tsm3, tsm3, lplane, dplane);
			GrayClipSprite32_AND_R(5 + 96, 0, 100, tsm4, tsm4, lplane, dplane);
			GrayClipSprite32_AND_R(5 + 128, 0, 100, tsm5, tsm5, lplane, dplane);

	  	GrayClipSprite32_OR_R(5, 0, 97, tsi1, ts1, lplane, dplane);
			GrayClipSprite32_OR_R(5 + 32, 0, 100, tsi2, ts2, lplane, dplane);
			GrayClipSprite32_OR_R(5 + 64, 0, 100, tsi3, ts3, lplane, dplane);
			GrayClipSprite32_OR_R(5 + 96, 0, 96, tsi4, ts4, lplane, dplane);
			GrayClipSprite32_OR_R(5 + 128, 0, 85, tsi5, ts5, lplane, dplane);
	  }//end if title
	
	else if(screen==mainmenu)
	  {
	  	GrayClipSprite32_OR_R(43, 30, 21, BttnVersus, BttnVersus, lplane, dplane);
			GrayClipSprite32_OR_R(83, 30, 21, BttnTeams, BttnTeams, lplane, dplane);
			//ClipSprite32_OR_R(41, 55, 21, BttnTeams, lplane);
			//ClipSprite32_OR_R(80, 54, 21, BttnOptions, dplane);
			//ClipSprite32_OR_R(80, 54, 21, BttnOptions, lplane);
			//ClipSprite32_OR_R(81, 55, 21, BttnOptions, lplane);
			
			drawokx();
			
			FontSetSys(2);
			drawtxt(11,3,"WORMS WORLD PARTY",2);
			drawtxt(12,4,"WORMS WORLD PARTY",0);
			drawtxt(13,5,"WORMS WORLD PARTY",1);
			FontSetSys(1);
			
			//draws the selection for what ever is selected
			if(sel==1)
			  {
			  	ClipSprite32_OR_R(44, 31, 21, BttnVersus, lplane);
			  	drawtxt(25,90,"Make A Versus Game",0);
			  }
			else if(sel>1)
			  {
			  	ClipSprite32_OR_R(84, 31, 21, BttnTeams, lplane);
			  	drawtxt(28,90,"Set Up Your Teams",0);
			  	sel=2;
			  }
			/*if(sel==3 || sel>3)
			  {
			  	sel=3;
			  	ClipSprite32_OR_R(82, 56, 21, BttnOptions, lplane);
			  	drawtxt(37,90,"Set Up Options",0);
			  }*/
	  }//end if main menu
	  
	
	else if(screen==teamsetup)
	  {
			drawokx();
			
	  	FontSetSys(2);
			drawtxt(37,3,"TEAM SETUP",2);
			drawtxt(38,4,"TEAM SETUP",0);
			drawtxt(39,5,"TEAM SETUP",1);
			FontSetSys(1);
			
			drawtxt(10,25,"1) New Team",1);
			drawtxt(10,36,"2) Edit Team",1);
			
			//draws the selection for what ever is selected
			if(sel==1)
			  {
			  	drawtxt(10,25,"1) New Team",0);
			  	drawtxt(33,90,"Make A New Team",0);
			  }
			else if(sel==2 || sel>2)
			  {
			  	sel=2;
			  	drawtxt(10,36,"2) Edit Team",0);
			  	drawtxt(30,90,"Edit An Old Team",0);
			  }
			
	  }//end if teamsetup
	  
	else if(screen==newteam)
	  {  
	    drawokx();
	  
	  	FontSetSys(2);
			drawtxt(43,3,"NEW TEAM:",2);
			drawtxt(44,4,"NEW TEAM:",0);
			drawtxt(45,5,"NEW TEAM:",1);
			FontSetSys(1);
	  
	    drawtxt(6,20,"Team Name:",0);
	    drawtxtbox(6,28,60,names[0], 1);
	    drawtxt(70,20,"Team Members:",0);
	    drawtxtbox(70,28,40,names[1],1);
	    drawtxtbox(70,38,40,names[2],1);
	    drawtxtbox(70,48,40,names[3],1);
	    drawtxtbox(70,58,40,names[4],1);
	    drawtxtbox(110,28,40,names[5],1);
	    drawtxtbox(110,38,40,names[6],1);
	    drawtxtbox(110,48,40,names[7],1);
	    drawtxtbox(110,58,40,names[8],1);
	    drawtxt(6,40,"Grave:",0);
	    drawdropbox(6,48,60,names[9]);
	    
	    if(sel==1) drawtxtbox(6,28,60,"",0);
	    else if(sel==2) drawtxtbox(70,28,40,"",0);
	    else if(sel==3) drawtxtbox(70,38,40,"",0);
	    else if(sel==4) drawtxtbox(70,48,40,"",0);
	    else if(sel==5) drawtxtbox(70,58,40,"",0);
	    else if(sel==6) drawtxtbox(110,28,40,"",0);
	    else if(sel==7) drawtxtbox(110,38,40,"",0);
	    else if(sel==8) drawtxtbox(110,48,40,"",0);
	    else if(sel==9) drawtxtbox(110,58,40,"",0);
	    else if(sel>=10)
	      {
	      	sel=10;
	      	drawtxtbox(6,48,60,"",0);
	      }
	    
	    
	  }//end if newteam
	  
	  else if(screen==editteam)
	  {  

	    drawokx();
	    
	  	FontSetSys(2);
			drawtxt(38,3,"EDIT TEAM:",2);
			drawtxt(39,4,"EDIT TEAM:",0);
			drawtxt(40,5,"EDIT TEAM:",1);
			FontSetSys(1);
	  
	    drawtxt(6,20,"Team Name:",0);
	    drawdropbox(6,28,60, names[0]);
	    drawtxt(70,20,"Team Members:",0);
	    drawtxtbox(70,28,40,names[1],1);
	    drawtxtbox(70,38,40,names[2],1);
	    drawtxtbox(70,48,40,names[3],1);
	    drawtxtbox(70,58,40,names[4],1);
	    drawtxtbox(110,28,40,names[5],1);
	    drawtxtbox(110,38,40,names[6],1);
	    drawtxtbox(110,48,40,names[7],1);
	    drawtxtbox(110,58,40,names[8],1);
	    drawtxt(6,40,"Grave:",0);
	    drawdropbox(6,48,60,names[9]);
	    
	    if(sel==1) drawtxtbox(6,28,60,"",0);
	    else if(sel==2) drawtxtbox(70,28,40,"",0);
	    else if(sel==3) drawtxtbox(70,38,40,"",0);
	    else if(sel==4) drawtxtbox(70,48,40,"",0);
	    else if(sel==5) drawtxtbox(70,58,40,"",0);
	    else if(sel==6) drawtxtbox(110,28,40,"",0);
	    else if(sel==7) drawtxtbox(110,38,40,"",0);
	    else if(sel==8) drawtxtbox(110,48,40,"",0);
	    else if(sel==9) drawtxtbox(110,58,40,"",0);
	    else if(sel>=10)
	      {
	      	sel=10;
	      	drawtxtbox(6,48,60,"",0);
	      }
	      
	  }//end if newteam
	  
	else if(screen==setup)
	{
		drawokx();
		FontSetSys(2);
		drawtxt(36,3,"GAME SETUP:",2);
		drawtxt(37,4,"GAME SETUP:",0);
		drawtxt(38,5,"GAME SETUP:",1);
		FontSetSys(1);
		
		//draws the layout
		drawtxt(15,15,"Map:",0);
		drawdropbox(15,23,60,map);
		drawtxt(15,36,"Team 1:",0);
		drawdropbox(15,44,60,team1);
		drawtxt(15,57,"Team 2:",0);
		drawdropbox(15,65,60,team2);
		
		//stuff for selection
		if(sel==1)
		  {
		  	drawtxt(45,90,"Choose A Map",0);
        drawtxtbox(15,23,60,"",0);
		  }
		else if(sel==2)
		  {
		  	drawtxt(42,84,"Choose Team 1",0);
		  	drawtxt(29,92,"+/- Worms On Team",0);
        drawtxtbox(15,44,60,"",0);
        drawtxtbox(82,44,60,"",0);
		  }
    else if(sel==3)
		  {
		  	drawtxt(42,84,"Choose Team 2",0);
		  	drawtxt(29,92,"+/- Worms On Team",0);
        drawtxtbox(15,65,60,"",0);
        drawtxtbox(82,65,60,"",0);
		  }
		else if(sel==4)
		  {
		  	ClipSprite32_OR_R(79, 18, 21, BttnWeaps, lplane);
		  	drawtxt(37,90,"Choose Weapons",0);
		  }
		else if(sel>4)
		  {
		  	ClipSprite32_OR_R(114, 18, 21, BttnOptions, lplane);
		  	drawtxt(37,90,"Choose Options",0);
		  	sel=5;
		  }
		  
		//draws the dark buttons
		ClipSprite32_OR_R(79, 18, 21, BttnWeaps, dplane);
		ClipSprite32_OR_R(114, 18, 21, BttnOptions, dplane);
		
		//draws worms for team...
		drawtxtbox(82,44,60,"",1);
		for(x=0;x<Worms1;x++)
		  {
		  	GrayClipSprite16_AND_R((76 + (Worms1 * 6)) - (x * 6), 42, 15, WormRightI, WormRightI, lplane, dplane);
		  	GrayClipSprite16_OR_R((76 + (Worms1 * 6)) - (x * 6), 42, 15, WormRight, WormRight, lplane, dplane);
		  }
		drawtxtbox(82,65,60,"",1);
		for(x=0;x<Worms2;x++)
		  {
		  	GrayClipSprite16_AND_R((76 + (Worms2 * 6)) - (x * 6), 63, 15, WormRightI, WormRightI, lplane, dplane);
		  	GrayClipSprite16_OR_R((76 + (Worms2 * 6)) - (x * 6), 63, 15, WormRight, WormRight, lplane, dplane);
		  }
	}//end if set up
	
	else if(screen==weapons)
	  {
	  	drawokx();
			FontSetSys(2);
			drawtxt(46,3,"WEAPONS:",2);
			drawtxt(47,4,"WEAPONS:",0);
			drawtxt(48,5,"WEAPONS:",1);
			FontSetSys(1);
			
			GrayClipSprite32_OR_R(1, 15, 61, Weapons1, Weapons1, lplane, dplane);
			GrayClipSprite32_OR_R(33, 15, 61, Weapons2, Weapons2, lplane, dplane);
			GrayClipSprite32_OR_R(65, 15, 61, Weapons3, Weapons3, lplane, dplane);
			GrayClipSprite32_OR_R(97, 15, 61, Weapons4, Weapons4, lplane, dplane);
			GrayClipSprite32_OR_R(129, 15, 61, Weapons5, Weapons5, lplane, dplane);
		  
		  //draws the inverted square for the selected weapon..
		  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
		  ScrRectFill(&(SCR_RECT){{2+12*WX, 16+12*WY, 2+12*WX+10, 16+12*WY+10}}, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
		  GrayDBufSetHiddenAMSPlane(DARK_PLANE);
		  ScrRectFill(&(SCR_RECT){{2+12*WX, 16+12*WY, 2+12*WX+10, 16+12*WY+10}}, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
		  
		  //draws the weapon title
		  static const char Weaponz[5][14][20]={
			{"Jet Pack", "Bazooka", "Grenade", "Shot Gun", "Fire Punch", "Dynamite", "Air Strike", "Blow Torch", "Ninja Rope", "Super Banana Bomb", "Petrol Bomb", "Mad Cow Herd", "Skip Turn"},
			{"Low Gravity", "Homing Missle", "Cluster Bomb", "Hand Gun", "Dragon Ball", "Mine", "Napalm Strike", "Drill", "Bungee", "Holy Grenade", "Skunk", "Old Lady", "Surrender"},
			{"Fast Walk", "Mortar", "Banana Bomb", "Uzi", "Kamakazee", "Sheep", "Mail Strike", "Girder", "Parachute", "Flame Thower", "Ming Vase", "Concrete Donkey", "Change Worm"},
			{"Laser Sight", "Homing Pigeon", "Battle Axe", "Minigun", "Suicide Bomb", "Super Sheep", "Mine Strike", "Baseball Bat", "Teleport", "Sal Army", "Sheep Strike", "Nucular Test", "Freeze Worms"},
			{"Invisibility", "Sheep Launcher", "Earthquake", "Bow & Arrow", "Prod", "Mole", "Mole Strike", "Girder Starter Pack", "Scales Of Justice", "MB Bomb", "Carpet Bomb", "Armageddon", "Magic Bullet"}};
	    
	    char Count[8];
	    sprintf(Count, "%d", WeaponSet[WY][WX]);
	    if(WeaponSet[WY][WX]==9)
	      {
	      	Count[0]=(char)190;
	      	Count[1]=(char)0;
	      }
	    
	    drawtxt(27,77,Weaponz[WY][WX],0);
	    drawtxt(27,85,"Stock Per Round:",0);
	    drawtxt(123,85,Count,0);
	    drawtxt(27,93,"+/- Changes Stock",0);
	    
	    //makes weapons light gray if they are set to 0
	    GrayDBufSetHiddenAMSPlane(DARK_PLANE);
	    for(y=0;y<5;y++)
	      for(x=0;x<14;x++)
	        {
		  			if(WeaponSet[y][x]==0) ScrRectFill(&(SCR_RECT){{2+12*x, 16+12*y, 2+12*x+10, 16+12*y+10}}, &(SCR_RECT){{0, 0, 159, 99}}, A_REVERSE);
	        }//next x
	    
	    //draws instructions
	  }//end if weapons
	else if(screen==options)
	  {
	  	drawokx();
			FontSetSys(2);
			drawtxt(28,3,"GAME OPTIONS:",2);
			drawtxt(29,4,"GAME OPTIONS:",0);
			drawtxt(30,5,"GAME OPTIONS:",1);
			FontSetSys(0);
			
			//draws the frams to hold the options in
			GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
			DrawLine(29,19,130,19,A_NORMAL);
			DrawLine(29,42,130,42,A_NORMAL);
			DrawLine(28,20,28,41,A_NORMAL);
			DrawLine(131,20,131,41,A_NORMAL);
		  drawtxt(52,16,"General Options: ",0);
		  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
			DrawLine(5,51,86,51,A_NORMAL);
			DrawLine(5,74,86,74,A_NORMAL);
			DrawLine(4,52,4,73,A_NORMAL);
			DrawLine(87,52,87,73,A_NORMAL);
			drawtxt(19,48,"Object Options: ",0);
			GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
			DrawLine(93,51,154,51,A_NORMAL);
			DrawLine(93,74,154,74,A_NORMAL);
			DrawLine(92,52,92,73,A_NORMAL);
			DrawLine(155,52,155,73,A_NORMAL);
			drawtxt(99,48,"Crate Options: ",0);
			
			//draws the boxes for the options:
			GrayDBufSetHiddenAMSPlane(DARK_PLANE);
			DrawClipRect(&(WIN_RECT){31,24,48,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){51,24,68,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){71,24,88,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){91,24,108,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){111,24,128,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){7,56,24,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){27,56,44,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){47,56,64,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){67,56,84,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){95,56,112,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){115,56,132,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			DrawClipRect(&(WIN_RECT){135,56,152,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			
			//draws the selected box black and the caption text
			FontSetSys(1);
			GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
			if(sel==1) 
				{
					DrawClipRect(&(WIN_RECT){31,24,48,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(34,85,"Starting Health",0);
				}
			else if(sel==2) 
				{
					DrawClipRect(&(WIN_RECT){51,24,68,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(28,85,"Worms Selectable?",0);
				}
			else if(sel==3) 
				{
					DrawClipRect(&(WIN_RECT){71,24,88,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(42,85,"Place Worms?",0);
				}
			else if(sel==4) 
				{
					DrawClipRect(&(WIN_RECT){91,24,108,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(50,85,"Turn Time",0);
				}
			else if(sel==5) 
				{
					DrawClipRect(&(WIN_RECT){111,24,128,39}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(40,85,"Artilery Mode",0);
				}
			else if(sel==6) 
				{
					DrawClipRect(&(WIN_RECT){7,56,24,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(31,85,"Play With Mines?",0);
				}
			else if(sel==7) 
				{
					DrawClipRect(&(WIN_RECT){27,56,44,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(31,85,"Mine Fuse Length",0);
				}
			else if(sel==8) 
				{
					DrawClipRect(&(WIN_RECT){47,56,64,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(49,85,"Dud Mines?",0);
				}
			else if(sel==9) 
				{
					DrawClipRect(&(WIN_RECT){67,56,84,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(52,82,"Play With",0);
					drawtxt(45,91,"Oil Barrols?",0);
				}
			else if(sel==10) 
				{
					DrawClipRect(&(WIN_RECT){95,56,112,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(42,85,"Tool Crates?",0);
				}
			else if(sel==11) 
				{
					DrawClipRect(&(WIN_RECT){115,56,132,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
					drawtxt(38,85,"Health Crates?",0);
				}
			else if(sel>11)
			  {
			  	DrawClipRect(&(WIN_RECT){135,56,152,71}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			  	drawtxt(38,85,"Weapon Crates?",0);
			  	sel=12;
			  }
			
			//draws what has been selected
			//HEALTH SETTINGS
			if(Opt[0]==0)
			  {
			  	GrayClipSprite16_OR_R(32, 25, 14, Health50, Health50, lplane, dplane);
			  }
			else if(Opt[0]==1)
			  {
			  	GrayClipSprite16_OR_R(32, 25, 14, Health100, Health100, lplane, dplane);
			  }
			else if(Opt[0]==2)
			  {
			  	GrayClipSprite16_OR_R(32, 25, 14, Health200, Health200, lplane, dplane);
			  }
			//SELCTION SETTINGS
			if(Opt[1]==0)
			  {
			  	GrayClipSprite16_OR_R(52, 25, 14, SelSel, SelSel, lplane, dplane);
			  }
			else if(Opt[1]==1)
			  {
			  	GrayClipSprite16_OR_R(52, 25, 14, SelStat, SelStat, lplane, dplane);
			  }
			//PlACE SETTINGS
			if(Opt[2]==0)
			  {
			  	GrayClipSprite16_OR_R(72, 25, 13, PlaceYes, PlaceYes, lplane, dplane);
			  }
			else if(Opt[2]==1)
			  {
			  	GrayClipSprite16_OR_R(72, 25, 13, PlaceNo, PlaceNo, lplane, dplane);
			  }
			//TIME SETTINGS 
			if(Opt[3]==0)
			  {
			  	GrayClipSprite16_OR_R(92, 25, 14, Time30, Time30, lplane, dplane);
			  }
			else if(Opt[3]==1)
			  {
			  	GrayClipSprite16_OR_R(92, 25, 14, Time60, Time60, lplane, dplane);
			  }
			else if(Opt[3]==2)
			  {
			  	GrayClipSprite16_OR_R(92, 25, 14, Time90, Time90, lplane, dplane);
			  }
			//ALTERY MODE SETTINGS
			if(Opt[4]==0)
				{
					GrayClipSprite16_OR_R(112, 25, 13, ArtileryNo, ArtileryNo, lplane, dplane);
				}
			else if(Opt[4]==1)
				{
					GrayClipSprite16_OR_R(112, 25, 13, ArtileryYes, ArtileryYes, lplane, dplane);
				}
			//MINE SETTINGS
			if(Opt[5]==0)
			  {
			  	GrayClipSprite16_OR_R(8, 57, 9, MinesYes, MinesYes, lplane, dplane);
			  }
			else if(Opt[5]==1)
			  {
			  	GrayClipSprite16_OR_R(8, 57, 13, MinesNo, MinesNo, lplane, dplane);
			  }
			//MINE FUSE SETTINGS
			if(Opt[6]==0)
			  {
			  	GrayClipSprite16_OR_R(28, 57, 13, MineRnd, MineRnd, lplane, dplane);
			  }
			else if(Opt[6]==1)
			  {
			  	GrayClipSprite16_OR_R(28, 57, 13, Mine0, Mine0, lplane, dplane);
			  }
			else if(Opt[6]==2)
			  {
			  	GrayClipSprite16_OR_R(28, 57, 13, Mine1, Mine1, lplane, dplane);
			  }
			else if(Opt[6]==3)
			  {
			  	GrayClipSprite16_OR_R(28, 57, 13, Mine2, Mine2, lplane, dplane);
			  }
			else if(Opt[6]==4)
			  {
			  	GrayClipSprite16_OR_R(28, 57, 13, Mine3, Mine3, lplane, dplane);
			  }
			//MINE SETTINGS
			if(Opt[7]==0)
			  {
			  	GrayClipSprite16_OR_R(48, 57, 13, DudMineYes, DudMineYes, lplane, dplane);
			  }
			else if(Opt[7]==1)
			  {
			  	GrayClipSprite16_OR_R(48, 57, 13, DudMineNo, DudMineNo, lplane, dplane);
			  }
			//BARROL SETTINGS
			if(Opt[8]==0)
			  {
			  	GrayClipSprite16_OR_R(68, 57, 12, BarrolsYes, BarrolsYes, lplane, dplane);
			  }
			else if(Opt[8]==1)
			  {
			  	GrayClipSprite16_OR_R(68, 57, 13, BarrolsNo, BarrolsNo, lplane, dplane);
			  }
			//TOOL SETTINGS
			if(Opt[9]==0)
			  {
			  	GrayClipSprite16_OR_R(96, 57, 12, ToolYes, ToolYes, lplane, dplane);
			  }
			else if(Opt[9]==1)
			  {
			  	GrayClipSprite16_OR_R(96, 57, 13, ToolNo, ToolNo, lplane, dplane);
			  }
			//HEALTH SETTINGS
			if(Opt[10]==0)
			  {
			  	GrayClipSprite16_OR_R(116, 57, 12, HealthYes, HealthYes, lplane, dplane);
			  }
			else if(Opt[10]==1)
			  {
			  	GrayClipSprite16_OR_R(116, 57, 13, HealthNo, HealthNo, lplane, dplane);
			  }
			//CRATE SETTINGS
			if(Opt[11]==0)
			  {
			  	GrayClipSprite16_OR_R(136, 57, 13, CratesYes, CratesYes, lplane, dplane);
			  }
			else if(Opt[11]==1)
			  {
			  	GrayClipSprite16_OR_R(136, 57, 13, CratesNo, CratesNo, lplane, dplane);
			  }
			
			FontSetSys(1);
	  }//end if options
	
	//togle the gray buffers
	GrayDBufToggleSync();
  
  /* On HW1, the flip will be effective only after 1 or 2 plane switches
       depending on the phase. We must not draw to the "hidden" planes before
       they are really hidden! */
  if (!_GrayIsRealHW2()) GrayWaitNSwitches(2);
}

//DRAWS THE CLOSE \ CHECK BUTTONS
void drawokx()
{
  void * lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void * dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
  //close button
	GrayClipSprite32_OR_R(5, 80, 18, BttnClose, BttnClose, lplane, dplane);
	ClipSprite32_OR_R(6, 81, 18, BttnClose, lplane);
	ClipSprite32_OR_R(6, 81, 18, BttnCloseI, lplane);
	
	
	//ok button
	GrayClipSprite32_OR_R(135, 78, 20, BttnOk, BttnOk, lplane, dplane);
	ClipSprite32_OR_R(136, 79, 20, BttnOk, lplane);
	ClipSprite32_OR_R(136, 79, 20, BttnOkI, lplane);
}

//DRAWS A TEXT BOX
void drawtxtbox(int x, int y, int width, const char *str, short col)
{
  if(col==0 || col==1)
    {
    	GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
    	DrawLine(x,y,x+width,y,1);
			DrawLine(x,y+10,x+width,y+10,1);
			DrawLine(x,y,x,y+10,1);
			DrawLine(x+width,y,x+width,y+10,1);
    	//GrayDBufSetHiddenAMSPlane(DARK_PLANE);
    }
  if(col==0 || col==2)
		{
			GrayDBufSetHiddenAMSPlane(DARK_PLANE);
			DrawLine(x,y,x+width,y,1);
			DrawLine(x,y+10,x+width,y+10,1);
			DrawLine(x,y,x,y+10,1);
			DrawLine(x+width,y,x+width,y+10,1);
		}
	FontSetSys(0);
	drawtxt(x+3,y+3,str,0);
	FontSetSys(1);
}//end sub

//DRAW DROP BOX
void drawdropbox(int x, int y, int width, const char *cap)
{
  char down[2]={20,0}; //makes a string with the down arrow
  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
	DrawLine(x,y,x+width,y,1);
	DrawLine(x,y+10,x+width,y+10,1);
	DrawLine(x,y,x,y+10,1);
	DrawLine(x+width,y,x+width,y+10,1);
	DrawLine(x+width-9,y,x+width-9,y+10,1);
	drawtxt(x+width-7,y+2,down,0);
	FontSetSys(0);
	drawtxt(x+2,y+3,cap,0);
	FontSetSys(1);
	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
}

//HANDLES ALL THE KEY PRESSES!
void KeyHandle()
{
	if(_keytest(RR_2ND)) //handles for every key press of second
	  {
	  	if(screen==gtronics)
				{
					screen=team17;
	  	  	while(_keytest(RR_2ND));
	  	  	return;
	  	  } //if gt screen, then change screen to team17
      else if(screen==team17)
				{
					screen=titus;
	  	  	while(_keytest(RR_2ND));
	  	  	return;
	  	  } //if gt screen, then change screen to team17
      else if(screen==titus)
				{
					screen=title;
	  	  	while(_keytest(RR_2ND));
	  	  	return;
	  	  } //if gt screen, then change screen to team17
	  	else if(screen==title)
				{
					screen=mainmenu;
	  	  	while(_keytest(RR_2ND));
	  	  	return;
	  	  } //if gt screen, then change screen to team17
	  }
	if(_keytest(RR_F1))
		{
		  while(_keytest(RR_F1)); //waits for keyip
		  
		  //acts according to each screen
			if(screen==mainmenu)
			  {
			  	MsgBox("Are You Sure You Want To Exit?","Exit?");
			  	exitexe=true;
			  }
			if(screen==teamsetup) screen=mainmenu;
			else if(screen==newteam) screen=teamsetup;
			else if(screen==editteam) screen=teamsetup;
			else if(screen==scheme) screen=mainmenu;
			else if(screen==setup) screen=mainmenu;
			else if(screen==weapons) screen=setup;
			else if(screen==mapedit) screen=setup;
			else if(screen==teams) screen=setup;
			else if(screen==options) screen=setup;
			sel=1;
		}
		
	//hangles keys for the weapons screen
  if(screen==weapons)
    {
    	if(_keytest(RR_LEFT))
    	  WX--;
    	if(_keytest(RR_RIGHT))
    	  WX++;
    	if(_keytest(RR_UP))
    	  WY--;
    	if(_keytest(RR_DOWN))
    	  WY++;
    	if(WX<0) WX=0;
    	if(WX>13) WX=13;
    	if(WY<0) WY=0;
    	if(WY>4) WY=4;
      
      if(_keytest(RR_PLUS))
        WeaponSet[WY][WX]++;
      if(_keytest(RR_MINUS))
        WeaponSet[WY][WX]--;
      
      if(WeaponSet[WY][WX]<0)
        WeaponSet[WY][WX]=0;
      if(WeaponSet[WY][WX]>9)
        WeaponSet[WY][WX]=9;
      
      while(_keytest(RR_LEFT) || _keytest(RR_RIGHT) || _keytest(RR_UP) || _keytest(RR_DOWN) || _keytest(RR_PLUS) || _keytest(RR_MINUS));
    
    	if(_keytest(RR_F5))
    		screen=setup;
    }//end if weapons
    
		
	//if(_keytest(RR_ESC)) //if person presses ESC, the game will exit
	//  exitexe=true;
	if(_keytest(RR_LEFT) || _keytest(RR_UP)) //if left is being pressed
	  {
	  	sel--;
	  	if(sel<1) sel=1;
	  	while(_keytest(RR_LEFT));
	  	while(_keytest(RR_UP));
	  }
	if(_keytest(RR_RIGHT) || _keytest(RR_DOWN)) //if right is being pressed
	  {
	  	sel++;
	  	while(_keytest(RR_RIGHT));
	  	while(_keytest(RR_DOWN));
	  }
  
  //handles keys for the options screen
  if(screen==options)
    {
    	if(_keytest(RR_MINUS))
    	  {
    	  	Opt[sel-1]--;
    	  	if(Opt[sel-1]<0)
    	  	  Opt[sel-1]=0;
    	  	  
    	  	//waits for key up
    	  	while(_keytest(RR_MINUS));
    	  }
    	if(_keytest(RR_PLUS) || _keytest(RR_ENTER) || _keytest(RR_2ND))
    	  {
    	  	Opt[sel-1]++;
    	  	if(sel==1 && Opt[sel-1]>2) Opt[sel-1]=0;
    	  	else if(sel==2 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==3 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==4 && Opt[sel-1]>2) Opt[sel-1]=0;
    	  	else if(sel==5 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==6 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==7 && Opt[sel-1]>4) Opt[sel-1]=0;
    	  	else if(sel==8 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==9 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==10 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==11 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	else if(sel==12 && Opt[sel-1]>1) Opt[sel-1]=0;
    	  	
    	  	//waits for key up
    	  	while(_keytest(RR_PLUS) || _keytest(RR_ENTER) || _keytest(RR_2ND));
    	  }
    	  
    	if(_keytest(RR_F5))
    		screen=setup;
    }
    
	//handles keys for the setup screen
	else if(screen==setup)
	  {
	  	if(sel==2)
	  	  {
	  	  	//Changes worms on team 1
	  	  	if(_keytest(RR_PLUS))
	  	  	  if(Worms1+1<9) Worms1++;
	  	  	if(_keytest(RR_MINUS))
	  	  	  if(Worms1-1>0) Worms1--;
	  	  	while(_keytest(RR_PLUS) || _keytest(RR_MINUS));
	  	  }//end if sel 2
	  	else if(sel==3)
	  	  {
	  	  	//Changes worms on team 1
	  	  	if(_keytest(RR_PLUS))
	  	  	  if(Worms2+1<9) Worms2++;
	  	  	if(_keytest(RR_MINUS))
	  	  	  if(Worms2-1>0) Worms2--;
	  	  	while(_keytest(RR_PLUS) || _keytest(RR_MINUS));
	  	  }//end if sel 2	    
	  	 
	  	 if(_keytest(RR_2ND) || _keytest(RR_ENTER))
	  	   {
	  	   	  while((_keytest(RR_2ND) || _keytest(RR_ENTER)));
	  	   	  
	  	   	  //acts upon selection
	  	   	  short PopResult;
	  	   	  if(sel==1)
	  	   	    {
	  	   	    	PopResult=DoPopUp(15,23,"Rndm Map\0Default \0Dots    \0Hills   \0",4);
	  	   	    	if(PopResult==0)
	  	   	    	  strcpy(map,"Rndm Map");
	  	   	    	else if(PopResult==1)
	  	   	    	  strcpy(map,"Default");
	  	   	    	else if(PopResult==2)
	  	   	    	  strcpy(map,"Dots");
	  	   	    	else if(PopResult==3)
	  	   	    	  strcpy(map,"Hills");
	  	   	    	else if(PopResult>3)
	  	   	    	  strcpy(map,&maps[PopResult-3]);
	  	   	    }
	  	   	  else if(sel==2)
	  	   	    {
	  	   	    	//PopResult=DoPopUp(15,44,"This    \0Isn't   \0Done    \0Yet     \0", 4);
	  	   	    	GetTeams(15,44);
	  	   	    	strcpy(team1,names[0]);
	  	   	    }
	  	   	  else if(sel==3)
	  	   	    {
	  	   	    	//PopResult=DoPopUp(15,59,"This    \0Isn't   \0Done    \0Yet     \0", 4);
	  	   	    	GetTeams(15,59);
	  	   	    	strcpy(team2,names[0]);
	  	   	    }
	  	   	  else if(sel==4)
	  	   	    {
	  	   	    	screen=weapons;
	  	   	    	WX=0;
	  	   	    	WY=0;
	  	   	    }
	  	   	    
	  	   	  else if(sel==5)
	  	   	    {
	  	   	    	screen=options;
	  	   	    	sel=1;
	  	   	    }
	  	   }
	  	   
				if(_keytest(RR_F5))
    			StartGame();
	  }//end if setup
	  
	//handles keys for the main screen..
	else if(screen==mainmenu)
	  {
	  	if(_keytest(RR_F5) || _keytest(RR_2ND))
	  	  {
	  	  	while(_keytest(RR_F5) || _keytest(RR_2ND));
	  	  	
	  	  	if(sel==1) screen=setup;
	  	  	else if(sel==2) screen=teamsetup;
	  	  	else if(sel==3) screen=scheme;
	  	  	
	  	  	sel=1;
	  	  }
	  }//end if main menu
	
	//handles keys for the team setup screen..
	else if(screen==teamsetup)
	  {
	  	if(_keytest(RR_F5) || _keytest(RR_2ND))
	  	  {
	  	  	while(_keytest(RR_F5) || _keytest(RR_2ND));
	  	  	
	  	  	if(sel==1) screen=newteam;
	  	  	else if(sel==2)
	  	  	  {
	  	  	  	screen=editteam;
	  	  	  	strcpy(names[0],"<Name>");
	  	  	  	names[1][0]=0;names[2][0]=0;names[3][0]=0;names[4][0]=0;names[5][0]=0;
	  	  	  	names[6][0]=0;names[7][0]=0;names[8][0]=0;names[9][0]=0;
	  	  	  	//GetTeams();
	  	  	  	sel=1;
	  	  	  }
	  	  }
	  }//end if team setup
	  
	//handles keys for the new team screen..
	else if(screen==newteam || screen==editteam)
	  {
	  	if(_keytest(RR_F5))
	  	  {
	  	  	while(_keytest(RR_F5));
	  	  	SaveTeam(); //saves the team to a file
	  	  }
	  	if(sel>0 && sel<10 && (_keytest(RR_ENTER) || _keytest(RR_2ND)))
	  	  {
	  	  	if(sel==1 && screen==editteam)
	  	  	  {
	  	  	  	GetTeams(6,28); //lets the user choose a team
	  	  	  	if(CheckAr("teams", names[0]) == true) //makes sure the team selected isnt locked or archived
	  	  	  		{
	  	  	  			MsgBox("Error: Team Locked Or Archived","File Access Error");
	  	  	  			strcpy(names[0],"<Name>");
	  	  	  			ClrNames();
	  	  	  			return;
	  	  	  		}
	  	  	  	//time to load the team
  						LoadTeam(names[0]);
	  	  	  }
	  	  	if(sel==1 && screen==newteam) InputStr(7+1,29+2,names[sel-1],8);
	  	  	if(sel>1 && !strcmp(names[0],"<Name>")  && screen==editteam) sel=1;
			    if(sel==2) InputStr(71+1,29+2,names[sel-1],8);
			    else if(sel==3) InputStr(71+1,39+2,names[sel-1],8);
			    else if(sel==4) InputStr(71+1,49+2,names[sel-1],8);
			    else if(sel==5) InputStr(71+1,59+2,names[sel-1],8);
			    else if(sel==6) InputStr(111+1,29+2,names[sel-1],8);
			    else if(sel==7) InputStr(111+1,39+2,names[sel-1],8);
			    else if(sel==8) InputStr(111+1,49+2,names[sel-1],8);
			    else if(sel==9) InputStr(111+1,59+2,names[sel-1],8);
				}//end if sel edit
			if(sel>9)
			  {
			  	sel=10;
			  	if(_keytest(RR_ENTER) || _keytest(RR_2ND))
			  	  {
			  	  	short PopResult;
			  	  	PopResult=DoPopUp(6,48,"Pyrimid \0Cross   \0Worm    \0Stone   \0Rope    \0Skull   \0", 6);
			  	  	if(PopResult==0)
			  	  		strcpy(names[9],"Pyrimid");
			  	  	else if(PopResult==1)
			  	  		strcpy(names[9],"Cross");
			  	  	else if(PopResult==2)
			  	  		strcpy(names[9],"Worm");
			  	  	else if(PopResult==3)
			  	  		strcpy(names[9],"Stone");
			  	  	else if(PopResult==4)
			  	  		strcpy(names[9],"Rope");
			  	  	else if(PopResult==5)
			  	  		strcpy(names[9],"Skull");
			  	  }
			  }	
	  }//end if new team
	  
	//handles keys for the edit team screen..
	if(screen==editteam)
	  {
			//stuff
	  }//end if edit team
	  
}//end sub

//THIS SUB DRAWS TEXT AT POINT X, Y, WITH STRING STR, IN COLOR COL, 0=BLACK, 1=DARK GRAY, 2=LIGHT GRAY
void drawtxt(int x, int y, const char *str, short col)
{
	if(col==2 || col==0)
	  {
	  	GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
	  	printf_xy(x,y,str);
	  	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
	  }//end if
	if(col==1 || col==0)
		{
			GrayDBufSetHiddenAMSPlane(DARK_PLANE);
			printf_xy(x,y,str);
		}//end if
}//end sub

// Custom String Input Function
void InputStr(int x, int y, char *buffer, unsigned short maxlen)
{
  //kills grayscale (needed for kill interupts)
  GGrayOff();
  //kills interuprs
  SetIntVec(AUTO_INT_1, save_1a); 
	SetIntVec(AUTO_INT_5, save_5a); 
	//makes font small
	FontSetSys(0);
	
  MoveTo (x-1, y);
  SCR_STATE ss;
  short key;
  unsigned short i = 0;
  buffer[0] = 0;

  SaveScrState (&ss);
  do
    {
      MoveTo (ss.CurX, ss.CurY);
      printf ("%s_  ", buffer);
        // Note that two spaces are required only if the F_4x6 font is used
      key = ngetchx ();
      if (key >= ' ' && key <= '~' && i < maxlen)
        buffer[i++] = key;
      else if (key == KEY_BACKSPACE && i)
        i--;
      buffer[i] = 0;
    } while (key != KEY_ENTER);
  
  //waits for key enter to stop being pressed
  while(_keytest(RR_ENTER));
  
  //restores grayscale \ font \ interuprs
  SetIntVec(AUTO_INT_1, DUMMY_HANDLER); 
	SetIntVec(AUTO_INT_5, DUMMY_HANDLER);
	GGrayOn();
	FontSetSys(1);
} //end sub


//DISPLAYS A REALLY COOL MESSAGE BOX
void MsgBox(const char *msg, const char *cap)
{
  //draws the msg box
	GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
	ScrRectFill(&(SCR_RECT){{20,20,136,80}}, &(SCR_RECT){{0, 0, 159, 99}}, A_REVERSE);
	//ScrRectFill(&(SCR_RECT){{20,20,136,32}}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
	DrawClipRect(&(WIN_RECT){20,20,136,32}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
	DrawClipRect(&(WIN_RECT){20,20,136,80}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
	//ScrRectFill(&(SCR_RECT){{68,60,88,75}}, &(SCR_RECT){{0, 0, 159, 99}}, A_REVERSE);
	DrawClipRect(&(WIN_RECT){68,60,88,73}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);

  
	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
	ScrRectFill(&(SCR_RECT){{20,20,136,80}}, &(SCR_RECT){{0, 0, 159, 99}}, A_REVERSE);
	DrawClipRect(&(WIN_RECT){20,20,136,32}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
	DrawClipRect(&(WIN_RECT){20,20,136,80}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
	DrawClipRect(&(WIN_RECT){68,60,88,73}, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
  
  //draw the text on the msg box
	drawtxt(23,23,cap,0);
  FontSetSys(0);
  drawtxt(23,36,msg,0);
  FontSetSys(1);
  drawtxt(71,63,"Ok",0);
  
	//updates the screen
	GrayDBufToggleSync();
  if (!_GrayIsRealHW2()) GrayWaitNSwitches(2);
  
  //waits for key press
  while(!_keytest(RR_ENTER) && !_keytest(RR_2ND));
  //waits for key up
  while(_keytest(RR_ENTER) || _keytest(RR_2ND));
}


//SAVES THE TEAM DATA ENTERED IN THE NAMES STRINGS TO A FILE!
void SaveTeam()
{
  short x, length, pos;
  char msg[33],filename[15];
	//first it must check to see if all the names are vaild
	if(names[0][0]==0)
	  {
	    MsgBox("Please Type A Team Name.", "Error:");
	    return;	
	  }
	for(x=1;x<9;x++)
	  if(names[x][0]==0)
		  {
		    MsgBox("Please Type All Names.", "Error:");
		    return;	
		  }
		  
	//checks if a grave has been selected
	if(names[9][0]==0)
		{
	    MsgBox("Please Choose A Grave.", "Error:");
	    return;	
	  }
  //names[9][0]='f';
  //strcpy(names[9],"Pyramid");
  
	//counts how big the save will be.
	length=10+strlen(names[0])+strlen(names[1])+strlen(names[2])+strlen(names[3])+strlen(names[4])+
	        strlen(names[5])+strlen(names[6])+strlen(names[7])+strlen(names[8])+strlen(names[9])+3;
	
	//sets up the data
	strcpy(filename,"teams\\");
	strcat(filename,names[0]);
	
	//makes sure the folder exists to prevent crash
	if(FolderFind(SYMSTR("teams"))==NOT_FOUND) //if it cant find it...
		FolderAdd (SYMSTR("teams")); //it makes it
	
	//it checks to see if that file already exists, if it does, it errors and exits
	HSym hsym2=SymFind(SYMSTR(filename));
	if(hsym2.folder!=0 && screen!=editteam)
		{
			MsgBox("That Team Alredy Exists!", "Error: Rename Team");
			sel=1;
			//drawtxtbox(6,28,60,"",0);
			//InputStr(7+1,29+2,names[sel-1],8);
			return;
		}
		 
	//creats teh file
	HSym hsym = SymAdd (SYMSTR(filename));
	// HeapAlloc must be executed before DerefSym
	// because of possible garbage collection.
	HANDLE handle = HeapAlloc (100);
	SYM_ENTRY *SymPtr = (DerefSym (hsym));
  MULTI_EXPR *VarPtr = HeapDeref (SymPtr->handle = handle);
  
  // FIXME STR variables containing 0x00 do not transfer correctly using TI-Connect nowadays (TILP is fine) => Worms89 should switch to OTH files, like many other games.
  pos=1;
  VarPtr->Size = length;
  VarPtr->Expr[0] = 0;         // zero marks the beginning of the actual variable data
  
  //saves the data
  for(x=0;x<10;x++)
    {
    	memcpy(&VarPtr->Expr[pos], names[x], strlen(names[x]));
    	pos+=strlen(names[x]);
    	VarPtr->Expr[pos]=';';
    	pos++;
    }
  
  //end the data
  VarPtr->Expr[length-2] = 0;         // end-of-string marker
	VarPtr->Expr[length-1] = STR_TAG;   // the last byte is the type (see STR_TAG)
	
	if(screen==newteam)
	  {
	  	//HeapFree(handle);
			strcpy(msg,"Team: ");
			strcat(msg, names[0]);
			strcat(msg, " Has Been Saved!");
			MsgBox(msg,"Team Saved:");
	  }else
	  {
			strcpy(msg,"Team: ");
			strcat(msg, names[0]);
			strcat(msg, " Has Been Updated!");
			MsgBox(msg,"Changes Saved:");
	  }

	
	//clears all the values in the text boxes
	names[0][0]=0;
	names[1][0]=0;
	names[2][0]=0;
	names[3][0]=0;
	names[4][0]=0;
	names[5][0]=0;
	names[6][0]=0;
	names[7][0]=0;
	names[8][0]=0;
	names[9][0]=0;
} //end sub

//THIS SUB GETS AND SAVES A LIST OF ALL THE TEAMS ON THE CALCULATOR
void GetTeams(short boxx, short boxy)
{
  //first makes sure there are teams...
  //checks to see if the teams folder is there
  short FoldCount = FolderCount (DerefSym (SymFindHome (SYMSTR ("teams"))));
  
	if(FolderFind(SYMSTR("teams"))==NOT_FOUND) //if it cant find it...
	  {
	  	MsgBox("You Have No Teams To Edit!", "Error: No Teams!");
	    return;
	  }
	//now that we know the folder is there, it checks to see if it has files in it
	if(FoldCount==0)
	  {
	  	MsgBox("You Have No Teams To Edit!", "Error: No Teams!");
	    return;
	  }
	
	//we now know that the calc DOES have teams saved, now we must load them.
	//we need to hold enought space for them
	char *Teams=malloc(sizeof(char)*9*FoldCount);
	//DoPopUp(6,28,"greg    \0miller  \0is hella\0cool    \0and he  \0likes to\0fuck hot\0girls in\0their   \0vaginas \0", 10);
	
	//now well fill out new array teams with the folder names
	short counter = 0;
	SYM_ENTRY *SymPtr = SymFindFirst(SYMSTR ("teams"), FO_SINGLE_FOLDER);
	
	while (SymPtr)
		{
		  strcpy(&Teams[counter], SymPtr->name);
		  Teams[counter+8]=0;
		  counter+=9;
		  SymPtr = SymFindNext();
		}//loops until all files are filled into the array
  
  //it makes a variable for which item was selected
  short index;
  //since this code is called for the pop up, it calls a pop up
  index=DoPopUp(boxx,boxy,Teams, FoldCount);
  
  //selects the name
  strcpy(names[0],&Teams[index*9]);
  
  //frees the memory for the teams list
  free(Teams);
}

short DoPopUp(short x, short y, const char *ListData, short MaxList)
{
  short pos=0, datapos=0;
	char down[2]={20,0}; //makes a string with the down arrow
	char up[2]={19,0}; //makes a string with the up arrow
			
  //waits until using let up on the ket
  while(_keytest(RR_ENTER) || _keytest(RR_2ND) || _keytest(RR_ESC));
  
  //loops until the key is pressed again
  while(!_keytest(RR_ENTER) && !_keytest(RR_2ND) && !_keytest(RR_ESC))
    {
    	if(_keytest(RR_DOWN))
    	  {
    	  	//moves the position in teh list up (down)
    	  	pos++;
    	  	if(pos>3) //the list only shows four positions
    	  	  {
    	  	  	pos=3; //so it keeps it at the bottom, and
    	  	  	datapos++; //instead scrolls the list iteself, which
    	  	  	if(datapos>MaxList-4) datapos=MaxList-4; //maxes out 4 before the end
    	  	  }
    	  	while(_keytest(RR_DOWN));
    	  }//end if key down
    	if(_keytest(RR_UP))
    	  {
    	  	//moves the postion in teh list down (up)
    	  	pos--;
    	  	if(pos<0) //the list shows 4 opositions, 0 is the top
    	  	  {
    	  	  	pos=0; //so it keeps it at the top, and
    	  	  	datapos--; //instead scrolls the list itself, which
    	  	  	if(datapos<0) datapos=0; //starts at 0
    	  	  }
    	  	while(_keytest(RR_UP));
    	  }//end if key up
    	  

    	
    	//first it draws the pop up box
			GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
			ScrRectFill(&(SCR_RECT){{x,y,x+60,y+40}}, &(SCR_RECT){{0, 0, 159, 99}}, A_REVERSE);
			DrawLine(x,y,x+60,y,1);
			DrawLine(x,y+40,x+60,y+40,1);
			DrawLine(x+60,y,x+60,y+40,1);
			DrawLine(x+51,y,x+51,y+40,1);
			
			drawtxtbox(x,y,60,"",0);
			drawtxtbox(x,y+10,51,"",0);
			drawtxtbox(x,y+20,51,"",0);
			drawtxtbox(x,y+30,60,"",0);
			
			GrayDBufSetHiddenAMSPlane(DARK_PLANE);
			ScrRectFill(&(SCR_RECT){{x,y,x+60,y+40}}, &(SCR_RECT){{0, 0, 159, 99}}, A_REVERSE);
			DrawLine(x,y,x+60,y,1);
			DrawLine(x,y+40,x+60,y+40,1);
			DrawLine(x+60,y,x+60,y+40,1);
			DrawLine(x+51,y,x+51,y+40,1);
			
			drawtxtbox(x,y,60,"",0);
			drawtxtbox(x,y+10,51,"",0);
			drawtxtbox(x,y+20,51,"",0);
			drawtxtbox(x,y+30,60,"",0);
						
			drawtxt(x+60-7,y+2,up,0);
			drawtxt(x+60-7,y+32,down,0);
			

		  FontSetSys(0);
		  if(MaxList>=1) drawtxt(x+2,y+3,&ListData[datapos*9],0);
		  if(MaxList>=2) drawtxt(x+2,y+13,&ListData[datapos*9+9],0);
		  if(MaxList>=3) drawtxt(x+2,y+23,&ListData[datapos*9+18],0);
		  if(MaxList>=4) drawtxt(x+2,y+33,&ListData[datapos*9+27],0);
		  FontSetSys(1);
		  
		  
		  //draws the selection box
		  ScrRectFill(&(SCR_RECT){{x+1,y+(pos*10)+1,x+50,y+(pos*10)+9}}, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
		  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
		  ScrRectFill(&(SCR_RECT){{x+1,y+(pos*10)+1,x+50,y+(pos*10)+9}}, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
		  
    	GrayDBufToggleSync();
  		if (!_GrayIsRealHW2()) GrayWaitNSwitches(2);
  		
    }//loop while user chooses thing
    
	//wait for key up
  while(_keytest(RR_ENTER) || _keytest(RR_2ND) || _keytest(RR_ESC));
  
  //returns what was selected
  return (datapos + pos);
}

//this sub resets the loaded team, if its archived or locked
short CheckAr(const char *fold, const char *str)
{
  char dir[20];
  strcpy(dir,fold);
  strcat(dir,"\\");
  strcat(dir,str);
  
	SYM_ENTRY * ptr = SymFindPtr(SYMSTR(dir),0);
	if(ptr->flags.bits.locked==1 || ptr->flags.bits.archived==1)
	  	return true;
	  else
    	return false;
}

//clears teh names
void ClrNames()
{
	//names[0][0]=0;
	names[1][0]=0;
	names[2][0]=0;
	names[3][0]=0;
	names[4][0]=0;
	names[5][0]=0;
	names[6][0]=0;
	names[7][0]=0;
	names[8][0]=0;
	names[9][0]=0;
  strcpy(names[0],"<Name>");
}

//LOADS THE TEAM NAMES INTO THEIR STRINGS FROM A FILE
void LoadTeam()
{
  char dir[20];
  short x=0,z;
  strcpy(dir,"teams");
  strcat(dir,"\\");
  strcat(dir,names[0]);
  
  //grabs the pointer to the file
	SYM_ENTRY *SymThing = SymFindPtr(SYMSTR(dir),0);
	char *TPtr= HeapDeref(SymThing->handle);
	
	//scans until a null is found (beging of file)
	while(TPtr[x]!=0) x++;
	
	//finds the first semi colon
	while(TPtr[x]!=';') x++;
	x++;
	
	//loops to get all the variables
	for(z=1;z<10;z++)
	  {
	  	names[z][0]=0;
	  	while(TPtr[x]!=';')
	  	  {
	  	  	//strcat(names[z],&TPtr[x]);
	  	  	dir[0]=TPtr[x];
	  	    dir[1]=0;
	  	  	strcat(names[z],dir);
	  	  	x++;
	  	  }
	  	x++;
	  	//MsgBox("Test","Test");
	  }//next z
}





//THIS SUB IS STARTS UP THE GAME PART OF IT
void StartGame()
{
	//saves the settings...
	SaveSettings();
	
	//exits the exe so the launcher takes you to the game
	exitexe=true;
}


//THIS SUB SAVES THE GAMES CURRENT SETTINGS SO THE GAME CAN LOAD THEM...
//SOME STUFF
void SaveSettings()
{
	short x, length, pos;
  char filename[15];
	//first it must check to see if the needed information is correct...
	if(strcmp(map,"<Map>   ")==0)
	  {
	    MsgBox("Please Choose A Map", "Error:");
	    return;	
	  }
  if(strcmp(team1,"<Name>  ")==0 || strcmp(team2,"<Name>  ")==0)
	  {
	    MsgBox("Please Choose Both Teams", "Error:");
	    return;	
	  }
	
	//the length to save should be 109...
			//70 Weapons
			//12 Options
			//24 Charectars for teams and maps (8 chars per team and map) (8*3) = 24
			//2 For the number of worms on each team...
			//3 for File Header and such
			//Total 111...
	length=111;
	
	//sets up the data name
	strcpy(filename,"wwpini");

		 
	//creats teh file
	HSym hsym = SymAdd (SYMSTR(filename));
	// HeapAlloc must be executed before DerefSym
	// because of possible garbage collection.
	HANDLE handle = HeapAlloc (120);
	SYM_ENTRY *SymPtr = (DerefSym (hsym));
  MULTI_EXPR *VarPtr = HeapDeref (SymPtr->handle = handle);
  
  
  pos=0;
  VarPtr->Size = length;
  VarPtr->Expr[0] = 0;         // zero marks the beginning of the actual variable data
  
  // FIXME this is unoptimized code.
  // FIXME STR variables containing 0x00 do not transfer correctly using TI-Connect nowadays (TILP is fine) => Worms89 should switch to OTH files, like many other games.
  //saves the weapon data
  for(x=0;x<70;x++)
    {
    	//ups the write pos
    	pos++;
    	//saves the number of weapon x
    	memcpy(&VarPtr->Expr[pos], &WeaponSet[0][x], sizeof(short));
    }
  
  //saves options
  for(x=0;x<12;x++)
  {
  	//ups the write pos
  	pos++;
  	//saves the option setting
    memcpy(&VarPtr->Expr[pos], &Opt[x], sizeof(short));
  }
  
  //now it must save the teams 1,2, and the map chosen
  //team 1...
  pos++;
  memcpy(&VarPtr->Expr[pos], team1, strlen(team1));
  pos+=8;
  //team 2...
  pos++;
  memcpy(&VarPtr->Expr[pos], team2, strlen(team1));
  pos+=8;
  //team 3...
  pos++;
  memcpy(&VarPtr->Expr[pos], map, strlen(team1));
  pos+=9;
  
  //save the number of worms on each team..
  VarPtr->Expr[pos] = Worms1;
  VarPtr->Expr[pos+1] = Worms2;
  
  //end the data
  VarPtr->Expr[length-2] = 0;         // end-of-string marker
	VarPtr->Expr[length-1] = STR_TAG;   // the last byte is the type (see STR_TAG)
}
