// C Source File
// Created 1/4/2004; 8:46:00 PM

#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

// #define OPTIMIZE_ROM_CALLS // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files
#include "extgraph.h"

//SPRITES FROM DLL!!
#define ArrowLeft _DLL_reference (unsigned char, 125)
#define ArrowRight _DLL_reference (unsigned char, 126)

//LOADS STUFF FROM DLL!!
//LOADS VARIABLS~!~!~!~!~!~!~!~!~!~!~!!!!!!
#define white_x _DLL_reference (short, 127)
#define white_y _DLL_reference (short, 128)
#define white_h _DLL_reference (short, 129)
#define white_dir _DLL_reference (short, 130)
#define white_w _DLL_glbvar (short, 131)
#define white_weap _DLL_glbvar (short, 132)
#define black_x _DLL_reference (short, 133)
#define black_y _DLL_reference (short, 134)
#define black_h _DLL_reference (short, 135)
#define black_dir _DLL_reference (short, 136)
#define black_w _DLL_glbvar (short, 137)
#define black_weap _DLL_glbvar (short, 138)
#define crate_x _DLL_reference (short, 139)
#define crate_y _DLL_reference (short, 140)
#define crate_type _DLL_reference (short, 141)
#define mine_x _DLL_reference (short, 142)
#define mine_y _DLL_reference (short, 143)
#define oil_x _DLL_reference (short, 144)
#define oil_y _DLL_reference (short, 145)
#define exp_x _DLL_reference (short, 146)
#define exp_y _DLL_reference (short, 147)
#define exp_t _DLL_reference (short, 148)
#define exp_max _DLL_reference (short, 149)
#define curre _DLL_glbvar (short, 150)
#define weap_type _DLL_reference (short, 151)
#define weap_time _DLL_reference (short, 152)
#define weap_x _DLL_reference (float, 153)
#define weap_y _DLL_reference (float, 154)
#define weap_dirx _DLL_reference (float, 155)
#define weap_diry _DLL_reference (float, 156)
#define GameMode _DLL_glbvar (short, 157)
#define team _DLL_glbvar (short, 158)
#define maxworms _DLL_glbvar (short, 159)
#define jumping _DLL_glbvar (short, 160)
#define jtime _DLL_glbvar (short, 161)
#define jdir _DLL_glbvar (short, 162)
#define backflip _DLL_glbvar (short, 163)
#define moving _DLL_glbvar (short, 164)
#define crosshair _DLL_glbvar (short, 165)
#define XHx _DLL_glbvar (short, 166)
#define XHy _DLL_glbvar (short, 167)
#define xspotx _DLL_glbvar (short, 168)
#define xspoty _DLL_glbvar (short, 169)
#define CursorDir _DLL_glbvar (short, 170)
#define CursorX _DLL_glbvar (short, 171)
#define CursorY _DLL_glbvar (short, 172)
#define weapson _DLL_glbvar (short, 173)
#define currw _DLL_glbvar (short, 174)
#define chargew _DLL_glbvar (short, 175)
#define charge _DLL_glbvar (short, 176)
#define canfire _DLL_glbvar (short, 177)
#define cluster _DLL_glbvar (short, 178)
#define firetime _DLL_glbvar (short, 179)
#define Wx _DLL_glbvar (short, 180)
#define Wy _DLL_glbvar (short, 181)
#define LockX _DLL_glbvar (short, 182)
#define LockY _DLL_glbvar (short, 183)
#define LockTime _DLL_glbvar (short, 184)
#define Lock _DLL_glbvar (short, 185)
#define xhpos _DLL_glbvar (float, 186)
//#define MapLeft _DLL_reference (char, 187)
//#define MapLeftUp _DLL_reference (char, 188)
//#define MapRight _DLL_reference (char, 189)
//#define MapRightUp _DLL_reference (char, 190)
#define scrollx _DLL_glbvar (short, 191)
#define scrolly _DLL_glbvar (short, 192)
#define girder _DLL_glbvar (short, 215)
#define girdermode _DLL_glbvar (short, 216)
#define girders _DLL_glbvar (short, 217)
#define ParaMode _DLL_glbvar (short, 219)
#define Falling _DLL_glbvar (short, 220)
#define lowgrav _DLL_glbvar (short, 221)
#define fastwalk _DLL_glbvar (short, 222)
#define whiteinvis _DLL_glbvar (short, 223)
#define blackinvis _DLL_glbvar (short, 224)
#define WeaponSet _DLL_glbvar (short, 225)


//IMPORT FUNCTIONS!!
#define DrawWorms _DLL_call (void, (), 193)
//#define fixs _DLL_call (int, (int), 194)
#define Facing _DLL_call (int, (), 195)
#define DllGrayOn _DLL_call (void, (), 196)
#define DrawMap _DLL_call (void, (), 197)
#define DrawMap2 _DLL_call (void, (), 198)
#define DrawChunk  _DLL_call (void, void, short, short, short, short, int, int), 199);
#define DrawChunk2 _DLL_call (void, void, short, short, short, int, int), 200);
#define DrawSel _DLL_call (void, (), 201)
#define DrawObjects _DLL_call (void, (), 202)
#define DrawWaves _DLL_call (void, (), 203)
#define DrawWeaps _DLL_call (void, (), 204)
#define DrawXHair _DLL_call (void, (), 205)
#define DrawCursor _DLL_call (void, (), 206)
#define DrawXSpot _DLL_call (void, (), 207)
#define DrawExp _DLL_call (void, (), 208)
#define DrawCharge _DLL_call (void, (), 209)
#define DrawWeap _DLL_call (void, (), 210)
#define CamFocus _DLL_call (void, (), 211)
#define drawgfx _DLL_call (void, (), 212)
#define DllGrayOff _DLL_call (void, (), 213)
#define DrawCake _DLL_call (void, (), 214)
#define MapGirder _DLL_call (void, (), 218)
#define SetMapBuffers _DLL_call (void, (char *), 226)

//FUNCTION DECLARATION
//void drawgfx();
void MainLoop();
void KeyStuff();
void makemap();
void InitVars();
void StartGame();
void CollDetect();
void CollDetect2();
void Gravity(int worm);
void Gravity2();
void MoveLeft();
void MoveRight();
void FocusWorm(int TheWorm, int teamzor);
void ToggleWDir(int dir);
void Jump();
void JumpLeft();
void JumpRight();
void BackFlip();
void MoveJump();
void EndJump();
//int fixs(int ToFix);
int point(short x, short y);
int testpos(short x);
void GetWeap();
void UseWeapon();
void CursorClick();
//int Facing();
void pointoff(short x, short y);
void TextOut(short x, short y, const char *TOutStr);
void SetExp(short x, short y, short max);
void MoveWeaps();
void WeapCollide(short weap);
void TimeExpire(short weap);
void SetCluster(short x, short y, short type);
short ClusterOver();
void LockCam();
void EndWeap(short weap);
void EndGun();
void MapArrow(short dir, short x, short y);
void SecondWeap();
void LockWorm();
void UnLockWorm();
void SetWorm();
void ToggleTeam();
void WeapsOff();


/*//VAIBABLES
short white_x[8],white_y[8],white_h[8],white_dir[8],white_w,white_weap;
short black_x[8],black_y[8],black_h[8],black_dir[8],black_w,black_weap;
short crate_x[15],crate_y[15],crate_type[15];
short mine_x[10],mine_y[10],oil_x[8],oil_y[8],exp_x[8],exp_y[8],exp_t[8],exp_max[8],curre;
short weap_type[5],weap_time[5];
float weap_x[5],weap_y[5],weap_dirx[5],weap_diry[5];
short GameMode,team,maxworms,jumping,jtime,jdir,backflip,moving,crosshair,XHx,XHy,xspotx,xspoty,CursorDir,CursorX,CursorY,weapson,currw,chargew,charge,canfire,cluster,firetime;
short Wx=0,Wy=0; //for the current weapong selection in the weapon screen
short LockX,LockY,LockTime,Lock;

float xhpos;

//THE MAP VARZ!!
short scrollx,scrolly;*/
char * MapLeft;
char * MapRight;
char * MapLeftUp;
char * MapRightUp;

short weap_temp, orgx, orgy, WormLock, changed;

//SOME CONSTANTS
const short true=1;
const short false=0;
const short TWhite=1;
const short TBlack=2;

enum GameModes {M_Select, M_Game, M_Weapon, M_Cursor};
enum Weapons {WJetPack, WLowG, WFastWalk, WLaser, WInvis, WBazooka, WHoming, WMorter, WHomingP, WSheepLaunch, WGrenade, WCluster, WBanana, WAxe, WQuake, WShotG, WHandG, WUzi, WMiniG, WBow, WPunch, WDragonBall, WDeath, WSBomb, WProd, WDyna, WMine, WSheep, WSSheep, WMole, WAirStrike, WNapStrike, WMailStrike, WMineStrike, WMoleStrike, WBlow, WDrill, WGirder, WBaseball, WGirderPak, WNinja, WBungee, WParachute, WTeleport, WScales, WSBanana, WHolyGrenade, WFlame, WSalArmy, WMB, WMolotov, WSkunk, WMingVase, WSheepStrike, WCarpet, WCows, WOldLady, WDonkey, WNuke, WGeddon, WSkip, WSurrender, WSwitch, WIce, WMagicB, WCluster2, WMing2, WBowLeft, WBowRight, WHoming2, WMole2, WLady2, WSheepStrike2, WBatLeft, WBatRight, WCarpet2};


void InitVars()
{
  int x;
  
	//sets the map to the left
  scrollx=0;
  //sets the map to the left
  scrolly=0;
  
  //gives xhpos a valu
  xhpos=0;
  
  //inits the crates and barols!
  for(x=0;x<8;x++)
  	{
  		oil_x[x]=0;
  		oil_y[x]=-1;
  	}//next x
  for(x=0;x<15;x++)
  	{
  		crate_x[x]=0;
  		crate_y[x]=-1;
  		crate_type[x]=0;
  	}//next x	
  for(x=0;x<10;x++)
  	{
  		mine_x[x]=0;
  		mine_y[x]=-1;
  	}//next x	
  
  //inits scroll timer
  //ScrollTmr=0;
  //IsAnimal=false;
}



// Main Function
void _main(void)
{

  //if (!dbuffer) {GrayOff();return;} // make sure it worked
  //GrayDBufInit(dbuffer); // enable double-buffering
	// Place your code here.
	//INITS STUFF
	
	//clears the screen
	ClearScreen();

	MapLeft = malloc(4 * LCD_SIZE);
	if (MapLeft == NULL)
    {
      DlgMessage ("ERROR", "Error allocating memory!", BT_OK, BT_NONE);
      return;
    }
  MapRight = MapLeft + LCD_SIZE;
  MapLeftUp = MapRight + LCD_SIZE;
  MapRightUp = MapLeftUp + LCD_SIZE;
  memset(MapLeft, 0, 4 * LCD_SIZE);
	//attempts to load the ddl, otherwise errors
	if (LoadDLL ("wormsdll", 593223953, 1, 0) != DLL_OK) 
    {
      DlgMessage ("ERROR", "Error loading DLL!", BT_OK, BT_NONE);
      free(MapLeft);
      return;
    }

	SetMapBuffers(MapLeft);

	// Sets It Up For _keytest usage..
	INT_HANDLER save_1 = GetIntVec(AUTO_INT_1); 
	INT_HANDLER save_5 = GetIntVec(AUTO_INT_5); 
	SetIntVec(AUTO_INT_1, DUMMY_HANDLER); 
	SetIntVec(AUTO_INT_5, DUMMY_HANDLER); 
	
	//turns greyscale one
	DllGrayOn();
	
	//makes a random map
	makemap();
  
  //initializes variabls
  InitVars();
  
	//startgame -- thro's us rite into a game
	StartGame();
	
	//goes to main loop	
	MainLoop();

	//truns grey scale off
	DllGrayOff();
	
	//resets some stuff
	SetIntVec(AUTO_INT_1, save_1); 
	SetIntVec(AUTO_INT_5, save_5); 
	
	//unloads the ddl from memory
	UnloadDLL();
	free(MapLeft);
}



