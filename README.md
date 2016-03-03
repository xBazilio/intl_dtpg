# IntlDateTimePatternGenerator

IntlDateTimePatternGenerator — the missing part from PHP's `intl` extension.

## Motivation

The motivation is described in https://blog.ksimka.io/a-long-journey-to-formatting-a-date-without-a-year-internationally-with-php/#header .

## Installation

+ Install PHPCPP — http://www.php-cpp.com/documentation/install .
+ Install ICU
  `sudo apt-get install libicu-dev`
+ Build and install extension 
  `make && make clean && sudo make install`
+ Try it using example

## Examples

See [example.php](example.php).

## Warning!

I'm neither C++ nor C developer. This extension was developed nearly randomly. So yes, it's as is so far. May be you'll not be able to build it. Any improvements are highly appreciated.

## TODO

PHP 7. AFAIK there is no PHP 7 support in PHPCPP currently.
