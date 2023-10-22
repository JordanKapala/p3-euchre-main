#include <iostream>
#include <string>
#include "Player.hpp"
#include "Pack.hpp"


class Game {
    public:
    Game(int points_to_win, Pack pack_in,
        const std::string player_0_name, const std::string player_0_strat,
        const std::string player_1_name, const std::string player_1_strat,
        const std::string player_2_name, const std::string player_2_strat,
        const std::string player_3_name, const std::string player_3_strat)
        : points_to_win(points_to_win), pack(pack_in){
            players.push_back(Player_factory(player_0_name, player_0_strat));
            players.push_back(Player_factory(player_1_name, player_1_strat));
            players.push_back(Player_factory(player_2_name, player_2_strat));
            players.push_back(Player_factory(player_3_name, player_3_strat));
        }

    void play() {
        for (int dealer_index; dealer_index <= 3; dealer_index++) {
            deal(dealer_index);

            up_card = pack.deal_one();
            make_trump(players[dealer_index], up_card);
        }
    }

    private:
    int points_to_win;
    Suit trump;
    Card up_card;
    Card winning_card;
    Pack pack;
    std::vector<Player*> players;

    void shuffle() {
        pack.shuffle();
    }

    void deal(int d_index) {
        for(int p_index = d_index+1, batch = 0; p_index < p_index + 8; p_index++, batch++){
            players[p_index%4]->add_card(pack.deal_one());
            players[p_index%4]->add_card(pack.deal_one());
            if (batch == 0 || 2 || 5 || 7) {
                players[p_index%4]->add_card(pack.deal_one());
            }
        }
        
    }
    void make_trump(Player * dealer, Card up_card) {
        for (int round = 1; round <= 2; round++) {
            for (int p_index = 0; p_index <= 3; p_index++) {
                if (players[p_index]->make_trump(up_card,players[p_index]==dealer, round, trump) && round == 1) {
                    dealer->add_and_discard(up_card);
                    break;
                }
            }
        }
    }
    
    void play_hand(int dealer_index) {
        int leader_index = dealer_index + 1;
        Card led_card;
        Card follow_up;
        for (int trick = 0; trick <=5 ; trick++) {
            led_card = players[leader_index]->lead_card(trump); //I think you can just make this the parameter for the play_card
            winning_card = led_card;
            for (int index = leader_index+1; index <= index+2; index++) {
                follow_up = players[index%4]->play_card(led_card, trump);
                if (Card_less(winning_card, follow_up, led_card, trump)) {
                    winning_card = follow_up;
                    leader_index = index%4;
                }
            }

            

        }
    }

};

int main(int argc, char **argv) {

}
