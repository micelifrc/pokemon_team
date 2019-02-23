/**
 * A program to compute the best possible pokemon team (in terms of mismatches with all 18 types of gen. 6)
 */

#include <iostream>
#include "FindBestTeam.h"

int main() {
   // set the following parameters
   std::vector<Pokemon> fixed_pokemon{};
   std::vector<PokeTeam> best_teams;
   unsigned regions = RegionsFlag::KANTO | RegionsFlag::JOHTO | RegionsFlag::HOENN;
   unsigned inclusions = InclusionFlag::PREEVOLUTIONS | InclusionFlag::PSEUDOLEGENDARIES | InclusionFlag::FOSSILS |
                         InclusionFlag::STARTERS;

   int best_score = FindBestTeam(fixed_pokemon, best_teams, regions, inclusions).find_best_teams();

   std::cout << "This is a list of the best teams:\n\n";
   for (const auto &team: best_teams) {
      std::cout << team << std::endl;
   }
   std::cout << "\nThe total score is: " << best_score << std::endl;

   return 0;
}