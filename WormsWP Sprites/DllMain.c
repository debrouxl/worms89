// C Source File
// Created 1/15/2004; 3:03:22 PM

#include <tigcclib.h>
#include "extgraph.h"

//Tis a DLL
#ifdef DO_DLL
DLL_INTERFACE
#endif

#include "Sprites.c"

//definaitions / vabiables GO HERE!!
//ALOT OF VARIABLE DEFINITIONS
short white_x[8],white_y[8],white_h[8],white_dir[8],white_w,white_weap,whiteinvis; //WHITE WORM X POSIOTONS< WW Y POSITIONS, WW HEALTH, WHITE_DIR: WHAT POSITION IS THE WORM IN? WHITE_W = WHITE WHITE WORMS TURN IS IT? (CONTROLL WITCH WW), WHITE_WEAP: WHAT WEAPON IS WHITE TEAM USING \ USED? WHITEINIS: BOOLEAN, IS THIS TEAM INVISIBLE?
short black_x[8],black_y[8],black_h[8],black_dir[8],black_w,black_weap,blackinvis; //BASICALLY THE SAME DEAL FOR BLACK
short crate_x[15],crate_y[15],crate_type[15]; //REMEMVERS THE X,Y POS OF THE INGAME CRATES AND WHAT TYPE THEY ARE, 15 PER GAME, MAX
short mine_x[10],mine_y[10],oil_x[8],oil_y[8],exp_x[8],exp_y[8],exp_t[8],exp_max[8],curre; //SAVES X,Y POS OF MINES, OIL BARROLS, EXPLOSIONS. exp_t: THE FRAME OF ANIMATION FOR THE EXPLOSTION, exp_max: THE BIGGEST RADIUS OF THE EXPOSION BEFORE IT DISAPREARS, curre: THE CURRECNT EXPLOSION BEING DETONATED \ DRAWN \ WHATEVER
short weap_type[5],weap_time[5]; //THE TYPES OF WEAPONS ACTIVE ON SCREEN (UP TO 5 ROCKETS, COWS, CLUSTERS ETC CAN BE IN GAME AT ONCE) AND THE TIME OF EACH (IE: FUSE LENTH)
float weap_x[5],weap_y[5],weap_dirx[5],weap_diry[5]; //SAVES THE X,Y POS OF EACH OF THE 5 WEAPONS< AS WELL AS ITS DIRX AND DIRY WHICH ARE ITS HORIAZONTAL AND VERICAL COMPONENTS. THE GAME REMEMBERS THESES INSTEAD OF A VECTOR, THIS WAY I CAN AVOID THE SLOW SIN CALCULATION OF TIGCC
short GameMode,team,maxworms,jumping,jtime,jdir,backflip,moving,crosshair,XHx,XHy,xspotx,xspoty,CursorDir,CursorX,CursorY,weapson,currw,chargew,charge,canfire,cluster,firetime; //WAY TO MUCH TO EXPLAIN IN ONE LINE, DETIALS COMMING SOON
short Wx=0,Wy=0; //for the current weapong selection in the weapon screen
short LockX,LockY,LockTime,Lock; //THE X,Y POS THE CAMERA IS LOCKED AT, and HOW LONG ITS LOCKED UNTIL YOU CAN USE IT AGAIN and THE BOOLEAN IF ITS LOCKED OR NOT
void *GblDBuffer; //GLOBAL DOUBLE BUFFER
float xhpos; //xh=crosshair, so this is the CROSSHAIR POSITION, more specifically, the THETA of its rotationg
int girder, girdermode, girders; //girder: I FORGET, girdermode: IS THE USER PLACEING GIRDERS? THIS IS A BOOLEAN. girders: I FORGET =(
short ParaMode, Falling, lowgrav, fastwalk; //ParaMode: BOOLEAN: ARE YOU PARACHUTING? Falling: BOOLEAN: ARE YOU FALLING? lowgrav: BOOLEAN: IS LOWGRAVITY ON? fastwalk: BOOLEAN: IS FASTWALK ENABLED?
short WeaponSet[5][14]={ //HOW MANY OF EACH WEAPON DO YOU HAVE? LIST IS SET UP IDENTICALLY TO HOW IT IS ON THE SCREEN / WWP WEAPON MENU. FOR NOW ITS DEFAULT TO THE VALUES BELOW
	{0,9,9,9,9,1,1,3,5,0,2,0,9,1},
	{0,1,3,9,9,2,1,3,2,0,1,0,9,1},
	{0,5,0,9,1,1,0,3,2,0,0,0,3,1},
	{0,0,2,0,0,0,0,1,2,0,0,0,0,1},
	{0,0,0,2,9,0,0,0,0,0,0,0,0,1}};
static const char directions[14] = {0, 1,  0, 1, 1, 0,  1, 0, 1, 0,  1, 0, 1, 0};

//THE MAP VARZ!!
short scrollx,scrolly; //WHERE IS THE MAP SCROLLED TO?
//THE MAP IS COMPOSED OF FOUR CORNERS: LEFT RIGHT UP and DOWN
char * MapLeft;
char * MapRight;
char * MapLeftUp;
char * MapRightUp;
char MapDummy[1];


//FUNCTION DECLARATIONS
static void DrawWorms(); //Draw the worms
//Usualy used for calculating "min"
static __attribute__((regparm)) int fixs(int ToFix)
{
	return (ToFix-(ToFix&7))>>3;
}
static int Facing(); //returns if the worms are facing left or right
static void DllGrayOn(); //turns grayscale on within the dll
static void SetMapBuffers(char * Maps)
{
  MapLeft = Maps;
  MapRight = MapLeft + LCD_SIZE;
  MapLeftUp = MapRight + LCD_SIZE;
  MapRightUp = MapLeftUp + LCD_SIZE;
}
static void CamFocus(int x, int y); //sets the camera to look at x,y
static void CamFocus2(short x, short y); //basically the same thing
static void CamFocusY(int y); //sets just the cameras vertical position
static void MapGirder(); //places a grider on the map (makes it part of the map)

//draw funcs
static void DrawMap(); //draws the map
static void DrawMap2(); //draws the map
static void DrawChunk(void *mem, void *out, short width, short height, short xout, short xin, int yout, int yin); //draws a peice of the map
static void DrawChunk2(void *mem, void *out, short width, short height, short xout, int yout, int yin); //draws a peice of the map
static void DrawSel(); //draws the selection cursor over the worms head
//void DrawWorms();
static void DrawObjects(); //draws ingame random objects
static void DrawWaves(); //draws the waves at the bottom of the screens
static void DrawWeaps(); //draws the weapon selection menu
static void DrawXHair(); //draws the cross hair for aiming a weapon
static void DrawCursor(); //draws the mouse-arrow currsor for air strikes, teleport, etc..
static void DrawXSpot(); //draws the "X" marks the spot x for airstrikes and such
static void DrawExp(); //draws the ring of fire in an explosions
static void DrawCharge(); //draws the weapon charge meter at the top of the screen (for holding power on weaps like bazooka)
static void DrawWeap(); //draws the weapon you fired (ie: cows, a rockect, a grenade, etc..)
static void drawgfx(); //the main grafix drawing routing
static void DllGrayOff(); //turns grayscale off from within the dll
static void DrawCake(); //draws the loading map cake, (doesnt work for somereason or another)
static void DrawNumber(short x, short y, int num); //unfinish, was supposed to draw a number for the health above a worms head

//CONSTANTS
#define false 0
#define true 1
#define TWhite 0
#define TBlack 1

