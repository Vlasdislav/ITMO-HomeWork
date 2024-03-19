#include <cstring>
#include <string>
#include <limits>

class StringView {
    public:
        inline static const size_t npos = std::numeric_limits<size_t>::max();
        StringView();
        StringView(const char*, size_t);
        StringView(const char*);
        StringView(const std::string&);
        StringView(const StringView&);
        StringView& operator=(const StringView&);
        StringView& operator=(const char*);
        StringView& operator=(const std::string&);
        const char* data() const;
        size_t size() const;
        StringView substr(size_t, size_t=npos) const;
        const char& operator[](size_t) const;
        size_t find(const char) const;
        size_t find(const StringView) const;
        bool startsWith(StringView) const;
        bool startsWith(const char) const;
        bool endsWith(StringView) const;
        bool endsWith(const char) const;
        size_t findFirstOf(const StringView&, size_t=0) const;
        size_t findFirstOf(const char, size_t=0) const;
        size_t findFirstNotOf(StringView, size_t=0) const;
        size_t findFirstNotOf(const char, size_t=0) const;
        void removePrefix(size_t);
    private:
        char* str_;
        size_t size_;
};