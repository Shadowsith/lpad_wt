#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <memory>
#include <Wt/WWebWidget.h>

namespace Pad {

class WidgetFacory {
public:
    std::unique_ptr<Wt::WContainerWidget> createContainer(const std::string tag, 
            const std::string cl = "", const std::string id = "") {
        auto w = std::make_unique<Wt::WContainerWidget>();
        setAttr(w.get(), tag, cl , id);
        return w;
    }

    std::unique_ptr<Wt::WText> createText(const std::string tag, 
            const std::string cl = "", const std::string id = "") {
        auto w = std::make_unique<Wt::WText>();
        setAttr(w.get(), tag, cl , id);
        return w;
    }

private:
    void setAttr(Wt::WWebWidget* ptr, const std::string &tag, const std::string &cl, const std::string &id) {
        ptr->setHtmlTagName(tag);
        if (cl != "") ptr->setStyleClass(cl);
        if (id != "") ptr->setId(id);
    }
};

}

#endif