enum GameModes {M_Select, M_Game, M_Weapon, M_Cursor}; //THE DIFFERENT MODES THE GAME OPERATES IN, M_Select: choose a worm to play with. M_Game: game play. M_Weapon: choose a weapon. M_Cursor: move the arrow
enum Weapons {WJetPack, WLowG, WFastWalk, WLaser, WInvis, WBazooka, WHoming, WMorter, WHomingP, WSheepLaunch, WGrenade, WCluster, WBanana, WAxe, WQuake, WShotG, WHandG, WUzi, WMiniG, WBow, WPunch, WDragonBall, WDeath, WSBomb, WProd, WDyna, WMine, WSheep, WSSheep, WMole, WAirStrike, WNapStrike, WMailStrike, WMineStrike, WMoleStrike, WBlow, WDrill, WGirder, WBaseball, WGirderPak, WNinja, WBungee, WParachute, WTeleport, WScales, WSBanana, WHolyGrenade, WFlame, WSalArmy, WMB, WMolotov, WSkunk, WMingVase, WSheepStrike, WCarpet, WCows, WOldLady, WDonkey, WNuke, WGeddon, WSkip, WSurrender, WSwitch, WIce, WMagicB, WCluster2, WMing2, WBowLeft, WBowRight, WHoming2, WMole2, WLady2, WSheepStrike2, WBatLeft, WBatRight, WCarpet2}; //handy weapons enumeration


//generic dll junk
#ifdef DO_DLL
DLL_ID 593223953
DLL_VERSION 1,0
//the some 220 variables i export!
DLL_EXPORTS  Wave1, Wave2, Wave3, Wave1I, Wave2I, Wave3I, CandleCake, CandleCake2, WormRight, WormLeft, WormRightI, WormLeftI, WormRight2, WormLeft2, WormRight2I, WormLeft2I, WormRightJump, WormLeftJump, WormRightJumpI, WormLeftJumpI, WormRightJump2, WormLeftJump2, WormRightJump2I, WormLeftJump2I, WormRightU, WormLeftU, WormRightUI, WormLeftUI, WormLeftSideU, WormRightSideU, WormLeftSideUI, WormRightSideUI, WormRightSide, WormLeftSide, WormRightSideI, WormLeftSideI, WormHammer, WormHammerI, Rot1, Rot2, Rot3, Rot4, Oil, OilI, Health, Crate, CrateI, Toolz, ToolzI, Mine, MineI, Weapons1, Weapons2, Weapons3, Weapons4, Weapons5, SelBox, XHair, CursorLeft, CursorLeftI, CursorRight, CursorRightI, XSpot, XSpotI, Banana, BananaI, Banana2, Banana2I, Dynamite, DynamiteI, Molotov, MolotovI, Radio, RadioI, MingVase, MingVaseI, Rocket, RocketI, ShotGLeft, ShotGLeftI, ShotGRight, ShotGRightI, HandGLeft, HandGLeftI, HandGRight, HandGRightI, UziLeft, UziLeftI, UziRight, UziRightI, MiniGLeft, MiniGLeftI, MiniGRight, MiniGRightI, BowLeft, BowLeftI, BowRight, BowRightI, FlameLeft, FlameLeftI, FlameRight, FlameRightI, Grenade, GrenadeI, HolyG, HolyGI, Bat, BatI, Axe, AxeI, Ninja, NinjaI, Flag, FlagI, BlowLeft, BlowLeftI, BlowRight, BlowRightI, JetRight, JetRightI, JetLeft, JetLeftI, Bazook, Ming2, Bullet, ArrowLeft, ArrowRight, white_x, white_y, white_h, white_dir, &white_w, &white_weap, black_x, black_y, black_h, black_dir, &black_w, &black_weap, crate_x, crate_y, crate_type, mine_x, mine_y, oil_x, oil_y, exp_x, exp_y, exp_t, exp_max, &curre, weap_type, weap_time, weap_x, weap_y, weap_dirx, weap_diry, &GameMode, &team, &maxworms, &jumping, &jtime, &jdir, &backflip, &moving, &crosshair, &XHx, &XHy, &xspotx, &xspoty, &CursorDir, &CursorX, &CursorY, &weapson, &currw, &chargew, &charge, &canfire, &cluster, &firetime, &Wx, &Wy, &LockX, &LockY, &LockTime, &Lock, &xhpos, MapDummy, MapDummy, MapDummy, MapDummy, &scrollx, &scrolly, DrawWorms, fixs, Facing, DllGrayOn, DrawMap, DrawMap2, DrawChunk, DrawChunk2, DrawSel, DrawObjects, DrawWaves, DrawWeaps, DrawXHair, DrawCursor, DrawXSpot, DrawExp, DrawCharge, DrawWeap, CamFocus, drawgfx, DllGrayOff, DrawCake, &girder, &girdermode, &girders, &MapGirder, &ParaMode, &Falling, &lowgrav, &fastwalk, &whiteinvis, &blackinvis, WeaponSet, SetMapBuffers, directions

//And here we go...
DLL_IMPLEMENTATION
//DLL CODE GOES HERE
#endif


