#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

//initializer tests

    //not reading in file

TEST(test_card_init_no_parameters) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_card_init_with_parameters_basic) {
    Card c(JACK, CLUBS);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(CLUBS, c.get_suit());
}

TEST(test_card_init_with_parameters_min) {
    Card c(NINE, SPADES);
    ASSERT_EQUAL(NINE, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_card_init_with_parameters_max) {
    Card c(ACE, DIAMONDS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
}

    //reading from file



//accessor tests (e.g. get_rank, get_suit, get_suit(trump))

TEST (test_get_rank_and_get_suit_basic) {
    Card c1(THREE, HEARTS);
    Card c2(FIVE, DIAMONDS);
    Card c3(TEN, CLUBS);
    Card c4(QUEEN, CLUBS);
    Card c5(KING, SPADES);

    Suit trump = CLUBS;

    ASSERT_EQUAL(THREE, c1.get_rank());
    ASSERT_EQUAL(HEARTS, c1.get_suit());

    ASSERT_EQUAL(FIVE, c2.get_rank());
    ASSERT_EQUAL(DIAMONDS, c2.get_suit());

    ASSERT_EQUAL(TEN, c3.get_rank());
    ASSERT_EQUAL(CLUBS, c3.get_suit());

    ASSERT_EQUAL(QUEEN, c4.get_rank());
    ASSERT_EQUAL(CLUBS, c4.get_suit());

    ASSERT_EQUAL(KING, c5.get_rank());
    ASSERT_EQUAL(SPADES, c5.get_suit());

    ASSERT_EQUAL(HEARTS, c1.get_suit(trump));
    ASSERT_EQUAL(DIAMONDS, c2.get_suit(trump));
    ASSERT_EQUAL(CLUBS, c3.get_suit(trump));
    ASSERT_EQUAL(CLUBS, c4.get_suit(trump));
    ASSERT_EQUAL(SPADES, c5.get_suit(trump));

    ASSERT_EQUAL(c1.get_suit(), c1.get_suit(trump));
    ASSERT_EQUAL(c2.get_suit(), c2.get_suit(trump));
    ASSERT_EQUAL(c3.get_suit(), c3.get_suit(trump));
    ASSERT_EQUAL(c4.get_suit(), c4.get_suit(trump));
    ASSERT_EQUAL(c5.get_suit(), c5.get_suit(trump));
}

TEST (test_get_rank_and_get_suit_right_bower) {
    Card c(JACK, HEARTS);

    Suit trump = HEARTS;

    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
    ASSERT_EQUAL(HEARTS, c.get_suit(trump));
    ASSERT_EQUAL(c.get_suit(), c.get_suit(trump));
}

TEST (test_get_rank_and_get_suit_left_bower) {
    Card c(JACK, CLUBS);
    
    Suit trump = SPADES;

    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(CLUBS, c.get_suit());
    ASSERT_EQUAL(SPADES, c.get_suit(trump));

    ASSERT_NOT_EQUAL(CLUBS, c.get_suit(trump));
    ASSERT_NOT_EQUAL(c.get_suit(), c.get_suit(trump));
}

TEST (test_get_rank_and_get_suit_all_jacks) {
    Card c_right(JACK, DIAMONDS);
    Card c_left(JACK, HEARTS);
    Card c_clubs(JACK, CLUBS);
    Card c_spades(JACK, SPADES);
    
    Suit trump = DIAMONDS;

    ASSERT_EQUAL(JACK, c_right.get_rank());
    ASSERT_EQUAL(JACK, c_left.get_rank());
    ASSERT_EQUAL(JACK, c_clubs.get_rank());
    ASSERT_EQUAL(JACK, c_spades.get_rank());

    ASSERT_NOT_EQUAL(c_right.get_suit(), c_left.get_suit());
    ASSERT_EQUAL(c_right.get_suit(), c_left.get_suit(trump));
    
    ASSERT_NOT_EQUAL(c_right.get_suit(), c_clubs.get_suit());
    ASSERT_NOT_EQUAL(c_right.get_suit(), c_spades.get_suit());

    ASSERT_NOT_EQUAL(c_left.get_suit(trump), c_clubs.get_suit());
    ASSERT_NOT_EQUAL(c_left.get_suit(trump), c_spades.get_suit());
}


//boolean tests

TEST (test_is_face_or_ace_card) {
    Card c1(THREE, HEARTS);
    Card c2(FIVE, DIAMONDS);
    Card c3(TEN, CLUBS);
    Card c4(JACK, CLUBS);
    Card c5(QUEEN, SPADES);
    Card c6(KING, CLUBS);
    Card c7(ACE, SPADES);
    Card c8(ACE, DIAMONDS);

    ASSERT_FALSE(c1.is_face_or_ace());
    ASSERT_FALSE(c2.is_face_or_ace());
    ASSERT_FALSE(c3.is_face_or_ace());

    ASSERT_TRUE(c4.is_face_or_ace());
    ASSERT_TRUE(c5.is_face_or_ace());
    ASSERT_TRUE(c6.is_face_or_ace());
    ASSERT_TRUE(c7.is_face_or_ace());
    ASSERT_TRUE(c8.is_face_or_ace());
}

TEST (test_is_right_bower_and_is_left_bower) {
    Card c_right(JACK, CLUBS);
    Card c_left(JACK, SPADES);
    Card c_diamonds(JACK, DIAMONDS);
    Card c_hearts(JACK, HEARTS);

    Card c1(TEN, CLUBS);
    Card c2(KING, CLUBS);
    Card c3(ACE, SPADES);
    Card c4(QUEEN, SPADES);
    
    Suit trump = CLUBS;

    ASSERT_FALSE(c_left.is_right_bower(trump));
    ASSERT_FALSE(c_diamonds.is_right_bower(trump));
    ASSERT_FALSE(c_hearts.is_right_bower(trump));
    ASSERT_FALSE(c1.is_right_bower(trump));
    ASSERT_FALSE(c2.is_right_bower(trump));
    ASSERT_FALSE(c3.is_right_bower(trump));
    ASSERT_FALSE(c4.is_right_bower(trump));
    ASSERT_TRUE(c_right.is_right_bower(trump));

    ASSERT_FALSE(c_right.is_left_bower(trump));
    ASSERT_FALSE(c_diamonds.is_left_bower(trump));
    ASSERT_FALSE(c_hearts.is_left_bower(trump));
    ASSERT_FALSE(c1.is_left_bower(trump));
    ASSERT_FALSE(c2.is_left_bower(trump));
    ASSERT_FALSE(c3.is_left_bower(trump));
    ASSERT_FALSE(c4.is_left_bower(trump));
    ASSERT_TRUE(c_left.is_left_bower(trump));
}

TEST (test_is_trump) {
    Card c1(TEN, SPADES);
    Card c2(JACK, SPADES);
    Card c3(QUEEN, DIAMONDS);
    Card c4(KING, HEARTS);
    Card c5(JACK, CLUBS);
    Card c6(NINE, CLUBS);

    Suit trump = CLUBS;

    ASSERT_FALSE(c1.is_trump(trump));
    ASSERT_FALSE(c3.is_trump(trump));
    ASSERT_FALSE(c4.is_trump(trump));

    ASSERT_TRUE(c2.is_trump(trump));
    ASSERT_TRUE(c5.is_trump(trump));
    ASSERT_TRUE(c6.is_trump(trump));
}

//operator tests


//suit_next tests

TEST (test_suit_next) {
    Card c1(TEN, SPADES);
    Card c2(JACK, CLUBS);
    Card c3(QUEEN, DIAMONDS);
    Card c4(KING, HEARTS);

    ASSERT_EQUAL(SPADES, Suit_next(c2.get_suit()));
    ASSERT_EQUAL(c1.get_suit(), Suit_next(c2.get_suit()));
    ASSERT_EQUAL(c1.get_suit(), Suit_next(CLUBS));

    ASSERT_EQUAL(CLUBS, Suit_next(c1.get_suit()));
    ASSERT_EQUAL(c2.get_suit(), Suit_next(c1.get_suit()));
    ASSERT_EQUAL(c2.get_suit(), Suit_next(SPADES));

    ASSERT_EQUAL(DIAMONDS, Suit_next(c4.get_suit()));
    ASSERT_EQUAL(c3.get_suit(), Suit_next(c4.get_suit()));
    ASSERT_EQUAL(c3.get_suit(), Suit_next(HEARTS));

    ASSERT_EQUAL(HEARTS, Suit_next(c3.get_suit()));
    ASSERT_EQUAL(c4.get_suit(), Suit_next(c3.get_suit()));
    ASSERT_EQUAL(c4.get_suit(), Suit_next(DIAMONDS));

    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));

    ASSERT_NOT_EQUAL(HEARTS, Suit_next(HEARTS));
    ASSERT_NOT_EQUAL(CLUBS, Suit_next(CLUBS));
}


