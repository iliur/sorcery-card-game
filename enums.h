#ifndef _ENUMS_H_
#define _ENUMS_H_

enum class AbilityType {NONE, ACTIVE, PASSIVE};
enum class CardType{ MINION, SPELL, ENCHANTMENT, RITUAL};
enum class Location { DECK, HAND, GRAVEYARD, FIELD, RITUAL };
enum class Condition {NONE, ON_MINION_LEAVE, ON_MINION_ENTER, ON_TURN_END, ON_TURN_BEGIN};
enum class Target {NONE, BOTH_FIELDS, ALLY_FIELD, ENEMY_FIELD, RITUAL, ENEMY_RITUAL, PLAYER, ENEMY, SUMMON, SINGLE, SELF};
enum class Modify {ADD, SUBTRACT, MULTIPLY, DIVIDE};
enum class PlayerSide {MINE, THEIRS, BOTH};
enum class MinionStatus {NONE, SILENCED};

#endif
