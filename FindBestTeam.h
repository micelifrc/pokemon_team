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
                unsigned last_generation_to_include_ = 3, bool include_starters_ = true, bool include_ancients_ = false,
                bool include_semilegendaries_ = false, bool include_legendaries_ = false);

   // Will find the best possible team, for the first _num_fixed_pokemon already fixed in _current_team
   int operator()();

private:
   // The main looping procedure for operator()
   void find_best_team_loop_iter(unsigned already_in_team, unsigned long next_to_try);

   static void
   add_kanto_pokedex(Pokedex &pokedex, bool include_starters, bool include_ancients, bool include_semilegendaries,
                     bool include_legendaries) noexcept;

   static void
   add_johto_pokedex(Pokedex &pokedex, bool include_starters, bool include_ancients, bool include_semilegendaries,
                     bool include_legendaries) noexcept;

   static void
   add_hoenn_pokedex(Pokedex &pokedex, bool include_starters, bool include_ancients, bool include_semilegendaries,
                     bool include_legendaries) noexcept;

   unsigned _num_fixed_pokemon;  // the number of pokemon we specify from constructor
   std::vector<PokeTeam> &_best_teams;  // the list of all best teams found
   int _max_score;  // the max score found in the computation
   std::function<int(Pokemon *, Pokemon::Type)> _evaluation;  // the function to compute which team is the best
   int _filter_factor;  // A number to adjust the computation (if 0, we only consider the bad match-ups, this is weak)
   PokeTeam _current_team;  // the team we are currently testing
   std::array<std::array<int, Pokemon::NUM_TYPES>, 6> _partial_scoring;  // The partial scoring for the team
   Pokedex _pokedex;  // The pokedex where to search the other pokemon for the team
};


#endif //POKEMON_TEAM_FINDBESTTEAM_H
