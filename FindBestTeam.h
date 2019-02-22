//
// Created by mich on 21/02/19.
//

#ifndef POKEMON_TEAM_FINDBESTTEAM_H
#define POKEMON_TEAM_FINDBESTTEAM_H

#include <functional>
#include "Pokedex.h"

class FindBestTeam {
public:
   /**
    * Creates an instance for FindBestTeam to find the best possible team extension
    * @param fixed_pokemon_ The pokemon you want in your team (can be empty)
    * @param best_teams_ The list of the teams realizing the optimum objective (the output)
    * @param inclusions_ A flag from InclusionFlag to say which kinds of pokemon we should consider
    * @param last_generation_to_include_ The last generation to include. In future cound be replaced with another flag
    * @param consider_defence_ You should consider the defensive resistances in the objective?
    * @param consider_offence_ You should consider the offensive effectiveness in the objective?
    * @param filter_factor_ A value in order to also consider effectiveness, and not just weakness.
    * @param allow_type_repetitions_ Do you allow two pokemon in your team to share (at least) one type?
    */
   FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                unsigned regions_ = Pokedex::RegionsFlag::KALOS | Pokedex::RegionsFlag::JOHTO |
                               Pokedex::RegionsFlag::HOENN | Pokedex::RegionsFlag::SINNOH,
                unsigned inclusions_ = Pokedex::InclusionFlag::STARTERS, bool consider_defence_ = true,
                bool consider_offence_ = false, int filter_factor_ = 1, bool allow_type_repetitions_ = true);

   // Will find the best possible team, for the first _num_fixed_pokemon already fixed in _current_team
   int find_best_teams();

private:
   // The main looping procedure for operator()
   void find_best_team_loop_iter(unsigned already_in_team, unsigned long next_to_try);

   unsigned _num_fixed_pokemon;  // the number of pokemon we specify from constructor
   std::vector<PokeTeam> &_best_teams;  // the list of all best teams found
   int _max_score;  // the max score found in the computation
   std::function<int(Pokemon *, Pokemon::Type)> _evaluation;  // the function to compute which team is the best
   int _filter_factor;  // A number to adjust the computation (if 0, we only consider the bad match-ups, this is weak)
   PokeTeam _current_team;  // the team we are currently testing
   std::array<std::array<int, Pokemon::NUM_TYPES>, 6> _partial_scoring;  // The partial scoring for the team
   Pokedex _pokedex;  // The pokedex where to search the other pokemon for the team
   bool _allow_type_repetitions;
};


#endif //POKEMON_TEAM_FINDBESTTEAM_H
