/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <time.h>
#include "scene02a.h"

Scene02a::Scene02a() : SuperScene()
{
	srand((unsigned)time(NULL));

	text[0]->message("Scene02a: Lists of n Things (SpriteBatch)");

	// create Boids
	int amount = 2500;
	for (int i=0; i<amount; i++) {
		Sprite* b = new Sprite();
		b->setupSprite("assets/boid.tga", 0.5f, 0.5f, 1.0f, 1.0f, DEFAULTFILTER, DEFAULTWRAP);

		static RGBAColor rgb = RED;
		b->color = rgb;
		//rgb = Color::rotate(rgb, 1.0f/amount);
		rgb = Color::rotate(rgb, 0.004f);

		_spritebatch.push_back(b); // to the Entity vector<Sprite*> _spritebatch

		//add a Boid object to update
		Boid* boid = new Boid();
		boids.push_back(boid);
	}
}

Scene02a::~Scene02a()
{
	int s = _spritebatch.size();
	for (int i=0; i<s; i++) {
		delete _spritebatch[i];
	}
	_spritebatch.clear();

	s = boids.size();
	for (int i=0; i<s; i++) {
		delete boids[i];
	}
	boids.clear();
}

void Scene02a::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	int s = boids.size();
	for (int i=0; i<s; i++) {
		boids[i]->update(deltaTime);
		_spritebatch[i]->spriteposition = boids[i]->position;
		_spritebatch[i]->spriterotation = boids[i]->rotation;
		_spritebatch[i]->spritescale = boids[i]->scale;
	}
}
