#include <phpcpp.h>
#include "unicode/dtptngen.h"

using icu::UnicodeString;
using icu::Locale;
using icu::DateTimePatternGenerator;

using namespace std;

class IntlDateTimePatternGenerator : public Php::Base
{
private:
    DateTimePatternGenerator *dtpg;
    UErrorCode status = U_ZERO_ERROR;
public:
    IntlDateTimePatternGenerator() {}
    virtual ~IntlDateTimePatternGenerator() {
        if (dtpg != NULL) { delete dtpg; } 
    }

    /**
     * @internal for usage in function
     */
    void initIcuDtpg(const char* locale) {
        dtpg = DateTimePatternGenerator::createInstance(Locale(locale), status);
    }

    /**
     * php "constructor"
     * @param  params
     */
    void __construct(Php::Parameters &params)
    {
        initIcuDtpg(params[0]);
    }

    /**
     * @internal for usage in function
     */
    string findBestPattern(const char* skeleton) {
        UnicodeString pattern = dtpg->getBestPattern(skeleton, status);
        string s; 
        pattern.toUTF8String(s);
        return s;
    }

    /**
     *  Finds best pattern for given skeleton.
     *  @return string
     */
    Php::Value phpFindBestPattern(Php::Parameters &params) { 
        //const char* skeleton = params[0];
        return findBestPattern(params[0]);
    }
};

/**
 *  intl_dtpg_find_best_pattern()
 *  @return Php::Value
 */
Php::Value intl_dtpg_find_best_pattern(Php::Parameters &params)
{
    // const char* input_skeleton = params[1];

    //vector<string> constr_params (1, params[0]);
//    vector<const char*> call_params (1, params[1]);

    IntlDateTimePatternGenerator* dtpg = new IntlDateTimePatternGenerator();
    dtpg->initIcuDtpg(params[0]);
    string pattern = dtpg->findBestPattern(params[1]);
    delete dtpg;

    return pattern;
}

// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("intl_dtpg","0.1.0");
        
        // add function to extension
        extension.add("intl_dtpg_find_best_pattern", intl_dtpg_find_best_pattern, {
            Php::ByVal("locale", Php::Type::String),
            Php::ByVal("skeleton", Php::Type::String)
        });

        Php::Class<IntlDateTimePatternGenerator> intl_dtpg_class("IntlDateTimePatternGenerator");
        intl_dtpg_class.method("__construct", &IntlDateTimePatternGenerator::__construct, {
            Php::ByVal("locale", Php::Type::String)
        });
        intl_dtpg_class.method("findBestPattern", &IntlDateTimePatternGenerator::phpFindBestPattern, { 
            Php::ByVal("skeleton", Php::Type::String) 
        });        

        extension.add(std::move(intl_dtpg_class));
        // return the extension module
        return extension.module();
    }
}
