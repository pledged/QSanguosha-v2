#include "RoomState.h"
#include "engine.h"
#include "WrappedCard.h"

RoomState::~RoomState()
{
    foreach (Card* card, m_cards.values())
    {
        delete card;
    }
    m_cards.clear();
}

Card* RoomState::getCard(int cardId) const
{
    if (!m_cards.contains(cardId))
    {
        return NULL;
    }
    return m_cards[cardId];
}

void RoomState::resetCard(int cardId)
{
    Card* newCard = Card::Clone(Sanguosha->getEngineCard(cardId));
    if (newCard == NULL) return;
    m_cards[cardId]->deleteLater();
    m_cards[cardId] = new WrappedCard(newCard);
}

// Reset all cards, generals' states of the room instance
void RoomState::reset()
{
    foreach (WrappedCard* card, m_cards.values())
    {
        delete card;
    }
    m_cards.clear();

    int n = Sanguosha->getCardCount();
    for (int i = 0; i < n; i++)
    {
        const Card* card = Sanguosha->getEngineCard(i);
        Card* clonedCard = Card::Clone(card);
        m_cards[i] = new WrappedCard(Card::Clone(clonedCard));
    }
}