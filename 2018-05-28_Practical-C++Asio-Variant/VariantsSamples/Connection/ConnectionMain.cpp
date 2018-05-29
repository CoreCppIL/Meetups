#include "ConnectionClassic.h"
#include "ConnectionVariant.h"

template<typename Connection>
void alg() {
  Connection connection;
  connection.interrupt();
  connection.disconnect();
}

int main() {
  alg<classic::Connection>();
  alg<variant::Connection>();
}