#pragma once

#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_


#include <map>
#include <string>
#include "BaseObject.h"

class ObjectManager
{
public:
	static ObjectManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectManager(); }

	void Add(std::string objectId, BaseObject* pObject);
	void Drop(std::string objectId);
	void Clean();

	BaseObject* GetObject(std::string objectId);

private:
	ObjectManager() {}
	static ObjectManager* s_Instance;
	std::map<std::string, BaseObject*> m_ObjectMap;	
};
#endif // !OBJECTMANAGER_H_

