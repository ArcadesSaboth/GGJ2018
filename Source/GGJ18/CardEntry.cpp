#include "CardEntry.h"


FCardEntry::FCardEntry()
	: m_timer(0.f)
{
	
}

void FCardEntry::Tick(float dt)
{
	m_timer -= dt;
}

bool FCardEntry::IsExpired() const
{
	return m_timer < 0.f;
}

float FCardEntry::GetCurrentTime() const
{
	return m_timer;
}
