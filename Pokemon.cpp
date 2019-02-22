//
// Created by mich on 21/02/19.
//

#include "Pokemon.h"

int Pokemon::resistance(PokeType enemy_type) const {
   return std::min(2, -static_cast<int>(effectiveness(enemy_type, _types.first)) -
                      static_cast<int>(effectiveness(enemy_type, _types.second)));
}

int Pokemon::offensive_effectiveness(PokeType enemy_type) const {
   return std::max(-1, static_cast<int>(std::max(effectiveness(_types.first, enemy_type),
                                                 effectiveness(_types.second, enemy_type))));
}

int Pokemon::mismatch(PokeType enemy_type) const {
   return resistance(enemy_type) + offensive_effectiveness(enemy_type);
}

Pokemon::Effectiveness Pokemon::effectiveness(PokeType atk, PokeType def) {
   switch (def) {
      case PokeType::Normal: {
         switch (atk) {
            case PokeType::Fighting:
               return Effectiveness::Supereffective;
            case PokeType::Ghost:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Fighting: {
         switch (atk) {
            case PokeType::Flying:
            case PokeType::Psychic:
            case PokeType::Fairy:
               return Effectiveness::Supereffective;
            case PokeType::Rock:
            case PokeType::Bug:
            case PokeType::Dark:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Flying: {
         switch (atk) {
            case PokeType::Rock:
            case PokeType::Electric:
            case PokeType::Ice:
               return Effectiveness::Supereffective;
            case PokeType::Fighting:
            case PokeType::Bug:
            case PokeType::Grass:
               return Effectiveness::NonVeryEffective;
            case PokeType::Ground:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Poison: {
         switch (atk) {
            case PokeType::Ground:
            case PokeType::Psychic:
               return Effectiveness::Supereffective;
            case PokeType::Fighting:
            case PokeType::Poison:
            case PokeType::Bug:
            case PokeType::Grass:
            case PokeType::Fairy:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Ground: {
         switch (atk) {
            case PokeType::Water:
            case PokeType::Grass:
            case PokeType::Ice:
               return Effectiveness::Supereffective;
            case PokeType::Poison:
            case PokeType::Rock:
               return Effectiveness::NonVeryEffective;
            case PokeType::Electric:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Rock: {
         switch (atk) {
            case PokeType::Fighting:
            case PokeType::Ground:
            case PokeType::Steel:
            case PokeType::Water:
            case PokeType::Grass:
               return Effectiveness::Supereffective;
            case PokeType::Normal:
            case PokeType::Flying:
            case PokeType::Poison:
            case PokeType::Fire:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Bug: {
         switch (atk) {
            case PokeType::Flying:
            case PokeType::Rock:
            case PokeType::Fire:
               return Effectiveness::Supereffective;
            case PokeType::Fighting:
            case PokeType::Ground:
            case PokeType::Grass:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Ghost: {
         switch (atk) {
            case PokeType::Ghost:
            case PokeType::Dark:
               return Effectiveness::Supereffective;
            case PokeType::Poison:
            case PokeType::Bug:
               return Effectiveness::NonVeryEffective;
            case PokeType::Normal:
            case PokeType::Fighting:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Steel: {
         switch (atk) {
            case PokeType::Fighting:
            case PokeType::Ground:
            case PokeType::Fire:
               return Effectiveness::Supereffective;
            case PokeType::Normal:
            case PokeType::Flying:
            case PokeType::Rock:
            case PokeType::Bug:
            case PokeType::Steel:
            case PokeType::Grass:
            case PokeType::Psychic:
            case PokeType::Ice:
            case PokeType::Dragon:
            case PokeType::Fairy:
               return Effectiveness::NonVeryEffective;
            case PokeType::Poison:
               return Effectiveness::Ineffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Fire: {
         switch (atk) {
            case PokeType::Ground:
            case PokeType::Rock:
            case PokeType::Water:
               return Effectiveness::Supereffective;
            case PokeType::Bug:
            case PokeType::Steel:
            case PokeType::Fire:
            case PokeType::Grass:
            case PokeType::Ice:
            case PokeType::Fairy:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Water: {
         switch (atk) {
            case PokeType::Grass:
            case PokeType::Electric:
               return Effectiveness::Supereffective;
            case PokeType::Steel:
            case PokeType::Fire:
            case PokeType::Water:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Grass: {
         switch (atk) {
            case PokeType::Flying:
            case PokeType::Poison:
            case PokeType::Bug:
            case PokeType::Fire:
            case PokeType::Ice:
               return Effectiveness::Supereffective;
            case PokeType::Ground:
            case PokeType::Water:
            case PokeType::Grass:
            case PokeType::Electric:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Electric: {
         switch (atk) {
            case PokeType::Ground:
               return Effectiveness::Supereffective;
            case PokeType::Flying:
            case PokeType::Steel:
            case PokeType::Electric:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Psychic: {
         switch (atk) {
            case PokeType::Bug:
            case PokeType::Ghost:
            case PokeType::Dark:
               return Effectiveness::Supereffective;
            case PokeType::Fighting:
            case PokeType::Psychic:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Ice: {
         switch (atk) {
            case PokeType::Fighting:
            case PokeType::Rock:
            case PokeType::Steel:
            case PokeType::Fire:
               return Effectiveness::Supereffective;
            case PokeType::Ice:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Dragon: {
         switch (atk) {
            case PokeType::Ice:
            case PokeType::Dragon:
            case PokeType::Fairy:
               return Effectiveness::Supereffective;
            case PokeType::Fire:
            case PokeType::Water:
            case PokeType::Grass:
            case PokeType::Electric:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Dark: {
         switch (atk) {
            case PokeType::Fighting:
            case PokeType::Bug:
            case PokeType::Fairy:
               return Effectiveness::Supereffective;
            case PokeType::Ghost:
            case PokeType::Dark:
               return Effectiveness::NonVeryEffective;
            default:
               return Effectiveness::Effective;
         }
      }
      case PokeType::Fairy: {
         switch (atk) {
            case PokeType::Poison:
            case PokeType::Steel:
               return Effectiveness::Supereffective;
            case PokeType::Fighting:
            case PokeType::Bug:
            case PokeType::Dark:
               return Effectiveness::NonVeryEffective;
            case PokeType::Dragon:
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
          (lhs.types().second == rhs.types().second and lhs.types().second != PokeType::Nothing);
}

bool operator==(const Pokemon &lhs, const Pokemon &rhs) {
   return lhs.id() == rhs.id();
}

bool operator!=(const Pokemon &lhs, const Pokemon &rhs) {
   return not(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Pokemon &poke) {
   return os << poke.name();
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