class CurrentPiece
{
public:
  CurrentPiece(void);
  ~CurrentPiece(void);
  
  int iCord;
  int jCord;
  
  
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

#define BLUE 2
#define RED 1
int  bluepins[3][3] = {1,2,3,4,5,6,7,8,9}; // may need change due to pin assignments.
int  redpins[3][3]  = {10,11,12,13,14,15,16,17,18};
int hallpins[3][3]  = {1,2,3,4,5,6,7,8,9};
Square board[3][3];





void setup() {

  Square board[3][3];
  // put your setup code here, to run once:
  Piece p1("Pawn"   , 1 , 1);
  Piece p2("Bishop"  ,1, 1);
  Piece p3("Knight"  ,1,1);
  Piece p4("Pawn"    ,2,2);
  Piece p5("Bishop"  ,2,2);
  Piece p6("Knight"  ,2,2);



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
int checkChange(void)
{
  int i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(board[i][j].piece->prevplayer != board[i][j].piece->player)
      {
      }
    }
  }
}
  
void legalMoves(void)
{
  int i, j, player;
  int movePiece;
  player = board[iCord][jCord].piece->player;
  
  switch(movePiece)
  {
    case 1:
    //pawn
      if (player==1){
        for(i=0; i<3; i++){
          for(j=0; j<3; j++){
            if(board[i+1][j].piece->player==0)//if the space in front of pawn is open
            {
              digitalWrite(bluepins[i+1][j], HIGH); 
            }
            else if(board[i+1][j+1].piece->player==2) //if there is an enemy within grasp
            {
              digitalWrite(bluepins[i+1][j+1], HIGH); 
            }
            else if(board[i+1][j-1].piece->player==2) //if there is an enemy within grasp
            {
              digitalWrite(bluepins[i+1][j-1], HIGH); 
            }
          }
        }
      }
      else if(player==2){
        for(i=2; i>=0; i--){
          for(j=2; j>=0; j--){
            if(board[i-1][j].piece->player==0)//if the space in front of pawn is open
            {
              digitalWrite(redpins[i-1][j], HIGH); 
            }
            else if(board[i-1][j-1].piece->player==1) //if there is an enemy within grasp
            {
              digitalWrite(redpins[i-1][j-1], HIGH); 
            }
            else if(board[i-1][j+1].piece->player==1) //if there is an enemy within grasp
            {
              digitalWrite(redpins[i-1][j+1], HIGH); 
            }        
           }
         }
       }
       break;
       
    case 2:
    //bishop 
      if (player==1){
        for(i=0; i<3; i++){
          for(j=0; j<3; j++){
            digitalWrite(bluepins[i+1][i+1], HIGH); //available spots to move. if enemy is there, free to take
            digitalWrite(bluepins[i+1][i-1], HIGH);
          }
        }
      }
        else if(player==2){
          for(i=2; i>=0; i--){
            for(j=2; j>=0; j--){
              digitalWrite(redpins[i-1][j-1], HIGH); //available spots to move. if enemy is there, free to take
              digitalWrite(redpins[i-1][j+1], HIGH);
          }
        }
      }
        break;
  }
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
            break;
          case BLUE:
            digitalWrite(bluepins[iCord+i][jCord+j] , HIGH);
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
            break;
          case BLUE:
            digitalWrite(bluepins[iCord+i][jCord+j] , HIGH);
            break;
        } 
      }
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