//DRAWS THE WORMS
void DrawWorms()
{
  int x,min=0; //looping var, min is some sort of offset variable to make sure the sprite is in the right place, it has to do with the way the map scrolls, making sure the worms dont move in blocks, IM for help on this if you need it, min shows up alot
  short zWormLeft=0, WormTop=0, WormWeapon=0;
  void * lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void * dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
  short xcoord;
  short ycoord;

	for(x=0;x<maxworms;x++)
		{
	  	//makes sure its the correct min (
		  min=(scrollx&7);
      
      
      //IF THE PARACHUTE IS BEING USED, DRAW IT OVER THE CURRENT WORMS HEAD
      if((Falling) && (ParaMode))
        {
        	if(team==TWhite) //if its the white team, draw parachut over the whities
        	  {//extgraph spriteage
        	  	GrayClipSprite16_OR_R(white_x[white_w] - (fixs(scrollx) * 8) - 6 - min, white_y[white_w] - scrolly - 10, 9, Chute, Chute, lplane, dplane);
        	  }
        	else //else draw it over the blackies
        	  {//extgraph spriteage
        	  	GrayClipSprite16_OR_R(black_x[black_w] - (fixs(scrollx) * 8) - 6 - min, black_y[black_w] - scrolly - 10, 9, Chute, Chute, lplane, dplane);
        	  }
        	
        }
      
      if(whiteinvis) goto drblack; //if the team is invisible, dont draw them!
	  	//drwas the worms
	  	//if(((white_w!=x) & (team==TWhite)) || (team==TBlack)) TextOut(white_x[x]-(fixs(scrollx)*8)-5-min,white_y[x]-scrolly-8,"100");
	  	//WHAT POSITION IS THE WORM IN? JUMPING? BACKFLIP? WALKING? white_dir holds this info, and thus we draw it
	  	xcoord = white_x[x] - (fixs(scrollx) * 8) - 5 - min;
	  	ycoord = white_y[x] - scrolly + 1;
	  	if(white_dir[x]==0)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormRightI, WormRight, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==1)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormLeftI, WormLeft, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==2)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormRight2I, WormRight2, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==3)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormLeft2I, WormLeft2, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==4)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormLeftJumpI, WormLeftJump, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==5)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormRightJumpI, WormRightJump, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==6) //straight jump left
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormLeftJump2I, WormLeftJump2, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==7) //straight jump right
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormRightJump2I, WormRightJump2, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==8) //on side, left up
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormLeftSideUI, WormLeftSideU, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==9) //on side, right up
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormRightSideUI, WormRightSideU, lplane, dplane);
	  	  }//endif dir 0
			else if(white_dir[x]==10) //upside down left 
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormRightUI, WormRightU, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==11) //upside down right
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormLeftUI, WormLeftU, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==13) //upside down left side
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormRightSideI, WormRightSide, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==12) //upside down right side
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormLeftSideI, WormLeftSide, lplane, dplane);
	  	  }//endif dir 0
	  	else if(white_dir[x]==14) //jack hammer
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 20, WormHammerI, WormHammer, lplane, dplane);
	  	  }//endif dir 0
	  	
	  	  
	  	//if(((team==TBlack) & (black_w!=x)) || (team==TWhite)) TextOut(black_x[x]-(fixs(scrollx)*8)-5-min,black_y[x]-scrolly-8,"100");
	  	//drwas the worms
	  	//DOES THE SAME FOR THE BLACK WORKS
	  	drblack:
	  	if(blackinvis) continue; //if the team is invisible, dont draw them!
	  	xcoord = black_x[x] - (fixs(scrollx) * 8) - 5 - min;
	  	ycoord = black_y[x] - scrolly + 1;
	  	if(black_dir[x]==0)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormRight, WormRightI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==1)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormLeft, WormLeftI, lplane, dplane);
	  	  }//endif dir 0
	  	//drwas the worms
	  	else if(black_dir[x]==2)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormRight2, WormRight2I, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==3)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormLeft2, WormLeft2I, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==4)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormLeftJump, WormLeftJumpI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==5)
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormRightJump, WormRightJumpI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==6) //straight jump left
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormLeftJump2, WormLeftJump2I, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==7) //straight jump right
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 17, WormRightJump2, WormRightJump2I, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==8) //on side, left up
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormLeftSideU, WormLeftSideUI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==9) //on side, right up
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormRightSideU, WormRightSideUI, lplane, dplane);
	  	  }//endif dir 0
			else if(black_dir[x]==10) //upside down left 
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormRightU, WormRightUI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==11) //upside down right
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 15, WormLeftU, WormLeftUI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==13) //upside down left side
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormRightSide, WormRightSideI, lplane, dplane);
	  	  }//endif dir 0
	  	else if(black_dir[x]==12) //upside down right side
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 13, WormLeftSide, WormLeftSideI, lplane, dplane);
	  	  }//endif dir 0
	    else if(black_dir[x]==14) //jack hammer
	  	  {
	  	  	GrayClipSprite16_OR_R(xcoord, ycoord, 20, WormHammer, WormHammerI, lplane, dplane);
	  	  }//endif dir 0
		}//next x
	
	//DONT DRAW THE WEAPON EQUIPED IF ITS SELECT MODE, FIRED WEAPON MODE, or WALKING MODE
	if((moving==false) & (_keytest(RR_LEFT)==false) & (_keytest(RR_RIGHT)==false) & (GameMode!=M_Select) & (weapson==false))
	  {
	  	//draws the weapons on the current worm..
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
		  
		  //SIMPLE WAY TO DRAW MULTIPLE WEAPONS WITH THE SAME SPRITE...
		  if(WormWeapon==WBazooka || WormWeapon==WHoming || WormWeapon==WHomingP || WormWeapon==WMorter || WormWeapon==WSheepLaunch || WormWeapon==WMagicB) WormWeapon=-10;
		  else if(WormWeapon==WAirStrike || WormWeapon==WNapStrike || WormWeapon==WMB || WormWeapon==WMineStrike || WormWeapon==WMailStrike || WormWeapon==WCarpet || WormWeapon==WTeleport || WormWeapon==WSheepStrike || WormWeapon==WMoleStrike) WormWeapon=-11;
		  else if(WormWeapon==WGrenade || WormWeapon==WCluster) WormWeapon=-12;
		  
		  
		  //draws the weapong on the worm...
      switch(WormWeapon)
		    {
		    case WDyna:
		      GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 10, DynamiteI, DynamiteI, lplane, dplane);
		    	GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 10, Dynamite, Dynamite, lplane, dplane);
					break;
				case WHolyGrenade:
		      GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 5, 10, HolyGI, HolyGI, lplane, dplane);
		    	GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 5, 10, HolyG, HolyG, lplane, dplane);
					break;
		    case WMine:
		      GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 5, MineI, MineI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 5, Mine, Mine, lplane, dplane);
					break;
				case WBanana:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 10, Banana2I, Banana2I, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 10, Banana2, Banana2, lplane, dplane);
					break;
				case WSBanana:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, BananaI, BananaI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, Banana, Banana, lplane, dplane);
					break;
				case WMolotov:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, MolotovI, MolotovI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, Molotov, Molotov, lplane, dplane);
					break;
				case WMingVase:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, MingVaseI, MingVaseI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, MingVase, MingVase, lplane, dplane);
					break;
				case WBaseball:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, BatI, BatI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, Bat, Bat, lplane, dplane);
					break;
			  case WBatLeft:
				  GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 5 - min, WormTop - scrolly + 1 + 10, 4, BatLeft, BatLeft, lplane, dplane);
		      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 5 - min, WormTop - scrolly + 1 + 10, 4, BatLeft, BatLeft, lplane, dplane);
					break;
			  case WBatRight:
				  GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 10, 4, BatRight, BatRight, lplane, dplane);
		      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 10, 4, BatRight, BatRight, lplane, dplane);
					break;
			  
			  case WAxe:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, AxeI, AxeI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, Axe, Axe, lplane, dplane);
					break;
			  case WNinja:
			    GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 7, 5, NinjaI, NinjaI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 7, 5, Ninja, Ninja, lplane, dplane);
					break;
				case WSurrender:
			    GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 7, 10, FlagI, FlagI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 7, 10, Flag, Flag, lplane, dplane);
				  break;
				//right or left cases
				case WShotG:
				  if(Facing())
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 8, 5, ShotGLeftI, ShotGLeftI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 8, 5, ShotGLeft, ShotGLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) + 7 - min, WormTop - scrolly + 1 + 8, 5, ShotGRightI, ShotGRightI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) + 7 - min, WormTop - scrolly + 1 + 8, 5, ShotGRight, ShotGRight, lplane, dplane);
				    }
				    break;
				case WHandG:
				  if(Facing())
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 8, 7, HandGLeftI, HandGLeftI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 8, 7, HandGLeft, HandGLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) + 8 - min, WormTop - scrolly + 1 + 8, 7, HandGRightI, HandGRightI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) + 8 - min, WormTop - scrolly + 1 + 8, 7, HandGRight, HandGRight, lplane, dplane);
				    }
					  break;
				case WMiniG:
				  if(Facing())
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 17 - min, WormTop - scrolly + 1 + 8, 6, MiniGLeftI, MiniGLeftI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 17 - min, WormTop - scrolly + 1 + 8, 6, MiniGLeft, MiniGLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) + 6 - min, WormTop - scrolly + 1 + 8, 6, MiniGRightI, MiniGRightI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) + 6 - min, WormTop - scrolly + 1 + 8, 6, MiniGRight, MiniGRight, lplane, dplane);
				    }
					break;
				case WUzi:
				  if(Facing())
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 5, 10, UziLeftI, UziLeftI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 5, 10, UziLeft, UziLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) + 8 - min, WormTop - scrolly + 1 + 5, 10, UziRightI, UziRightI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) + 8 - min, WormTop - scrolly + 1 + 5, 10, UziRight, UziRight, lplane, dplane);
				    }
					  break;
				case WBow:
				  if(Facing())
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 4, 11, BowLeftI, BowLeftI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 15 - min, WormTop - scrolly + 1 + 4, 11, BowLeft, BowLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) + 7 - min, WormTop - scrolly + 1 + 4, 11, BowRightI, BowRightI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) + 7 - min, WormTop - scrolly + 1 + 4, 11, BowRight, BowRight, lplane, dplane);
				    }
					break;
				case WBlow:
				  if(Facing())
				    {
				    	GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 7 - min, WormTop - scrolly + 1 + 4, 11, BlowLeftI, BlowLeftI, lplane, dplane);
				      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 7 - min, WormTop - scrolly + 1 + 4, 11, BlowLeft, BlowLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) + 7 - min, WormTop - scrolly + 1 + 4, 11, BlowRightI, BlowRightI, lplane, dplane);
				      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) + 7 - min, WormTop - scrolly + 1 + 4, 11, BlowRight, BlowRight, lplane, dplane);
				    }
					break;
				case WJetPack:
				  if(Facing())
				    {
				    	GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) + 5 - min, WormTop - scrolly + 1 + 4, 6, JetLeftI, JetLeftI, lplane, dplane);
				      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) + 5 - min, WormTop - scrolly + 1 + 4, 6, JetLeft, JetLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 5 - min, WormTop - scrolly + 1 + 5, 6, JetRightI, JetRightI, lplane, dplane);
				      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 5 - min, WormTop - scrolly + 1 + 5, 6, JetRight, JetRight, lplane, dplane);
				    }
					break;
				case WFlame:
				  if(Facing())
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) - 9 - min, WormTop - scrolly + 1 + 2, 12, FlameLeftI, FlameLeftI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - 9 - min, WormTop - scrolly + 1 + 2, 12, FlameLeft, FlameLeft, lplane, dplane);
				    }
				    else
				    {
				    	GrayClipSprite16_AND_R(zWormLeft - (fixs(scrollx) * 8) + 0 - min, WormTop - scrolly + 1 + 2, 12, FlameRightI, FlameRightI, lplane, dplane);
				      GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) + 0 - min, WormTop - scrolly + 1 + 2, 12, FlameRight, FlameRight, lplane, dplane);
				    }
					break;
				//special cases
				case -10:
				  GrayClipSprite8_AND_R(zWormLeft-(fixs(scrollx)*8)-2-min, WormTop-scrolly+1+7, 5, RocketI, RocketI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 7, 5, Rocket, Rocket, lplane, dplane);
					break;
				case -11:
				  GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, RadioI, RadioI, lplane, dplane);
		      GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 4, 11, Radio, Radio, lplane, dplane);
					break;
        case -12:
		      GrayClipSprite8_AND_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 5, 9, GrenadeI, GrenadeI, lplane, dplane);
		    	GrayClipSprite8_OR_R(zWormLeft - (fixs(scrollx) * 8) - 2 - min, WormTop - scrolly + 1 + 5, 9, Grenade, Grenade, lplane, dplane);
					break;
				case WDrill:
		      if(team==TWhite)
		        white_dir[white_w]=14;
		      else
		        black_dir[black_w]=14;
					break;
		    default:
		      ;
		    }
	  }
}




