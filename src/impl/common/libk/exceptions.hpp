#pragma once

namespace std
{
class exception
{
public:
    virtual const char* what() const noexcept = 0;
};

class invalid_argument : public exception
{
public:
    explicit invalid_argument(const char* msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_; }

private:
    const char* msg_;
};

class out_of_range : public exception
{
public:
    explicit out_of_range(const char* msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_; }

private:
    const char* msg_;
};

class logic_error : public exception
{
public:
    explicit logic_error(const char* msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_; }

private:
    const char* msg_;
};

}  // namespace std
