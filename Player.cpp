#include "Player.hpp"
#include <iostream>
#include <algorithm>
#include <cassert>

class SimplePlayer : public Player
{
private:
    std::string name;
    std::vector<Card> hand;

    // helper functions
    Card find_highest_card(const std::vector<Card> &hand, Suit trump)
{
    // locate highest card in hand
    Card highest_card = hand[0];

    for (int i = 0; i < hand.size(); i++)
    {
        if (Card_less(highest_card, hand[i], trump))
        {
            highest_card = hand[i];
        }
    }

    return highest_card;
}

    Card find_lowest_card(const std::vector<Card> &hand, Suit trump)
    {
        // locate highest card in hand
        Card lowest_card = hand[0];

        for (int i = 0; i < hand.size(); i++)
        {
            if (Card_less(hand[i], lowest_card, trump))
            {
                lowest_card = hand[i];
            }
        }

        return lowest_card;
    }

    int find_highest_card_index(const std::vector<Card> &hand, Suit trump)
    {
        // locate highest card in hand
        Card highest_card = hand[0];
        int highest_index = 0;

        for (int i = 0; i < hand.size(); i++)
        {
            if (Card_less(highest_card, hand[i], trump))
            {
                highest_card = hand[i];
                highest_index = i;
            }
        }

        return highest_index;
    }

    int find_lowest_card_index(const std::vector<Card> &hand, Suit trump)
    {
        // locate highest card in hand
        Card lowest_card = hand[0];
        int lowest_index = 0;

        for (int i = 0; i < hand.size(); i++)
        {
            if (Card_less(hand[i], lowest_card, trump))
            {
                lowest_card = hand[i];
                lowest_index = i;
            }
        }

        return lowest_index;
    }

public:
    // constructor
    SimplePlayer(std::string name_in) : Player()
    {
        name = name_in;
    }

    // accessors
    const std::string & get_name() const override
    {   
        return name;
    }

