#pragma once
#ifndef ABSTRACTPAGE_H_
#define ABSTRACTPAGE_H_

class AbstractPage {
protected:
	bool m_IsActivate;
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	inline void SetActivate(bool activate) { m_IsActivate = activate; }
	inline bool IsActivate() const { return m_IsActivate; }
};

#endif // !ABSTRACTPAGE_H_
