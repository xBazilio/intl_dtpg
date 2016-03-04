# IntlDateTimePatternGenerator

This PHP extension introduces `IntlDateTimePatternGenerator` class — the missing part from PHP's `intl` extension. There is also a function `intl_dtpg_find_best_pattern` with same functionality.

## Motivation

The motivation is described in https://blog.ksimka.io/a-long-journey-to-formatting-a-date-without-a-year-internationally-with-php/#header .

Long story short: currently (with standard `intl`) there is no way to format a date internationally without a year field (like "February 10" or "10 февраля"). `IntlDateTimePatternGenerator` fixes this issue, see examples.

## Installation

+ [Install PHPCPP](http://www.php-cpp.com/documentation/install).
+ Install ICU
  `sudo apt-get install libicu-dev`
+ Build and install extension 
  `make && make clean && sudo make install`
+ Try it using example
  `php example.php`

## Examples

See [example.php](example.php).

```php
<?php

foreach (['ru_RU', 'en_US', 'fr_FR', 'zh_CN', 'fa_IR'] as $locale) {
    echo $locale, PHP_EOL;

    $dtpg = new IntlDateTimePatternGenerator($locale);

    foreach (['MMMMd', 'MMMdHHmm', 'YYMMM', 'eeeeMMMMdH'] as $skeleton) {
        $pattern = $dtpg->findBestPattern($skeleton);
        $formatted = (new IntlDateFormatter($locale, 0, 0, null, null, $pattern))->format(1455111783);
        printf("  %s%s%s\n", str_pad($skeleton, 12), str_pad($pattern, 20), str_pad($formatted, 32));
    }
}

/*
ru_RU
  MMMMd       d MMMM              10 февраля               
  MMMdHHmm    d MMM, H:mm         10 февр., 17:43             
  YYMMM       LLL YY              Февр. 16                    
  eeeeMMMMdH  cccc, d MMMM, H     Среда, 10 февраля, 17
en_US
  MMMMd       MMMM d              February 10                     
  MMMdHHmm    MMM d, HH:mm        Feb 10, 17:43                   
  YYMMM       MMM YY              Feb 16                          
  eeeeMMMMdH  EEEE, MMMM d, HH    Wednesday, February 10, 17      
fr_FR
  MMMMd       d MMMM              10 février                     
  MMMdHHmm    d MMM HH:mm         10 févr. 17:43                 
  YYMMM       MMM YY              févr. 16                       
  eeeeMMMMdH  EEEE d MMMM HH 'h'  mercredi 10 février 17 h       
zh_CN
  MMMMd       M月d日            2月10日                       
  MMMdHHmm    M月d日 HH:mm      2月10日 17:43                 
  YYMMM       YY年M月           16年2月                       
  eeeeMMMMdH  M月d日EEEE H时   2月10日星期三 17时        
fa_IR
  MMMMd       d LLLL              ۱۰ فوریه                 
  MMMdHHmm    d LLL،‏ H:mm     ۱۰ فوریه،‏ ۱۷:۴۳  
  YYMMM       MMM YY G            فوریهٔ ۱۶ م.           
  eeeeMMMMdH  EEEE d LLLL،‏ H  چهارشنبه ۱۰ فوریه،‏ ۱۷
*/
```

## Warning!

I'm neither C++ nor C developer. This extension was developed nearly randomly. So yes, it's as is so far. May be you'll not be able to build it. Any improvements are highly appreciated.

## TODO

+ PHP 7. AFAIK there is no PHP 7 support in PHPCPP currently.
+ port other useful methods from DTPG
