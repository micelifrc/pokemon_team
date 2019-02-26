/**
 * A program to compute the best possible pokemon team (in terms of mismatches with all 18 types of gen. 6)
 */

#include <iostream>
#include "FindBestTeam.h"

int main() {
   // set the following parameters to customize the computation
   unsigned regions = RegionsFlag::KANTO | RegionsFlag::JOHTO | RegionsFlag::HOENN;
   unsigned typologies = TypologyFlag::PREEVOLUTIONS | TypologyFlag::PSEUDOLEGENDARIES | TypologyFlag::FOSSILS |
                         TypologyFlag::STARTERS;
   std::vector<Pokemon> fixed_pokemon{Pokemon(65, 500, "Alakazam", PokeType::Psychic)};
   unsigned num_threads = 4;
   bool consider_defence = true;
   bool consider_offence = false;
   bool allow_repetitions = false;
   std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)> filter_factors =
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


   std::vector<PokeTeam> best_teams;
   int best_score = FindBestTeam(best_teams, regions, typologies).find_best_teams(fixed_pokemon, num_threads,
                                                                                  consider_defence, consider_offence,
                                                                                  allow_repetitions, filter_factors);

   std::cout << "This is a list of the best teams:\n\n";
   for (const auto &team: best_teams) {
      std::cout << team << std::endl;
   }
   std::cout << "\nThe total score is: " << best_score << std::endl;
   return 0;
}