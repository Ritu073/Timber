#include<SFML/Graphics.hpp>
#include<sstream>
using namespace sf;
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side{LEFT,RIGHT,NONE};
side branchPositions[NUM_BRANCHES];

void updateRain(int seed);
const int NUM_RAIN=10;
Sprite rain[NUM_RAIN];

enum class rainside{a,b,c,d,e,f,g,h};
rainside rainPositions[NUM_RAIN];

int main() {
VideoMode vm(960,540);
RenderWindow window(vm,"Timber!!");
//mapping 1920x1080 to 960x540 using view class
View view(FloatRect(0,0,1920,1080)); // create rectangle  
window.setView(view);

//Background import
Texture textureBackground; //texture
textureBackground.loadFromFile("graphics/background.png");
Sprite spriteBackground;
spriteBackground.setTexture(textureBackground);
spriteBackground.setPosition(0,0);

//tree
Texture textureTree;
textureTree.loadFromFile("graphics/tree.png");
Sprite spriteTree;
spriteTree.setTexture(textureTree);
spriteTree.setPosition(810,0);

//bee animation
Texture textureBee;
textureBee.loadFromFile("graphics/bee.png");
Sprite spriteBee;
spriteBee.setTexture(textureBee);
spriteBee.setPosition(0,800);

//Aeroplane animation
Texture textureAero;
textureAero.loadFromFile("graphics/aero.png");
Sprite spriteAero;
spriteAero.setTexture(textureAero);
spriteAero.setPosition(1700,0);

bool beeActive=false;
float beeSpeed =0.0f;

//cloud1
Texture textureCloud;
textureCloud.loadFromFile("graphics/cloud.png");

Sprite spriteCloud0;
spriteCloud0.setTexture(textureCloud);
spriteCloud0.setPosition(0,0);

Sprite spriteCloud1;
spriteCloud1.setTexture(textureCloud);
spriteCloud1.setPosition(0,250);

Sprite spriteCloud2;
spriteCloud2.setTexture(textureCloud);
spriteCloud2.setPosition(0,500);

//Player addition
Texture texturePlayer;
texturePlayer.loadFromFile("graphics/player.png");

Sprite spritePlayer;
spritePlayer.setTexture(texturePlayer);
spritePlayer.setPosition(1150,700);

bool cloud0Active=false;
float cloud0Speed =0.0f;
bool cloud1Active=false;
float cloud1Speed =0.0f;
bool cloud2Active=false;
float cloud2Speed =0.0f;

bool aeroActive=false;
float aeroSpeed=0.0f;

Clock clock;

//TimeBar addition
RectangleShape timeBar;
float timeBarStartWidth=400;
float timeBarHeight=80;
timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
timeBar.setFillColor(Color::White);
timeBar.setPosition((1920/2)-timeBarStartWidth/2,980);
Time gameTimeTotal;
float timeRemaining=6.0f;
float timeBarWidthPerSecond=timeBarStartWidth/timeRemaining;


bool paused= true;

//Font addition
int score=0;
Font font;
font.loadFromFile("fonts/KOMIKAP_.ttf");
Text messageText;
Text scoreText;
messageText.setFont(font);
scoreText.setFont(font);
messageText.setString("Press Enter to start!!!");
scoreText.setString("Score=0");
messageText.setCharacterSize(75);
scoreText.setCharacterSize(100);
messageText.setFillColor(Color::White);
scoreText.setFillColor(Color::Yellow);

FloatRect textRect=messageText.getLocalBounds();
messageText.setOrigin(textRect.left+textRect.width/2.0f, textRect.top+textRect.height/2.0f);
messageText.setPosition(1920/2.0f,1080/2.0f);
scoreText.setPosition(20,20);

//rain
Texture textureRain;
textureRain.loadFromFile("graphics/rain.png");
for(int i = 0;i<NUM_RAIN; i++){
rain[i].setTexture(textureRain);
rain[i].setPosition(-2000,-2000);
rain[i].setOrigin(220,20);
}

//branch
Texture textureBranch;
textureBranch.loadFromFile("graphics/branch.png");
for(int i = 0;i<NUM_BRANCHES; i++){
branches[i].setTexture(textureBranch);
branches[i].setPosition(-2000,-2000);
branches[i].setOrigin(220,20);
}

//game loop
while(window.isOpen()){
//1.Handle input
if(Keyboard::isKeyPressed(Keyboard::Escape)){
window.close();
}
if(Keyboard::isKeyPressed(Keyboard::Return)){
paused=false;
score=0;
timeRemaining=6.0f;

}

//update scene
if(!paused){
//2.Update the scene
Time dt=clock.restart();

timeRemaining-=dt.asSeconds();
timeBar.setSize(Vector2f (timeBarWidthPerSecond*timeRemaining,timeBarHeight));

for(int i=1;i<NUM_BRANCHES;i++){
updateBranches(i);
}

for(int i=1;i<NUM_RAIN;i++){
updateRain(i);
}


if(timeRemaining<=0.0f){
paused=true;
messageText.setString("Game Over!!!");
FloatRect textRect=messageText.getLocalBounds();
messageText.setOrigin(textRect.left+textRect.width/2.0f, textRect.top+textRect.height/2.0f);
messageText.setPosition(1920/2.0f,1080/2.0f);
scoreText.setPosition(20,20);
}

if(!beeActive){
srand((int)time(0));
beeSpeed=(rand()% 90)+90; //200-400 speed range
srand((int) time(0) * 10);
float height= (rand()%500) + 500; //500 to 1000 range
spriteBee.setPosition(2000,height);
beeActive =  true;
}
else{
spriteBee.setPosition(spriteBee.getPosition().x-(beeSpeed * dt.asSeconds()),spriteBee.getPosition().y);
if(spriteBee.getPosition().x<-100)
{
beeActive=false;
}
}
//cloud move
if(!cloud0Active){
srand((int)time(0));
cloud0Speed=(rand()% 150)+40; //200-400 speed range
srand((int) time(0) * 15);
float height= (rand()%100) + 100; //500 to 1000 range
spriteCloud0.setPosition(2000,height);
cloud0Active =  true;
}
else{
spriteCloud0.setPosition(spriteCloud0.getPosition().x-(cloud0Speed *            dt.asSeconds()),spriteCloud0.getPosition().y);
if(spriteCloud0.getPosition().x<-100)
{
cloud0Active=false;
}
}

if(!cloud1Active){
srand((int)time(0));
cloud1Speed=(rand()% 100)+40; //200-400 speed range
srand((int) time(0) * 17);
float height= (rand()%120) + 100; //500 to 1000 range
spriteCloud1.setPosition(2000,height);
cloud1Active =  true;
}
else{
spriteCloud1.setPosition(spriteCloud1.getPosition().x-(cloud1Speed *            dt.asSeconds()),spriteCloud1.getPosition().y);
if(spriteCloud1.getPosition().x<-100)
{
cloud1Active=false;
}
}

if(!cloud2Active){
srand((int)time(0));
cloud2Speed=(rand()% 100)+80; //200-400 speed range
srand((int) time(0) * 20);
float height= (rand()%150) + 100; //500 to 1000 range
spriteCloud2.setPosition(2000,height);
cloud2Active =  true;
}
else{
spriteCloud2.setPosition(spriteCloud2.getPosition().x-(cloud2Speed *            dt.asSeconds()),spriteCloud2.getPosition().y);
if(spriteCloud2.getPosition().x<-100)
{
cloud2Active=false;
}
}


if(!aeroActive){
srand((int)time(0));
aeroSpeed=(rand()% 200)+100; //200-400 speed range
srand((int) time(0) * 20);
float height= (rand()%100) + 100; //500 to 1000 range
spriteAero.setPosition(2000,height);
aeroActive =  true;
}
else{
spriteAero.setPosition(spriteAero.getPosition().x-(aeroSpeed *            dt.asSeconds()),spriteAero.getPosition().y);
if(spriteAero.getPosition().x<-100)
{
aeroActive=false;
}
}

std::stringstream ss;
ss<<"Score = " <<score;
scoreText.setString(ss.str());

for(int i=0;i<NUM_BRANCHES;i++){
float height=i*150;
if(branchPositions[i]==side::LEFT){
  branches[i].setPosition(610,height);
  branches[i].setRotation(180);
}else if(branchPositions[i]==side::RIGHT){
branches[i].setPosition(1330,height);
  branches[i].setRotation(0);
}else{
branches[i].setPosition(3000,height);
 
}
}

for(int i=0;i<NUM_RAIN;i++){
float height=i*100;
if(rainPositions[i]==rainside::a){
rain[i].setPosition(400,height);
}else if(rainPositions[i]==rainside::b){
rain[i].setPosition(700,height);
}else if(rainPositions[i]==rainside::c){
    rain[i].setPosition(800,height);
}else if(rainPositions[i]==rainside::d){
    rain[i].setPosition(950,height);
}else if(rainPositions[i]==rainside::e){
        rain[i].setPosition(1150,height);
}else if(rainPositions[i]==rainside::f){
    rain[i].setPosition(1000,height);
}else if(rainPositions[i]==rainside::g){
    rain[i].setPosition(1200,height);
}else{
 rain[i].setPosition(1250,height);
}

}

}

//3.draw the scene
window.clear();
window.draw(spriteBackground);
window.draw(spriteCloud0);
window.draw(spriteCloud1);
window.draw(spriteCloud2);
window.draw(spriteAero);
window.draw(spriteTree);
window.draw(spriteBee);

window.draw(scoreText);
for(int i=0;i<NUM_BRANCHES;i++){
window.draw(branches[i]);
}

for(int j=0;j<NUM_RAIN;j++){
window.draw(rain[j]);
}
window.draw(timeBar);
window.draw(spritePlayer);
if(paused){
window.draw(messageText);
}

window.display();

}
return 0;
}

void updateBranches(int seed){
for (int j=NUM_BRANCHES-1;j>0;j--){
     branchPositions[j]=branchPositions[j-1];

}
srand((int)time(0) + seed);
int r=(rand()%3);
switch(r){
case 0:
branchPositions[0]=side::LEFT;
break;
case 1:
branchPositions[0]=side::RIGHT;
break;
default:
branchPositions[0]=side::NONE;
break;
}}

void updateRain(int seed){
for (int j=NUM_RAIN-1;j>0;j--){
     rainPositions[j]=rainPositions[j-1];

}
srand((int)time(0) + seed);
int d=(rand()%9);
switch(d){
case 0:
rainPositions[0]=rainside::a;
break;
case 1:
rainPositions[0]=rainside::b;
break;
case 2:
rainPositions[0]=rainside::c;
break;
case 3:
rainPositions[0]=rainside::d;
break;
case 4:
rainPositions[0]=rainside::e;
break;
case 5:
rainPositions[0]=rainside::f;
break;
default:
rainPositions[0]=rainside::g;
break;
}}


