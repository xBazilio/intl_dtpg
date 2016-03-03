<?php

foreach (['ru_RU', 'en_US', 'fr_FR', 'zh_CN', 'fa_IR'] as $locale) {
    echo $locale, PHP_EOL;

    $dtpg = new IntlDateTimePatternGenerator($locale);

    foreach (['MMMMd', 'MMMdHHmm', 'YYMMM', 'eeeeMMMMdH'] as $skeleton) {
        $pattern = $dtpg->findBestPattern($skeleton);
        $formatted = (new IntlDateFormatter($locale, 0, 0, null, null, $pattern))->format(1455111783);
        printf("  %s: %s => %s\n", $skeleton, $pattern, $formatted);
    }
}

/*
ru_RU
  MMMMd: d MMMM => 10 февраля
  MMMdHHmm: d MMM, H:mm => 10 февр., 17:43
  YYMMM: LLL YY => Февр. 16
  eeeeMMMMdH: cccc, d MMMM, H => Среда, 10 февраля, 17
en_US
  MMMMd: MMMM d => February 10
  MMMdHHmm: MMM d, HH:mm => Feb 10, 17:43
  YYMMM: MMM YY => Feb 16
  eeeeMMMMdH: EEEE, MMMM d, HH => Wednesday, February 10, 17
fr_FR
  MMMMd: d MMMM => 10 février
  MMMdHHmm: d MMM HH:mm => 10 févr. 17:43
  YYMMM: MMM YY => févr. 16
  eeeeMMMMdH: EEEE d MMMM HH 'h' => mercredi 10 février 17 h
zh_CN
  MMMMd: M月d日 => 2月10日
  MMMdHHmm: M月d日 HH:mm => 2月10日 17:43
  YYMMM: YY年M月 => 16年2月
  eeeeMMMMdH: M月d日EEEE H时 => 2月10日星期三 17时
fa_IR
  MMMMd: d LLLL => ۱۰ فوریه
  MMMdHHmm: d LLL،‏ H:mm => ۱۰ فوریه،‏ ۱۷:۴۳
  YYMMM: MMM YY G => فوریهٔ ۱۶ م.
  eeeeMMMMdH: EEEE d LLLL،‏ H => چهارشنبه ۱۰ فوریه،‏ ۱۷
*/
