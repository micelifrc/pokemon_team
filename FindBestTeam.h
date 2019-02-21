//
// Created by mich on 21/02/19.
//

#ifndef POKEMON_TEAM_FINDBESTTEAM_H
#define POKEMON_TEAM_FINDBESTTEAM_H

#include <functional>
#include "Pokemon.h"

class FindBestTeam {
public:
   FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                bool consider_defence_ = true, bool consider_offence_ = false, int filter_factor_ = 1,
                bool include_duplicates_ = false);

   // Will find the best possible team, for the first _num_fixed_pokemon already fixed in _current_team
   int operator()();

private:
   // The main looping procedure for operator()
   void find_best_team_loop_iter(unsigned already_in_team, unsigned long next_to_try);

   static void add_kanto_pokedex(Pokedex &pokedex) noexcept;
   static const std::array<Pokemon::Type, Pokemon::NUM_TYPES> _all_types;  // An array containing all the types

   unsigned _num_fixed_pokemon;  // the number of pokemon we specify from constructor
   std::vector<PokeTeam> &_best_teams;  // the list of all best teams found
   int _max_score;  // the max score found in the computation
   std::function<int(Pokemon *, Pokemon::Type)> _evaluation;  // the function to compute which team is the best
   int _filter_factor;  // A number to adjust the computation (if 0, we only consider the bad mathups, this is weak)
   PokeTeam _current_team;  // the team we are currently testing
   std::array<std::array<int, Pokemon::NUM_TYPES>, 6> _partial_scoring;  // The partial scorings for the team
   unsigned _duplicate_step;  // 0 if include duplicates, 1 if no duplicates
   Pokedex _pokedex;  // The pokedex where to search the other pokemon for the team
};


#endif //POKEMON_TEAM_FINDBESTTEAM_H
