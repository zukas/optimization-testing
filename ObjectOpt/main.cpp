#include <math.h>
#include <random>

class Model;
class Object {
  float m_Pos[2];
  float m_Velocity[2];
  char m_Name[32];
  Model *m_Model;
  // ... other members ...
  float m_Foo;

public:
  void UpdateFoo(float f) {
    float mag =
        sqrtf(m_Velocity[0] * m_Velocity[0] + m_Velocity[1] * m_Velocity[1]);
    m_Foo += mag * f;
  }
};

int main() {

  Object o;
  o.UpdateFoo((float)rand() / 17.5f);
  return 0;
}
