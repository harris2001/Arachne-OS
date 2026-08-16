#pragma once 

/**
 * With this templated check we can verify if two classes are of the same type
 */
template <typename T, typename U>
struct is_same {
  static constexpr bool value = false;
};

template <typename T>
struct is_same<T, T> {
  static constexpr bool value = true;
};

template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;


// Validation
static_assert(is_same_v<int,float> == false);
static_assert(is_same_v<int,int> == true);
