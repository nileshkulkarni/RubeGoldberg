/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"
#include <cmath>
#define PI 3.14159265

namespace cs296
{
  dominos_t::dominos_t()
  {
  
      //World Ground
   b2Body* worldGround;
    
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      b2BodyDef bd;
      worldGround = m_world->CreateBody(&bd);
      worldGround->CreateFixture(&shape, 0.0f);
    
      
	b2Body* platform;
	shape.Set(b2Vec2(-10.0f, 10.0f), b2Vec2(10.0f, 10.0f));
    platform = m_world->CreateBody(&bd);
	platform->CreateFixture(&shape, 0.0f);

	Ball *b= new Ball(m_world); 


/*
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 5; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(shiftX+24-i*1.5, shiftY+29.5f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
   */ 
  }
    


  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
