#include "overload.h"
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

namespace lvariant_examples {

#define lvariant struct
template <typename T> void inspect(T t) {}

lvariant user_information {
  std::string name;
  int id;
};

lvariant json_value {
  std::map<std::string, std::unique_ptr<json_value>> object;
  std::vector<std::unique_ptr<json_value>> array;
  std::string string;
  double number;
  bool boolean;
  std::monostate null;
};

namespace command {
namespace library_based {
struct set_score {
  std::size_t value;
};

struct fire_missile {};

struct fire_laser {
  unsigned intensity;
};

struct rotate {
  double amount;
};

struct command {
  std::variant<set_score, fire_missile, fire_laser, rotate> value;
};

std::ostream &operator<<(std::ostream &stream, const command &cmd) {
  std::visit(overload(
                 [&](const set_score &ss) {
                   stream << "Set the score to " << ss.value << ".\n";
                 },
                 [&](const fire_missile &) { stream << "Fire a missile.\n"; },
                 [&](const fire_laser &fl) {
                   stream << "Fire a laser with " << fl.intensity
                          << " intensity.\n";
                 },
                 [&](const rotate &r) {
                   stream << "Rotate by " << r.amount << " degrees.\n";
                 }),
             cmd.value);
  return stream;
}
} // namespace library_based

namespace language_based {

lvariant command {
  std::size_t set_score;
  std::monostate fire_missile;
  unsigned fire_laser;
  double rotate;
};

#if 0
std::ostream &operator<<(std::ostream &stream, const command &cmd) {
  return inspect(cmd) {
    set_score value => 
      stream << "Set the score to " << value << ".\n";
    fire_missile _ => 
      stream << "Fire a missile.\n";
    fire_laser intensity => 
      stream << "Fire a laser with " << intensity << " intensity.\n";
    rotate degrees => 
      stream << "Rotate by " << degrees << " degrees.\n";
  };
}
#endif

} // namespace language_based
} // namespace command

namespace enum_inspect {
enum color { red, yellow, green, blue };
using Vec3 = std::tuple<double, double, double>;

namespace before {
void foo() {
  color c;
  const Vec3 opengl_color = [&c] {
    switch (c) {
    case red:
      return Vec3(1.0, 0.0, 0.0);
      break;
    case yellow:
      return Vec3(1.0, 1.0, 0.0);
      break;
    case green:
      return Vec3(0.0, 1.0, 0.0);
      break;
    case blue:
      return Vec3(0.0, 0.0, 1.0);
      break;
    default:
      std::abort();
    }
  }();
}
} // namespace before
namespace after {
void foo() {
#if 0
  color c;
  const Vec3 opengl_color =
    inspect(c) {
      red => Vec3(1.0, 0.0, 0.0)
      yellow => Vec3(1.0, 1.0, 0.0)
      green => Vec3(0.0, 1.0, 0.0)
      blue => Vec3(0.0, 0.0, 1.0)
  };
#endif
}
} // namespace after
} // namespace enum_inspect

namespace struct_inspect {
struct player {
  std::string name;
  int hitpoints;
  int lives;
};

void gameOver();
void messageAlmostDead();

namespace before {
void takeDamage(player &p) {
  if (p.hitpoints == 0 && p.lives == 0)
    gameOver();
  else if (p.hitpoints == 0) {
    p.hitpoints = 10;
    p.lives--;
  } else if (p.hitpoints <= 3) {
    p.hitpoints--;
    messageAlmostDead();
  } else {
    p.hitpoints--;
  }
}
} // namespace before

namespace after {
#if 0
void takeDamage(player &p) {
  inspect(p) {
    {hitpoints : 0, lives : 0}    => gameOver();
    {hitpoints:hp @0, lives : l}  => hp = 10, l--;
    {hitpoints:hp} if (hp <= 3)   => { hp--; messageAlmostDead(); }
    {hitpoints : hp} => hp--;
  }
}
#endif
}
} // namespace struct_inspect
}