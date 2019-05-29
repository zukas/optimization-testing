#ifndef CONCEPT_IDIOMS_H
#define CONCEPT_IDIOMS_H

#include <memory>
#include <type_traits>
#include <vector>

template <typename __T> void execute(const __T &t) noexcept;

class concept_obj_t {
public:
  template <typename __T>
  concept_obj_t(__T val)
      : value(std::make_unique<model_t<__T>>(std::move(val))) {}
  concept_obj_t(concept_obj_t &&) noexcept = default;
  concept_obj_t(const concept_obj_t &other) : value(other.value->make_copy()) {}
  friend void execute(const concept_obj_t &t) noexcept { t.value->execute(); }

private:
  struct concept_t {
    virtual ~concept_t();
    virtual void execute() const noexcept = 0;
    virtual std::unique_ptr<concept_t> make_copy() const = 0;
  };
  template <typename __T> struct model_t final : concept_t {
    model_t(__T val) noexcept : value(std::move(val)) {}
    virtual void execute() const noexcept override { ::execute(value); }
    virtual std::unique_ptr<concept_t> make_copy() const override {
      return std::make_unique<model_t>(value);
    }
    __T value;
  };
  std::unique_ptr<concept_t> value;
};

typedef std::vector<concept_obj_t> concept_container_t;

template <>
void execute<concept_container_t>(
    const concept_container_t &container) noexcept;

#endif // CONCEPT_IDIOMS_H