//card_less tests

    //no leading card

TEST (test_card_less_basic) {
    Card c(KING, SPADES);

    Suit trump = SPADES;

    for (int s = SPADES; s <= DIAMONDS; s++) {
        for (int r = NINE; r <= ACE; r++) {
            Card a_card(static_cast<Rank>(r), static_cast<Suit>(s));
            if ((s == SPADES && r == ACE) || a_card.is_left_bower(trump) || a_card.is_right_bower(trump)) {
                ASSERT_FALSE(Card_less(a_card, c, trump));
            }
            else if (c == a_card) {
                ASSERT_EQUAL(c, a_card);
            }
            else {
                ASSERT_TRUE(Card_less(a_card, c, trump));
            }
        }
    }
}

TEST (test_card_less_suit_ranking) {
    Card c1(QUEEN, CLUBS);
    Card c2(ACE, SPADES);

    Card c3(QUEEN, DIAMONDS);
    Card c4(QUEEN, CLUBS);
    Card c5(QUEEN, HEARTS);
    Card c6(QUEEN, SPADES);

    Suit trump = DIAMONDS;
    Suit trump2 = SPADES;

    ASSERT_TRUE(Card_less(c1, c2, trump));

    ASSERT_TRUE(Card_less(c4, c3, trump));
    ASSERT_TRUE(Card_less(c5, c3, trump));
    ASSERT_TRUE(Card_less(c6, c3, trump));

    ASSERT_FALSE(Card_less(c3, c4, trump));
    ASSERT_TRUE(Card_less(c5, c4, trump));
    ASSERT_TRUE(Card_less(c6, c4, trump));

    ASSERT_FALSE(Card_less(c3, c5, trump));
    ASSERT_FALSE(Card_less(c4, c5, trump));
    ASSERT_TRUE(Card_less(c6, c5, trump));

    ASSERT_FALSE(Card_less(c3, c6, trump));
    ASSERT_FALSE(Card_less(c5, c6, trump));
    ASSERT_FALSE(Card_less(c4, c6, trump));

    ASSERT_TRUE(Card_less(c4, c3, trump2));
    ASSERT_TRUE(Card_less(c5, c3, trump2));
    ASSERT_FALSE(Card_less(c6, c3, trump2));

    ASSERT_FALSE(Card_less(c3, c4, trump2));
    ASSERT_TRUE(Card_less(c5, c4, trump2));
    ASSERT_FALSE(Card_less(c6, c4, trump2));

    ASSERT_FALSE(Card_less(c4, c5, trump2));
    ASSERT_FALSE(Card_less(c3, c5, trump2));
    ASSERT_FALSE(Card_less(c6, c5, trump2));

    ASSERT_FALSE(Card_less(c1, c1, c1, trump2));
    ASSERT_FALSE(Card_less(c2, c2, c2, trump2));
    ASSERT_FALSE(Card_less(c3, c3, c1, trump2));
    ASSERT_FALSE(Card_less(c4, c4, c6, trump2));
    ASSERT_FALSE(Card_less(c5, c5, c2, trump2));
    ASSERT_FALSE(Card_less(c6, c6, c5, trump2));
}

    //with leading card

