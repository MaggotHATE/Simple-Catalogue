#include <cstdio>
#include <iostream>
#include <json/reader.h>
#include <json/value.h>
#include <string>

namespace validate {

    bool isEqualItem(const std::string& s1, const std::string& s2,
        const std::string& keysJson) {
        Json::Value v1, v2, keysValue;
        struct Spec {
            const std::string& s;
            Json::Value& v;
        };
        const Spec specs[] = { {s1, v1}, {s2, v2}, {keysJson, keysValue} };
        for (const auto& spec : specs) {
            JSONCPP_STRING errs;
            std::unique_ptr<Json::CharReader> reader(
                Json::CharReaderBuilder().newCharReader());
            bool ok = reader->parse(spec.s.data(),
                spec.s.data() + spec.s.size(),
                &spec.v, &errs);
            if (!ok) {
                std::cerr << "parse error in: \"" << spec.s << "\": " << errs << std::endl;
                return false;
            }
        };

        for (const std::string& member : keysValue.getMemberNames()) {
            // showing error in order!=root2.end error is cannot compare structures
            const Json::Value& m1 = v1[member];
            const Json::Value& m2 = v2[member];
            if (m1 != m2) {
                std::cerr << "mismatched member " << member << std::endl;
                return false;
            }
        }
        return true;
    }

} // namespace validate

int testJsont() {
    struct {
        int line;
        std::string a;
        std::string b;
        std::string keys;
        bool expected;
    } const testCases[] = {
        {__LINE__,
         R"({"id": 1, "name": "test", "randomNo": 1})",
         R"({"id": 1, "name": "test", "randomNo": 1})",
         R"({"id": null, "name": null, "randomNo": null})", true},
        {__LINE__,
         R"({"id": 1, "name": "test", "randomNo": 1})",
         R"({"id": 1, "name": "test", "randomNo": 2})",
         R"({"id": null, "name": null, "randomNo": null})", false},
        {__LINE__,
         R"({"id": 1, "name": "test", "randomNo": 1})",
         R"({"id": 1, "name": "test", "randomNo": 3})",
         R"({"id": null, "name": null})", true} };
    for (const auto& tc : testCases) {
        bool r = validate::isEqualItem(tc.a, tc.b, tc.keys);
        if (r != tc.expected) {
            fprintf(stderr, "assertion failed for line %d\n", tc.line);
            return 1;
        }
    }
    return 0;
}
