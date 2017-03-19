#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "intl_dtpg.h"
#include <unicode/ustdio.h>
#include <unicode/smpdtfmt.h>

zend_class_entry *IntlDateTimePatternGenerator_ce;
zend_object_handlers IntlDateTimePatternGenerator_object_handlers;

/* {{{ IntlDateTimePatternGenerator_objects_dtor */
static void IntlDateTimePatternGenerator_object_dtor(zend_object *object)
{
    zend_objects_destroy_object(object);
}
/* }}} */

/* {{{ IntlDateTimePatternGenerator_objects_free */
void IntlDateTimePatternGenerator_object_free(zend_object *object)
{
    IntlDateTimePatternGenerator_object *dtpgo = php_intl_datetimepatterngenerator_fetch_object(object);

    zend_object_std_dtor(&dtpgo->zo);

    dtpgo->status = U_ZERO_ERROR;
    if (dtpgo->dtpg) {
        delete dtpgo->dtpg;
        dtpgo->dtpg = nullptr;
    }
}
/* }}} */

/* {{{ IntlDateTimePatternGenerator_object_create */
zend_object *IntlDateTimePatternGenerator_object_create(zend_class_entry *ce)
{
    IntlDateTimePatternGenerator_object* intern;

    intern = (IntlDateTimePatternGenerator_object*)ecalloc(1,
                        sizeof(IntlDateTimePatternGenerator_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->zo, ce);
    object_properties_init(&intern->zo, ce);
    intern->dtpg = nullptr;
    intern->status = U_ZERO_ERROR;

    intern->zo.handlers = &IntlDateTimePatternGenerator_object_handlers;

    return &intern->zo;
}
/* }}} */

/* {{{ proto void IntlDateTimePatternGenerator::__construct(string $locale)
 * IntlDateTimePatternGenerator object constructor.
 */
PHP_METHOD(IntlDateTimePatternGenerator, __construct)
{
    zend_string *locale;
    zval *object;
    IntlDateTimePatternGenerator_object* dtpg = nullptr;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &locale) == FAILURE) {
        return;
    }

    object = getThis();

    dtpg = php_intl_datetimepatterngenerator_fetch_object(Z_OBJ_P(object));

    dtpg->status = U_ZERO_ERROR;
    dtpg->dtpg = DateTimePatternGenerator::createInstance(Locale(ZSTR_VAL(locale)), dtpg->status);
}
/* }}} */

/* {{{ proto string IntlDateTimePatternGenerator::findBestPattern(string $skeleton)
 * Return the best pattern matching the input skeleton.
 */
PHP_METHOD(IntlDateTimePatternGenerator, findBestPattern)
{
    zend_string *skeleton;
    zval *object;
    IntlDateTimePatternGenerator_object* dtpg = nullptr;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &skeleton) == FAILURE) {
        return;
    }

    object = getThis();
    dtpg = php_intl_datetimepatterngenerator_fetch_object(Z_OBJ_P(object));

    UnicodeString pattern = dtpg->dtpg->getBestPattern(UnicodeString(ZSTR_VAL(skeleton)), dtpg->status);

    std::string s;
    pattern.toUTF8String(s);
    RETURN_STRING(s.c_str());
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_findBestPattern, 0, 0, 1)
    ZEND_ARG_INFO(0, skeleton)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo___construct, 0, 0, 1)
    ZEND_ARG_INFO(0, locale)
ZEND_END_ARG_INFO()

const zend_function_entry IntlDateTimePatternGenerator_functions[] = {
    PHP_ME(IntlDateTimePatternGenerator, __construct, arginfo___construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(IntlDateTimePatternGenerator, findBestPattern, arginfo_findBestPattern, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(intl_dtpg)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "IntlDateTimePatternGenerator", IntlDateTimePatternGenerator_functions);
    ce.create_object = IntlDateTimePatternGenerator_object_create;
    IntlDateTimePatternGenerator_ce = zend_register_internal_class(&ce);

    memcpy(&IntlDateTimePatternGenerator_object_handlers, zend_get_std_object_handlers(),
        sizeof IntlDateTimePatternGenerator_object_handlers);
    IntlDateTimePatternGenerator_object_handlers.offset =
                    XtOffsetOf(IntlDateTimePatternGenerator_object, zo);
    IntlDateTimePatternGenerator_object_handlers.clone_obj = NULL; //no clone support
    IntlDateTimePatternGenerator_object_handlers.dtor_obj = IntlDateTimePatternGenerator_object_dtor;
    IntlDateTimePatternGenerator_object_handlers.free_obj = IntlDateTimePatternGenerator_object_free;

    if(!IntlDateTimePatternGenerator_ce) {
        zend_error(E_ERROR, "Failed to register IntlDateTimePatternGenerator class");
        return FAILURE;
    }

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(intl_dtpg)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(intl_dtpg)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "intl_dtpg support", "enabled");
    php_info_print_table_header(2, "intl_dtpg version", INTL_DTPG_VERSION);
    php_info_print_table_end();
}
/* }}} */

PHP_FUNCTION(findBestPattern) {
    zend_string *skeleton;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &skeleton) == FAILURE) {
        return;
    }
}

/* {{{ intl_dtpg_functions[]
 */
const zend_function_entry intl_dtpg_functions[] = {
    PHP_FE_END
};
/* }}} */

/* {{{ intl_dtpg_module_entry
 */
zend_module_entry intl_dtpg_module_entry = {
    STANDARD_MODULE_HEADER,
    "intl_dtpg",
    intl_dtpg_functions,
    PHP_MINIT(intl_dtpg),
    PHP_MSHUTDOWN(intl_dtpg),
    NULL,
    NULL,
    PHP_MINFO(intl_dtpg),
    INTL_DTPG_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */



#ifdef COMPILE_DL_INTL_DTPG
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(intl_dtpg)
#endif