//RETURNS WHAT DIRECIONT THE CURRENT WORM IS FACING
int __attribute__((noinline)) Facing()
{
  int ToReturn=0;
  
  //dir just isnt left or right, its the action the worm is doing (such as jumping, or walking) so it quite complicatedly returns what dir based on the action
	if(team==TWhite)
	  {
			ToReturn = directions[white_dir[white_w]];
      /*if(white_dir[white_w]==0) ToReturn=0;
			else if(white_dir[white_w]==1) ToReturn=1;
	  	else if(white_dir[white_w]==2) ToReturn=0;
			else if(white_dir[white_w]==3) ToReturn=1;
			else if(white_dir[white_w]==4) ToReturn=1;
			else if(white_dir[white_w]==5) ToReturn=0;
			else if(white_dir[white_w]==6) ToReturn=1;
			else if(white_dir[white_w]==7) ToReturn=0;
			else if(white_dir[white_w]==8) ToReturn=1;
			else if(white_dir[white_w]==9) ToReturn=0;
			else if(white_dir[white_w]==10) ToReturn=1;
			else if(white_dir[white_w]==11) ToReturn=0;
			else if(white_dir[white_w]==12) ToReturn=1;
			else if(white_dir[white_w]==13) ToReturn=0;*/
	  }
	else //if(team==TBlack)
	  {
			ToReturn = directions[black_dir[black_w]];
	  	/*if(black_dir[black_w]==0) ToReturn=0;
			else if(black_dir[black_w]==1) ToReturn=1;
	  	else if(black_dir[black_w]==2) ToReturn=0;
			else if(black_dir[black_w]==3) ToReturn=1;
			else if(black_dir[black_w]==4) ToReturn=1;
			else if(black_dir[black_w]==5) ToReturn=0;
		  else if(black_dir[black_w]==6) ToReturn=1;
			else if(black_dir[black_w]==7) ToReturn=0;
			else if(black_dir[black_w]==8) ToReturn=1;
			else if(black_dir[black_w]==9) ToReturn=0;
			else if(black_dir[black_w]==10) ToReturn=1;
			else if(black_dir[black_w]==11) ToReturn=0;
			else if(black_dir[black_w]==12) ToReturn=1;
			else if(black_dir[black_w]==13) ToReturn=0;*/
	  }
	
	return ToReturn;
}


//TURNS GRAYSCALE ON
void DllGrayOn()
{
	GrayOn();
	void *dbuffer=malloc(GRAYDBUFFER_SIZE); // allocate space for double-buffering
  GrayDBufInit(dbuffer); // enable double-buffering
  GblDBuffer=dbuffer;
}

//TURNS GRAYSCALE OFF
void DllGrayOff()
{
	GrayOff();
	free(GblDBuffer);
}

//DRAWS THE MAP
void DrawMap()
{
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
  DrawChunk(MapLeftUp,dplane,20-fixs(scrollx) /*width*/, 100-scrolly /*height*/, 0 /*xout*/, fixs(scrollx) /*xin*/, 0 /*yout*/, scrolly /*yin*/);
  DrawChunk(MapRightUp,dplane,fixs(scrollx) /*width*/,100-scrolly /*height*/,20-fixs(scrollx) /*xout*/,0 /*xin*/,0 /*yout*/,scrolly /*yin*/);
  DrawChunk(MapLeft,dplane,20-fixs(scrollx) /*width*/, scrolly /*height*/, 0 /*xout*/, fixs(scrollx) /*xin*/, 100-scrolly /*yout*/, 0 /*yin*/);
  DrawChunk(MapRight,dplane,fixs(scrollx) /*width*/,scrolly /*height*/,20-fixs(scrollx) /*xout*/,0 /*xin*/,100-scrolly /*yout*/,0 /*yin*/); 
}

//ALSO DRAWS THE MAP.. SOMEHOW DIFFERENT... I WISH I REMEBER THE DIFF
void DrawMap2()
{
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
	DrawChunk2(MapRight,dplane,scrollx&7 /*width*/,scrolly /*height*/, 160-(scrollx&7) /*xout*/, 100-scrolly /*yout*/, 0 /*yin*/);
	DrawChunk2(MapRightUp,dplane,scrollx&7 /*width*/,100-scrolly /*height*/, 160-(scrollx&7) /*xout*/, 0 /*yout*/, scrolly /*yin*/);
}


//DRAWS A PART OF THE MAP
void DrawChunk2(void *mem, void *out, short width, short height, short xout, int yout, int yin)
{
  int x,y;
  char bit;
  char *row,*col;
  char *orow,*ocol;
  
  //sets the rowls and colums to 0,0 on both in\out
  row=mem;
  orow=out;
  
  //makes them the correct pos
  for(x=0;x<yin;x++)
  	row+=30;
  for(x=0;x<yout;x++)
  	orow+=30;
  
  
  col=row;
  ocol=orow;

	for(y=0;y<height;y++)
		{
		
		  //sets the colums to the begingin of the row
  		col=row+fixs(scrollx)-0;
  		ocol=orow+fixs(xout);
			
			//copies WIDTH bits over
			//cpy=*col;
			
			for(x=0;x<width;x++)
				{
					bit=peek_bit(col,7-x);
					if(bit==0)
					  poke_bclr(ocol,(width-1)-x);
					else
						poke_bset(ocol,(width-1)-x);
				}
			//*ocol=cpy;
				
			//makes each go down a row
		  row+=30;
		  orow+=30;
		}//next y
}

//DRAWS A PART OF THE MAP
void DrawChunk(void *mem, void *out, short width, short height, short xout, short xin, int yout, int yin)
{
  int x,y;
  char cpy;
  char *row,*col;
  char *orow,*ocol;
  
  //sets the rowls and colums to 0,0 on both in\out
  row=mem;
  orow=out;
  
  //makes them the correct pos
  for(x=0;x<yin;x++)
  	row+=30;
  for(x=0;x<yout;x++)
  	orow+=30;
  
  
  col=row;
  ocol=orow;

	for(y=0;y<height;y++)
		{
		
		  //sets the colums to the begingin of the row
  		col=row+xin;
  		ocol=orow+xout;

			for(x=0;x<width;x++)
				{
					cpy=*col;
					*ocol=cpy;
					
					//makes the colums go over one..
					col+=1;
					ocol+=1;
				}//next x
				
			//makes each go down a row
		  row+=30;
		  orow+=30;
		}//next y
}

