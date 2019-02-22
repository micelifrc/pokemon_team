//
// Created by mich on 21/02/19.
//

#include "Pokemon.h"

int Pokemon::resistance(Pokemon::Type enemy_type) const {
   return std::min(2, -static_cast<int>(effectiveness(enemy_type, _types.first)) -
                      static_cast<int>(effectiveness(enemy_type, _types.second)));
}

int Pokemon::offensive_effectiveness(Pokemon::Type enemy_type) const {
   return std::max(-1, static_cast<int>(std::max(effectiveness(_types.first, enemy_type),
                                                 effectiveness(_types.second, enemy_type))));
}

int Pokemon::mismatch(Pokemon::Type enemy_type) const {
   return resistance(enemy_type) + offensive_effectiveness(enemy_type);
}

Pokemon::Effectiveness Pokemon::effectiveness(Pokemon::Type atk, Pokemon::Type def) {
   switch (def) {
      case Type::Normal: {
         switch (atk) {
            case Type::Fighting:
               return Effectiveness::Supereffective;
            case Type::Ghost:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Fighting: {
         switch (atk) {
            case Type::Flying:
            case Type::Psychic:
            case Type::Fairy:
               return Effectiveness::Supereffective;
            case Type::Rock:
            case Type::Bug:
            case Type::Dark:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Flying: {
         switch (atk) {
            case Type::Rock:
            case Type::Electric:
            case Type::Ice:
               return Effectiveness::Supereffective;
            case Type::Fighting:
            case Type::Bug:
            case Type::Grass:
               return Effectiveness::NonVeryEffective;
            case Type::Ground:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Poison: {
         switch (atk) {
            case Type::Ground:
            case Type::Psychic:
               return Effectiveness::Supereffective;
            case Type::Fighting:
            case Type::Poison:
            case Type::Bug:
            case Type::Grass:
            case Type::Fairy:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Ground: {
         switch (atk) {
            case Type::Water:
            case Type::Grass:
            case Type::Ice:
               return Effectiveness::Supereffective;
            case Type::Poison:
            case Type::Rock:
               return Effectiveness::NonVeryEffective;
            case Type::Electric:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Rock: {
         switch (atk) {
            case Type::Fighting:
            case Type::Ground:
            case Type::Steel:
            case Type::Water:
            case Type::Grass:
               return Effectiveness::Supereffective;
            case Type::Normal:
            case Type::Flying:
            case Type::Poison:
            case Type::Fire:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Bug: {
         switch (atk) {
            case Type::Flying:
            case Type::Rock:
            case Type::Fire:
               return Effectiveness::Supereffective;
            case Type::Fighting:
            case Type::Ground:
            case Type::Grass:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Ghost: {
         switch (atk) {
            case Type::Ghost:
            case Type::Dark:
               return Effectiveness::Supereffective;
            case Type::Poison:
            case Type::Bug:
               return Effectiveness::NonVeryEffective;
            case Type::Normal:
            case Type::Fighting:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Steel: {
         switch (atk) {
            case Type::Fighting:
            case Type::Ground:
            case Type::Fire:
               return Effectiveness::Supereffective;
            case Type::Normal:
            case Type::Flying:
            case Type::Rock:
            case Type::Bug:
            case Type::Steel:
            case Type::Grass:
            case Type::Psychic:
            case Type::Ice:
            case Type::Dragon:
            case Type::Fairy:
               return Effectiveness::NonVeryEffective;
            case Type::Poison:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Fire: {
         switch (atk) {
            case Type::Ground:
            case Type::Rock:
            case Type::Water:
               return Effectiveness::Supereffective;
            case Type::Bug:
            case Type::Steel:
            case Type::Fire:
            case Type::Grass:
            case Type::Ice:
            case Type::Fairy:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Water: {
         switch (atk) {
            case Type::Grass:
            case Type::Electric:
               return Effectiveness::Supereffective;
            case Type::Steel:
            case Type::Fire:
            case Type::Water:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Grass: {
         switch (atk) {
            case Type::Flying:
            case Type::Poison:
            case Type::Bug:
            case Type::Fire:
            case Type::Ice:
               return Effectiveness::Supereffective;
            case Type::Ground:
            case Type::Water:
            case Type::Grass:
            case Type::Electric:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Electric: {
         switch (atk) {
            case Type::Ground:
               return Effectiveness::Supereffective;
            case Type::Flying:
            case Type::Steel:
            case Type::Electric:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Psychic: {
         switch (atk) {
            case Type::Bug:
            case Type::Ghost:
            case Type::Dark:
               return Effectiveness::Supereffective;
            case Type::Fighting:
            case Type::Psychic:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Ice: {
         switch (atk) {
            case Type::Fighting:
            case Type::Rock:
            case Type::Steel:
            case Type::Fire:
               return Effectiveness::Supereffective;
            case Type::Ice:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Dragon: {
         switch (atk) {
            case Type::Ice:
            case Type::Dragon:
            case Type::Fairy:
               return Effectiveness::Supereffective;
            case Type::Fire:
            case Type::Water:
            case Type::Grass:
            case Type::Electric:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Dark: {
         switch (atk) {
            case Type::Fighting:
            case Type::Bug:
            case Type::Fairy:
               return Effectiveness::Supereffective;
            case Type::Ghost:
            case Type::Dark:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case Type::Fairy: {
         switch (atk) {
            case Type::Poison:
            case Type::Steel:
               return Effectiveness::Supereffective;
            case Type::Fighting:
            case Type::Bug:
            case Type::Dark:
               return Effectiveness::NonVeryEffective;
            case Type::Dragon:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      default:
         return Effectiveness::Effective;
   }
}

bool share_type(const Pokemon &lhs, const Pokemon &rhs) {
   return lhs.types().first == rhs.types().first or lhs.types().first == rhs.types().second or
          lhs.types().second == rhs.types().first or
          (lhs.types().second == rhs.types().second and lhs.types().second != Pokemon::Type::Nothing);
}

bool operator==(const Pokemon &lhs, const Pokemon &rhs) {
   return lhs.id() == rhs.id();
}

bool operator!=(const Pokemon &lhs, const Pokemon &rhs) {
   return not (lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Pokemon &poke) {
   return os << poke.name();
}

void Pokedex::extract_representatives() {
   _representatives.clear();
   for (unsigned x = 0; x != Pokemon::NUM_TYPES; ++x) {
      for (unsigned y = x; y != Pokemon::NUM_TYPES; ++y) {
         if (not _matrix[x][y]->empty()) {
            _representatives.emplace_back(&_matrix[x][y]->front());
         }
      }
   }
}

std::array<std::array<std::shared_ptr<std::vector<Pokemon>>, Pokemon::NUM_TYPES>, Pokemon::NUM_TYPES>
Pokedex::create_type_pair_matrix() {
   std::array<std::array<std::shared_ptr<std::vector<Pokemon>>, Pokemon::NUM_TYPES>, Pokemon::NUM_TYPES> matrix;
   for (unsigned x = 0; x != Pokemon::NUM_TYPES; ++x) {
      for (unsigned y = 0; y != Pokemon::NUM_TYPES; ++y) {
         if (x <= y) {
            matrix[x][y] = std::make_shared<std::vector<Pokemon>>(std::vector<Pokemon>(0));
         } else {
            matrix[x][y] = matrix[y][x];
         }
      }
   }
   return matrix;
}

const Pokemon &PokeTeam::operator[](unsigned idx) const {
   if (idx >= 6) {
      throw std::out_of_range("Invalid call of operator[] for PokeTeam. There are only 6 pokemon in the team");
   }
   return _pokemon_list[idx];
}

Pokemon &PokeTeam::operator[](unsigned idx) {
   return const_cast<Pokemon &>(static_cast<const PokeTeam &>(*this)[idx]);
}

std::ostream &operator<<(std::ostream &os, const PokeTeam &pt) {
   os << '[' << pt[0];
   for (unsigned idx = 1; idx != 6; ++idx) {
      os << ", " << pt[idx];
   }
   return os << ']';
}