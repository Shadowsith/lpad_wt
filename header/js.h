#ifndef JS_H
#define JS_H

#include <string>
#include <Wt/WString.h>

namespace Pad {

// js function provider
class EScript {
public:
    std::string alertBla() {
        std::string code = 
            build("alert('bla');");
        return code;
    }

    std::string announce(std::string msg, std::string option) {
        std::string code = "";
        if(option == "info" || option == "danger" || option == "success" 
            || option == "warning") {
            code = build("$.announce." + option + "('" + msg + "');");
        }
        return code;
    }

private:
    std::string build(std::string body, std::string name="") {
        std::string code = 
            "function " + name + " (object, event) { " + body + " }";
        return code;
    }
};

}

#endif // JS_H