//DA
void DrawSel()
{
	static short Frame=0;
	static short UntilF=0;
	
	if(weapson) return; //dont draw it until weapon mode is OVER
	
  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
	UntilF++; //ups the timer until frame changes
	if(UntilF>4) //if its time for a new frame...
		{
			UntilF=0; //resets time
			Frame++; //changes the frame
	    if(Frame>4) Frame=1; //loops frame if needed
		}//endif frame change
	
	
	if(team==TWhite)
		{
			short xcoord = white_x[white_w] - 4 - (fixs(scrollx) * 8) - (scrollx & 7);
			short ycoord = white_y[white_w] - 17 - scrolly;
			if(Frame==1)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 15, Rot1, Rot1, lplane, dplane);
				}//endif frame 1
			else if(Frame==2)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 15, Rot2, Rot2, lplane, dplane);
				}//endif frame 2
			else if(Frame==3)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 11, Rot3, Rot3, lplane, dplane);
				}//endif frame 3
			else if(Frame==4)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 11, Rot4, Rot4, lplane, dplane);
				}//endif frame 4
		}//endif WHITE TEAM
	
	else //if(team==TBlack)
		{
			short xcoord = black_x[black_w] - 4 - (fixs(scrollx) * 8) - (scrollx & 7);
			short ycoord = black_y[black_w] - 17 - scrolly;
			if(Frame==1)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 15, Rot1, Rot1, lplane, dplane);
				}//endif frame 1
			else if(Frame==2)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 15, Rot2, Rot2, lplane, dplane);
				}//endif frame 2
			else if(Frame==3)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 11, Rot3, Rot3, lplane, dplane);
				}//endif frame 3
			else if(Frame==4)
				{
					GrayClipSprite16_OR_R(xcoord, ycoord, 11, Rot4, Rot4, lplane, dplane);
				}//endif frame 4
		}//endif BLACK TEAM
	
}


//draws the cursor on the screen
void DrawCursor()
{
  int min=(scrollx&7);
  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
  
  short xcoord = CursorX - (fixs(scrollx) * 8) - 5 - min;
  short ycoord = CursorY - scrolly + 1;
  if(girdermode)
    {
    	switch(girder)
    	  {
	    	  case 0:
	    	    {
	    	    	GrayClipSprite8_OR_R(xcoord, ycoord, 3, Girder0, Girder0, lplane, dplane);
							break;
	    	    }
	    	  case 1:
	    	    {
	    	    	GrayClipSprite8_OR_R(xcoord, ycoord, 7, Girder45, Girder45, lplane, dplane);
							break;
	    	    }
	    	  case 2:
	    	    {
	    	    	GrayClipSprite8_OR_R(xcoord, ycoord, 8, Girder90, Girder90, lplane, dplane);
							break;
	    	    }
	    	  case 3:
	    	    {
	    	    	GrayClipSprite8_OR_R(xcoord, ycoord, 7, GirderN45, GirderN45, lplane, dplane);
							break;
	    	    }
	    	  case 4:
	    	    {
	    	    	GrayClipSprite16_OR_R(xcoord, ycoord, 3, BigGirder0, BigGirder0, lplane, dplane);
							break;
	    	    }
	    	  case 5:
	    	    {
	    	    	GrayClipSprite16_OR_R(xcoord, ycoord, 12, BigGirder45, BigGirder45, lplane, dplane);
							break;
	    	    }
	    	  case 6:
	    	    {
	    	    	GrayClipSprite8_OR_R(xcoord, ycoord, 15, BigGirder90, BigGirder90, lplane, dplane);
							break;
	    	    }
	    	  case 7:
	    	    {
	    	    	GrayClipSprite16_OR_R(xcoord, ycoord, 12, BigGirderN45, BigGirderN45, lplane, dplane);
							break;
	    	    }
	    	  default:
	    	  	;
	    	}//end switch
	    return ;
    }//end if girder mode
    
    
	if(CursorDir==0)
	  {
	  	GrayClipSprite16_OR_R(xcoord, ycoord, 11, CursorLeft, CursorLeftI, lplane, dplane);
	  }
	else
	  {
	  	GrayClipSprite16_OR_R(xcoord, ycoord, 11, CursorRight, CursorRightI, lplane, dplane);
	  }
}

//draws the homing X
void DrawXSpot()
{
  int min=(scrollx&7);
	GrayClipSprite8_OR_R(xspotx - (fixs(scrollx) * 8) - 5 - min, xspoty - scrolly + 1, 8, XSpotI, XSpot, GrayDBufGetHiddenPlane(LIGHT_PLANE), GrayDBufGetHiddenPlane(DARK_PLANE));
}







void DrawObjects()
{
  int x,min;
  min=(scrollx&7);
  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);

	//draws all in one loop..
	for(x=0;x<15;x++)
	  {
	  	if((mine_y[x]!=-1) & (x<10))
	  		{
	  			GrayClipSprite8_OR_R(mine_x[x] - (fixs(scrollx) * 8) - min - 3, mine_y[x] - scrolly + 1, 5, MineI, Mine, lplane, dplane);
	  		}//endif MINE
	  	if((oil_y[x]!=-1) & (x<8))
	  		{
	  			GrayClipSprite16_OR_R(oil_x[x] - (fixs(scrollx) * 8) - min - 5, oil_y[x] - scrolly + 1, 11, OilI, Oil, lplane, dplane);
	  		}//endif MINE
	  	if(crate_y[x]!=-1)
	  		{
	  			short xcoord = crate_x[x] - (fixs(scrollx) * 8) - min;
	  			short ycoord = crate_y[x] - scrolly + 1;
	  			if(crate_type[x]==1)
	  			  {
	  			  	GrayClipSprite16_OR_R(xcoord, ycoord, 11, Health, Health, lplane, dplane);
	  			  }
	  			else if(crate_type[x]==2)
	  			  {
	  			  	GrayClipSprite16_OR_R(xcoord, ycoord, 11, CrateI, Crate, lplane, dplane);
	  			  }
	  			else if(crate_type[x]==3)
	  			  {
	  			  	GrayClipSprite16_OR_R(xcoord, ycoord, 11, ToolzI, Toolz, lplane, dplane);
	  			  }
	  		}
	  }//next x
}

void DrawXHair()
{
  short zWormLeft=0, WormTop=0, WormWeapon, min;
  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
	
	min=(scrollx&7);
	
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
	
	if(Facing())
		{
			GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - min - XHx - 6, WormTop - scrolly + 1 + XHy, 9, XHair, XHair, lplane, dplane);
		}
	else
		{
			GrayClipSprite16_OR_R(zWormLeft - (fixs(scrollx) * 8) - min + XHx, WormTop - scrolly + 1 + XHy, 9, XHair, XHair, lplane, dplane);
		}
}

