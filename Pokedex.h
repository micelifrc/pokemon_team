//
// Created by mich on 22/02/19.
//

#ifndef POKEMON_TEAM_POKEDEX_H
#define POKEMON_TEAM_POKEDEX_H

#include "Pokemon.h"

struct RegionsFlag {
   enum Values : unsigned {
      KANTO = 0x0001,
      JOHTO = 0x0002,
      HOENN = 0x0004,
      SINNOH = 0x0008,
      UNOVA = 0x0010,
      KALOS = 0x0020,
      ALOLA = 0x0040
   };
};

struct TipologyFlag {
   enum Values : unsigned {
      STARTERS = 0x0001,
      FOSSILS = 0x0002,
      PSEUDOLEGENDARIES = 0x0004,
      LEGENDARIES = 0x0008,
      MYSTERIOUS = 0x0010,
      MEGAS = 0x0020,
      ALOLAFORMS = 0x0040,
      ULTRACREATURES = 0x0080,
      PREEVOLUTIONS = 0x0100,
   };
};

// This class represents a subset of a pokedex of a certain region
class Pokedex {
public:

   Pokedex() : _matrix{std::move(create_type_pair_matrix())} {}

   // Takes in input two flags, formed from RegionsFlag and InclusionFlag respectively
   void make(unsigned regions, unsigned tipologies);

   const std::vector<const Pokemon *> &representatives() const { return _representatives; }

   const unsigned long num_representatives() const { return _representatives.size(); }

private:
   template<typename... Args>
   void add_pokemon(Args... args);

   template<typename... Args>
   void remove_pokemon(Args... args);

   // extracts the vector of representatives. If you use add_pokemon or remove_pokemon,
   // @p _representatives will be wrong until you call extract_representatives again
   void extract_representatives();

   static std::array<std::array<std::shared_ptr<std::vector<Pokemon>>, static_cast<unsigned>(PokeType::NUM_TYPES)>, static_cast<unsigned>(PokeType::NUM_TYPES)>
   create_type_pair_matrix();

   // A matrix containing pointers to vectors containing all the pokemon for that pair of type in the pokedex
   // The order of the types is not relevant, and if a pokemon is single-type, it is in the diagonal of the matrix
   std::array<std::array<std::shared_ptr<std::vector<Pokemon>>, static_cast<unsigned>(PokeType::NUM_TYPES)>, static_cast<unsigned>(PokeType::NUM_TYPES)> _matrix;
   // One pokemon for each pair of types in the pokedex
   std::vector<const Pokemon *> _representatives;
};

template<typename... Args>
void Pokedex::add_pokemon(Args... args) {
   Pokemon poke{args...};
   for (const auto &similar_poke: *_matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)]) {
      if (similar_poke == poke) {
         return;
      }
   }
   _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)]->emplace_back(poke);
}

template<typename... Args>
void Pokedex::remove_pokemon(Args... args) {
   Pokemon poke{args...};
   unsigned idx = 0;
   while (idx !=
          _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)]->size()) {
      if ((*_matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)])[idx] ==
          poke) {
         (*_matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)])[idx] =
               _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)]->back();
         _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(poke.types().second)]->pop_back();
      } else {
         ++idx;
      }
   }
}


#endif //POKEMON_TEAM_POKEDEX_H
