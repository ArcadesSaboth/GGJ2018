#include "CardEntry.h"
#include "TextUtils.h"


FCardEntry::FCardEntry()
	: m_timer(0.f)
	, HighlightedCharacters(0)
	, Index(0)
{
	
}

void FCardEntry::Tick(float dt)
{
	m_timer += dt;
}

bool FCardEntry::IsExpired() const
{
	return m_timer > Lifetime;
}


void FCardEntry::CalculateMatchingChars(const FString& text)
{
	HighlightedCharacters = UTextUtils::CountSimilarTextes(Word, text);
}

float FCardEntry::GetCurrentTime() const
{
	return m_timer;
}

float FCardEntry::GetNormalizedLifetime() const
{
	if (Lifetime == 0.f)
	{
		return 0.f;
	}
	return 1.f - (m_timer / Lifetime);
}
