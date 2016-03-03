/**
 *  functionreturnvalue.cpp
 *  @author Jasper van Eck<jasper.vaneck@copernica.com>
 * 
 *  An example file to show the working of a function call with a return value.
 */

/**
 *  Libraries used.
 */
#include <phpcpp.h>
#include "unicode/dtptngen.h"

using icu::UnicodeString;
using icu::Locale;
using icu::DateTimePatternGenerator;

using namespace std;

string _intl_dtpg_find_best_pattern(Locale locale, UnicodeString skeleton) {
    UErrorCode status = U_ZERO_ERROR;
    
    DateTimePatternGenerator *dtpg = DateTimePatternGenerator::createInstance(locale, status);
    // use getBestPattern method to get the best pattern for the given skeleton
    UnicodeString pattern = dtpg->getBestPattern(skeleton, status);
    delete dtpg;

    string s;
    pattern.toUTF8String(s);

    return s;
}

/**
 *  intl_dtpg_find_best_pattern()
 *  @return Php::Value
 */
Php::Value intl_dtpg_find_best_pattern(Php::Parameters &params)
{
    const char* input_skeleton = params[1];

    return _intl_dtpg_find_best_pattern(Locale(params[0]), input_skeleton);
}

class IntlDateTimePatternGenerator : public Php::Base
{
private:
    /**
     *  @var Locale
     */
    Locale locale;

public:
    IntlDateTimePatternGenerator() {}
    virtual ~IntlDateTimePatternGenerator() {}

    /**
     * php "constructor"
     * @param  params
     */
    void __construct(Php::Parameters &params)
    {
        if (params.size() > 0) {
            locale = Locale(params[0]);
        }
    }

    /**
     *  Finds best pattern for given skeleton.
     *  @return string
     */
    Php::Value findBestPattern(Php::Parameters &params) { 
        const char* input_skeleton = params[0];

        return _intl_dtpg_find_best_pattern(locale, input_skeleton); 
    }
};

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
        intl_dtpg_class.method("findBestPattern", &IntlDateTimePatternGenerator::findBestPattern, { 
            Php::ByVal("skeleton", Php::Type::String) 
        });        

        extension.add(std::move(intl_dtpg_class));
        // return the extension module
        return extension.module();
    }
}