//WHAT ELSE, THAN THE MAIN LOOP!
void MainLoop()
{ 
	while((_keytest(RR_ESC)!=true) || (GameMode==M_Weapon))
		{
		  if(Lock)
			  {
			  	scrollx=LockX;//sets cam to locked pos
			  	scrolly=LockY;
			  	LockTime--; //decreased time until unlock
			  	if(LockTime<0)
			  	  {
			  	  	LockTime=0;
			  	  	Lock=false;
			  	  }//if it dosent need to lock anymore...
			  }
			
			KeyStuff();
			
			//makes sure worm is locked
			if(WormLock) SetWorm();
			
			drawgfx();
			//printf_xy(0,0,"%d",mapptr[0]);
			
			//makes all objects go downzor..
			Gravity(-1);
			Gravity2();
			
			//makes sure that you and the objects are not in the map..
			CollDetect();
			CollDetect2();
			
			//if you are jumping
			if(jumping!=-1)
				MoveJump();
			
			//if a weapon is active (like a bazooka moveing).. then..
			if(weapson)
			  MoveWeaps();

			  
			
			//makes sure your worm is on camera unless your shift scrolling
			if((!_keytest(RR_SHIFT)) & (GameMode != M_Cursor) & (weapson==false) & (Lock==false))
				{
					if(team==TWhite) FocusWorm(white_w, TWhite);
					else /*if(team==TBlack)*/ FocusWorm(black_w, TBlack);	
				}
			
			//if its cursor mode, it must focus on the cursor..
			if(GameMode==M_Cursor)
			  {
			  	CamFocus(CursorX, CursorY);
			  	cluster=false;
			  }
				
			
			
		}//wend
	 
}//end func main loop



//STARTS A GAME...
void StartGame()
{
  ClearScreen();
  
  int x;
  int px,py,timeout;
  
  //displays loading sprite
	DrawCake();
	
	//starts setting up the map...
	//Gives worms health and dir..
	for(x=0;x<8;x++)
		{
		  randomize();
			white_h[x]=100;
			black_h[x]=100;
			white_dir[x]=random(2);
			black_dir[x]=random(2);
			
			randomize();
			white_x[x]=random(300)+10;
			white_y[x]=-100+(random(180)+10);
			
			//white_y[x]=10;
			black_x[x]=random(300)+10;
			black_y[x]=random(180)+10;
			
			//nulls all the explosions
			exp_x[x]=-1;
			exp_y[x]=-1;
			exp_t[x]=1;
			exp_max[x]=20;
		}//next x
    
    white_x[0]=10;
    white_y[0]=145;
    
    white_x[1]=80;
    white_y[1]=130;
    
    white_x[2]=153;
    white_y[2]=150;
    
    white_x[3]=196;
    white_y[3]=110;
    
    white_x[4]=230;
    white_y[4]=65;
    
    white_x[5]=20;
    white_y[5]=20;
    
    white_x[6]=70;
    white_y[6]=40;
    
    white_x[7]=185;
    white_y[7]=30;
    
    
    black_x[0]=25;
    black_y[0]=145;
    
    black_x[1]=65;
    black_y[1]=130;
    
    black_x[2]=270;
    black_y[2]=150;
    
    black_x[3]=210;
    black_y[3]=110;
    
    black_x[4]=265;
    black_y[4]=65;
    
    black_x[5]=3;
    black_y[5]=20;
    
    black_x[6]=90;
    black_y[6]=40;
    
    black_x[7]=250;
    black_y[7]=30;
	  
    //sets up the teams for selection
    team=TWhite;
    white_w=0;
    black_w=0;
    
    //sets the mode to worm-select mode
    GameMode=M_Select;
    
    //this game will have 8 worms
    maxworms=8;
    
    //sets up the starting weapons (bazooka) for each team..
    white_weap=6;
    black_weap=6;
    crosshair = true;
    
    //no worm is moving..
    moving=0;
    
    //sets up the mines...
    for(x=0;x<8;x++)
    	{
    	  timeout=0;
    		do
    			{
    			  //do
    			    //{
		    				px=random(300);
		    				py=random(200);
		    			//}while(testpos(px)==0);
		    			
		    		timeout++;
    			}while(((point(px,py)==1) && (point(px,py-11)==1)) && (timeout<20));
    		
    		if(timeout>19) py=-1; //if it could not fidn a spot (timeout is over 20 or more) then it nulls it
    		oil_x[x]=px;
    		oil_y[x]=py-11;
    		
    		timeout=0;
    		do
    			{
    			  //do
    			   // {
    			    	px=random(320);
    						py=random(200);
    			    //}while(testpos(px)==0);
    			    
    				timeout++;
    			}while(((point(px,py)==1) && (point(px,py-5)==1)) && (timeout<20));
    		
    		if(timeout>19) py=-1;  //if it could not fidn a spot (timeout is over 20 or more) then it nulls it
    		mine_x[x]=px;
    		mine_y[x]=py-5;
    	}//next x
    
    //inits the weapon objet variables
    for(x=0;x<5;x++)
    	{
    		weap_x[x]=-1;
    		weap_y[x]=-1;
    		weap_type[x]=-1;
    		weap_dirx[x]=0;
    		weap_diry[x]=0;
    	}
    
    //inits the other mines..
    mine_y[6]=-1;
    mine_y[7]=-1;
    
    //uses gravity to have everything set on the map..
    for(x=0;x<100;x++)
    	Gravity(-1);
    
    //uses gtravity 2, to have all the objects set ont he map...
    for(x=0;x<100;x++)
    	Gravity2();
    
    //uses collision dection to make sure no worms are sunk into the map...
    for(x=0;x<100;x++)
    	CollDetect();
    
    //uses collision dection2 to make sure no objects are sunk into the map...
    for(x=0;x<100;x++)
    	CollDetect2();
    	
    jumping=-1; //no one is jumping..
    
    //there is no xspot yet..
    xspotx=-1;
    xspoty=-1;
    
    //cursor will start facing left..
    CursorDir=0;
    
    //set to upper left just to init it.
    CursorX=0;
    CursorX=0;
    
    //sets the current explosion..
    curre=0;
    
    //sets the weapon mode to false..
    weapson=false;
    currw=0;
    chargew=false;
    charge=0;
    
    //makes it so you CAN fire
    canfire=true;
}



int point(short x, short y)
{
	if((x<160) & (y<100))
		if(EXT_GETPIX(MapLeftUp,x,y)==0) return 0;
	if((x<160) & (y>=100))
		if(EXT_GETPIX(MapLeft,x,y-100)==0) return 0;
	if((x>=160) & (y<100))
		if(EXT_GETPIX(MapRightUp,x-160,y)==0) return 0;
	if((x>=160) & (y>=100))
		if(EXT_GETPIX(MapRight,x-160,y-100)==0) return 0;
	
	return 1;
}

void pointoff(short x, short y)
{
	if((x<160) & (y<100))
		EXT_CLRPIX(MapLeftUp,x,y);
	if((x<160) & (y>=100))
		EXT_CLRPIX(MapLeft,x,y-100);
	if((x>=160) & (y<100))
		EXT_CLRPIX(MapRightUp,x-160,y);
	if((x>=160) & (y>=100))
		EXT_CLRPIX(MapRight,x-160,y-100);
}

int testpos(short zx)
{
  int x;
	for(x=0;x<8;x++)
		{
			if(
			    (
			   	  (zx<oil_x[x]+15)
			   	  &
			   	  (zx>oil_x[x]-7)
			    )
			    ||
			    (
			   	  (zx<mine_x[x]+10)
			   	  &
			   	  (zx>mine_x[x]-7)
			    )
			    /*||
			    (
			   	  (zx<white_x[x]+10)
			   	  &
			   	  (zx>white_x[x]-7)
			    )
			    ||
			    (
			   	  (zx<black_x[x]+10)
			   	  &
			   	  (zx>black_x[x]-7)
			    )*/
			  )
			  return 0;
		}//next x
	
	return 1;
}



void makemap() //this function makes a random map in each of the buffers...
{
  int x,height,height2;
  
  //DRAWS THE LOWER MAPS
	//DRAWS THE LOWER MAPS
	//DRAWS THE LOWER MAPS
  height=30; //starts the map generating in the middle of the map
  randomize();
  
  PortSet(MapLeft, 239, 99); //sets all the drawing routines of the first buffer
	for(x=0;x<160;x++) //draws the random height lines
		{
		  height+=random(3)-1;
		  
		  //makes sure its not out of bounds
		  if(height<0) height=0;
		  else if(height>LCD_HEIGHT) height=LCD_HEIGHT;
		  
			DrawLine((short)x,LCD_HEIGHT-1,(short)x,LCD_HEIGHT-(short)height,A_NORMAL); //draws the map
		}
		
	PortSet(MapRight, 239, 99); //sets all the drawing routines of the first buffer
	for(x=0;x<160;x++) //draws the random height lines
		{
		  height+=random(3)-1;
		  
		  //makes sure its not out of bounds
		  if(height<0) height=0;
		  else if(height>LCD_HEIGHT) height=LCD_HEIGHT;
		  
			DrawLine((short)x,LCD_HEIGHT-1,(short)x,LCD_HEIGHT-(short)height,A_NORMAL); //draws the map
		}
		
	
	//DRAWS THE UPPER MAPS
	//DRAWS THE UPPER MAPS
	//DRAWS THE UPPER MAPS
	height=10; //starts the map generating in the middle of the map
  height2=0;
  
  PortSet(MapLeftUp, 239, 99); //sets all the drawing routines of the first buffer
	for(x=0;x<160;x++) //draws the random height lines
		{
		  height+=random(3)-1;
		  height2+=random(3)-1;
		  
		  if((x>100) & (x<130))
		  	{
		  		height=0;
		  		height2=0;
		  	}
		  //makes sure its not out of bounds
		  if(height<0) height=0;
		  else if(height>LCD_HEIGHT) height=LCD_HEIGHT;
		  if(height2<0) height2=0;
		  else if(height2>LCD_HEIGHT) height2=LCD_HEIGHT;
		  
			DrawLine((short)x,LCD_HEIGHT-height2,(short)x,LCD_HEIGHT-(short)height,A_NORMAL); //draws the map
		}
		
	PortSet(MapRightUp, 239, 99); //sets all the drawing routines of the first buffer
	for(x=0;x<160;x++) //draws the random height lines
		{
		  height+=random(3)-1;
		  height2+=random(3)-1;
		  
		  //makes sure its not out of bounds
		  if(height<0) height=0;
		  else if(height>LCD_HEIGHT) height=LCD_HEIGHT;
		  if(height2<0) height2=0;
		  else if(height2>LCD_HEIGHT) height2=LCD_HEIGHT;
		  
			DrawLine((short)x,LCD_HEIGHT-height2,(short)x,LCD_HEIGHT-(short)height,A_NORMAL); //draws the map
		}
	PortRestore(); //sets the drawing ports back to normal
	
}














