#include "Library.h"

using namespace std;

map<string, shared_ptr<Minion>> minionLibrary = {};
map<string, shared_ptr<Spell>> spellLibrary = {};
map<string, shared_ptr<Enchantment>> enchantmentLibrary = {};
map<string, shared_ptr<Ritual>> ritualLibrary = {};

void initLibrary () {
  minionLibrary = {    
    {"Air Elemental", 
      make_shared<Minion>("Air Elemental", CardType::MINION, 0, 
      Ability{AbilityType::NONE, Condition::NONE, Target::NONE,
      NoEffect{}}, 1, 1)
    },

    {"Earth Elemental",
      make_shared<Minion>("Earth Elemental", CardType::MINION, 3, 
      Ability{AbilityType::NONE, Condition::NONE, Target::NONE,
      NoEffect{}}, 4, 4)
    },
    {"Bone Golem",
      make_shared<Minion>("Bone Golem", CardType::MINION, 2, 
      Ability{AbilityType::PASSIVE, Condition::ON_MINION_LEAVE, Target::SELF,
      StatModifyEffect{Modify::ADD, 1, Modify::ADD, 1}, "Gain +1/+1 whenever a minion leaves play."}, 1, 3)
    },
    {"Fire Elemental",
      make_shared<Minion>("Fire Elemental", CardType::MINION, 2,
      Ability{AbilityType::PASSIVE, Condition::ON_MINION_ENTER, Target::ENEMY_FIELD, 
      StatModifyEffect{Modify::ADD, 0, Modify::SUBTRACT, 1}, "Whenever an opponent's minion enters play, deal 1 damage to it."}, 2, 2)
    },
    {"Potion Seller",
      make_shared<Minion>("Potion Seller", CardType::MINION, 2,
      Ability{AbilityType::PASSIVE, Condition::ON_TURN_END, Target::ALLY_FIELD,
      StatModifyEffect{Modify::ADD, 0, Modify::ADD, 1}, "At the end of your turn, all your minions gain +0/+1."}, 1, 3)
    },
    {"Novice Pyromancer",
      make_shared<Minion>("Novice Pyromancer", CardType::MINION, 1,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      StatModifyEffect{Modify::ADD, 0, Modify::SUBTRACT, 1}, "Deal 1 damage to target minion", 1}, 0, 1)
    },
    {"Apprentice Summoner", 
      make_shared<Minion>("Apprentice Summoner", CardType::MINION, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SUMMON, 
      SummonEffect{"Air Elemental", 1, PlayerSide::MINE}, "Summon a 1/1 air elemental", 1}, 0, 1)
    },
    {"Master Summoner",
      make_shared<Minion>("Master Summoner", CardType::MINION, 3,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SUMMON, 
      SummonEffect{"Air Elemental", 3, PlayerSide::MINE}, "Summon up to three 1/1 air elementals", 2}, 2, 3)
    },
    {"Yorick",
      make_shared<Minion>("Yorick", CardType::MINION, 3,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SUMMON, 
      SummonDeadEffect{3}, "Summon the minion at the top of the graveyard with 3 defense", 2}, 2, 3)
    },
    {"Soraka",
      make_shared<Minion>("Soraka", CardType::MINION, 1,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      StatModifyEffect{Modify::ADD, 0, Modify::ADD, 2}, "Gain 2 magic at the start of your turn", 0}, 0, 2)
    },
    {"Thief",
      make_shared<Minion>("Thief", CardType::MINION, 1,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      MoveEffect{Location::HAND, PlayerSide::MINE}, "Selects a target on the field and moves it to your hand", 3}, 1, 1)
    }
  };

  spellLibrary = {
    {"Banish",
      make_shared<Spell>("Banish", CardType::SPELL, 2, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE, 
      MoveEffect{Location::GRAVEYARD, PlayerSide::THEIRS}, "Destroy target minion or ritual"}) // need to pass in index from the minion
    },
    {"Unsummon",
      make_shared<Spell>("Unsummon", CardType::SPELL, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE, 
      MoveEffect{Location::HAND, PlayerSide::THEIRS}, "Return target minion to its owner's hand"})
    },
    {"Recharge",
      make_shared<Spell>("Recharge", CardType::SPELL, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::RITUAL, 
      ChargeModifyEffect{3}, "Your ritual gains 3 charges"})
    },
    {"Disenchant",
      make_shared<Spell>("Disenchant", CardType::SPELL, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE, 
      RemoveEnchantEffect{}, "Destroy the top enchantment on target minion"})
    },
    {"Raise Dead",
      make_shared<Spell>("Raise Dead", CardType::SPELL, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SUMMON, 
      SummonDeadEffect{1}, "Resurrect the top minion in your graveyard and set its defence to 1"})
    },
    {"Blizzard",
      make_shared<Spell>("Blizzard", CardType::SPELL, 3, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::BOTH_FIELDS,
      StatModifyEffect{Modify::ADD, 0, Modify::SUBTRACT, 2}, "Deal 2 damage to all minions"})
    },
    {"Exhaust",
      make_shared<Spell>("Exhaust", CardType::SPELL, 1,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      StatModifyEffect{Modify::SUBTRACT, 1, Modify::ADD, 0}, "Reduces the targeted minion's attack by 1"})
    }
  };

  enchantmentLibrary = {
    {"Giant Strength",
      make_shared<Enchantment>("Giant Strength", CardType::ENCHANTMENT, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE, 
      StatModifyEffect{Modify::ADD, 2, Modify::ADD, 2}}, "+2", "+2")
    },
    {"Enrage",
      make_shared<Enchantment>("Enrage", CardType::ENCHANTMENT, 2, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE, 
      StatModifyEffect{Modify::MULTIPLY, 2, Modify::MULTIPLY, 2}}, " 2", "*2")
    },
    {"Haste",
      make_shared<Enchantment>("Haste", CardType::ENCHANTMENT, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      ActionModifyEffect{1}, "Enchanted minion gains +1 action each turn"})
    },
    {"Magic Fatigue",
      make_shared<Enchantment>("Magic Fatigue", CardType::ENCHANTMENT, 0, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      AbilityCostModifyEffect{2}, "Enchanted minion's activated ability costs 2 more"})
    },
    {"Silence",
      make_shared<Enchantment>("Silence", CardType::ENCHANTMENT, 1, 
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE, 
      StatusChangeEffect{MinionStatus::SILENCED}, "Enchanted minion cannot use abilities"})
    },
    {"Magic Enhance",
      make_shared<Enchantment>("Magic Enhance", CardType::ENCHANTMENT, 0,
      Ability{AbilityType::ACTIVE, Condition::NONE, Target::SINGLE,
      AbilityCostModifyEffect{-1}, "Enchanted minion's activated ability costs 1 less"})
    }
  };

  ritualLibrary = {
    {"Dark Ritual",
      make_shared<Ritual>("Dark Ritual", CardType::RITUAL, 0, 
      Ability{AbilityType::PASSIVE, Condition::ON_TURN_BEGIN, Target::PLAYER, 
      MagicModifyEffect{1}, "At the start of your turn, gain 1 magic"}, 5, 1)
    },
    {"Aura of Power",
      make_shared<Ritual>("Aura of Power", CardType::RITUAL, 1, 
      Ability{AbilityType::PASSIVE, Condition::ON_MINION_ENTER, Target::SINGLE,
      StatModifyEffect{Modify::ADD, 1, Modify::ADD, 1}, "Whenever a minion enters play under your control, it gains +1/+1"}, 4, 1)
    },
    {"Standstill",
      make_shared<Ritual>("Standstill", CardType::RITUAL, 3, 
      Ability{AbilityType::PASSIVE, Condition::ON_MINION_ENTER, Target::SINGLE,
      MoveEffect{Location::GRAVEYARD, PlayerSide::BOTH}, "Whenever a minion enters play, destroy it"}, 4, 2)
    },
    {"Aura of Poison",
      make_shared<Ritual>("Aura of Poison", CardType::RITUAL, 2,
      Ability{AbilityType::PASSIVE, Condition::ON_TURN_BEGIN, Target::BOTH_FIELDS,
      StatModifyEffect{Modify::ADD, 0, Modify::SUBTRACT, 1}, "At the start of your turn, damage all minion on the field by 1"}, 5, 1)
    }
  };
}

void removeLibrary() {
//   // for (const auto& entry : minionLibrary) {
//   //   delete entry.second;
//   // }
//   for (const auto& entry : spellLibrary) {
//     delete entry.second;
//   }
//   for (const auto& entry : enchantmentLibrary) {
//     delete entry.second;
//   }
//   for (const auto& entry : ritualLibrary) {
//     delete entry.second;
//   }
}
