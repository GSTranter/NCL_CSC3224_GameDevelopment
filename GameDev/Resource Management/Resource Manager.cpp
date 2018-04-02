/***********************************************************************
Class: ResourceManager
File Type: h
Author: George Tranter
Description: Class to be used to load and handle game resources
***********************************************************************/

#include "Resource Manager.h"

//^~^CONSTRUCTOR^~^//
ResourceManager::ResourceManager() {
	memory = malloc(MEM_SIZE);
	allocator = new LinearAllocator(MEM_SIZE, memory);
}
ResourceManager::~ResourceManager() {
}

//^~^FUNCTIONS^~^//
//Allocate resources
void ResourceManager::allocateResources(EntityManager* &gameEntities, rend::Renderer* &gameRenderer, in::InputManager* &gameInput, Physics* &gamePhysics) {

	gameEntities = (EntityManager*) allocator->allocate(sizeof(gameEntities), 0);
	gameRenderer = (rend::Renderer*) allocator->allocate(sizeof(gameRenderer), 0);
	gameInput = (in::InputManager*) allocator->allocate(sizeof(gameInput), 0);
	gamePhysics = (Physics*) allocator->allocate(sizeof(gamePhysics), 0);

}

//Deallocate resources
void ResourceManager::deallocateReources() {
	allocator->clear();
	delete allocator;

	free(memory);
}