void KeyStuff()
{
  int hor,ver;
  
  hor=0;
  ver=3;
  
  static short ScrollTmr=0;
  static short move;
  static short walk=0;
  
	//checks for keys being pressed and acts accordingly
	//checks for left and right WHILE SHIFT is down.. scrolls map
	if(_keytest(RR_SHIFT))
		{
			if((_keytest(RR_LEFT)))
				{
				  ScrollTmr++;
				  if(ScrollTmr>hor)
						{
							scrollx-=3;
							ScrollTmr=0;
							
							if(scrollx<0) //if you cant scroll anymore..
								scrollx=0;
						}//endnf timne to scroll
				}//end if key left
			if((_keytest(RR_RIGHT)))
				{
					ScrollTmr++;
				  if(ScrollTmr>hor)
						{
							scrollx+=3;
							ScrollTmr=0;
							
							if(scrollx>160)
					  		scrollx=160;
						}//endnf timne to scroll
				}//end if key right
				
			if((_keytest(RR_DOWN)))
				{
					scrolly+=ver;
					if(scrolly>100)
						scrolly=100;
				}//end if key down
			if((_keytest(RR_UP)))
				{
					scrolly-=ver;
					if(scrolly<0)
						scrolly=0;
				}//end if key up
		}//end if shift scroll
  
  if(
      (_keytest(RR_SHIFT)!=true) 
        &
        (
          (_keytest(RR_LEFT))
          ||
          (_keytest(RR_RIGHT))
          ||
          (_keytest(RR_UP))
          ||
          (_keytest(RR_DOWN))
        )
        &
        (jumping==-1)
        &
        (GameMode!=M_Weapon)
        &
        (GameMode!=M_Cursor)
        &
        (moving==false)
    )
  	{
  		if((_keytest(RR_LEFT)))
				{
				  if(GameMode==M_Select && weapson==false) {GameMode=M_Game; changed=false;}
				  if(GameMode==M_Select && weapson) return;
				    //MOVES THE WORM LEFT
				    //resets the camera if nessicary
						//if(team==TWhite) FocusWorm(white_w,team);
				  	//else /*if(team==TBlack)*/ FocusWorm(black_w,team);
				  	

				  	walk++;
				  	if(walk>2)
				  		{
				  			walk=0;
				  			
				  			MoveLeft();
						  	move++;
								if(move>5)
									{
										move=0;
										ToggleWDir(1);
									}//endif time to toggle pos
				  		}//endif time to walk
				  	
				}//end if key left
			if((_keytest(RR_RIGHT)))
				{
					if(GameMode==M_Select && weapson==false) {GameMode=M_Game; changed=false;}
				  if(GameMode==M_Select && weapson) return;
					  //MOVES THE WORM LEFT
					  //resets the camera if nessicary
	          //if(team==TWhite) FocusWorm(white_w,team);
				  	//else /*if(team==TBlack)*/ FocusWorm(black_w,team);
				  	
	          walk++;
				  	if(walk>2)
				  		{
				  			walk=0;
						  	MoveRight();
						  	
							  move++;
								if(move>5)
									{
										move=0;
										ToggleWDir(1);
									}//endif time to toggle pos
							}//endif time to walk
				}//end if key right
			if((_keytest(RR_UP)))
				{
					if(GameMode==M_Select) GameMode=M_Game;
					if(crosshair)
						{
							xhpos+=0.1;
							if(xhpos>3.1) xhpos=3.1;
							XHx=sin(xhpos)*15;
							XHy=cos(xhpos)*15;
						}
				}//end if key down
			if((_keytest(RR_DOWN)))
				{
					if(GameMode==M_Select) GameMode=M_Game;
						{
							xhpos-=0.1;
							if(xhpos<0.1) xhpos=0.1;
							XHx=sin(xhpos)*15;
							XHy=cos(xhpos)*15;
						}
				}//end if key up
  	}else//endif shift not pressed
		{
			ToggleWDir(0);
		}
	
	if(GameMode==M_Cursor)
	  {
	  	if(girdermode)
	  	  {
	  	  	//tests to see if you are roatating the girder right or left..
	  	  	if(_keytest(RR_PLUS))
	  	  	  {
	  	  	  	girder--;
	  	  	  	if(girder<0) girder=7;
	  	  	  	while(_keytest(RR_PLUS));
	  	  	  }
	  	  	if(_keytest(RR_MINUS))
	  	  	  {
	  	  	  	girder++;
	  	  	  	if(girder>7) girder=0;
	  	  	  	while(_keytest(RR_MINUS));
	  	  	  }
	  	  	
	  	  	
	  	  }//end if girder mode
	  	  
	  	//mvoes the cursor...
	  	if(_keytest(RR_UP))
	  		CursorY-=4;
	  	if(_keytest(RR_DOWN))
	  		CursorY+=4;
	    if(_keytest(RR_LEFT))
	  		{
	  			CursorX-=4;
	  			CursorDir=0; //it faces left
	  		}
	  		
	  	if(_keytest(RR_RIGHT))
	  		{
	  			CursorX+=4;
	  			CursorDir=1; //it faces Right
	  		}

	    //makes sure its still in bounds..
	    if(CursorX<0) CursorX=0;
	    else if(CursorX>310) CursorX=310;
	    if(CursorY<0) CursorY=0;
	    else if(CursorY>188) CursorY=188;
	    
	    if(_keytest(RR_2ND))
	    	CursorClick();
	    	
	  }//endif GAMEMODE IS M_CURSOR
	  
	//if its select worm, and you press [APPS] you cycle worms
	if((GameMode==M_Select) & (_keytest(RR_APPS)))
		{
			if(team==TWhite)
				{
					white_w++;
					if(white_w>=maxworms)
						white_w=0;
					//FocusWorm(white_w,TWhite);
				}//endif WHITE TEAM
			else //if(team==TBlack)
				{
					black_w++;
					if(black_w>=maxworms)
						black_w=0;
					//FocusWorm(black_w,TBlack);
				}//endif BLACK TEAM
			while(_keytest(RR_APPS));      
		}//end if choose worm
		
	if((GameMode==M_Game) & (_keytest(RR_APPS)))
	  {
	  	ToggleTeam();
	  }


  //chris cross will make ya Jump! Jump!	  
	if((GameMode==M_Game) & (_keytest(RR_DIAMOND)) & (jumping==-1) & (moving==false))
		Jump();
		
  //hip-hop will make ya Jump! Jump!	  
	if((GameMode==M_Game) & (_keytest(RR_ALPHA)) & (jumping==-1) & (moving==false))
		BackFlip();

  //if you press F1 or Catalog you get weapons...
  if((_keytest(RR_F1)) || (_keytest(RR_CATALOG)) & (GameMode==M_Game))
 		GameMode=M_Weapon;
  
  //if you press ESC during weapong mode it exits the weapong screen..
  if((_keytest(RR_ESC)) & (GameMode==M_Weapon))
 		{
 			GameMode=M_Game;
 			while(_keytest(RR_ESC));
 		}
 	
 	//if you press ENTER or 2ND durig weapon mode, then you select the weapong the cursor is on..
 	if(((_keytest(RR_2ND)) || (_keytest(RR_ENTER))) && ((GameMode==M_Weapon) || (GameMode==M_Cursor)))
		{
		  while((_keytest(RR_2ND)) || (_keytest(RR_ENTER)));
			GetWeap();
		}
		
  //if you press 2ND it will use the current weapon you have selected (if you are in game mode) NOT CHARGE MODE
  if((_keytest(RR_2ND)) && (GameMode==M_Game) && (chargew==false) && (canfire))
    UseWeapon();
  
  //if you press 2ND it will charge the current weapon you have selected (if you are in game mode) IS CHARGE MODE
  if((_keytest(RR_2ND)) && (GameMode==M_Game) && (chargew) && (charge<=15) && (canfire))
    charge++;
  
  //if you release 2ND it will use the current weapon you have selected (if you are in game mode) IS CHARGE MODE
  if((((_keytest(RR_2ND)==false) && (GameMode==M_Game) && (chargew) && (charge>0)) || (charge>15)) && (canfire))
    UseWeapon();
  
  if((_keytest(RR_2ND)) && (weapson))
    {
    	SecondWeap();
    	
    }//endif 2nd during weapon
    
  //if the user presses F1 then the were be an explosio where the worm was...
  if(_keytest(RR_F2))
  	{
  		if(team==TWhite)
  		  SetExp(white_x[white_w],white_y[white_w]+6,20);
  		else //if(team==TBlack)
  		  SetExp(black_x[black_w],black_y[black_w]+6,20);
  		
  	while(_keytest(RR_F2)); //waits until key is released..
  	}//endif pressed f1
  
  //move\choose weapon..
  if(GameMode==M_Weapon)
    {
    	//lets the user scroll true the weapons...
		  if(_keytest(RR_SHIFT)==false)
		  	{
		  		if(_keytest(RR_LEFT))
				    Wx--;
				  if(_keytest(RR_RIGHT))
				    Wx++;
				  if(_keytest(RR_UP))
				    Wy--;
				  if(_keytest(RR_DOWN))
				    Wy++;
				  if(Wy>4) Wy=0;
				  else if(Wy<0) Wy=4;
				  if(Wx>12) Wx=0;
				  else if(Wx<0) Wx=12;
				  
				  while(_keytest(RR_LEFT) || _keytest(RR_RIGHT) || _keytest(RR_UP) || _keytest(RR_DOWN));
		  	}
    }
}//end key stuff





void ToggleWDir(int dir)
{
  if(team==TWhite)
  	{
  		if((dir==0) & (jumping==-1))
				{
					if(white_dir[white_w]==2) white_dir[white_w]=0;
					else if(white_dir[white_w]==3) white_dir[white_w]=1;
					else if(white_dir[white_w]==4) white_dir[white_w]=1;
					else if(white_dir[white_w]==5) white_dir[white_w]=0;
					else if(white_dir[white_w]==6) white_dir[white_w]=1;
					else if(white_dir[white_w]==7) white_dir[white_w]=0;
					else if(white_dir[white_w]==8) white_dir[white_w]=1;
					else if(white_dir[white_w]==9) white_dir[white_w]=0;
					else if(white_dir[white_w]==10) white_dir[white_w]=1;
					else if(white_dir[white_w]==11) white_dir[white_w]=0;
					else if(white_dir[white_w]==12) white_dir[white_w]=1;
					else if(white_dir[white_w]==13) white_dir[white_w]=0;
					
					
				}//endif reset
			else if(dir==1)
				{
					switch(white_dir[white_w])
						{
							case 3:
							  white_dir[white_w]=1;
							  break;
							case 1:
							  white_dir[white_w]=3;
							  break;
							case 2:
							  white_dir[white_w]=0;
							  break;
							case 0:
							  white_dir[white_w]=2;
							  break;
							default:
							  ;
						}
				}//endif reset
  	}//endif white team
  
	else //if(team==TBlack)
  	{
  		if((dir==0) & (jumping==-1))
				{
					if(black_dir[black_w]==2) black_dir[black_w]=0;
					else if(black_dir[black_w]==3) black_dir[black_w]=1;
					else if(black_dir[black_w]==4) black_dir[black_w]=1;
					else if(black_dir[black_w]==5) black_dir[black_w]=0;
				  else if(black_dir[black_w]==6) black_dir[black_w]=1;
					else if(black_dir[black_w]==7) black_dir[black_w]=0;
					else if(black_dir[black_w]==8) black_dir[black_w]=1;
					else if(black_dir[black_w]==9) black_dir[black_w]=0;
					else if(black_dir[black_w]==10) black_dir[black_w]=1;
					else if(black_dir[black_w]==11) black_dir[black_w]=0;
					else if(black_dir[black_w]==12) black_dir[black_w]=1;
					else if(black_dir[black_w]==13) black_dir[black_w]=0;
				}//endif reset
			else if(dir==1)
				{
					switch(black_dir[black_w])
						{
							case 2:
							  black_dir[black_w]=0;
							  break;
							case 0:
							  black_dir[black_w]=2;
							  break;
							case 3:
							  black_dir[black_w]=1;
							  break;
							case 1:
							  black_dir[black_w]=3;
							  break;
							default:
							  ;
						}
					
				}//endif reset
  	}//endif white team
}









