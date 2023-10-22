#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_general_test) {
    Player * James = Player_factory("James", "Simple");

    Card up_c1(JACK, SPADES);
    Card up_c2(KING, HEARTS);
    Card up_c3(ACE, CLUBS);
    Card up_c4(TEN, DIAMONDS);

    James->add_card(Card(ACE, SPADES));
    James->add_card(Card(TEN, SPADES));
    James->add_card(Card(QUEEN, HEARTS));
    James->add_card(Card(NINE, CLUBS));
    James->add_card(Card(KING, DIAMONDS));

    Suit trump = SPADES;

    // round one

    ASSERT_FALSE(James->make_trump(up_c1, false, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c2, false, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c3, false, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c4, false, 1, trump));

    ASSERT_FALSE(James->make_trump(up_c1, true, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c2, true, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c3, true, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c4, true, 1, trump));

    James->make_trump(up_c1, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c2, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c3, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);

    James->make_trump(up_c1, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c2, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c3, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);

    // round two

    ASSERT_FALSE(James->make_trump(up_c1, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c2, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c3, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c4, false, 2, trump));

    trump = SPADES;

    James->make_trump(up_c1, false, 2, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c2, false, 2, trump);
    ASSERT_EQUAL(trump, DIAMONDS);
    James->make_trump(up_c3, false, 2, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, false, 2, trump);
    ASSERT_EQUAL(trump, HEARTS);

    ASSERT_TRUE(James->make_trump(up_c1, true, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c2, true, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c3, true, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c4, true, 2, trump));

    James->make_trump(up_c1, true, 2, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c2, true, 2, trump);
    ASSERT_EQUAL(trump, DIAMONDS);
    James->make_trump(up_c3, true, 2, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, true, 2, trump);
    ASSERT_EQUAL(trump, HEARTS);



    delete James;

}

TEST (test_general_test_2) {
    Player * James = Player_factory("James", "Simple");

    Card c1(QUEEN, SPADES);
    Card c2(JACK, SPADES);
    Card c3(JACK, HEARTS);
    Card c4(ACE, CLUBS);
    Card c5(KING, DIAMONDS);

    Card up_c1(JACK, SPADES);
    Card up_c2(JACK, HEARTS);
    Card up_c3(JACK, CLUBS);
    Card up_c4(JACK, DIAMONDS);

    James->add_card(c1);
    James->add_card(c2);
    James->add_card(c3);
    James->add_card(c4);
    James->add_card(c5);

    Suit trump = CLUBS;

    // round one

    ASSERT_TRUE(James->make_trump(up_c1, false, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c2, false, 1, trump));
    ASSERT_TRUE(James->make_trump(up_c3, false, 1, trump));
    ASSERT_TRUE(James->make_trump(up_c4, false, 1, trump));

    James->make_trump(up_c1, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c2, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c3, false, 1, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c4, false, 1, trump);
    ASSERT_EQUAL(trump, DIAMONDS);

    ASSERT_TRUE(James->make_trump(up_c1, true, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c2, true, 1, trump));
    ASSERT_TRUE(James->make_trump(up_c3, true, 1, trump));
    ASSERT_TRUE(James->make_trump(up_c4, true, 1, trump));

    James->make_trump(up_c1, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c2, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c3, true, 1, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c4, true, 1, trump);
    ASSERT_EQUAL(trump, DIAMONDS);

    // round two

    ASSERT_TRUE(James->make_trump(up_c1, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c2, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c3, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c4, false, 2, trump));

    James->make_trump(up_c1, false, 2, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c2, false, 2, trump);
    ASSERT_EQUAL(trump, DIAMONDS);
    James->make_trump(up_c3, false, 2, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, false, 2, trump);
    ASSERT_EQUAL(trump, HEARTS);

    ASSERT_TRUE(James->make_trump(up_c1, true, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c2, true, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c3, true, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c4, true, 2, trump));

    James->make_trump(up_c1, true, 2, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c2, true, 2, trump);
    ASSERT_EQUAL(trump, DIAMONDS);
    James->make_trump(up_c3, true, 2, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, true, 2, trump);
    ASSERT_EQUAL(trump, HEARTS);


    delete James;
}

