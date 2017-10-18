#include "player.h"
#include "simple_logger.h"

void initPlayer(Player *plr, EntityManager *entMan)
{

	plr->ent = &entMan->entList[0];
	plr->ent = initEntity(plr->ent);
	plr->ent->update = &updatePlayer;
	plr->ent->position = vector2d(400,400);
	plr->ent->direction = 2;
}

void movePlayer(Entity *ent)
{
	
	/**********
	*255 6  5 *
	* 0     4 *
	* 1  2  3 *
	**********/

	if (ent->direction == 0)
	{
		if (strcmp(ent->currAnim,"left") != 0) setEntityAnim(ent, "left");
		ent->velocity.x = -PLAYER_SPEED_HALF;
		ent->velocity.y = 0;
		scrollUp(&(ent->position.y), PLAYER_SPEED, NULL, NULL);
	}
	else if (ent->direction == 1)
	{
		if (strcmp(ent->currAnim, "downleft") != 0) setEntityAnim(ent, "downleft");
		ent->velocity.x = -PLAYER_SPEED_HALF;
		ent->velocity.y = PLAYER_SPEED_HALF;
	}
	else if (ent->direction == 2)
	{
		if (strcmp(ent->currAnim, "down") != 0) setEntityAnim(ent, "down");
		ent->velocity.x = 0;
		ent->velocity.y = PLAYER_SPEED;
	}
	else if (ent->direction == 3)
	{
		if (strcmp(ent->currAnim, "downright") != 0) setEntityAnim(ent, "downright");
		ent->velocity.x = PLAYER_SPEED_HALF;
		ent->velocity.y = PLAYER_SPEED_HALF;
	}
	else if (ent->direction == 4)
	{
		if (strcmp(ent->currAnim, "right") != 0) setEntityAnim(ent, "right");
		ent->velocity.x = PLAYER_SPEED_HALF;
		ent->velocity.y = 0;
		scrollUp(&(ent->position.y), PLAYER_SPEED, NULL, NULL);
	}
	else if (ent->direction == 5)
	{
		if (strcmp(ent->currAnim, "upright") != 0) setEntityAnim(ent, "upright");
		ent->velocity.x = 0;
		ent->velocity.y = -PLAYER_SPEED;
		move(ent);
		ent->direction = 4;
	}
	else  if (ent->direction == 255)
	{
		if (strcmp(ent->currAnim, "upleft") != 0) setEntityAnim(ent, "upleft");
		ent->velocity.x = 0;
		ent->velocity.y = -PLAYER_SPEED;
		move(ent);
		ent->direction = 0;
	}
}

void updatePlayer(Entity *ent)
{
	movePlayer(ent, PLAYER_SPEED);
	move(ent);
	if (ent->position.y < 0)
	{
		ent->position.y = 0;
		ent->direction = 2;
	}

	if (ent->position.y > SCREEN_HEIGHT)
	{
		ent->position.y = SCREEN_HEIGHT; 
		if (ent->direction >= 2) ent->direction = 4;
		else ent->direction = 0;
	}

	nextEntFrame(ent);
}