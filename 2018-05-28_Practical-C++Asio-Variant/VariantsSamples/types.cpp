#include <tuple>
#include <cstdint>
#include <optional>
#include <variant>

// clang-format off
namespace level1 {
  bool;
  char;
  void;
  namespace empty {
    struct Foo {};
  }
  enum FireSwampDangers : int8_t {
    FLAME_SPURTS,
    LIGHTNING_SAND,
    ROUSES
  };
  namespace templated {
    template <typename T>
    struct Foo {
      T m_t;
    };
  }
}
namespace type_equivalence {
  bool;

  enum class InatorButtons {
    ON_OFF,
    SELF_DESTRUCT
  };
}

namespace level2 {
  std::pair<char, bool>;

  namespace non_templated {
    struct Foo {
      char a;
      bool b;
    };
  }

  std::tuple<bool, bool, bool>;

  namespace templated {
    template <typename T, typename U>
    struct Foo {
      T m_t;
      U m_u;
    };
  }
}

namespace level3 {
  std::optional<char>;

  std::variant<char, bool>;  template <typename T, typename U>
  struct Foo {
    std::variant<T, U> m_v;
  };
}

namespace level4 {
  namespace first {
    bool f(bool);    bool f1(bool b) { return b; }
    bool f2(bool) { return true; }
    bool f3(bool) { return false; }
    bool f4(bool b) { return !b; }  }  namespace second {    char f(bool);  }  namespace third {    enum class Foo
    {
      BAR,
      BAZ,
      QUUX
    };
    char f(Foo);  }  namespace fourth {    template <class T, class U>
    U f(T);  }}

// clang-format on