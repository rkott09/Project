
//defines
#define BLUE 2
#define RED 1
#define EMPTY 0


//global variables
int  bluepins[3][3] = {1,2,3,4,5,6,7,8,9}; // may need change due to pin assignments.
int  redpins[3][3]  = {10,11,12,13,14,15,16,17,18};
int hallpins[3][3]  = {1,2,3,4,5,6,7,8,9};
Square board[3][3];
CurrentPiece currp;

class CurrentPiece
{
public:
  CurrentPiece(void);
  ~CurrentPiece(void);
  
  int iCord;
  int jCord;
  int movesi[10];
  int movesj[10];
  
  
  
  CurrentPiece(int i, int j);
};
CurrentPiece::CurrentPiece(void)
{
}


CurrentPiece::CurrentPiece(void)
{
}

CurrentPiece::CurrentPiece(int i, int j) { //name is set to type in arg

  iCord = i;
  jCord = j;
  movesi[10] = {0,0,0,0,0,0,0,0,0,0};
  movesj[10] = {0,0,0,0,0,0,0,0,0,0};
}




class Square
{
public:
  Square(void);
  ~Square(void);

  class Piece *piece; //pointer to piece on the square. void if no piece is present.

  Square(Piece *);
};

Square::Square(void)
{
  piece = nullptr;  //initialize the square to null
}

Square::Square(Piece *p){

  piece = p;

}


Square::~Square(void)
{
}


class Piece
{
public:
  Piece(void);
  ~Piece(void);

  String name;
  int player;
  int prevplayer;

  Piece(String t, int p,int pp); //type constructor
};

Piece::Piece(void)
{
}


Piece::~Piece(void)
{
}

Piece::Piece(String t, int p, int pp) { //name is set to type in arg

  name = t;
  player = p;
  prevplayer = pp;

}





void setup() {

  Square board[3][3];
  // put your setup code here, to run once:
  Piece p1("Pawn"   , RED, RED);
  Piece p2("Bishop"  ,RED, RED);
  Piece p3("Knight"  ,RED, RED);
  Piece p4("Pawn"    ,BLUE,BLUE);
  Piece p5("Bishop"  ,BLUE,BLUE);
  Piece p6("Knight"  ,BLUE,BLUE);



  board[0][0].piece = &p1;
  board[0][1].piece = &p2;
  board[0][2].piece = &p3;
  board[2][0].piece = &p4;
  board[2][1].piece = &p5;
  board[2][2].piece = &p6;

  int i,j;
  for (i=0; i< 3; i++)
  {
    for (j=0; j<3; j++)
    {
      if(board[i][j].piece->player == RED)
      {
        //turn led red
        digitalWrite(redpins[i][j], HIGH);
      }
      else if(board[i][j].piece->player == BLUE)
      {
        //turn on blu light
        digitalWrite(bluepins[i][j], HIGH);
      }
    }
  }
  int currentPlayer = BLUE;  //start at 2 so that the switch makes it p1's turn first...
  
  
}
void checkHallEffect()
{
  int analogVal;
  int i;
  int j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      analogVal = analogRead(hallpins[i][j]);
      if(analogVal < 2)
      {
        board[i][j].piece->prevplayer = board[i][j].piece->player; 
        board[i][j].piece->player = 1; //white piece
      }
      if(analogVal >3)
      {
        board[i][j].piece->prevplayer = board[i][j].piece->player;
        board[i][j].piece->player = 2; //black piece
      }
      else
      {
        board[i][j].piece->prevplayer = board[i][j].piece->player;
        board[i][j].piece->player = 0; //no piece
      }
    }
  }
}
void DisplayLEDS(void)
{
  int i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(board[i][j].piece->player == RED)
      {
        digitalWrite(redpins[i][j], HIGH);
        digitalWrite(bluepins[i][j], LOW);
      }
      if(board[i][j].piece->player == BLUE)
      {
        digitalWrite(bluepins[i][j], HIGH);
        digitalWrite(redpins[i][j], LOW);
      }
      else
      {
        digitalWrite(redpins[i][j], LOW);
        digitalWrite(bluepins[i][j], LOW);
      }
    }
        
} 
bool checkChange(void)
{
  int i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(board[i][j].piece->prevplayer != board[i][j].piece->player)
      {
        currp.Currentpiece(i,j);
        checkHallEffect();
        return TRUE;
      }
    }
  }
  return FALSE; // no pieces changed
}
  
