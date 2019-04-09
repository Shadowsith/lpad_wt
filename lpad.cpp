#include <memory>
#include <Wt/WApplication.h>
#include <Wt/WWebWidget.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WLabel.h>
#include <Wt/WTemplate.h>
#include <Wt/WJavaScript.h>
#include <Wt/WMessageResourceBundle.h>
#include "./header/widgetFactory.h"
#include "./header/js.h"

namespace Pad {

class Lpad : public Wt::WApplication {
public:
    Lpad(const Wt::WEnvironment& env);
    void addLogin();
    void addRegister();
    void addPad();
    void registerLoginEvents();
    void pbLoginClicked();
    void handleInternalPath(const std::string &internalPath);

private:
    struct paths {
        std::string login = "login";
        std::string signup = "register";
        std::string pad = "pad";
    } _path;

    std::unique_ptr<WidgetFacory> _wfa;

    // Global used
    Wt::WContainerWidget *_cw;
    Wt::WContainerWidget *_test;
    Wt::WText *_headline;

    // Login + Register
    Wt::WTemplate *_form1;
    Wt::WContainerWidget *_fgUser;
    Wt::WContainerWidget *_fgPwd;
    Wt::WAnchor *_aRegLogin;
    Wt::WLabel *_lblUser;
    Wt::WLabel *_lblPwd; 
    Wt::WLineEdit *_leUser;
    Wt::WLineEdit *_lePwd;
    Wt::WPushButton *_pbLogReg;

    // Register
    Wt::WContainerWidget *_fgEmailRegister;
    Wt::WContainerWidget *_fgPwd2Register;
    Wt::WLabel *_lblEmailRegister;
    Wt::WLabel *_lblPwd2Register;
    Wt::WLineEdit *_leEmailRegister;
    Wt::WLineEdit *_lePwd2Register;

    // Main site
    Wt::WTemplate *_nav;
    Wt::WContainerWidget *_navCon;
    Wt::WContainerWidget *_menu;
    Wt::WAnchor *_padName;
    Wt::WContainerWidget *_navSide;
    Wt::WContainerWidget *_navCollapse;

