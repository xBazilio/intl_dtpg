#ifndef INTL_DTPG_H
#define INTL_DTPG_H

#include <zend_modules.h>
#include <zend_types.h>
#include <unicode/dtptngen.h>

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
}

extern zend_module_entry intl_dtpg_module_entry;
#define phpext_intl_dtpg_ptr &intl_dtpg_module_entry

#define INTL_DTPG_VERSION "1.0.0"

#ifdef ZTS
#include "TSRM.h"
#endif

typedef struct {
    DateTimePatternGenerator *dtpg;
    UErrorCode status;
    zend_object zo;
} IntlDateTimePatternGenerator_object;

static inline IntlDateTimePatternGenerator_object *php_intl_datetimepatterngenerator_fetch_object(zend_object *obj) {
    return (IntlDateTimePatternGenerator_object *)((char*)(obj) - XtOffsetOf(IntlDateTimePatternGenerator_object, zo));
}

#if defined(ZTS) && defined(COMPILE_DL_INTL_DTPG)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif /* INTL_DTPG_H */
