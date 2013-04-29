	#include "Player.h"
	
Player::Player(int nx, int ny, int nz, QPixmap* pixmap, MyList<QPixmap*>* animation): GameObject( nx,  ny, nz, pixmap){
	animationSpeed=1;
	animationCounter=0;
	RanimationCounter=32;
	anim = animation;
	animationFrame=0;
	type="Player";
	moveSpeed=4;
	health=3;
	setTransformOriginPoint(pixmap->width()/2, pixmap->height()/2);
}
	
Player::~Player(){

}

void Player::spawnTurret(){
	//Spawn a turret on the player.
	emit Spawn(1, gX()-60, gY()-50, 0);
	return;
}

void Player::keyPressed(QKeyEvent* key){
	if (key->key() == Qt::Key_A){
		if (gX()>5)
				MoveDir(-20,  0,  moveSpeed*3/4);
	}else
	if (key->key() == Qt::Key_D){
		if (gX()<600)
			MoveDir( 20,  0,  moveSpeed);
	}
}

void Player::Update(){
//Animate the player
	if (animationCounter<=0){
		animationCounter=RanimationCounter;
		if (animationFrame<anim->size()){
			setPixmap(*(anim->at(animationFrame)));
		}
		else{
			animationFrame=-1;
		}	
		animationFrame++;
	}
	if (animationCounter>0){
		animationCounter--;
	}
	
}

void Player::OnCollisionEnter(MyList<GameObject*>* gameObjects){
	for (int i=0; i<gameObjects->size(); i++){
		if (gameObjects->at(i)->getType() == "EnemyMissile" || gameObjects->at(i)->getType() == "EnemyHamster"){
			if (collidesWithItem(gameObjects->at(i))){
				gameObjects->at(i)->HandleCollision(type);
				setHealth(getHealth()-1);
				emit changeHealth(getHealth());
				if (health<=0){
				//Implement dying here later.
					emit Lose();
					return;
				}
			}
		}
	}
}

void Player::setMoveSpeed(int speed){
	moveSpeed=  speed;
}
int Player::getMoveSpeed(){
	return moveSpeed;
}
	
int Player::getHealth(){
	return health;
}
int Player::getLives(){
	return lives;
}

void Player::setLives(int life){
	lives = life;
}
void Player::setHealth(int health){
	if (health<=3)
		this->health = health;
	else 
	this->health = 3;
}
