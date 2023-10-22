#include "Pack.hpp"
#include <string>
#include <cassert>

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack()
{
  // initialize cards array
  int index = 0;

  for (int s = SPADES; s <= DIAMONDS; s++) 
  {
    for (int r = NINE; r <= ACE; r++) 
    {
      Card card(static_cast<Rank>(r), static_cast<Suit>(s));

      // place card into deck
      cards[index] = card;

      // increment index
      index++;
    }
  }

  // initialize next
  next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input)
{
  std::string buffer;
  std::string rank, suit;
  
  // initialize cards array
  for (int i = 0; i < PACK_SIZE; i++) 
  {
    // read card info from stream
    pack_input >> rank;
    pack_input >> buffer;
    pack_input >> suit;

    Card card(string_to_rank(rank), string_to_suit(suit));

    // place card into deck
    cards[i] = card;
  }

  // initialize next
  next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one()
{
  // test requirements
  assert(next < PACK_SIZE);

  // increment next
  next++;

  return cards[next - 1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset()
{
  next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle()
{
  std::array<Card, PACK_SIZE> shuffled_deck;

  // shuffle cards
  int index = 0;

  for (int i = 0; i < 7; i++)
  {
    for (int iterator1 = 0, iterator2 = PACK_SIZE / 2; iterator2 < PACK_SIZE; iterator1++, iterator2++)
    {
      // place cards into shuffled positions
      shuffled_deck[index] = cards[iterator2];
      shuffled_deck[index + 1] = cards[iterator1];

      // increment index
      index += 2;
    }

    // reset index and cards
    index = 0;
    cards = shuffled_deck;
  }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const
{
  if (next < PACK_SIZE) 
  { 
    return false; 
  }
  return true;
}