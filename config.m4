PHP_ARG_ENABLE(intl-dtpg, whether to enable intl-dtpg support,
[  --enable-intl-dtpg           Enable intl-dtpg support])

if test "$PHP_INTL_DTPG" != "no"; then
  PHP_SETUP_ICU(INTL_DTPG_SHARED_LIBADD)
  PHP_SUBST(INTL_DTPG_SHARED_LIBADD)
  PHP_REQUIRE_CXX()

  PHP_NEW_EXTENSION(intl_dtpg, intl_dtpg.cpp, $ext_shared,,-std=c++0x $ICU_INCS -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1, cxx)
fi