void legalMoves(void)
{
  int i, j, player, name, z;
  int movePiece;
  int iCord;
  int jCord;
  z = 0;
  iCord = currp.iCord;
  jCord = currp.jCord;
  player = board[iCord][jCord].piece->player;
  name   = board[iCord][jCord].piece->name;

  switch (name)
  {
    case "Pawn" :
      if (player == RED)
      {
        if(board[iCord+1][jCord].piece->player== EMPTY)//if the space in front of pawn is open
        {
          digitalWrite(redpins[iCord+1][jCord], HIGH); 
          currp->movesi[z] = iCord+1;
          currp->movesj[z] = jCord;
          z++;
        }
        else if(board[iCord+1][jCord+1].piece->player== BLUE) //if there is an enemy within grasp
        {
          digitalWrite(redpins[iCord+1][jCord+1], HIGH); 
          currp->movesi[z] = iCord+1;
          currp->movesj[z] = jCord+1;
          z++;
        }
        else if(board[iCord+1][jCord-1].piece->player== BLUE) //if there is an enemy within grasp
        {
          digitalWrite(redpins[iCord+1][jCord-1], HIGH);
          currp->movesi[z] = iCord+1;
          currp->movesj[z] = jCord-1;
          z++;
        }

      }
      else if(player == BLUE)
      {
        if(board[iCord-1][jCord].piece->player==EMPTY)//if the space in front of pawn is open
        {
          digitalWrite(bluepins[iCord-1][jCord], HIGH); 
          currp->movesi[z] = iCord-1;
          currp->movesj[z] = jCord;
          z++;
        }
        else if(board[iCord-1][jCord-1].piece->player== RED) //if there is an enemy within grasp
        {
          digitalWrite(bluepins[iCord-1][jCord-1], HIGH); 
          currp->movesi[z] = iCord-1;
          currp->movesj[z] = jCord-1;
          z++;
        }
        else if(board[iCord-1][jCord+1].piece->player== RED) //if there is an enemy within grasp
        {
          digitalWrite(bluepins[iCord-1][jCord+1], HIGH); 
          currp->movesi[z] = iCord-1;
          currp->movesj[z] = jCord+1;
          z++;
        }        

       }
      break;
       
    case 2:
    //bishop 

    case "Knight":

    /*
    all possible moves
    -------------------
    +2 -1   where tuple = (row addition , column addition)
    +2 +1
    +1 +2
    +1 -2
    -2 +1
    -2 -1
    -1 +2
    -1 -2
    */
  
    int i, j;
    for(i=-2; i <= 2 ; i+4)
    {
      for(j=-1;j<=1;j+2)
      {
        if(board[iCord+i][jCord+j].piece->player != player)
        {
          switch(player)
          {
            case RED:
              digitalWrite(redpins[iCord+i][jCord+j] , HIGH);
              movesi[z] = iCord+i;
              movesj[z] = jCord+j;
              break;
            case BLUE:
              digitalWrite(bluepins[iCord+i][jCord+j] , HIGH);
              moves[z] = iCord+i;
              moves[z] = jCord+j;
              break;
          } 

        //add to list of moves to check for changes in moves possible 
        }
      }
    }
    for(i=-1; i<=1; i+2)
    {
      for(j=-2;j<=2;j+4)
      {
        if(board[iCord+i][jCord+j].piece->player != player)
        {
          switch(player)
          {
            case RED:
              digitalWrite(redpins[iCord+i][jCord+j] , HIGH);
              movesi[z] = iCord+i;
              movesj[z] = jCord+j;
              break;
            case BLUE:
              digitalWrite(bluepins[iCord+i][jCord+j] , HIGH);
              movesi[z] = iCord+i;
              movesj[z] = jCord+j;
              break;
          } 
        }
      }
    }
    break;
  }
  
  
bool void checkMovement(void)
{
  int done = 0;
  int checki[10]=currp->movesi[10];
  int checkj[10]=currp->movesj[10];
  int i;
  while(done == 0)
  {
    for(i=0;i<10;i++)
    {
      if(board[checki[i]][checkj[j]].piece->player != board[checki[i]][checkj[j]].piece->prevplayer)
      {
        done = 1;
        
      }
    }
  }
}
void lightMoves()
{

  for( int i = 0; i < currp.index; i++)
  {
    switch(board[currp.iCord][currp.jCord].piece->player)
    {
      case RED:
        digitalWrite(redpins[currp.movesi[i]][currp.movesj[j]], HIGH);
        break;
      case BLUE:
        digitalWrite(redpins[currp.movesi[i]][currp.movesj[j]], HIGH);
        break;
    }
  }
}
void checkMoves()
{
  for(int i = 0; i < currp.index; i++)
    if(board[currp.movesi[i]][currp.movesj[j]].piece->player != board[currp.iCord][currp.jCord])
    {
      done = checkChange();
    }
  }
  
void loop() {
  // put your main code here, to run repeatedly:
  
    checkHallEffect()
    DisplayLEDS();
    if(checkChange())
    {
      board[iCord][jCord].piece->player
      legalMoves();
      while(done)
      {
        lightMoves();
        done = checkMoves();
      }
    }
  }
    
  }
}