void DrawWeaps()
{
  int x;
  char WeaponName[25], temp[5];
  
  static const char Weaponz[5][14][20]={
	{"Jet Pack", "Bazooka", "Grenade", "Shot Gun", "Fire Punch", "Dynamite", "Air Strike", "Blow Torch", "Ninja Rope", "Super Banana Bomb", "Petrol Bomb", "Mad Cow Herd", "Skip Turn"},
	{"Low Gravity", "Homing Missle", "Cluster Bomb", "Hand Gun", "Dragon Ball", "Mine", "Napalm Strike", "Drill", "Bungee", "Holy Grenade", "Skunk", "Old Lady", "Surrender"},
	{"Fast Walk", "Mortar", "Banana Bomb", "Uzi", "Kamakazee", "Sheep", "Mail Strike", "Girder", "Parachute", "Flame Thower", "Ming Vase", "Concrete Donkey", "Change Worm"},
	{"Laser Sight", "Homing Pigeon", "Battle Axe", "Minigun", "Suicide Bomb", "Super Sheep", "Mine Strike", "Baseball Bat", "Teleport", "Sal Army", "Sheep Strike", "Nucular Test", "Freeze Worms"},
	{"Invisibility", "Sheep Launcher", "Earthquake", "Bow & Arrow", "Prod", "Mole", "Mole Strike", "Girder Starter Pack", "Scales Of Justice", "MB Bomb", "Carpet Bomb", "Armageddon", "Magic Bullet"}};
	
  //erases the space for the waepons text to be drawn
  for(x=61;x<=70;x++)
    {
    	GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
    	DrawLine(0,x,160,x,A_REVERSE);
    	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
    	DrawLine(0,x,160,x,A_REVERSE);
    }
  	
  //sets up the text to show for teh weapon..
  strcpy(WeaponName,Weaponz[Wy][Wx]);
  strcat(WeaponName," x ");
  sprintf(temp, "%d", WeaponSet[Wy][Wx]);
	strcat(WeaponName,temp);

  //makes a box for the weapon text..
  GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
  DrawLine(0,70,156,70,A_NORMAL);
  DrawLine(0,61,0,70,A_NORMAL);
  DrawLine(156,61,156,70,A_NORMAL);
  printf_xy(4,62,"%s",WeaponName);
  GrayDBufSetHiddenAMSPlane(DARK_PLANE);
  DrawLine(0,70,156,70,A_NORMAL);
  DrawLine(0,61,0,70,A_NORMAL);
  DrawLine(156,61,156,70,A_NORMAL);
  printf_xy(4,62,"%s",WeaponName);  

  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);

  //draws part 1
	ClipSprite32_OR_R(0, 0, 61, Weapons1, dplane);
	ClipSprite32_OR_R(0, 0, 61, Weapons1, lplane);
	ClipSprite32_AND_R(0, 0, 61, Weapons1, dplane);
	ClipSprite32_AND_R(0, 0, 61, Weapons1, lplane);
	//draws part 2
	ClipSprite32_OR_R(32, 0, 61, Weapons2, dplane);
	ClipSprite32_OR_R(32, 0, 61, Weapons2, lplane);
  ClipSprite32_AND_R(32, 0, 61, Weapons2, dplane);
	ClipSprite32_AND_R(32, 0, 61, Weapons2, lplane);
	//draws part 3
	ClipSprite32_OR_R(64, 0, 61, Weapons3, dplane);
	ClipSprite32_OR_R(64, 0, 61, Weapons3, lplane);
	ClipSprite32_AND_R(64, 0, 61, Weapons3, dplane);
	ClipSprite32_AND_R(64, 0, 61, Weapons3, lplane);
	//draws part 4
	ClipSprite32_OR_R(96, 0, 61, Weapons4, dplane);
	ClipSprite32_OR_R(96, 0, 61, Weapons4, lplane);
	ClipSprite32_AND_R(96, 0, 61, Weapons4, dplane);
	ClipSprite32_AND_R(96, 0, 61, Weapons4, lplane);
	//draws part 5
	ClipSprite32_OR_R(128, 0, 61, Weapons5, dplane);
	ClipSprite32_OR_R(128, 0, 61, Weapons5, lplane);
	ClipSprite32_AND_R(128, 0, 61, Weapons5, dplane);
	ClipSprite32_AND_R(128, 0, 61, Weapons5, lplane);
	
	//selbox
  ClipSprite16_XOR_R(Wx*12+1, Wy*12+1, 11, SelBox, dplane);
  ClipSprite16_XOR_R(Wx*12+1, Wy*12+1, 11, SelBox, lplane);
}

//DRAWS THE WAVES ON THE BOTTOM OF THE SCREEN
void DrawWaves()
{
	static short wave[11]={0,0,0,0,0,0,0,0,0,0},WDir=0,WTmr=0;
	int x;
	
	//ups the time until the next wave
	WTmr++;
	if(WTmr>3)
		{
			WTmr=0;
			
			//moves the waves accordingly..
			for(x=10;x>0;x--)
				wave[x]=wave[x-1];
		
			//moves the left most wave up or down
			if(WDir==0)
			  wave[0]++;
			else
			  wave[0]--;
			
			//if its gone to hight or low it resets it
			if(wave[0]>2)
				{
					wave[0]=2;
					WDir=1;
				}
			else if(wave[0]<0)
				{
					wave[0]=0;
					WDir=0;
				}
		}

  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);

	//draws the waves.
	for(x=0;x<11;x++)
		{
			if(wave[x]==0)
			  {
			  	GrayClipSprite16_OR_R((x * 16) - (scrollx & 15), 192 - scrolly, 9, Wave1, Wave1, lplane, dplane);
			  	ClipSprite16_XOR_R((x*16)-(scrollx&15),192-scrolly, 9, Wave1I, dplane);
			  }
			else if(wave[x]==1)
			  {
			  	GrayClipSprite16_OR_R((x * 16) - (scrollx & 15), 192 - scrolly, 9, Wave2, Wave2, lplane, dplane);
			  	ClipSprite16_XOR_R((x*16)-(scrollx&15),192-scrolly, 9, Wave2I, dplane);
			  }
			else if(wave[x]==2)
			  {
			  	GrayClipSprite16_OR_R((x * 16) - (scrollx & 15), 192 - scrolly, 9, Wave3, Wave3, lplane, dplane);
			  	ClipSprite16_XOR_R((x*16)-(scrollx&15),192-scrolly, 9, Wave3I, dplane);
			  } 
			
		}//next x
}

