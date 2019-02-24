/**
 * A program to compute the best possible pokemon team (in terms of mismatches with all 18 types of gen. 6)
 */

#include <iostream>
#include <chrono>
#include "FindBestTeam.h"

int main() {
   auto start = std::chrono::system_clock::now();
   // set the following parameters
   std::vector<Pokemon> fixed_pokemon{};
   std::vector<PokeTeam> best_teams;
   unsigned regions =
         RegionsFlag::KANTO | RegionsFlag::JOHTO | RegionsFlag::HOENN | RegionsFlag::SINNOH | RegionsFlag::UNOVA |
         RegionsFlag::KALOS | RegionsFlag::ALOLA;
   unsigned inclusions = InclusionFlag::PREEVOLUTIONS | InclusionFlag::PSEUDOLEGENDARIES | InclusionFlag::FOSSILS |
                         InclusionFlag::STARTERS;

   int best_score = FindBestTeam(fixed_pokemon, best_teams, regions, inclusions).find_best_teams();
   auto end = std::chrono::system_clock::now();

   std::cout << "This is a list of the best teams:\n\n";
   for (const auto &team: best_teams) {
      std::cout << team << std::endl;
   }
   std::cout << "\nThe total score is: " << best_score << std::endl;
   std::cout << "\nThe runtime is = " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << '\n';
   return 0;
}