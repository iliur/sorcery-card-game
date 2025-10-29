#include "StatusChangeEffect.h"

using namespace std;

StatusChangeEffect::StatusChangeEffect(MinionStatus newStatus): newStatus{newStatus} {}

StatusChangeEffect::StatusChangeEffect(const StatusChangeEffect &other): newStatus{other.newStatus} {}

MinionStatus StatusChangeEffect::getNewStatus() { return newStatus; }