    // mutators
    void add_card(const Card &c) override
    {
        // test requirements
        assert(hand.size() < MAX_HAND_SIZE);

        // place card into hand
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override
    {
        // test requirements
        assert(round == 1 || round == 2);

        // declare variable for total number of cards that meet criteria
        int total_cards = 0;

        // find cards that meet criteria
        if (round == 1)
        {
            for (Card card : hand)
            {
                if (card.is_face_or_ace() && card.is_trump(upcard.get_suit()))
                {
                    total_cards++;
                }
            }

            // test if player wants to select suit
            if (total_cards >= 2)
            {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        else if (round == 2)
        {
            for (Card card : hand)
            {
                if (is_dealer)
                {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
                else if (card.is_face_or_ace() && card.is_trump(Suit_next(upcard.get_suit())))
                {
                    order_up_suit = card.get_suit();
                    return true;
                }
            }
        }

        return false;
    }

    void add_and_discard(const Card &upcard) override
    {
        // test requirements
        assert(hand.size() >= 1);

        // find lowest card in current deck
        Card lowest_card = find_lowest_card(hand, upcard.get_suit());
        int lowest_index = find_lowest_card_index(hand, upcard.get_suit());

        // remove lowest card
        if (Card_less(lowest_card, upcard, upcard.get_suit()))
        {
            hand[lowest_index] = upcard;
        }
    }

    Card lead_card(Suit trump) override
    {
        // test requirements
        assert(hand.size() >= 1);

        std::vector<Card> hand_copy = hand;
        bool all_trump = true;

        // remove all trump cards in hand
        for (int i = 0; i < hand_copy.size(); i++)
        {
            if (hand_copy[i].is_trump(trump))
            {
                hand_copy[i] = Card(TWO, Suit_next(trump));
                continue;
            }
            all_trump = false;
        }

        // look for highest card in hand
        Card highest_card;
        int highest_index;

        if (all_trump)
        {
            highest_card = find_highest_card(hand, trump);
            highest_index = find_highest_card_index(hand, trump);
        }
        else
        {
            highest_card = find_highest_card(hand_copy, trump);
            highest_index = find_highest_card_index(hand_copy, trump);
        }

        // remove card
        hand.erase(hand.begin() + highest_index);

        return highest_card;
    }

    Card play_card(const Card &led_card, Suit trump) override
    {
        // test requirements
        assert(hand.size() >= 1);

        // look for leading card suit in hand
        bool has_suit = false;
        std::vector<Card> hand_copy = hand;

        for (int i = 0; i < hand.size(); i++)
        {
            if (hand[i].get_suit() == led_card.get_suit()) { has_suit = true; }
            else { hand_copy[i] = Card(TWO, led_card.get_suit()); }
        }

        // remove card from hand and return card
        if (has_suit)
        {
            Card highest_card = find_highest_card(hand_copy, trump);
            int highest_index = find_highest_card_index(hand_copy, trump);

            hand.erase(hand.begin() + highest_index);
            return highest_card;
        }
        else
        {
            Card lowest_card = find_lowest_card(hand, trump);
            int lowest_index = find_lowest_card_index(hand, trump);

            hand.erase(hand.begin() + lowest_index);
            return lowest_card;
        }
    }
};

class HumanPlayer : public Player
{
private:
    std::string name;
    std::vector<Card> hand;

    void print_hand() const 
    {
        for (size_t i=0; i < hand.size(); ++i)
        {
            std::cout << "Human player " << name << "'s hand: "
                      << "[" << i << "] " << hand[i] << "\n";
        }
    }

public:
    // constructor
    HumanPlayer(std::string name_in) : Player()
    {
        name = name_in;
    }

    // accessors
    const std::string & get_name() const override
    {
        return name;
    }

    // mutators
    void add_card(const Card &c) override
    {
        // test requirements
        assert(hand.size() < MAX_HAND_SIZE);

        // place card into hand
        hand.push_back(c);

        // sort hand
        std::sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override
    {
        // test requirements
        assert(round == 1 || round == 2);

        // print player's hand
        print_hand();

        // get decision of player
        std::string decision;
        std::cout << "Human player " << name << ", please enter a suit, or \"pass\":";
        std::cin >> decision;

        // test decision of player
        if (decision == "pass")
        {
            return false;
        }
        else
        {
            order_up_suit = string_to_suit(decision);
            return true;
        }
    }

    void add_and_discard(const Card &upcard) override
    {
        // test requirements
        assert(hand.size() >= 1);

        // print the player's hand
        print_hand();

        // get decision of which card to discard
        int decision;
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << name << ", please select a card to discard:\n";
        std::cin >> decision;

        // discard selected card
        if (decision != -1)
        {
            hand.erase(hand.begin() + decision);
            add_card(upcard);
        }

        // sort hand
        std::sort(hand.begin(), hand.end());
    }

    Card lead_card(Suit trump) override
    {
        // test requirements
        assert(hand.size() >= 1);

        // sort hand
        std::sort(hand.begin(), hand.end());

        // print the player's hand
        print_hand();

        // get player's card decision
        int decision;
        std::cout << "Human player " << name << ", please select a card:";
        std::cin >> decision;
        Card chosen_card = hand[decision];

        // remove card from hand
        hand.erase(hand.begin() + decision);

        // sort hand
        std::sort(hand.begin(), hand.end());

        return chosen_card;
    }

    Card play_card(const Card &led_card, Suit trump) override
    {
        // test requirements
        assert(hand.size() >= 1);

        // sort hand
        std::sort(hand.begin(), hand.end());

        // print the player's hand
        print_hand();

        // get player's card decision
        int decision;
        std::cout << "Human player " << name << ", please select a card:";
        std::cin >> decision;
        Card chosen_card = hand[decision];

        // remove card from hand
        hand.erase(hand.begin() + decision);

        // sort hand
        std::sort(hand.begin(), hand.end());

        return chosen_card;
    }
};

Player * Player_factory(const std::string &name, const std::string &strategy)
{
    if (strategy == "Human")
    {
        return new HumanPlayer(name);
    }
    else if (strategy == "Simple")
    {
        return new SimplePlayer(name);
    }

    // quit program if no strategy matches selection
    assert(false);

    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p)
{
    // put player name into os
    os << p.get_name();

    return os;
}