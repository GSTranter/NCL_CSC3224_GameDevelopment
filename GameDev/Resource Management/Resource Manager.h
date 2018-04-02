/***********************************************************************
Class: ResourceManager
File Type: h
Author: George Tranter
Description: Class to be used to load and handle game resources
***********************************************************************/

#pragma once

#include "Renderer.h"
#include "InputManager.h"
#include "LinearAllocator.h"
#include "Physics.h"
#include "Audio.h"
#include <iostream>
				 
#define MEM_SIZE 1048576

class ResourceManager {
	private:
		LinearAllocator* allocator;
		void* memory;

	public:
		ResourceManager();
		virtual ~ResourceManager();

		void allocateResources(EntityManager* &gameEntities, rend::Renderer* &gameRenderer, in::InputManager* &gameInput, Physics* &gamePhysics);
		void deallocateReources();
};