    // JavaScript
    Wt::JSlot _slot;
    EScript _es;
};

Lpad::Lpad(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    _wfa = std::make_unique<WidgetFacory>();

    messageResourceBundle().use(appRoot() + "i18n/general");
    useStyleSheet("./lib/bootstrap/css/bootstrap.min.css");
    useStyleSheet("./lib/jquery-announce/jquery.announce.css");
    requireJQuery("./lib/jquery/jquery-3.3.1.min.js");
    requireJQuery("./lib/jquery-announce/jquery.announce.min.js");
    handleInternalPath(internalPath());
}

void Lpad::addLogin() {
    _cw = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    _cw->addStyleClass("container form-signin border mt-5 pl-5 pr-5");

    _test = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    _test->setHtmlTagName("form");

    _headline = _cw->addWidget(_wfa->createText("h3", "mb-3"));
    _headline->setText(Wt::WString::tr("headline-register"));

    _form1 = _cw->addWidget(std::make_unique<Wt::WTemplate>());
    _form1->setTemplateText("<form class=\"form-signin\">${fg1} ${fg2}</form>");

    _fgUser = _form1->bindWidget("fg1", std::make_unique<Wt::WContainerWidget>());
    _fgUser->addStyleClass("form-group");
    _lblUser = _fgUser->addWidget(std::make_unique<Wt::WLabel>());
    _lblUser->setText(Wt::WString::tr("username")+":");

    _leUser = _fgUser->addWidget(std::make_unique<Wt::WLineEdit>());
    _leUser->addStyleClass("form-control");

    _fgPwd = _form1->bindWidget("fg2", std::make_unique<Wt::WContainerWidget>());
    _fgPwd->addStyleClass("form-group");

    _lblPwd = _fgPwd->addWidget(std::make_unique<Wt::WLabel>());
    _lblPwd->setText(Wt::WString::tr("password")+":");

    _lePwd = _fgPwd->addWidget(std::make_unique<Wt::WLineEdit>());
    _lePwd->addStyleClass("form-control");

    _pbLogReg = _cw->addWidget(std::make_unique<Wt::WPushButton>());
    _pbLogReg->setText(Wt::WString::tr("login"));
    _pbLogReg->addStyleClass("btn btn-lg btn-primary btn-block mb-5");
    
    _aRegLogin = _cw->addWidget(std::make_unique<Wt::WAnchor>());
    _aRegLogin->setText(Wt::WString::tr("goto-register"));
    _aRegLogin->setLink("/?_=" + _path.signup);
    _aRegLogin->addStyleClass("center-block");
}

void Lpad::addRegister() {
    _cw = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    _cw->addStyleClass("container form-signin border mt-5 pl-5 pr-5");

    _headline = _cw->addWidget(_wfa->createText("h3", "mb-3"));
    _headline->setText(Wt::WString::tr("headline-register"));

    _form1 = _cw->addWidget(std::make_unique<Wt::WTemplate>());
    _form1->setTemplateText("<form>${fg1} ${fg2} ${fg3} ${fg4}</form>");

    _fgUser = _form1->bindWidget("fg1", std::make_unique<Wt::WContainerWidget>());
    _fgUser->addStyleClass("form-group");
    _lblUser = _fgUser->addWidget(std::make_unique<Wt::WLabel>());
    _lblUser->setText(Wt::WString::tr("username")+":");

    _leUser = _fgUser->addWidget(std::make_unique<Wt::WLineEdit>());
    _leUser->addStyleClass("form-control");

    _fgEmailRegister = _form1->bindWidget("fg2", std::make_unique<Wt::WContainerWidget>());
    _fgEmailRegister->addStyleClass("form-group");
    _lblEmailRegister = _fgEmailRegister->addWidget(std::make_unique<Wt::WLabel>());
    _lblEmailRegister->setText(Wt::WString::tr("email")+":");

    _leEmailRegister = _fgEmailRegister->addWidget(std::make_unique<Wt::WLineEdit>());
    _leEmailRegister->addStyleClass("form-control");

    _fgPwd = _form1->bindWidget("fg3", std::make_unique<Wt::WContainerWidget>());
    _fgPwd->addStyleClass("form-group");
    _lblPwd = _fgPwd->addWidget(std::make_unique<Wt::WLabel>());
    _lblPwd->setText(Wt::WString::tr("password")+":");

    _lePwd = _fgPwd->addWidget(std::make_unique<Wt::WLineEdit>());
    _lePwd->addStyleClass("form-control");

    _fgPwd2Register = _form1->bindWidget("fg4", std::make_unique<Wt::WContainerWidget>());
    _fgPwd2Register->addStyleClass("form-group");
    _lblPwd2Register = _fgPwd2Register->addWidget(std::make_unique<Wt::WLabel>());
    _lblPwd2Register->setText(Wt::WString::tr("repeat-password")+":");

    _lePwd2Register = _fgPwd2Register->addWidget(std::make_unique<Wt::WLineEdit>());
    _lePwd2Register->addStyleClass("form-control");
    
    _pbLogReg = _cw->addWidget(std::make_unique<Wt::WPushButton>());
    _pbLogReg->setText(Wt::WString::tr("register"));
    _pbLogReg->addStyleClass("btn btn-lg btn-success btn-block mb-5");

    _aRegLogin = _cw->addWidget(std::make_unique<Wt::WAnchor>());
    _aRegLogin->setText(Wt::WString::tr("goto-login"));
    _aRegLogin->setLink("/?_=" + _path.login);
    _aRegLogin->addStyleClass("center-block");
}

void Lpad::addPad() {
    _nav = root()->addWidget(std::make_unique<Wt::WTemplate>
        ("<nav class=\"navbar navbar-expand-lg navbar-dark\""
        "style=\"background-color: #810541;\">"
        "${navcon}</nav>"));

    _navCon = _nav->bindWidget("navcon", std::make_unique<Wt::WContainerWidget>());
    _navCon->setStyleClass("container-fluid");

    _padName = _navCon->addWidget(std::make_unique<Wt::WAnchor>());
    _padName->setStyleClass("navbar-brand");
    _padName->setText(Wt::WString::tr("padname"));

    _navSide = _navCon->addWidget(std::make_unique<Wt::WContainerWidget>());
    _navSide->setStyleClass("sidenav");

    _navCollapse = _navCon->addWidget(std::make_unique<Wt::WContainerWidget>());
    _navCollapse->setStyleClass("collapse navbar-collapse");

    _menu = _navCollapse->addWidget(std::make_unique<Wt::WContainerWidget>());
    _menu->setList(true);
    _menu->setStyleClass("navbar-nav mr-auto");
    auto _itm1 = _menu->addWidget(std::make_unique<Wt::WText>("intro"));
    _itm1->setStyleClass("nav-item");
    auto _itm2 = _menu->addWidget(std::make_unique<Wt::WText>("Not yet available"));
    _itm2->setStyleClass("nav-item");

    _cw = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    _cw->setStyleClass("container-fluid");
}

void Lpad::registerLoginEvents() {
    pbLoginClicked();
}

void Lpad::pbLoginClicked() {
    _pbLogReg->clicked().connect([=] {
        Wt::WString usr = _leUser->text();
        Wt::WString pwd = _lePwd->text();
        if(usr != "" || pwd != "") {
            _slot.setJavaScript(_es.announce(usr.toUTF8() + " " + pwd.toUTF8(), "success"));
            _slot.exec();
        } else {
            _slot.setJavaScript(_es.announce(Wt::WString::tr("no-usr-pwd").toUTF8(), "warning"));
            _slot.exec();
        }
    });
}

void Lpad::handleInternalPath(const std::string &internalPath) {
    if(internalPath == "/" + _path.signup) {
        setTitle("Sign up to Lpad");
        addRegister();
    } else if(internalPath == "/" + _path.pad) {
        setTitle("Lpad");
        addPad();
    } else {
        setTitle("Login to Lpad");
        addLogin();
        registerLoginEvents();
    }
}

}

int main(int argc, char *argv[])
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<Pad::Lpad>(env);
    });
    return 0;
}