void DrawExp()
{
	short x,y,xx=0,xy=0,xs=0;
	for(x=0;x<8;x++)
		{
			if(exp_y[x]!=-1)
			  {
			  	
			  	for(y=0;y<5;y++)
			  	  {
					  	exp_t[x]++;
					  	if(exp_t[x]>exp_max[x])
					  	  {
					  	  	exp_t[x]=0;
					  	  	exp_y[x]=-1;
					  	  	exp_x[x]=-1;
					  	  	break;
					  	  }//endif explosio is over
					  	 
					  	xx=exp_x[x];
					  	xy=exp_y[x];
					  	xs=exp_t[x];
					  	
					  	//draws the explosion clipped on all maps..
			  	  	PortSet(MapLeftUp, 239, 127);
			  	  	DrawClipEllipse(xx, xy, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
			  	  	DrawClipEllipse(xx+1, xy+1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
							DrawClipEllipse(xx-1, xy-1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);

			  	  	PortSet(MapLeft, 239, 127);
			  	  	DrawClipEllipse(xx, xy-100, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
			  	  	DrawClipEllipse(xx+1, xy-100+1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
			  	  	DrawClipEllipse(xx-1, xy-100-1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);

			  	  	PortSet(MapRightUp, 239, 127);
			  	  	DrawClipEllipse(xx-160, xy, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
			  	  	DrawClipEllipse(xx+1-160, xy+1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
			  	  	DrawClipEllipse(xx-1-160, xy-1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);

			  	  	PortSet(MapRight, 239, 127);
			  	  	DrawClipEllipse(xx-160, xy-100, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
			  	  	DrawClipEllipse(xx+1-160, xy-100+1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
							DrawClipEllipse(xx-1-160, xy-100-1, xs, xs, &(SCR_RECT){{0, 0, 159, 99}},A_REVERSE);
							
							PortRestore();

							GrayDBufSetHiddenAMSPlane(DARK_PLANE);
							DrawClipEllipse(xx-(fixs(scrollx)*8)-(scrollx&7), xy-scrolly, xs, xs, &(SCR_RECT){{0, 0, 159, 99}}, A_NORMAL);
			  	  }
			  }//endif explosion is on screen...
		}//next x
	
	PortRestore();
}

void DrawCharge()
{
	short zWormLeft=0, WormTop=0, x;//, CLvl=0,min=(scrollx&7),Cx,Cy;
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
	
	//gets the strength of fire (0-5)
	//CLvl=charge-(charge%6);
	//CLvl=CLvl/6;
	
	
	/*//draws the charge for each lvl
	for(x=0;x<charge;x++)
		{
		  //gets the coords for the charge
			Cx=sin(xhpos)*(x*2);
			Cy=cos(xhpos)*(x*2);
			
			//draws the charge
			if(Facing()==0)
			  EXT_SETPIX(GrayDBufGetHiddenPlane(DARK_PLANE),WormLeft+Cx+4-(fixs(scrollx)*8)-5-min,WormTop+7+Cy-scrolly+1);
			  //DrawClipEllipse(WormLeft+Cx-(fixs(scrollx)*8)+4-min, WormTop+Cy-scrolly+7, x, x, &(SCR_RECT){{0, 0, 159, 99}},A_NORMAL);
      else
        EXT_SETPIX(GrayDBufGetHiddenPlane(DARK_PLANE),WormLeft-Cx-(fixs(scrollx)*8)-5-min,WormTop+7+Cy-scrolly+1);
        //DrawClipEllipse(WormLeft-Cx-(fixs(scrollx)*8)-4-min, WormTop+Cy-scrolly+7, x, x, &(SCR_RECT){{0, 0, 159, 99}},A_NORMAL);
		}//next x
	//printf_xy(1,1,"fuck");*/
	
	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
	//erases the space needed
	for(x=0;x<5;x++)
		DrawLine(64,1+x,96,1+x,A_REVERSE);
	
	//boxes the bar..
	DrawLine(64,1,96,1,A_NORMAL);
  DrawLine(64,5,96,5,A_NORMAL);
  DrawLine(64,1,64,5,A_NORMAL);
  DrawLine(96,1,96,5,A_NORMAL);
  
  //draws the power..
  for(x=0;x<3;x++)
		DrawLine(65,2+x,65+charge*2,2+x,A_NORMAL);
	
}

void DrawWeap()
{
  short x,wepx,wepy;
  void *lplane = GrayDBufGetHiddenPlane(LIGHT_PLANE);
  void *dplane = GrayDBufGetHiddenPlane(DARK_PLANE);
	for(x=0;x<5;x++)
		{
			if(weap_y[x]!=-1)
				{
					wepx=(int)weap_x[x];
					wepy=(int)weap_y[x];
					
					if(weap_type[x]==WBazooka || weap_type[x]==WMorter || weap_type[x]==WHoming || weap_type[x]==WHoming2 || weap_type[x]==WMagicB)
					  {
					  	//if(x==0)
					  	  //{
					  	  	if(cluster)
							  	  CamFocusY(wepy);
							  	else
							    	CamFocus2(wepx,wepy);
					  	  //}
					  	
					    
					    //if(wepy>(scrolly+100)) return;
					  	//ClipSprite8_OR_R(wepx-(fixs(scrollx)*8)-5-(scrollx&7), wepy-scrolly-5, 4, Bazook, lplane);
							//ClipSprite8_OR_R(wepx-(fixs(scrollx)*8)-5-(scrollx&7), wepy-scrolly-5, 4, Bazook, dplane);
							GrayClipSprite8_OR_R(wepx - 5 - (scrollx), wepy - scrolly - 5, 4, Bazook, Bazook, lplane, dplane);
							
							//if(x==0) CamFocus(wepx,wepy);
							
					  }
					else if(weap_type[x]==WMailStrike)
					  {

							CamFocusY(wepy);

							GrayClipSprite8_OR_R(wepx - 5 - (scrollx), wepy - scrolly - 5, 6, Mail, Mail, lplane, dplane);

					  }
					else if(weap_type[x]==WMB)
					  {
							CamFocusY(wepy);

							GrayClipSprite16_OR_R(wepx - 5 - (scrollx), wepy - scrolly - 5, 15, MBBomb, MBBomb, lplane, dplane);
					  }
					else if(weap_type[x]==WDonkey)
					  {
							CamFocusY(wepy);

							GrayClipSprite16_OR_R(wepx - 5 - (scrollx), wepy - scrolly - 15, 19, Donkey, Donkey, lplane, dplane);
					  }
					else if(weap_type[x]==WCarpet)
					  {
							CamFocusY(wepy);

							GrayClipSprite8_OR_R(wepx - 5 - (scrollx), wepy - scrolly - 5, 7, Carpet1, Carpet1, lplane, dplane);
					  }
					else if(weap_type[x]==WCarpet2)
					  {
							CamFocusY(wepy);

							GrayClipSprite8_OR_R(wepx - 5 - (scrollx), wepy - scrolly - 5, 7, Carpet2, Carpet2, lplane, dplane);
					  }
					else if(weap_type[x]==WSheepStrike || weap_type[x]==WSheepStrike2)
					  {

							CamFocusY(wepy);

							if(weap_dirx[x]<0)
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, SheepLeft, SheepLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, SheepRight, SheepRight, lplane, dplane);
					  	  }
					  }
					
					else if(weap_type[x]==WHomingP)
					  {
					    if(weap_x[x]<xspotx)
					      {
					      	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, PigeonRight, PigeonRight, lplane, dplane);
					      }else
					      {
					      	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, PigeonLeft, PigeonLeft, lplane, dplane);
					      }
					      CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WGrenade || weap_type[x]==WCluster)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 9, Grenade, Grenade, lplane, dplane);
							CamFocus(wepx,wepy);
					  }

					  
					else if(weap_type[x]==WBanana)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 10, Banana2, Banana2, lplane, dplane);
							CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WSBanana)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 10, Banana, Banana, lplane, dplane);
							CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WHolyGrenade)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 10, HolyG, HolyG, lplane, dplane);
							CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WMolotov)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 11, Petrol, Petrol, lplane, dplane);
							CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WCluster2)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 4, Bazook, Bazook, lplane, dplane);
							//CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WDyna)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 10, Dynamite, Dynamite, lplane, dplane);
							//CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WMing2)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 4, Ming2, Ming2, lplane, dplane);
							//CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WMingVase)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 10, MingVase, MingVase, lplane, dplane);
							//CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WShotG || weap_type[x]==WHandG || weap_type[x]==WUzi || weap_type[x]==WMiniG)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 1, Bullet, Bullet, lplane, dplane);
							if(weap_type[x]!=WUzi && weap_type[x]!=WMiniG) CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WBowLeft)
					  {
					  	
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 3, ArrowLeft, ArrowLeft, lplane, dplane);
					    CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WBowRight)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 3, ArrowRight, ArrowRight, lplane, dplane);
					    CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WLady2)
					  {
					  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, Lady2, Lady2, lplane, dplane);
					    CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WSheep)
					  {
					  	if(weap_dirx[x]<0)
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, SheepLeft, SheepLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, SheepRight, SheepRight, lplane, dplane);
					  	  }
					  	CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WCows)
					  {
					  	if(weap_dirx[x]==-1)
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 9, CowLeft, CowLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 9, CowRight, CowRight, lplane, dplane);
					  	  }
					  	if(x==0) CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WSkunk)
					  {
					  	if(weap_dirx[x]==-1)
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, SkunkLeft, SkunkLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 8, SkunkRight, SkunkRight, lplane, dplane);
					  	  }
					  	CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WMole || weap_type[x]==WMole2)
					  {
					  	if(weap_dirx[x]==-1)
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly, 6, MoleLeft, MoleLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite16_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly, 6, MoleRight, MoleRight, lplane, dplane);
					  	  }
					  	CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WOldLady)
					  {
					  	if(weap_dirx[x]<0)
					  	  {
					  	  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 11, LadyLeft, LadyLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 11, LadyRight, LadyRight, lplane, dplane);
					  	  }
					  	CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WSalArmy)
					  {
					  	if(weap_dirx[x]<0)
					  	  {
					  	  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 11, SalLeft, SalLeft, lplane, dplane);
					  	  }else
					  	  {
					  	  	GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 11, SalRight, SalRight, lplane, dplane);
					  	  }
					  	if(x==0) CamFocus(wepx,wepy);
					  }
					else if(weap_type[x]==WNapStrike)
					  {
					  	static short frame=0;
					  	frame++; if(frame>3) frame=1;
					  	
					  	if(frame==1)
					  	  {
					  	 		GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 7, Napalm1, Napalm1, lplane, dplane); 
								}
						  else if(frame==2)
					  	  {
					  	 		GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 6, Napalm2, Napalm2, lplane, dplane); 
								}
						  else if(frame==3)
					  	  {
					  	 		GrayClipSprite8_OR_R(wepx - (fixs(scrollx) * 8) - 5 - (scrollx & 7), wepy - scrolly - 5, 9, Napalm3, Napalm3, lplane, dplane); 
								}
						  
						  CamFocusY(wepy);
					  }
				}//endif weapon is on screen
		}//next x
}


void CamFocus(int x, int y)
{
  if((Lock) || (((cluster) && (weap_type[0]!=WCows)) && ((cluster) && (weap_type[0]!=WBazooka)))) return; //it should be able to fouc is the cam is locked..
  
  scrolly=y-50;
  scrollx=x-70;

	if(scrollx<0) scrollx=0;
	if(scrollx>160) scrollx=160;
	if(scrolly<0) scrolly=0;
	if(scrolly>100) scrolly=100;
}

