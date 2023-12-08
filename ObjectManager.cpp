#include "ObjectManager.h"

ObjectManager* ObjectManager::s_Instance = nullptr;

void ObjectManager::Add(std::string objectId, BaseObject* pObject)
{
	m_ObjectMap[objectId] = pObject;
}

void ObjectManager::Drop(std::string objectId)
{
	m_ObjectMap[objectId] = nullptr;
	m_ObjectMap.erase(objectId);
}

void ObjectManager::Clean()
{
	std::map<std::string, BaseObject*>::iterator it;
	for (it = m_ObjectMap.begin(); it != m_ObjectMap.end(); it++) {
		it->second = nullptr;
	}
	m_ObjectMap.clear();
}

BaseObject* ObjectManager::GetObject(std::string objectId)
{
	if (m_ObjectMap.find(objectId) != m_ObjectMap.end()) {
		return m_ObjectMap[objectId];
	}
	return nullptr;
}