TEST (test_card_less_with_leading_card) {

    Card lead_c(KING, CLUBS);

    Suit trump = SPADES;

    for (int s = SPADES; s <= DIAMONDS; s++) {
        for (int r = NINE; r <= ACE; r++) {
            if (!(s == CLUBS && r == KING)) {
                Card c(static_cast<Rank>(r), static_cast<Suit>(s));
                if (c.is_trump(trump) || (s==CLUBS && r==ACE)) {
                    ASSERT_FALSE(Card_less(c, lead_c, lead_c, trump));
                }
                else {
                    ASSERT_TRUE(Card_less(c, lead_c, lead_c, trump));
                }
            }
        }
    }
}

    //bower-specific tests

//test that the right bower is greater than any other card
TEST (test_right_bower_greatest_card) {
    Card c(JACK, SPADES);

    Suit trump = SPADES;

    for (int s = SPADES; s <= DIAMONDS; s++) {
        for (int r = NINE; r <= ACE; r++) {
            Card a_card(static_cast<Rank>(r), static_cast<Suit>(s));
            if (!(s == SPADES && r == JACK)) {
                ASSERT_TRUE(Card_less(a_card, c, trump));
            }
            else {
                ASSERT_EQUAL(a_card, c);
            }
           
        }
    }

    ASSERT_FALSE(Card_less(c,c, trump));
    ASSERT_FALSE(Card_less(c,c, c, trump));
}



//test that the left bower is greater than everything but the right bower

TEST (test_left_bower_second_greatest_card) {
    Card c(JACK, CLUBS);

    Suit trump = SPADES;

    for (int s = SPADES; s <= DIAMONDS; s++) {
        for (int r = NINE; r <= ACE; r++) {
            Card a_card(static_cast<Rank>(r), static_cast<Suit>(s));
            if (s == SPADES && r == JACK) {
                ASSERT_FALSE(Card_less(a_card, c, trump));
            } 
            else if (c == a_card) {
                ASSERT_EQUAL(c, a_card);
            }
            else {
                ASSERT_TRUE(Card_less(a_card, c, trump));
            }
        }
    }
}

//tests that the right bower is greater than the left bower
TEST (test_left_bower_2nd_greatest_card) {
    Card c_right(JACK, DIAMONDS);
    Card c_left(JACK, HEARTS);

    Suit trump = DIAMONDS;

    ASSERT_TRUE(Card_less(c_left, c_right, trump));
}


// Add more test cases here

TEST_MAIN()