TEST(test_general_test_3) {
    Player * James = Player_factory("James", "Simple");

    Card c1(ACE, SPADES);
    Card c2(JACK, SPADES);
    Card c3(JACK, CLUBS);
    Card c4(TEN, SPADES);
    Card c5(KING, SPADES);

    Card up_c1(JACK, SPADES);
    Card up_c2(KING, HEARTS);
    Card up_c3(ACE, CLUBS);
    Card up_c4(TEN, DIAMONDS);

    James->add_card(c1);
    James->add_card(c2);
    James->add_card(c3);
    James->add_card(c4);
    James->add_card(c5);

    Suit trump;

    //ASSERT_TRUE(James->make_trump(up_c1, false, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c2, false, 1, trump));
    ASSERT_TRUE(James->make_trump(up_c3, false, 1, trump));
    ASSERT_FALSE(James->make_trump(up_c4, false, 1, trump));

    James->make_trump(up_c1, false, 1, trump);
    ASSERT_EQUAL(trump, SPADES);

    trump = DIAMONDS;
    James->make_trump(up_c2, false, 1, trump);
    ASSERT_EQUAL(trump, DIAMONDS);
    James->make_trump(up_c3, false, 1, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c4, false, 1, trump);
    ASSERT_EQUAL(trump, CLUBS);

    ASSERT_TRUE(James->make_trump(up_c1, false, 2, trump));
    ASSERT_FALSE(James->make_trump(up_c2, false, 2, trump));
    ASSERT_TRUE(James->make_trump(up_c3, false, 2, trump));
    ASSERT_FALSE(James->make_trump(up_c4, false, 2, trump));

    James->make_trump(up_c1, false, 2, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c2, false, 2, trump);
    ASSERT_EQUAL(trump, CLUBS);
    James->make_trump(up_c3, false, 2, trump);
    ASSERT_EQUAL(trump, SPADES);
    James->make_trump(up_c4, false, 2, trump);
    ASSERT_EQUAL(trump, SPADES);

    delete James;

}

TEST(test_add_discard_take_upcard)
{
    // create new player
    Player * player1 = Player_factory("Andrew", "Simple");

    // add cards to hand
    player1->add_card(Card(ACE, SPADES));
    player1->add_card(Card(TEN, SPADES));
    player1->add_card(Card(QUEEN, HEARTS));
    player1->add_card(Card(NINE, CLUBS));
    player1->add_card(Card(KING, DIAMONDS));

    // create upcard
    Card upcard(JACK, SPADES);

    // test that add and discard discards the correct card
    player1->add_and_discard(upcard);

    ASSERT_EQUAL(Card(KING, DIAMONDS), player1->lead_card(SPADES));

    // delete player
    delete player1;
}

TEST(test_add_discard_discard_upcard)
{
    // create new player
    Player * player1 = Player_factory("Andrew", "Simple");

    // add cards to hand
    player1->add_card(Card(ACE, SPADES));
    player1->add_card(Card(TEN, SPADES));
    player1->add_card(Card(QUEEN, SPADES));
    player1->add_card(Card(JACK, SPADES));
    player1->add_card(Card(KING, SPADES));

    // create upcard
    Card upcard(NINE, SPADES);

    // test that add and discard discards the correct card
    player1->add_and_discard(upcard);

    for (int i = 0; i < 5; i++)
    {
        ASSERT_FALSE(Card(NINE, SPADES) == player1->lead_card(SPADES));
    }

    // delete player
    delete player1;
}

TEST(test_lead_card_non_trump)
{
    // create new player
    Player * player1 = Player_factory("Andrew", "Simple");

    // add cards to hand
    player1->add_card(Card(ACE, SPADES));
    player1->add_card(Card(TEN, SPADES));
    player1->add_card(Card(QUEEN, HEARTS));
    player1->add_card(Card(NINE, CLUBS));
    player1->add_card(Card(KING, DIAMONDS));

    // test lead card returns highest non trump card
    ASSERT_EQUAL(Card(KING, DIAMONDS), player1->lead_card(SPADES));

    // delete player
    delete player1;
}

TEST(test_lead_card_all_trump)
{
    // create new player
    Player * player1 = Player_factory("Andrew", "Simple");

    // add cards to hand
    player1->add_card(Card(ACE, SPADES));
    player1->add_card(Card(TEN, SPADES));
    player1->add_card(Card(QUEEN, SPADES));
    player1->add_card(Card(JACK, SPADES));
    player1->add_card(Card(KING, SPADES));

    // test that lead card returns highest trump card
    ASSERT_EQUAL(Card(JACK, SPADES), player1->lead_card(SPADES))

    // delete player
    delete player1;
}

TEST(test_play_card_has_suit)
{
    // create new player
    Player * player1 = Player_factory("Andrew", "Simple");

    // add cards to hand
    player1->add_card(Card(ACE, SPADES));
    player1->add_card(Card(TEN, SPADES));
    player1->add_card(Card(QUEEN, HEARTS));
    player1->add_card(Card(NINE, CLUBS));
    player1->add_card(Card(KING, DIAMONDS));

    // test that lead card returns highest trump card
    ASSERT_EQUAL(Card(QUEEN, HEARTS), player1->play_card(Card(ACE, HEARTS), SPADES))

    // delete player
    delete player1;
}

TEST(test_play_card_no_suit)
{
    // create new player
    Player * player1 = Player_factory("Andrew", "Simple");

    // add cards to hand
    player1->add_card(Card(ACE, SPADES));
    player1->add_card(Card(TEN, SPADES));
    player1->add_card(Card(QUEEN, SPADES));
    player1->add_card(Card(NINE, CLUBS));
    player1->add_card(Card(KING, DIAMONDS));

    // test that lead card returns highest trump card
    ASSERT_EQUAL(Card(NINE, CLUBS), player1->play_card(Card(ACE, HEARTS), SPADES))

    // delete player
    delete player1;
}

TEST_MAIN()