void CamFocusY(int y)
{
  scrolly=y-50;
  
	if(scrolly<0) scrolly=0;
	if(scrolly>100) scrolly=100;
}

void CamFocus2(short x, short y)
{
  //if((Lock) || ((cluster) && (weap_type[0]!=WCows))) return; //it should be able to fouc is the cam is locked..
  
  scrolly=y-50;
  scrollx=x-70;

	if(scrollx<0) scrollx=0;
	if(scrollx>160) scrollx=160;
	if(scrolly<0) scrolly=0;
	if(scrolly>100) scrolly=100;
}

void drawgfx()
{
  short x;
  
  //draws the worms..
  DrawWorms();
  
  //makes it so you draw to the light plane
	GrayDBufSetHiddenAMSPlane(LIGHT_PLANE);
	ClrScr();
	
  //makes a square
  //makesquare(GrayDBufGetHiddenPlane(LIGHT_PLANE),3,20);
  
	//makes it so you draw on the dark plane
	GrayDBufSetHiddenAMSPlane(DARK_PLANE);
	ClrScr();
	
	//printf_xy(1,1,"%d  %d",white_x[white_w],white_y[white_w]);

  //draws the map at the current pos
  DrawMap();
  
  //if its not scrolled perfectly, then it scrolz
  if((scrollx&7)!=0)
  	{
  	  for(x=0;x<(scrollx&7);x++)
  	  	{
  	    	ScrollLeft160_R(GrayDBufGetHiddenPlane(DARK_PLANE),100);
  	    	ScrollLeft160_R(GrayDBufGetHiddenPlane(LIGHT_PLANE),100);
  	    }
  	    
  	  //draws the remainder map at the current pos
  		DrawMap2();
  	}
  	
  //draws the worms
  DrawWorms();
  
  //draws the explosionzors...
  DrawExp();
  
  //draws crates & barols, & stuff
  DrawObjects();
  
  //draws the waves
  DrawWaves();
  
  //if its selection mode, it draws the spin or the arrow
  if(GameMode==M_Select) DrawSel();

  //if its cursor mode, it draws the cursor
  if(GameMode==M_Cursor) DrawCursor();
  
  //if the xspot is on screen, it shows it...
  if(xspoty!=-1) DrawXSpot();
  
  //if its a charge weapon, and your caring it.. it needs to draw charge
  if((chargew) & (charge>0))
    DrawCharge();
    
  //if its a cross hair type weapon selected, then it draws the xhair, if you arent moving
  if((crosshair) & (moving==false) & (_keytest(RR_LEFT)==false) & (_keytest(RR_RIGHT)==false) & (_keytest(RR_SHIFT)==false) & (weapson==false)) 
    DrawXHair();
  
  //if a weapn is being fired, it has to draw those grafx..
  if(weapson)
    DrawWeap();
  
  //if its choose weapong mode, then it draws the weapons...
  if(GameMode==M_Weapon) DrawWeaps();
  
  GrayDBufSetHiddenAMSPlane(DARK_PLANE);
  //debug
  //printf_xy(1,1,"%d %d", CursorX, CursorY);
  //printf_xy(1,1,"%d %d", weapson, firetime);
  //TextOut(10,10,"this is a test");
  
  // now flip the planes
  GrayDBufToggleSync();
    
  /* On HW1, the flip will be effective only after 1 or 2 plane switches
       depending on the phase. We must not draw to the "hidden" planes before
       they are really hidden! */
  if (!_GrayIsRealHW2()) GrayWaitNSwitches(2);
  
 
}


void DrawCake()
{
	Sprite32(60, 30, 23, CandleCake, GrayDBufGetHiddenPlane(DARK_PLANE), SPRT_OR);
	Sprite32(60, 30, 23, CandleCake2, GrayDBufGetHiddenPlane(LIGHT_PLANE), SPRT_OR);
}


//draws girders to the map
void MapGirder()
{
  //does the drawing to map..
	switch(girder)
		{
			case 0:
				{
    	    ClipSprite8_OR_R(CursorX-5, CursorY-99, 3, Girder0, MapLeft);
					ClipSprite8_OR_R(CursorX-165, CursorY-99, 3, Girder0, MapRight);
					ClipSprite8_OR_R(CursorX-5, CursorY+1, 3, Girder0, MapLeftUp);
					ClipSprite8_OR_R(CursorX-165, CursorY+1, 3, Girder0, MapRightUp);
					
					break;
				}
			case 1:
				{
    	    ClipSprite8_OR_R(CursorX-5, CursorY-99, 7, Girder45, MapLeft);
					ClipSprite8_OR_R(CursorX-165, CursorY-99, 7, Girder45, MapRight);
					ClipSprite8_OR_R(CursorX-5, CursorY+1, 7, Girder45, MapLeftUp);
					ClipSprite8_OR_R(CursorX-165, CursorY+1, 7, Girder45, MapRightUp);
					break;
    	  }
			case 2:
    	  {
    	    ClipSprite8_OR_R(CursorX-5, CursorY-99, 8, Girder90, MapLeft);
					ClipSprite8_OR_R(CursorX-165, CursorY-99, 8, Girder90, MapRight);
					ClipSprite8_OR_R(CursorX-5, CursorY+1, 8, Girder90, MapLeftUp);
					ClipSprite8_OR_R(CursorX-165, CursorY+1, 8, Girder90, MapRightUp);
					break;
				}
			case 3:
    	  {
    	    ClipSprite8_OR_R(CursorX-5, CursorY-99, 7, GirderN45, MapLeft);
					ClipSprite8_OR_R(CursorX-165, CursorY-99, 7, GirderN45, MapRight);
					ClipSprite8_OR_R(CursorX-5, CursorY+1, 7, GirderN45, MapLeftUp);
					ClipSprite8_OR_R(CursorX-165, CursorY+1, 7, GirderN45, MapRightUp);
					break;
    	  }
			case 4:
    	  {
    	    ClipSprite16_OR_R(CursorX-5, CursorY-99, 3, BigGirder0, MapLeft);
					ClipSprite16_OR_R(CursorX-165, CursorY-99, 3, BigGirder0, MapRight);
					ClipSprite16_OR_R(CursorX-4, CursorY+1, 3, BigGirder0, MapLeftUp);
					ClipSprite16_OR_R(CursorX-165, CursorY+1, 3, BigGirder0, MapRightUp);
					break;
    	  }
			case 5:
    	  {
    	    ClipSprite16_OR_R(CursorX-5, CursorY-99, 12, BigGirder45, MapLeft);
					ClipSprite16_OR_R(CursorX-165, CursorY-99, 12, BigGirder45, MapRight);
					ClipSprite16_OR_R(CursorX-5, CursorY+1, 12, BigGirder45, MapLeftUp);
					ClipSprite16_OR_R(CursorX-165, CursorY+1, 12, BigGirder45, MapRightUp);
					break;
    	  }
			case 6:
    	  {
    	    ClipSprite8_OR_R(CursorX-5, CursorY-99, 15, BigGirder90, MapLeft);
					ClipSprite8_OR_R(CursorX-165, CursorY-99, 15, BigGirder90, MapRight);
					ClipSprite8_OR_R(CursorX-5, CursorY+1, 15, BigGirder90, MapLeftUp);
					ClipSprite8_OR_R(CursorX-165, CursorY+1, 15, BigGirder90, MapRightUp);
					break;
				}
			case 7:
    	  {
    	    ClipSprite16_OR_R(CursorX-5, CursorY-99, 12, BigGirderN45, MapLeft);
					ClipSprite16_OR_R(CursorX-165, CursorY-99, 12, BigGirderN45, MapRight);
					ClipSprite16_OR_R(CursorX-5, CursorY+1, 12, BigGirderN45, MapLeftUp);
					ClipSprite16_OR_R(CursorX-165, CursorY+1, 12, BigGirderN45, MapRightUp);
					break;
				}
			default:
    	  ;
    }//end switch
  return ;
}


void DrawNumber(short x, short y, int num)
{
	x=0;
	y=0;
	num=0;
}