void Gravity(int TheWorm)
{
  int x, WOrg, BOrg;
  static short grav=0;
  Falling=false;
  
  grav++; if(grav>1) grav=0; if(grav==0 && lowgrav) return;
  //saves the original position of the worm (just the vertical value)
  WOrg=white_y[white_w];
  BOrg=black_y[black_w];
  
	for(x=0;x<maxworms;x++)
		{
		  //if something that was pased isnt ALL (-1) then it does it JUST for that worm...
		  if((TheWorm != -1) & (team==TWhite)) x=TheWorm;
		  if((TheWorm != -1) & (team==TBlack)) goto Blackies;
		  
			//white_y[x]++;
			//WHITE WORMS +++ WHITE WORMS +++ WHITE WORMS +++ WHITE WORMS
			if((white_x[x]<160) & (white_y[x]<85))
			  {
			  	if(EXT_GETPIX(MapLeftUp,white_x[x]+0,white_y[x]+15)==0)
			  	  {
			  	  	white_y[x]++;
			  	  	if((team==TWhite) & (white_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TWhite)) EndJump();
			  }//endif in BOTTOM LEFT
			  
			if((white_x[x]>=160) & (white_y[x]<85))
			  {
			  	if(EXT_GETPIX(MapRightUp,white_x[x]+0-160,white_y[x]+15)==0)
			  	  {
			  	  	white_y[x]++;
			  	  	if((team==TWhite) & (white_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TWhite)) EndJump();
			  }//endif in BOTTOM RIGHT
			  
			if((white_x[x]<160) & (white_y[x]>=85))
			  {
			  	if(EXT_GETPIX(MapLeft,white_x[x]+0,(white_y[x]-100)+15)==0)
			  	  {
			  	  	white_y[x]++;
			  	  	if((team==TWhite) & (white_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TWhite)) EndJump();
			  }//endif in UPPER LEFT
			
			if((white_x[x]>=160) & (white_y[x]>=85))
			  {
			  	if(EXT_GETPIX(MapRight,white_x[x]+0-160,(white_y[x]-100)+15)==0)
			  	  {
			  	  	white_y[x]++;
			  	  	if((team==TWhite) & (white_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TWhite)) EndJump();
			  }//endif in UPPER RIGHT
			//if(white_y[x]=85
			
			
			Blackies:
			if((TheWorm != -1) & (team==TWhite)) return;
		  if((TheWorm != -1) & (team==TBlack)) x=TheWorm;
		  
			//BLACK WORMS +++ BLACK WORMS +++ BLACK WORMS +++ BLACK WORMS
			if((black_x[x]<160) & (black_y[x]<85))
			  {
			  	if(EXT_GETPIX(MapLeftUp,black_x[x],black_y[x]+15)==0)
			  	  {
			  	  	black_y[x]++;
			  	  	if((team==TBlack) & (black_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TBlack)) EndJump();
			  }//endif in BOTTOM LEFT
			  
			if((black_x[x]>=160) & (black_y[x]<85))
			  {
			  	if(EXT_GETPIX(MapRightUp,black_x[x]-160,black_y[x]+15)==0)
			  	  {
			  	  	black_y[x]++;
			  	  	if((team==TBlack) & (black_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TBlack)) EndJump();
			  }//endif in BOTTOM RIGHT
			  
			if((black_x[x]<160) & (black_y[x]>=85))
			  {
			  	if(EXT_GETPIX(MapLeft,black_x[x],(black_y[x]-100)+15)==0)
			  	  {
			  	  	black_y[x]++;
			  	  	if((team==TBlack) & (black_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TBlack)) EndJump();
			  }//endif in UPPER LEFT
			
			if((black_x[x]>160) & (black_y[x]>=85))
			  {
			  	if(EXT_GETPIX(MapRight,black_x[x]-160,(black_y[x]-100)+15)==0)
			  	  {
			  	  	black_y[x]++;
			  	  	if((team==TBlack) & (black_w==x)) moving=true;
			  	  }//endif hit ground
			  	  else
			  	    if((jumping==x) & (team==TBlack)) EndJump();
			  }//endif in UPPER RIGHT
			
			if(TheWorm != -1) x=20;
		}//next x
		
		//test for parachute collision...
		if(team==TWhite)
		  {
		  	if(WOrg != white_y[white_w]) //if the original position doesn not match the new one, then it must be falling..
		  	  Falling=true;
		  	else if(ParaMode)//otherwise it must have landed..
		  	  {
		  	  	ParaMode=false;
  	  			EndWeap(0);
		  	  }
		  }
		else
		  {
		  	if(BOrg != black_y[black_w]) //if the original position doesn not match the new one, then it must be falling..
		  	  Falling=true;
		  	else if(ParaMode)//otherwise it must have landed..
		  	  {
		  	  	ParaMode=false;
  	  			EndWeap(0);
		  	  }
		  }
}


void Gravity2()
{
	int x;
	for(x=0;x<15;x++)
	{
			if((x<15) & (crate_y[x]!=-1))
				{
					//CRATES +++ CRATES +++ CRATES +++ CRATES
					if((crate_x[x]<160) & (crate_y[x]<90))
					  {
					  	if(EXT_GETPIX(MapLeftUp,crate_x[x],crate_y[x]+10)==0)
					  	  crate_y[x]++;
					  }//endif in BOTTOM LEFT
					  
					if((crate_x[x]>=160) & (crate_y[x]<90))
					  {
					  	if(EXT_GETPIX(MapRightUp,crate_x[x]-160,crate_y[x]+10)==0)
					  	  crate_y[x]++;
					  }//endif in BOTTOM RIGHT
					  
					if((crate_x[x]<160) & (crate_y[x]>=90))
					  {
					  	if(EXT_GETPIX(MapLeft,crate_x[x],(crate_y[x]-100)+10)==0)
					  	  crate_y[x]++;
					  }//endif in UPPER LEFT
					
					if((crate_x[x]>160) & (crate_y[x]>=90))
					  {
					  	if(EXT_GETPIX(MapRight,crate_x[x]-160,(crate_y[x]-100)+10)==0)
					  	  crate_y[x]++;
					  }//endif in UPPER RIGHT
				}
			if((x<10) & (mine_y[x]!=-1))
				{
					//MINES +++ MINES +++ MINES +++ MINES
					if((mine_x[x]<160) & (mine_y[x]<96))
					  {
					  	if(EXT_GETPIX(MapLeftUp,mine_x[x],mine_y[x]+4)==0)
					  	  mine_y[x]++;
					  }//endif in BOTTOM LEFT
					  
					if((mine_x[x]>=160) & (mine_y[x]<96))
					  {
					  	if(EXT_GETPIX(MapRightUp,mine_x[x]-160,mine_y[x]+4)==0)
					  	  mine_y[x]++;
					  }//endif in BOTTOM RIGHT
					  
					if((mine_x[x]<160) & (mine_y[x]>=96))
					  {
					  	if(EXT_GETPIX(MapLeft,mine_x[x],(mine_y[x]-100)+4)==0)
					  	  mine_y[x]++;
					  }//endif in UPPER LEFT
					
					if((mine_x[x]>160) & (mine_y[x]>=96))
					  {
					  	if(EXT_GETPIX(MapRight,mine_x[x]-160,(mine_y[x]-100)+4)==0)
					  	  mine_y[x]++;
					  }//endif in UPPER RIGHT
				}
			if((x<8) & (oil_y[x]!=-1))
				{
					//OIL +++ OIL +++ OIL +++ OIL
					if((oil_x[x]<160) & (oil_y[x]<89))
					  {
					  	if(EXT_GETPIX(MapLeftUp,oil_x[x],oil_y[x]+11)==0)
					  	  oil_y[x]++;
					  }//endif in BOTTOM LEFT
					  
					if((oil_x[x]>=160) & (oil_y[x]<89))
					  {
					  	if(EXT_GETPIX(MapRightUp,oil_x[x]-160,oil_y[x]+11)==0)
					  	  oil_y[x]++;
					  }//endif in BOTTOM RIGHT
					  
					if((oil_x[x]<160) & (oil_y[x]>=89))
					  {
					  	if(EXT_GETPIX(MapLeft,oil_x[x],(oil_y[x]-100)+11)==0)
					  	  oil_y[x]++;
					  }//endif in UPPER LEFT
					
					if((oil_x[x]>160) & (oil_y[x]>=89))
					  {
					  	if(EXT_GETPIX(MapRight,oil_x[x]-160,(oil_y[x]-100)+11)==0)
					  	  oil_y[x]++;
					  }//endif in UPPER RIGHT
				}
			//weapons..
			if(x<5)
			  {
			  	if(point(weap_x[x]+3,weap_y[x]+6)==1 && (weap_type[x]!=WNapStrike))
			  	  weap_y[x]--;
			  }
	}//next x
}

void CollDetect()
{
	int x, WOrg, BOrg;
	
	//saves the original position of the worm (just the vertical value)
  WOrg=white_y[white_w];
  BOrg=black_y[black_w];
  
	for(x=0;x<maxworms;x++)
		{
		  //if something that was pased isnt ALL (-1) then it does it JUST for that worm...
		  //if(TheWorm != -1) x=TheWorm;
		  
			//white_y[x]++;
			//WHITE WORMS +++ WHITE WORMS +++ WHITE WORMS +++ WHITE WORMS
			if((white_x[x]<160) & (white_y[x]<100))
			  {
			  	if(EXT_GETPIX(MapLeftUp,white_x[x]-5,white_y[x]+7)==1)
			  	  white_x[x]+=2;
          if(EXT_GETPIX(MapLeftUp,white_x[x]+5,white_y[x]+7)==1)
			  	  white_x[x]-=2; 
			  	if(EXT_GETPIX(MapLeftUp,white_x[x],white_y[x]-1)==1)
			  	  white_y[x]+=2;
			  	if(EXT_GETPIX(MapLeftUp,white_x[x],white_y[x]+15)==1)
			  	  {
			  	  	white_y[x]-=1;
			  	  	if((team==TWhite) && (jumping==x)) EndJump();
			  	  	if((team==TWhite) && (white_w==x)) moving=false;
			  	  }
			  	 
			  }//endif in BOTTOM LEFT
			  
			if((white_x[x]>=160) & (white_y[x]<100))
			  {
			  	if(EXT_GETPIX(MapRightUp,white_x[x]-5-160,white_y[x]+7)==1)
			  	  white_x[x]+=2;
			  	if(EXT_GETPIX(MapRightUp,white_x[x]+5-160,white_y[x]+7)==1)
			  	  white_x[x]-=2;
			  	if(EXT_GETPIX(MapRightUp,white_x[x]+0-160,white_y[x]-1)==1)
			  	  white_y[x]+=2;
			  	if(EXT_GETPIX(MapRightUp,white_x[x]+0-160,white_y[x]+15)==1)
			  	  {
			  	  	white_y[x]-=1;
			  	  	if((team==TWhite) & (jumping==x)) EndJump();
			  	  	if((team==TWhite) & (white_w==x)) moving=false;
			  	  }
			  }//endif in BOTTOM RIGHT
			  
			if((white_x[x]<160) & (white_y[x]>100))
			  {
			  	if(EXT_GETPIX(MapLeft,white_x[x]-5,(white_y[x]-100)+7)==1)
			  	  white_x[x]+=2;
			  	if(EXT_GETPIX(MapLeft,white_x[x]+5,(white_y[x]-100)+7)==1)
			  	  white_x[x]-=2;
			  	if(EXT_GETPIX(MapLeft,white_x[x]+0,(white_y[x]-100)-1)==1)
			  	  white_y[x]+=2;
			  	if(EXT_GETPIX(MapLeft,white_x[x]+0,(white_y[x]-100)+15)==1)
			  	  {
			  	  	white_y[x]-=1;
			  	  	if((team==TWhite) & (jumping==x)) EndJump();
			  	  	if((team==TWhite) & (white_w==x)) moving=false;
			  	  }
			  	
			  }//endif in UPPER LEFT
			
			if((white_x[x]>=160) & (white_y[x]>100))
			  {
			  	if(EXT_GETPIX(MapRight,white_x[x]-5-160,(white_y[x]-100)+7)==1)
			  	  white_x[x]+=2;
			  	if(EXT_GETPIX(MapRight,white_x[x]+5-160,(white_y[x]-100)+7)==1)
			  	  white_x[x]-=2;
			  	if(EXT_GETPIX(MapRight,white_x[x]+0-160,(white_y[x]-100)-1)==1)
			  	  white_y[x]+=2;
			  	if(EXT_GETPIX(MapRight,white_x[x]+0-160,(white_y[x]-100)+15)==1)
			  	  {
			  	  	white_y[x]-=1;
			  	  	if((team==TWhite) & (jumping==x)) EndJump();
			  	  	if((team==TWhite) & (white_w==x)) moving=false;
			  	  }
			  }//endif in UPPER RIGHT
			  
			//BLACK WORMS +++ BLACK WORMS +++ BLACK WORMS +++ BLACK WORMS
			if((black_x[x]<160) & (black_y[x]<100))
			  {
			  	if(EXT_GETPIX(MapLeftUp,black_x[x]-5,black_y[x]+7)==1)
			  	  black_x[x]+=2;
			  	if(EXT_GETPIX(MapLeftUp,black_x[x]+5,black_y[x]+7)==1)
			  	  black_x[x]-=2;
			  	if(EXT_GETPIX(MapLeftUp,black_x[x],black_y[x]-1)==1)
			  	  black_y[x]+=2;
			  	if(EXT_GETPIX(MapLeftUp,black_x[x],black_y[x]+15)==1)
			  	  {
			  	  	black_y[x]-=1;
			  	  	if((team==TBlack) & (jumping==x)) EndJump();
			  	  	if((team==TBlack) & (black_w==x)) moving=false;
			  	  }
			  	  
			  }//endif in BOTTOM LEFT
			  
			if((black_x[x]>=160) & (black_y[x]<100))
			  {
			  	if(EXT_GETPIX(MapRightUp,black_x[x]-5-160,black_y[x]+7)==1)
			  	  black_x[x]+=2;
			  	if(EXT_GETPIX(MapRightUp,black_x[x]+5-160,black_y[x]+7)==1)
			  	  black_x[x]-=2;
			  	if(EXT_GETPIX(MapRightUp,black_x[x]-160,black_y[x]-1)==1)
			  	  black_y[x]+=2;
			  	if(EXT_GETPIX(MapRightUp,black_x[x]-160,black_y[x]+15)==1)
			  	  {
			  	  	black_y[x]-=1;
			  	  	if((team==TBlack) & (jumping==x)) EndJump();
			  	  	if((team==TBlack) & (black_w==x)) moving=false;
			  	  }
			  	  
			  }//endif in BOTTOM RIGHT
			  
			if((black_x[x]<160) & (black_y[x]>100))
			  {
			  	if(EXT_GETPIX(MapLeft,black_x[x],(black_y[x]-5-100)+7)==1)
			  	  black_x[x]+=2;
			  	if(EXT_GETPIX(MapLeft,black_x[x],(black_y[x]+5-100)+7)==1)
			  	  black_x[x]-=2;
			  	if(EXT_GETPIX(MapLeft,black_x[x],(black_y[x]-100)-1)==1)
			  	  black_y[x]+=2;
			  	if(EXT_GETPIX(MapLeft,black_x[x],(black_y[x]-100)+15)==1)
			  	  {
			  	  	black_y[x]-=1;
			  	  	if((team==TBlack) & (jumping==x)) EndJump();
			  	  	if((team==TBlack) & (black_w==x)) moving=false;
			  	  }
			  	  
			  }//endif in UPPER LEFT
			
			if((black_x[x]>160) & (black_y[x]>100))
			  {
			  	if(EXT_GETPIX(MapRight,black_x[x]-5-160,(black_y[x]-100)+7)==1)
			  	  black_x[x]+=2;
			  	if(EXT_GETPIX(MapRight,black_x[x]+5-160,(black_y[x]-100)+7)==1)
			  	  black_x[x]-=2;
			  	if(EXT_GETPIX(MapRight,black_x[x]-160,(black_y[x]-100)-1)==1)
			  	  black_y[x]+=2;
			  	if(EXT_GETPIX(MapRight,black_x[x]-160,(black_y[x]-100)+15)==1)
			  	  {
			  	  	black_y[x]-=1;
			  	  	if((team==TBlack) & (jumping==x)) EndJump();
			  	  	if((team==TBlack) & (black_w==x)) moving=false;
			  	  }
			  	  
			  }//endif in UPPER RIGHT
		}//next x
		
		
		//test for parachute collision...
		if(team==TWhite)
		  {
		  	if(WOrg==white_y[white_w]) //if the original position doesn not match the new one, then it must be falling..
		  	  Falling=true;
		  	else if(ParaMode) //otherwise it must have landed..
		  	  {
		  	  	ParaMode=false;
  	  			EndWeap(0);
		  	  }
		  }
		else
		  {
		  	if(BOrg==black_y[black_w]) //if the original position doesn not match the new one, then it must be falling..
		  	  Falling=true;
		  	else if(ParaMode)//otherwise it must have landed..
		  	  {
		  	  	ParaMode=false;
  	  			EndWeap(0);
		  	  }
		  }
  SetWorm();
}	

void CollDetect2()
{
	int x;
	for(x=0;x<8;x++)
		{
			//OILS +++ OILS +++ OILS +++ OILS
			if((oil_x[x]<160) & (oil_y[x]<89))
			  {
			  	if(EXT_GETPIX(MapLeftUp,oil_x[x],oil_y[x]+11)==1)
			  	  oil_y[x]-=1;
			  }//endif in BOTTOM LEFT
			  
			if((oil_x[x]>=160) & (oil_y[x]<89))
			  {
			  	if(EXT_GETPIX(MapRightUp,oil_x[x]+0-160,oil_y[x]+11)==1)
			  	  oil_y[x]-=1;
			  }//endif in BOTTOM RIGHT
			  
			if((oil_x[x]<160) & (oil_y[x]>=89))
			  {
			  	if(EXT_GETPIX(MapLeft,oil_x[x]+0,(oil_y[x]-100)+11)==1)
			  	  oil_y[x]-=1;
			  	
			  }//endif in UPPER LEFT
			
			if((oil_x[x]>=160) & (oil_y[x]>=89))
			  {
			  	if(EXT_GETPIX(MapRight,oil_x[x]+0-160,(oil_y[x]-100)+11)==1)
			  	  oil_y[x]-=1;
			  }//endif in UPPER RIGHT
			  
			
			//MINES +++ MINES +++ MINES +++ MINES
			if((mine_x[x]<160) & (mine_y[x]<95))
			  {
			  	if(EXT_GETPIX(MapLeftUp,mine_x[x],mine_y[x]+5)==1)
			  	  mine_y[x]-=1;
			  }//endif in BOTTOM LEFT
			  
			if((mine_x[x]>=160) & (mine_y[x]<95))
			  {
			  	if(EXT_GETPIX(MapRightUp,mine_x[x]-160,mine_y[x]+5)==1)
			  	  mine_y[x]-=1;
			  }//endif in BOTTOM RIGHT
			  
			if((mine_x[x]<160) & (mine_y[x]>=95))
			  {
			  	if(EXT_GETPIX(MapLeft,mine_x[x],(mine_y[x]-100)+5)==1)
			  	  mine_y[x]-=1;
			  }//endif in UPPER LEFT
			
			if((mine_x[x]>160) & (mine_y[x]>=95))
			  {
			  	if(EXT_GETPIX(MapRight,mine_x[x]-160,(mine_y[x]-100)+5)==1)
			  	  mine_y[x]-=1;
			  }//endif in UPPER RIGHT
			
		}//next x
}	



void MoveLeft()
{
  int x=0;
  
  moving=true;
  
  //does based on current team...
  if(team==TWhite)
  	{ 
  		//makes the worm look left
		  if((white_dir[white_w]!=1) & (white_dir[white_w]!=3)) white_dir[white_w]=1;
		  
		  //TEST CODE
  	  white_x[white_w]-=1;
  	  if(fastwalk) white_x[white_w]-=2;
  	  
  	  white_y[white_w]=white_y[white_w]-15;
  	  for(x=0;x<15;x++)
  	    {
  	    	Gravity(white_w);
  	    	if(lowgrav) Gravity(white_w);
  	    }
  	    

			//makes sure they didnt go off screen
		  if(white_x[white_w]<0) white_x[white_w]=0;
  	}//endif WHITE TEAM
  
  else //if(team==TBlack)
  	{ 
  		//makes the worm look left
		  if((black_dir[black_w]!=1) & (black_dir[black_w]!=3)) black_dir[black_w]=1;
		  
		  //TEST CODE
  	  black_x[black_w]-=1;
  	  if(fastwalk) black_x[black_w]-=2;
  	  
  	  black_y[black_w]=black_y[black_w]-15;
  	  for(x=0;x<15;x++)
  	    {
	  	    Gravity(black_w);
					if(lowgrav) Gravity(white_w);
  	    }
		  //makes sure they didnt go off screen
		  if(black_x[black_w]<0) black_x[black_w]=0;
  	}//endif BLACK TEAM
}


void MoveRight()
{
  int x=0;
  
  moving=true;
  
  if(team==TWhite)
  	{
  		//makes the worm look right
		  if((white_dir[white_w]!=0) & (white_dir[white_w]!=2)) white_dir[white_w]=0;
		  
		  //TEST CODE
  	  white_x[white_w]+=1;
  	  if(fastwalk) white_x[white_w]+=2;
  	  
  	  white_y[white_w]=white_y[white_w]-15;
  	  for(x=0;x<15;x++)
  	    {
  	    	Gravity(white_w);
  	    	if(lowgrav) Gravity(white_w);
  	    }
  	    

			//makes sure they didnt go off screen
		  if(white_x[white_w]>310) white_x[white_w]=310;
  	}//end if WHITE TEAM

  else //if(team==TBlack)
  	{ 
  		//makes the worm look right
		  if((black_dir[black_w]!=0) & (black_dir[black_w]!=2)) black_dir[black_w]=0;
		  
		  //TEST CODE
  	  black_x[black_w]+=1;
  	  if(fastwalk) black_x[black_w]+=2;
  	  
  	  black_y[black_w]=black_y[black_w]-15;
  	  for(x=0;x<15;x++)
  	    {
  	    	Gravity(black_w);
  	    	if(lowgrav) Gravity(black_w);
  	    }
  	    

			//makes sure they didnt go off screen
		  if(black_x[black_w]>310) black_x[black_w]=310;
  	}//end if BLACK TEAM
}


//focuss on the worm..
void FocusWorm(int TheWorm, int teamzor)
{
  if(teamzor==TWhite)
  	{
  		scrolly=white_y[TheWorm]-50;
			scrollx=white_x[TheWorm]-70;
			/*temp=white_x[TheWorm]&7;
			temp=white_x[TheWorm]-temp;
			temp=temp/8;
			scrollx=temp-9;*/
		}
	else //if(teamzor==TBlack)
  	{
  		scrolly=black_y[TheWorm]-50;
  		scrollx=black_x[TheWorm]-70;
			/*temp=black_x[TheWorm]&7;
			temp=black_x[TheWorm]-temp;
			temp=temp/8;
			scrollx=temp-9;*/
		}
		
	if(scrollx<0) scrollx=0;
	else if(scrollx>160) scrollx=160;
	if(scrolly<0) scrolly=0;
	else if(scrolly>100) scrolly=100;
}



//this function acts as a middle man, so that you can call it, instead of having to excute this code each time u want to jump
void Jump()
{
	jtime=0;
	
  if(team==TWhite)
    {
    	jumping=white_w;
    	
    	if((white_dir[white_w]==0) || (white_dir[white_w]==2))
	      JumpRight();
	    else
	      JumpLeft();
	    
	    
    }
  else
    {
    	jumping=black_w;
    	
    	if((black_dir[black_w]==0) || (black_dir[black_w]==2))
	      JumpRight();
	    else
	      JumpLeft();
    }
}

void JumpLeft() //STARTS THE WORM JUMPING LEFT
{
  jdir=-1;
  
	if(team==TWhite)
		white_dir[jumping]=4;
	else
	  black_dir[jumping]=4;
	
	MoveJump();
}

void JumpRight() //STARTS THE WORM JUMPING RIGHT
{
  jdir=1;
	if(team==TWhite)
		white_dir[jumping]=5;
	else
	  black_dir[jumping]=5;
	  
	MoveJump();
}

void MoveJump()
{
  jtime++;
  
  moving=true;
  //if(team==TWhite) FocusWorm(jumping,TWhite);
  //if(team==TBlack) FocusWorm(jumping,TBlack);
  
  if(backflip==false)
  	{
  		if((jtime<15) || (jtime<30 && lowgrav))
				{
					if(team==TWhite) white_y[jumping]-=2;
					else /*if(team==TBlack)*/ black_y[jumping]-=2;
				}
			if(team==TWhite)
			  white_x[jumping]+=jdir;
			if(team==TBlack)
			  black_x[jumping]+=jdir;
			  
  	}//endif NOT BACK FLIP
  	
  if(backflip)
  	{
  		if(jtime<23)
				{
					if(team==TWhite)
						{
						  white_y[jumping]-=2;
						  if(jdir==1) white_dir[jumping]=6;
						  if(jdir==-1) white_dir[jumping]=7;
						}
						
					else //if(team==TBlack)
					  {
					  	black_y[jumping]-=2;
					  	if(jdir==1) black_dir[jumping]=6;
						  if(jdir==-1) black_dir[jumping]=7;
					  }
				}
			if((jtime>18) & (jtime<27))
				{
					if(team==TWhite)
					  {
					    white_x[jumping]+=jdir;
					    if(jdir==1) white_dir[jumping]=8;
						  if(jdir==-1) white_dir[jumping]=9;
					  }
					else //if(team==TBlack)
					  {
					  	black_x[jumping]+=jdir;
					  	if(jdir==1) black_dir[jumping]=8;
						  if(jdir==-1) black_dir[jumping]=9;
					  }
				}
			
			
			if((jtime>22) & (jtime<27))
				{
					if(team==TWhite)
					  {
					    if(jdir==1) white_dir[jumping]=10;
						  if(jdir==-1) white_dir[jumping]=11;
					  }
					else //if(team==TBlack)
					  {
					  	if(jdir==1) black_dir[jumping]=10;
						  if(jdir==-1) black_dir[jumping]=11;
					  }
				}
			if(jtime>26)
				{
					if(team==TWhite)
					  {
					    if(jdir==1) white_dir[jumping]=12;
						  if(jdir==-1) white_dir[jumping]=13;
					  }
					else //if(team==TBlack)
					  {
					  	if(jdir==1) black_dir[jumping]=12;
						  if(jdir==-1) black_dir[jumping]=13;
					  }
				}
			if(jtime>30)
				{
					if(team==TWhite)
					  {
					    if(jdir==1) white_dir[jumping]=6;
						  if(jdir==-1) white_dir[jumping]=7;
					  }
					else //if(team==TBlack)
					  {
					  	if(jdir==1) black_dir[jumping]=6;
						  if(jdir==-1) black_dir[jumping]=7;
					  }
				}
  	}//endif BACK FLIP
}



void EndJump() //ENDS THE JUMPING
{
  ToggleWDir(0);
	jumping=-1;
	backflip=false;
	moving=false;
}


void BackFlip()
{
	jtime=0;
	backflip=true;
	
	 if(team==TWhite)
    {
    	jumping=white_w;
    	
    	if((white_dir[white_w]==0) || (white_dir[white_w]==2))
	      jdir=-1;
	    else
	      jdir=1;
    }
  else
    {
    	jumping=black_w;
    	
    	if((black_dir[black_w]==0) || (black_dir[black_w]==2))
	      jdir=-1;
	    else
	      jdir=1;
    }
  
  MoveJump();
  MoveJump();
}





//reacts accorginly to a cursor click..
void CursorClick()
{
  //after you click, its no loger cursor mode..
  short TheWeap=0;
  GameMode=M_Game;
  
  if(team==TWhite) TheWeap=white_weap;
	else /*if(team==TBlack)*/ TheWeap=black_weap;
	
	while(_keytest(RR_2ND));
	
	if(girdermode)
	  {
	  	MapGirder();
	  	girders--;
	  	if(girders<=0)
	  	  EndWeap(TheWeap);
	  	else
	  	  GameMode=M_Cursor;
	  }
	  
	if((TheWeap==WHoming) || (TheWeap==WHomingP) || (TheWeap==WMagicB))
		{
			xspotx=CursorX;
	  	xspoty=CursorY;
	  	crosshair=true;
	  	xhpos=2;
			XHx=sin(xhpos)*15;
			XHy=cos(xhpos)*15;
			
			crosshair=true;
			if(TheWeap==WHoming) chargew=true;
			charge=0;
		}
		
  else if((TheWeap==WAirStrike) || (TheWeap==WNapStrike) || (TheWeap==WMineStrike) || (TheWeap==WMoleStrike) || (TheWeap==WSheepStrike) || (TheWeap==WCarpet) || (TheWeap==WMailStrike) || (TheWeap==WDonkey) || (TheWeap==WMB))
    {
   	  xspotx=CursorX;
	    xspoty=CursorY;
	    UseWeapon();
    }//endif strike
    
  else if(TheWeap==WTeleport)
 		{
 			if((point(CursorX,CursorY)==0) && (point(CursorX,CursorY-15)==0))
 			  {
 			  	if(team==TWhite)
 			  	  {
 			  	  	white_x[white_w]=CursorX;
 			  	  	white_y[white_w]=CursorY;
 			  	  }
 			  	else //if(team==TBlack)
 			  	  {
 			  	  	black_x[black_w]=CursorX;
 			  	  	black_y[black_w]=CursorY;
 			  	  }
 			  	
 			  }//endif valid tele point
 			  else
 			    GameMode=M_Cursor;
 		}//endif teleport
}





void TextOut(short x, short y, const char *TOutStr)
{
  short z;
  FontSetSys(F_4x6); //makes small font
  
  z=0;
  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE); //draws to the light plane first..
	while(TOutStr[z]!='\0')//whlie its a non null charetar
		{ 
			DrawClipChar (x+(z*4), y+1, TOutStr[z], &(SCR_RECT){{0, 0, 159, 99}}, 1); //disp letter
			z++;
		}//next z
		
  z=0;
  GrayDBufSetHiddenAMSPlane(DARK_PLANE); //draws to the dark plane second..
	while(TOutStr[z]!='\0')//whlie its a non null charetar
		{ 
			DrawClipChar (x+(z*4), y+1, TOutStr[z], &(SCR_RECT){{0, 0, 159, 99}}, 1); //disp letter
			z++;
		}//next z
	
	/*DrawClipLine(&(WIN_RECT){x, y, x+(strlen(TOutStr)*4), y},&(SCR_RECT){{0, 0, 159, 99}},1);
	DrawClipLine(&(WIN_RECT){x, y+6, x+(strlen(TOutStr)*4), y+6},&(SCR_RECT){{0, 0, 159, 99}},1);
	DrawClipLine(&(WIN_RECT){x, y, x, y+6},&(SCR_RECT){{0, 0, 159, 99}},1);
	DrawClipLine(&(WIN_RECT){x+(strlen(TOutStr)*4), y, x+(strlen(TOutStr)*4), y+6},&(SCR_RECT){{0, 0, 159, 99}},1);*/
	
	
	
}

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

void SetExp(short x, short y, short max)
{
	//finds a free explosion
	curre++;
	if(curre>7) curre=0;
	
	//sets up the explosion specified
	exp_x[curre]=x;
	exp_y[curre]=y;
	exp_max[curre]=max;
	exp_t[curre]=0;
}




void GetWeap()
{
  short TheWeap;
	GameMode=M_Game;
	girdermode=false;
	
	TheWeap=((Wx*5)+(Wy));
	if(team==TWhite) white_weap=TheWeap;
	else /*if(team==TBlack)*/ black_weap=TheWeap;
	
	//nulls the target spot
	xspotx=-1;
	xspoty=-1;
	
	//now that it has a weapon, it needs to see what aux mode to go into, ie: cross hair, or maby fully mode, ie: cursor aim.
	if((TheWeap==WBazooka) || (TheWeap==WSheepLaunch) || (TheWeap==WGrenade) || (TheWeap==WCluster) || (TheWeap==WBanana) || (TheWeap==WNinja) || (TheWeap==WSBanana) || (TheWeap==WHolyGrenade) || (TheWeap==WFlame) || (TheWeap==WMolotov))
		{
			XHx=sin(xhpos)*15;
			XHy=cos(xhpos)*15;
			crosshair=true;
			chargew=true;
			charge=0;
		}
	else
	  {
	  	chargew=false;
	  	charge=0;
	  	crosshair=false;
	  }
	
	if((TheWeap==WShotG) || (TheWeap==WHandG) || (TheWeap==WUzi) || (TheWeap==WMiniG) || (TheWeap==WMorter) || (TheWeap==WBow) || (TheWeap==WHoming))
	  {
	  	XHx=sin(xhpos)*15;
			XHy=cos(xhpos)*15;
			crosshair=true;
			chargew=false;
	  	charge=0;
	  }
	
	/*if((TheWeap==WSheep) || (TheWeap==WCows) || (TheWeap==WSkunk) || (TheWeap==WMole))
	  {
	  	IsAnimal=true;
	  }*/
	  
	//if its a weapong with the arrow.. it needs to go into arrow mode..
	if((TheWeap==WHoming) || (TheWeap==WHomingP) || (TheWeap==WAirStrike) || (TheWeap==WNapStrike) || (TheWeap==WMineStrike) || (TheWeap==WMoleStrike) || (TheWeap==WSheepStrike) || (TheWeap==WCarpet) || (TheWeap==WMailStrike) || (TheWeap==WDonkey) || (TheWeap==WTeleport) || (TheWeap==WMB) || (TheWeap==WGirder) || (TheWeap==WGirderPak) || (TheWeap==WMagicB))
	  {
	  	GameMode=M_Cursor;
	  	if(TheWeap==WGirder || TheWeap==WGirderPak)
	  	  {
	  	  	if(TheWeap==WGirder) girders=1;
	  	  	else if(TheWeap==WGirderPak) girders=5;
	  	  	
	  	  	girdermode=true;
	  	  	girder=1;
	  	  }
	  	  
	  	  
	  	if(team==TWhite)
	  	  {
	  	  	CursorX=white_x[white_w];
	  	  	CursorY=white_y[white_w];
	  	  }//endif team white
	  	else //if(team==TBlack)
	  	  {
	  	  	CursorX=black_x[black_w];
	  	  	CursorY=black_y[black_w];
	  	  }//endif team black
	  	xspotx=-1;
	  	xspoty=-1;
	  }
	//currw=TheWeap;
}


void UseWeapon()
{
	short x=0, zWormLeft=0, WormTop=0, WormWeapon=0;

  canfire=false; //a boolean that wont let you fire until shot is over!
  cluster=false;
  
  //makes sure 2nd is not down
  while(_keytest(RR_2ND));
	if(team==TWhite)
		{
			zWormLeft=white_x[white_w];
			WormTop=white_y[white_w];
			WormWeapon=white_weap;
		}//endif white team
	else //if(team==TBlack)
		{
			zWormLeft=black_x[black_w];
			WormTop=black_y[black_w];
			WormWeapon=black_weap;
		}//endif white team
	
	currw=WormWeapon;
	//does stuff for each weapon
	switch(WormWeapon)
	  {
	    case WSwitch:
	      GameMode=M_Select;
	      break;
	    case WSkip:
	      GameMode=M_Select;
	      if(team==TWhite)
	        team=TBlack;
	      else
	        team=TWhite;
	      break;
	    default:
	    	;
	  }//end switch
	
	//TOOLS TOOLS TOOLS TOOLS TOOLS
	// TODO probably add else
	if(currw==WLowG)
	  {
	  	lowgrav=true;
	  	WeapsOff();
	  	return;
	  }
	if(currw==WFastWalk)
	  {
	  	fastwalk=true;
	  	WeapsOff();
	  	return;
	  }
	if(currw==WInvis)
	  {
	  	if(team==TWhite)
	  	  {
	  	  	whiteinvis=true;
	  	  	ToggleTeam();
	  	  	WeapsOff();
	  			return;
	  	  }
	  	else //if(team==TBlack)
	  	  {
	  	  	blackinvis=true;
	  	  	ToggleTeam();
	  	  	WeapsOff();
	  			return;
	  	  }
	  	
	  }  
	
	//SMORE WEAPS!!!
	if(currw==WSBomb)
	  {
	  	SetExp(zWormLeft+3,WormTop+8,15);
	  	ToggleTeam();
	  }
	//sets up animals
	if(currw==WParachute)
	  {
	  	ParaMode=true;
	  	return;
	  }
	  	  
	if(currw==WAirStrike)
		{
			for(x=0;x<5;x++)
			  {
			  	weap_x[x]=xspotx-20 + (x*10);
			  	weap_y[x]=20;
			  	weap_diry[x]=1;
			  	if(CursorDir==1) weap_dirx[x]=2;
			  	else if(CursorDir==0) weap_dirx[x]=-2;
			  	weap_type[x]=WBazooka;
	      	weap_time[x]=30;
			  	weapson=true;
			  	canfire=false;
			  	//turns weapon mode one..
					weapson=true;
					cluster=true;

			  }//next x
		}
	if(currw==WNapStrike)
		{
			for(x=0;x<5;x++)
				{
				  weap_x[x]=xspotx-20 + (x*10);
				  weap_y[x]=20;
				  weap_diry[x]=1;
				  if(CursorDir==1) weap_dirx[x]=2;
				  else if(CursorDir==0) weap_dirx[x]=-2;
				  weap_type[x]=WNapStrike;
		      weap_time[x]=160;
				  weapson=true;
				  canfire=false;
				  //turns weapon mode one..
					weapson=true;
					cluster=true;
						
				}//next x
		}
		if(currw==WMoleStrike)
			{
				for(x=0;x<5;x++)
				  {
				  	weap_x[x]=xspotx-20 + (x*10);
				  	weap_y[x]=20;
				  	weap_diry[x]=1;
				  	if(CursorDir==1) weap_dirx[x]=2;
				  	else if(CursorDir==0) weap_dirx[x]=-2;
				  	weap_type[x]=WMole2;
		      	weap_time[x]=70;
				  	weapson=true;
				  	canfire=false;
				  	//turns weapon mode one..
						weapson=true;
						cluster=true;
						
				  }//next x
			}
		if(currw==WSheepStrike)
			{
				for(x=0;x<5;x++)
				  {
				  	weap_x[x]=xspotx-20 + (x*10);
				  	weap_y[x]=20;
				  	weap_diry[x]=1;
				  	if(CursorDir==1) weap_dirx[x]=2;
				  	else if(CursorDir==0) weap_dirx[x]=-2;
				  	weap_type[x]=WSheepStrike;
		      	weap_time[x]=70;
				  	weapson=true;
				  	canfire=false;
				  	//turns weapon mode one..
						weapson=true;
						cluster=true;
						
				  }//next x
			}
		if(currw==WCarpet)
			{
				for(x=0;x<5;x++)
				  {
				  	weap_x[x]=xspotx-20 + (x*10);
				  	weap_y[x]=20;
				  	weap_diry[x]=1;
				  	if(CursorDir==1) weap_dirx[x]=2;
				  	else if(CursorDir==0) weap_dirx[x]=-2;
				  	weap_type[x]=WCarpet;
		      	weap_time[x]=70;
				  	weapson=true;
				  	canfire=false;
				  	//turns weapon mode one..
						weapson=true;
						cluster=true;
						
				  }//next x
			}
		
		if(currw==WMailStrike)
			{
				for(x=0;x<5;x++)
				  {
				  	weap_x[x]=xspotx-20 + (x*10);
				  	weap_y[x]=20;
				  	weap_diry[x]=1;
				  	if(CursorDir==1) weap_dirx[x]=2;
				  	else if(CursorDir==0) weap_dirx[x]=-2;
				  	weap_type[x]=WMailStrike;
		      	weap_time[x]=70;
				  	weapson=true;
				  	canfire=false;
				  	//turns weapon mode one..
						weapson=true;
						cluster=true;
						
				  }//next x
			}
		if(currw==WMB)
		  {
		  	weap_x[0]=xspotx;
		  	weap_y[0]=20;
		  	weap_diry[x]=1;
		  	weap_dirx[0]=0;
		  	weap_type[0]=WMB;
      	weap_time[0]=70;
		  	weapson=true;
		  	canfire=false;
		  	//turns weapon mode one..
				weapson=true;
				cluster=true;
		  }
		if(currw==WDonkey)
		  {
		  	weap_x[0]=xspotx;
		  	weap_y[0]=20;
		  	weap_diry[x]=1;
		  	weap_dirx[0]=0;
		  	weap_type[0]=WDonkey;
      	weap_time[0]=500;
		  	weapson=true;
		  	canfire=false;
		  	//turns weapon mode one..
				weapson=true;
				cluster=true;
		  }
		
	if((currw==WSheep) || (currw==WCows) || (currw==WSkunk) || (currw==WMole) || (currw==WOldLady) || (currw==WSalArmy) || (currw==WMole))
	  {
	  	weap_x[0]=zWormLeft;
	  	weap_y[0]=WormTop+8;
	  	
	  	if(Facing()==1)
	  	  weap_dirx[0]=-1;
	  	else
	  	  weap_dirx[0]=1;
	  	
	  	//ladies move slower
	  	if((currw==WOldLady) || (currw==WSalArmy))
	  	  {
	  	  	if(Facing()==1)
			  	  weap_dirx[0]=-.5;
			  	else
			  	  weap_dirx[0]=.5;
	  	  }
	  	  
	  	weap_diry[0]=1;
	  	
	  	weap_time[0]=150;
	  	firetime=20;
	  	
	  	if(currw==WCows)
	  	  {
	  	  	firetime=10;
	  	  	cluster=true;
	  	  }
	  	  
	  	
	  	weap_temp=1;
	  	weap_type[0]=currw;
	  }
	  
	if(currw==WBazooka || currw==WSheepLaunch || currw==WHoming || currw==WHomingP || currw==WMorter || currw==WGrenade || currw==WCluster || currw==WBanana || currw==WSBanana || currw==WHolyGrenade  || currw==WMolotov || currw==WShotG || currw==WHandG || currw==WUzi || currw==WMiniG || currw==WBow || currw==WMagicB)
		{
			weap_x[0]=zWormLeft+3;
      weap_y[0]=WormTop+7;
      weap_type[0]=currw;
      weap_time[0]=70;
      firetime=100;
      
      if(currw==WSheepLaunch)
        weap_type[0]=WSheep;
        
      else if(currw==WShotG || currw==WHandG || currw==WUzi || currw==WMiniG || currw==WBow || currw==WMorter)
        charge=15;
      
      else if(currw==WHomingP || currw==WMagicB)
        charge=5;
      
      else if(currw==WHoming) weap_time[0]=20;
      
      //give it the x component
      if(Facing()==0)
        weap_dirx[0]=sin(xhpos)*charge;
      else
        weap_dirx[0]=-(sin(xhpos)*charge);
      
      if(currw==WBow)
        {
        	if(Facing()==1)
		        weap_type[0]=WBowLeft;
		      else
		        weap_type[0]=WBowRight;
        }
        
	        
      //gives it the y componente..
      weap_diry[0]=cos(xhpos)*charge;
      //SetExp(WormLeft,WormTop+7,charge);
		}//end if al thsoe weaps!
	
	if(currw==WDyna || currw==WMingVase)
	  {
	  	weap_x[0]=zWormLeft+3;
      weap_y[0]=WormTop+7;
      weap_type[0]=WormWeapon;
      weap_time[0]=70;
      weap_dirx[0]=0;
      weap_diry[0]=0;
	  }
	
	if(currw==WDrill)
	  {
	  	weap_time[0]=15;
	  	weap_type[0]=WDrill;
	  	LockWorm();
	  }
	//turns weapon mode one..
	weapson=true;
	//makes sure it nologer does anything related to charge.. or just makes it 0..
	charge=0;
}


void MoveWeaps()
{
  short x, WormTop=0, zWormLeft=0;
  static short currb=0;
  
  if(team==TWhite)
		{
			zWormLeft=white_x[white_w];
			WormTop=white_y[white_w];
		}//endif white team
	else //if(team==TBlack)
		{
			zWormLeft=black_x[black_w];
			WormTop=black_y[black_w];
		}//endif white team
										
										
  for(x=0;x<5;x++)
    {
    	if(weap_y[x]!=-1)
    	  {
    	  	if(weap_type[x]==WNapStrike)
						{
					  	weap_dirx[x]=0;
					  	weap_y[x]+=1;	  
					  	weap_time[x]--;
					  	if(weap_time[x]<0)
					  	  TimeExpire(x);
						}
    	  	else if(weap_type[x]==WMailStrike || weap_type[x]==WMB)
    	  	  {
    	  	  	weap_y[x]+=2;
    	  	  	weap_x[x]+=sin(weap_y[x])*5;
    	  	  }
    	  	else if(weap_type[x]==WBazooka || weap_type[x]==WHoming || weap_type[x]==WMorter || weap_type[x]==WGrenade || weap_type[x]==WCluster || weap_type[x]==WBanana || weap_type[x]==WSBanana || weap_type[x]==WHolyGrenade  || weap_type[x]==WMolotov || weap_type[x]==WCluster2 || weap_type[x]==WMing2 || weap_type[x]==WBowLeft || weap_type[x]==WBowRight || weap_type[x]==WMole2 || weap_type[x]==WLady2 || weap_type[x]==WSheepStrike || weap_type[x]==WSheepStrike2 || weap_type[x]==WCarpet || weap_type[x]==WCarpet2 || weap_type[x]==WDonkey)
					  {
					  	weap_x[x]+=weap_dirx[x]/2;
					  	weap_y[x]+=weap_diry[x]/2;
					  	weap_diry[x]+=.5;
					  	if(weap_diry[x]>10) weap_diry[x]=10;
					  	else if(weap_diry[x]<-10) weap_diry[x]=-10;
					  	
					  	weap_time[x]--;
					  	if(weap_time[x]<0)
					  	  TimeExpire(x);

					  	//CamFocus(weap_x[x],weap_y[x]);
					  }//end if its a weapn
					
					else if(weap_type[x]==WDyna || weap_type[x]==WMingVase)
					  {
					  	weap_y[x]+=1;
					  	weap_time[x]--;
					  	if(weap_time[x]<0)
					  	  TimeExpire(x);
					  }
					  
					else if((weap_type[x]==WSheep) || (weap_type[x]==WCows) || (weap_type[x]==WSkunk) || (weap_type[x]==WMole) || (weap_type[x]==WOldLady) || (weap_type[x]==WSalArmy) || (weap_type[x]==WMole))
					  {
					  	weap_x[x]+=weap_dirx[x];
					  	weap_y[x]+=weap_diry[x];
				  		weap_diry[x]+=.5;
					  	if(weap_diry[x]>10) weap_diry[x]=10;
					  	else if(weap_diry[x]<-10) weap_diry[x]=-10;
					  	
					  	weap_time[x]--;
					  	if(weap_time[x]<0)
					  	  TimeExpire(x);
					  	  
			  	    firetime--;
			  	    if(firetime<=0)
			  	      {
			  	      	if((weap_type[x]==WSheep) || (weap_type[x]==WSkunk))
			  	      	  {
			  	      	  	firetime=25;
			  	      			weap_diry[x]+=-2;
			  	      	  }

			  	      	if(weap_type[x]==WCows)
			  	      	  {
			  	      	  	weap_x[weap_temp]=zWormLeft;
									  	weap_y[weap_temp]=WormTop+8;
									  	
									  	weap_type[weap_temp]=WCows;
									  	
									  	if(Facing()==1)
									  	  weap_dirx[weap_temp]=-1;
									  	else
									  	  weap_dirx[weap_temp]=1;
									  	
									  	weap_diry[weap_temp]=1;
									  	
									  	weap_time[weap_temp]=150;
									  	firetime=20;
									  	
									  	weap_temp++;
									  	if(weap_temp>4) firetime=9000;
			  	      	  }
			  	      }//endif firetime expire
					  }
	  
					//printf_xy(1,1,"%d  %d",weap_type[x], WUzi);
				  else if(weap_type[x]==WHoming2 || weap_type[x]==WHomingP || weap_type[x]==WMagicB)
				    {
				    	weap_time[x]--;
				    	if(weap_time[x]<0)
					  	  TimeExpire(x);
				    	if(weap_x[x]<xspotx+4)
				    	  weap_x[x]+=2;
				    	else if(weap_x[x]>xspotx+4)
				    	  weap_x[x]-=2;
				    	if(weap_y[x]<xspoty+9)
				    	  weap_y[x]+=2;
				    	else if(weap_y[x]>xspoty+9)
				    	  weap_y[x]-=2;
				    }
				    
					else if(weap_type[x]==WShotG || weap_type[x]==WHandG || weap_type[x]==WUzi || weap_type[x]==WMiniG || weap_type[x]==WFlame)
					  {
					  	weap_x[x]+=weap_dirx[x]/2;
					  	weap_y[x]+=weap_diry[x]/2;
					  	
					  	
					  	if(weap_type[x]==WUzi || weap_type[x]==WMiniG)
					  	  {	
					  	  	firetime--;
					  	  	
					  	  	if(firetime<0)
					  	      EndGun();
					  	      
					  	    if(firetime%5==0)
					  	      {
					  	      	currb++; //gets next free bullet
					  	      	if(currb>4)
					  	      	  currb=0;
					  	      	  
					  	      	weap_x[currb]=zWormLeft+5;
								      weap_y[currb]=WormTop+15;
								      weap_type[currb]=WUzi;
								        
								      //give it the x component
								      if(Facing()==0)
								        weap_dirx[currb]=sin(xhpos)*15;
								      else
								        weap_dirx[currb]=-(sin(xhpos)*15);
								      
								      //gives it the y componente..
								      weap_diry[currb]=cos(xhpos)*15;
					  	      }//endif new bullet
					  	  }//endif uzi or minigun
					  }
    	  }//endif on screen
			else if(weap_type[x]==WDrill)
			  {
			  	short z;
			  	for(z=0;z<12;z++)
			  	{
			  	  pointoff(zWormLeft+z-6,WormTop+16);
			  	  pointoff(zWormLeft+z-6,WormTop+15);
			  	  pointoff(zWormLeft+z-6,WormTop+14);
			  	  pointoff(zWormLeft+z-6,WormTop+13);
			  	  pointoff(zWormLeft+z-6,WormTop+12);
			  	  pointoff(zWormLeft+z-6,WormTop+11);
			  	  pointoff(zWormLeft+z-6,WormTop+10);	
			  	}
			  	SetWorm();
			  	
			  	orgy++;
			  	
			  	CamFocus(zWormLeft, WormTop);
			  	
			  	//lowers time
			  	weap_time[x]--;
		    	if(weap_time[x]<0)
			  	  TimeExpire(x);
			  }//endif drill
    }//next x
	
	//test to see if the weapon went off screen..
	for(x=0;x<5;x++)
	  {
	  	if((weap_x[x]<-10) || (weap_x[x]>320) || (weap_y[x]>200))
	  	  {
	  	  	//weap_x[x]=-1;
	  	  	//weap_y[x]=-1;
	  	  	if(weap_type[x]==WNapStrike) continue;
	  	  	
	  	  	EndWeap(x);
	  	  }//nulls the weap
	  }//next x
	
	//test to see if the weapon has hit the map..
	for(x=0;x<5;x++)
		{
			if(weap_y[x]!=-1)
			  {
			  	if(
			  	    (point(weap_x[x],weap_y[x]))
			  	    ||
			  	    (point(weap_x[x]-3,weap_y[x]-3))
			  	    ||
			  	    (point(weap_x[x]-3,weap_y[x]+3))
			  	    ||
			  	    (point(weap_x[x]+3,weap_y[x]-3))
			  	    ||
			  	    (point(weap_x[x]+3,weap_y[x]+3))
			  	  )
			  	  WeapCollide(x);
			  }//endif weapon is onscreen
		}//next x
	
}




void WeapCollide(short weap)
{
  short x;
  if(weap_type[weap]==WMolotov)
  	{
  		for(x=1;x<5;x++)
				{
				  weap_diry[x]=0;
				  weap_dirx[x]=0;
				  weap_type[x]=WNapStrike;
		      weap_time[x]=100;
				  weapson=true;
				  canfire=false;
				  //turns weapon mode one..
					weapson=true;
					cluster=true;
						
				}//next x

				weap_x[1]=weap_x[0]-8;
				weap_x[2]=weap_x[0];
				weap_x[3]=weap_x[0]-8;
				weap_x[4]=weap_x[0];
				
				weap_y[1]=weap_y[0];
				weap_y[2]=weap_y[0];
				weap_y[3]=weap_y[0]+6;
				weap_y[4]=weap_y[0]+6;
				
				weap_x[0]=-1;
				weap_y[0]=-1;
				weap_type[0]=0;
				
				SetExp(weap_x[weap],weap_y[weap],5);
  	}
  else if(weap_type[weap]==WDonkey)
    {
    	SetExp(weap_x[weap],weap_y[weap],15);
    	weap_diry[weap]=-5;
    	ToggleTeam();
    	return;
    }
  else if(weap_type[weap]==WNapStrike)
	  {
	  	//short x;
	  	//for(x=0;x<5;x++)
	  	  weap_y[weap]-=.8;
	  	  
	  	SetExp(weap_x[weap]+random(4)-5,weap_y[weap]+2,random(2)+1);
	  	SetExp(weap_x[weap]+random(4)-5,weap_y[weap]+2,random(2)+1);
	  	SetExp(weap_x[weap]+random(4)-5,weap_y[weap]+2,random(2)+1);	
			return;
	  }
	  
  else if((weap_type[weap]==WSheep) || (weap_type[weap]==WCows) || (weap_type[weap]==WSkunk) || (weap_type[weap]==WMole) || (weap_type[weap]==WOldLady) || (weap_type[weap]==WSalArmy) || (weap_type[weap]==WMole))
	  {
	  	weap_diry[weap]=0;
	  	if(weap_dirx[weap]<0)
	  	  weap_dirx[weap]=-1;
	  	else
	  	  weap_dirx[weap]=1;	
	  }
	else if(weap_type[weap]==WMole2)
	  {
	  	SetExp(weap_x[weap],weap_y[weap],3);
	  }
	else if(weap_type[weap]==WBazooka || weap_type[weap]==WHoming || weap_type[weap]==WHoming2 || weap_type[weap]==WMing2 || weap_type[weap]==WMailStrike || weap_type[weap]==WSheepStrike2 || weap_type[weap]==WMagicB || weap_type[weap]==WCarpet2)
	  {
      SetExp(weap_x[weap],weap_y[weap],10);
      if(cluster)
        {
        	EndWeap(weap);
        	ToggleTeam();
        	return;
        }
      
			CamFocus((int)weap_x[weap],(int)weap_y[weap]);
			LockCam();
			EndWeap(weap);
	  }
	  
	else if(weap_type[weap]==WSheepStrike || weap_type[weap]==WCarpet)
	  {
	  	//simply bounces the sheep or whatever
	  	if(point(weap_x[weap]+3,weap_y[weap])) 
	  	  {
	  	  	weap_dirx[weap]*=-1;
	  	  	weap_dirx[weap]*=.7;
	  	  	weap_dirx[weap]*=.9;
	  	  	
	  	  }
	  	if(point(weap_x[weap]-3,weap_y[weap]))
	  	  {
	  	  	weap_dirx[weap]*=-1;
	  	  	weap_dirx[weap]*=.7;
	  	  	weap_diry[weap]*=.9;
	  	  }
	  	if(point(weap_x[weap],weap_y[weap]+3))
	  	  {
	  	  	weap_diry[weap]*=-1;
	  	  	weap_diry[weap]*=.7;
	  	  	weap_dirx[weap]*=.9;
	  	  }
	  	if(point(weap_x[weap],weap_y[weap]-3))
	  	  {
	  	  	weap_diry[weap]*=-1;
	  	  	weap_diry[weap]*=.7;
	  	  	weap_dirx[weap]*=.9;
	  	  }
	  	  
      SetExp(weap_x[weap],weap_y[weap],8);
      
      if(weap_type[weap]==WSheepStrike)
      	weap_type[weap]=WSheepStrike2;
      else
        weap_type[weap]=WCarpet2;
	  }
	  
	else if(weap_type[weap]==WCluster2 || weap_type[weap]==WShotG || weap_type[weap]==WHandG || weap_type[weap]==WUzi || weap_type[weap]==WMiniG)
	  {
      SetExp(weap_x[weap],weap_y[weap],4);
      //weap_y[weap]=-1;
      LockCam();
			//CamFocus(weap_x[weap],weap_y[weap]);
			EndWeap(weap);
	  }
	else if(weap_type[weap]==WLady2 || weap_type[weap]==WMB)
	  {
      SetExp(weap_x[weap],weap_y[weap],10);
      LockCam();
			EndWeap(weap);
	  }
	else if(weap_type[weap]==WMorter)
	  {
	  	SetExp(weap_x[weap],weap_y[weap],10);
			CamFocus(weap_x[weap],weap_y[weap]);
			SetCluster(weap_x[weap],weap_y[weap],WMorter);
			LockCam();
	  }
	else if(weap_type[weap]==WGrenade || weap_type[weap]==WCluster || weap_type[weap]==WBanana || weap_type[weap]==WSBanana || weap_type[weap]==WHolyGrenade  || weap_type[weap]==WMolotov)
	  {
	  	//simply bounces it..
	  	if(point(weap_x[weap]+3,weap_y[weap])) 
	  	  {
	  	  	weap_dirx[weap]*=-1;
	  	  	weap_dirx[weap]*=.7;
	  	  	weap_dirx[weap]*=.9;
	  	  	
	  	  }
	  	if(point(weap_x[weap]-3,weap_y[weap]))
	  	  {
	  	  	weap_dirx[weap]*=-1;
	  	  	weap_dirx[weap]*=.7;
	  	  	weap_diry[weap]*=.9;
	  	  }
	  	if(point(weap_x[weap],weap_y[weap]+3))
	  	  {
	  	  	weap_diry[weap]*=-1;
	  	  	weap_diry[weap]*=.7;
	  	  	weap_dirx[weap]*=.9;
	  	  }
	  	if(point(weap_x[weap],weap_y[weap]-3))
	  	  {
	  	  	weap_diry[weap]*=-1;
	  	  	weap_diry[weap]*=.7;
	  	  	weap_dirx[weap]*=.9;
	  	  }
	  	return;
	  }
	else if(weap_type[weap]==WBowLeft || weap_type[weap]==WBowRight)
	  {
	  	MapArrow(weap_type[weap], weap_x[weap], weap_y[weap]);
	  	EndWeap(weap);
	  }
	else if((weap_type[weap]==WCows) || (weap_type[weap]==WSheep) || (weap_type[weap]==WSkunk) || (weap_type[weap]==WMole) || (weap_type[weap]==WOldLady) || (weap_type[weap]==WSalArmy) || (weap_type[weap]==WMole))
	  {
	  	if((point(weap_x[weap]-3,weap_y[weap])) || (point(weap_x[weap]+3,weap_y[weap])))
	  	  {
	  	  	if(weap_dirx[weap]==-1)
	  	  	  weap_dirx[weap]=1;
	  	  	else
	  	  	  weap_dirx[weap]=-1;
	  	  }//endif right or left
	  	return;
	  }//endif its a cow
	  
	ToggleTeam();
}



//if a weapons fuse ends..
void TimeExpire(short weap)
{
	if(weap_type[weap]==WGrenade)
		{
			SetExp(weap_x[weap],weap_y[weap],10);
			weapson=false;
			canfire=true;
			MsgBox("Boom","Grenade Exploded");
		}
	else if(weap_type[weap]==WBanana)
		{
			SetExp(weap_x[weap],weap_y[weap],17);
			weapson=false;
			canfire=true;
		}
	else if(weap_type[weap]==WHolyGrenade || weap_type[weap]==WDyna || weap_type[weap]==WSkunk || weap_type[weap]==WSheep || weap_type[weap]==WOldLady)
		{
			SetExp(weap_x[weap],weap_y[weap],15);
			weapson=false;
			canfire=true;
		}
	else if(weap_type[weap]==WMingVase)
		{
			SetExp(weap_x[weap],weap_y[weap],15);
			SetCluster(weap_x[weap],weap_y[weap],WMingVase);
		}
	else if(weap_type[weap]==WCluster)
		{
			SetExp(weap_x[weap],weap_y[weap],5);
			SetCluster(weap_x[weap],weap_y[weap],WCluster);
		}
  else if(weap_type[weap]==WSalArmy)
    {
    	SetExp(weap_x[weap],weap_y[weap],15);
			SetCluster(weap_x[weap],weap_y[weap],WSalArmy);
    }
	else if(weap_type[weap]==WSBanana)
		{
			SetExp(weap_x[weap],weap_y[weap],15);
			SetCluster(weap_x[weap],weap_y[weap],WSBanana);
		}
  else if(weap_type[weap]==WHoming)
		{
			weap_type[weap]=WHoming2;
			weap_time[weap]=40;
			return;
		}
  else if(weap_type[weap]==WHoming2 || weap_type[weap]==WHomingP || weap_type[weap]==WMagicB)
		{
			SetExp(weap_x[weap],weap_y[weap],10);
			weapson=false;
			canfire=true;
		}
  else if(weap_type[weap]==WCows)
    {
    	SetExp(weap_x[weap],weap_y[weap],12);
      //weap_y[weap]=-1;
      LockCam();
			//CamFocus(weap_x[weap],weap_y[weap]);
			EndWeap(weap);
    }
  else if(weap_type[weap]==WNapStrike)
    {
      //LockCam();
      weap_y[weap]=-1;
			//CamFocus(weap_x[weap],weap_y[weap]);
			EndWeap(weap);
    }
  else if(weap_type[weap]==WMole)
    {
    	weap_type[weap]=WMole2;
			weap_time[weap]=40;
			weap_diry[weap]=-5;
			return;
    }
  else if(weap_type[weap]==WMole2)
    {
    	SetExp(weap_x[weap],weap_y[weap],12);
      //weap_y[weap]=-1;
      LockCam();
			//CamFocus(weap_x[weap],weap_y[weap]);
			EndWeap(weap);
    }
  else if(weap_type[weap]==WDrill)
    {
    	weapson=false;
			canfire=true;
			EndWeap(weap);
			UnLockWorm();
    }
  //nulls the dead weapon
  weap_y[weap]=-1;
  LockCam();
  
  ToggleTeam();
}


void SetCluster(short x, short y, short type)
{
	short z;
  cluster=true;
	for(z=0;z<5;z++)
		{
			weap_x[z]=x;
			weap_y[z]=y-2;
			
			weap_diry[z]=-4.5;
			weap_dirx[z]=2-z;
			
			if(type==WSBanana)
			  weap_type[z]=WBanana;
			else if(type==WCluster)
			  weap_type[z]=WCluster2;
		  else if(type==WMingVase)
		    weap_type[z]=WMing2;
		  else if(type==WSalArmy)
		    weap_type[z]=WLady2;
		  else if(type==WMorter)
		    {
		    	weap_type[z]=WCluster2;
		    	weap_diry[z]=1;
		    	weap_dirx[z]*=.5;
		    }
			weap_time[z]=50;
		}//next z
	
	//MoveWeaps();
	//MoveWeaps();
  
}

short ClusterOver()
{
	if(weap_y[0]==-1 && weap_y[1]==-1 && weap_y[2]==-1 && weap_y[3]==-1 && weap_y[4]==-1)
	  return 1;
	else
	  return 0;

}

void LockCam()
{
	LockX=scrollx;
	LockY=scrolly;
	LockTime=30;
	Lock=true;
}

void EndWeap(short weap)
{
  if(weap_type[weap]==WUzi || weap_type[weap]==WMiniG) return;
  
  weap_y[weap]=-1;
  weap_x[weap]=-1;
  
  if(weap_type[weap]==WNapStrike)
    {
    	weapson=false;
			canfire=true;
			cluster=false;
    }
	if(((cluster) && (ClusterOver())) || (cluster==false))
		{
	  	weapson=false;
			canfire=true;
	  }
	//if(cluster==false) ToggleTeam();
}

void WeapsOff()
{
	weapson=false;
	canfire=true;
	cluster=false;
}

void EndGun()
{
	short x;
	for(x=0;x<5;x++)
	  {
	  	weap_x[x]=-1;
	  	weap_y[x]=-1;
	  }
	weapson=false;
	canfire=true;
	ToggleTeam();
	
}

void MapArrow(short dir, short x, short y)
{
  unsigned char *map=MapLeft;
  
  if((x<160) && (y<100)) map=MapLeftUp;
  if((x>=160) && (y<100)) map=MapRightUp;
  if((x<160) && (y>=100)) map=MapLeft;
  if((x>=160) && (y>=100)) map=MapRight;
  
  if(x>160) x-=160;
  if(y>100) y-=100;
  
	if(dir==WBowRight)
	  ClipSprite8_OR_R(x, y-3, 3, ArrowRight, map);
	else
	  ClipSprite8_OR_R(x, y-3, 3, ArrowLeft, map);
}

void SecondWeap()
{
  short x;
	for(x=0;x<5;x++)
	  {
	  	//does early whatever for each type..
	  	if(weap_type[x]==WSBanana || weap_type[x]==WSheep || weap_type[x]==WDrill || weap_type[x]==WMole || weap_type[x]==WMole2 || weap_type[x]==WSalArmy)
	  	  weap_time[x]=0;
	  	if(weap_type[x]==WSBanana && currw==WSBanana)
	  	  weap_time[x]=0;
	  }//next x
	while(_keytest(RR_2ND));
}


void LockWorm()
{
  if(team==TWhite)
		{
			orgx=white_x[white_w];
			orgy=white_y[white_w];
		}//endif white team
	else //if(team==TBlack)
		{
			orgx=black_x[black_w];
			orgy=black_y[black_w];
		}//endif white team
	WormLock=true;
}

void SetWorm()
{
  if(WormLock==false) return;
  if(team==TWhite)
		{
			white_x[white_w]=orgx;
			white_y[white_w]=orgy;
		}//endif white team
	else //if(team==TBlack)
		{
			black_x[black_w]=orgx;
			black_y[black_w]=orgy;
		}//endif white team
}

void UnLockWorm()
{
	WormLock=false;
	
}

void ToggleTeam()
{
  //if the team has already been changed or a cluser is still in progress, then dont change again until the user moves the worm...
  if(changed || ClusterOver==false) return;

	lowgrav=false;
  fastwalk=false;

  //toggles team, and test it to select mode...
  if(team==TWhite)
  	team=TBlack;
  else
  	team=TWhite;
  	
  //sets game mode to select..
  GameMode=M_Select;
  
  if(team==TWhite)
    whiteinvis=false;
  else //if(team==TBlack)
    blackinvis=false;
  
  if(team==TWhite)
		{
			white_w++;
			if(white_w>=maxworms)
				white_w=0;
			//FocusWorm(white_w,TWhite);
		}//endif WHITE TEAM
	else //if(team==TBlack)
		{
			black_w++;
			if(black_w>=maxworms)
				black_w=0;
			//FocusWorm(black_w,TBlack);
		}//endif BLACK TEAM
		
  changed=true;
}
